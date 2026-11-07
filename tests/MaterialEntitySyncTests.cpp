#include <algorithm>
#include <array>
#include <climits>
#include <cstring>
#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>

#include <easylogging++.h>
#include <metamod/api.h>
#include <metamod/engine.h>
#include <metamod/engine_hooks.h>
#include <metamod/gamedll_hooks.h>

#include "fakes/RehldsServer.h"
#include "services/ncl_entities/MaterialEntitySync.h"
#include "utils/msg_ex.h"
#include "natives/material.cpp"

INITIALIZE_EASYLOGGINGPP

ServerEventsManager::ServerEventsManager() = default;
ServerEventsManager::~ServerEventsManager() = default;
sigslot::signal<ClientConnectingEvent>& ServerEventsManager::on_client_connecting() noexcept
{
    return client_connecting_;
}
sigslot::signal<ClientId>& ServerEventsManager::on_client_first_frame() noexcept
{
    return client_first_frame_;
}
sigslot::signal<ClientId>& ServerEventsManager::on_client_disconnected() noexcept
{
    return client_disconnected_;
}
sigslot::signal<ServerActivatedEvent>& ServerEventsManager::on_server_activated() noexcept
{
    return server_activated_;
}
sigslot::signal<>& ServerEventsManager::on_frame() noexcept
{
    return frame_;
}

namespace
{
    struct Message
    {
        int id{};
        cssdk::MessageType type{};
        cssdk::Edict* recipient{};
        std::vector<uint8_t> bytes;
    };

    std::vector<Message> g_Messages;
    std::map<std::string, int> g_MessageIds;
    MaterialEntitySync* g_Materials{};
    std::array<bool, 16> g_Visible{};

    void Require(bool condition, const char* description)
    {
        if (!condition)
        {
            throw std::runtime_error(description);
        }
    }

    class ClientInfo : public INextClientInfo
    {
    public:
        struct State
        {
            bool known = true;
            bool ready = true;
            NextClientVersion version{2, 6, 0};
        };

        std::array<State, 16> clients{};

        bool GetNextClientVersion(ClientId client, NextClientVersion& version) override
        {
            version = clients.at(client).version;
            return clients.at(client).known;
        }
        bool IsClientReady(ClientId client) override
        {
            return clients.at(client).ready;
        }
        int GetSupportedFeatures(ClientId) override
        {
            return 0;
        }
    };

    using IdPairs = std::vector<std::pair<uint16_t, uint16_t>>;

    uint32_t Bits(float value)
    {
        uint32_t result;
        std::memcpy(&result, &value, sizeof(result));
        return result;
    }

    struct MaterialState
    {
        uint32_t entity_index{};
        IdPairs bindings;
        std::map<uint16_t, uint32_t> params;
    };

    struct RecipientState
    {
        std::map<uint16_t, std::string> strings;
        std::map<uint16_t, MaterialState> entities;
    };

    struct TransportDecoder
    {
        std::map<int, RecipientState> clients;

        void Read()
        {
            for (const Message& message : g_Messages)
            {
                Require(message.type == cssdk::MessageType::One, "every message uses reliable per-client delivery");
                Require(message.recipient != nullptr, "every message retains its recipient");
                const int client = core::type_conversion::IndexOfEntity(message.recipient);
                Require(client > 0 && client <= cssdk::g_global_vars->max_clients, "message has a valid client recipient");
                Require(message.bytes.size() <= 192, "transport payload stays within the engine limit");
                RecipientState& state = clients[client];
                size_t offset = 0;
                const auto word = [&](size_t count) {
                    Require(offset + count <= message.bytes.size(), "complete transport decode");
                    uint32_t value = 0;
                    for (size_t byte = 0; byte < count; ++byte)
                    {
                        value |= static_cast<uint32_t>(message.bytes[offset++]) << (byte * 8);
                    }
                    return value;
                };
                const auto registered = [&](uint16_t id) {
                    Require(state.strings.count(id) != 0, "string registered before reference for this recipient");
                };

                if (message.id == g_MessageIds.at("ncl_str_reg"))
                {
                    const uint16_t id = static_cast<uint16_t>(word(2));
                    std::string text;
                    while (const uint8_t byte = static_cast<uint8_t>(word(1)))
                    {
                        text.push_back(static_cast<char>(byte));
                    }
                    Require(state.strings.emplace(id, text).second, "registration occurs once per connected recipient");
                }
                else
                {
                    Require(word(1) == static_cast<uint8_t>(ncl_entity::EntityTypeId::Material), "transport material type");
                    const uint16_t id = static_cast<uint16_t>(word(2));
                    if (message.id == g_MessageIds.at("nsync_destroy"))
                    {
                        Require(state.entities.erase(id) == 1, "destroy addresses a previously announced entity");
                    }
                    else
                    {
                        const bool create = message.id == g_MessageIds.at("nsync_create");
                        Require(create || message.id == g_MessageIds.at("nsync_update"), "known entity message");
                        if (create)
                        {
                            Require(state.entities.emplace(id, MaterialState{}).second, "create occurs once before destroy");
                        }
                        Require(state.entities.count(id) != 0, "update follows create for this recipient");
                        MaterialState& entity = state.entities.at(id);
                        const uint16_t mask = create ? 7 : static_cast<uint16_t>(word(2));
                        Require((mask & ~7) == 0, "known material fields");
                        if (mask & 1)
                        {
                            entity.entity_index = word(4);
                        }
                        for (uint16_t bit : {2, 4})
                        {
                            if (!(mask & bit))
                            {
                                continue;
                            }
                            const uint32_t added = word(1);
                            if (added == 255)
                            {
                                Require(!create, "collection clear is an update");
                                if (bit == 2)
                                {
                                    entity.bindings.clear();
                                }
                                else
                                {
                                    entity.params.clear();
                                }
                                continue;
                            }
                            for (uint32_t i = 0; i < added; ++i)
                            {
                                const uint16_t key = static_cast<uint16_t>(word(2));
                                const uint32_t value = word(bit == 2 ? 2 : 4);
                                registered(key);
                                if (bit == 2)
                                {
                                    registered(static_cast<uint16_t>(value));
                                    const std::pair<uint16_t, uint16_t> pair{key, static_cast<uint16_t>(value)};
                                    if (std::find(entity.bindings.begin(), entity.bindings.end(), pair) == entity.bindings.end())
                                    {
                                        entity.bindings.push_back(pair);
                                    }
                                }
                                else
                                {
                                    entity.params[key] = value;
                                }
                            }
                            const uint32_t removed = word(1);
                            for (uint32_t i = 0; i < removed; ++i)
                            {
                                const uint16_t key = static_cast<uint16_t>(word(2));
                                registered(key);
                                if (bit == 2)
                                {
                                    const std::pair<uint16_t, uint16_t> pair{key, static_cast<uint16_t>(word(2))};
                                    registered(pair.second);
                                    entity.bindings.erase(
                                        std::remove(entity.bindings.begin(), entity.bindings.end(), pair), entity.bindings.end()
                                    );
                                }
                                else
                                {
                                    entity.params.erase(key);
                                }
                            }
                        }
                    }
                }
                Require(offset == message.bytes.size(), "transport decodes every payload byte");
            }
            g_Messages.clear();
        }
    };

    struct Fixture
    {
        std::array<cssdk::Edict, 16> edicts{};
        cssdk::GlobalVars globals{};
        metamod::Globals meta_globals{};
        server_test::FakeIReHldsServerStatic server_static;
        server_test::FakeIReHldsServerData server_data;
        ServerEventsManager events;
        ClientInfo client;
        StringRegistry strings{events};
        EntitySync sync{events, strings, client};
        MaterialEntitySync materials{events, strings, sync, client};

        explicit Fixture(int max_clients = 1, bool first_frame = true)
        {
            g_Messages.clear();
            g_MessageIds.clear();
            globals.max_clients = max_clients;
            server_static.max_clients = max_clients;
            g_Visible.fill(true);
            globals.max_entities = 8;
            cssdk::g_global_vars = &globals;
            metamod::g_globals = &meta_globals;
            core::type_conversion::detail::first_edict = edicts.data();
            core::rehlds_api::detail::rehlds_server_static = &server_static;
            core::rehlds_api::detail::rehlds_server_data = &server_data;
            g_Materials = &materials;
            cssdk::g_engine_funcs.set_fat_pas = [](cssdk::Vector&) -> unsigned char* {
                static unsigned char visible{};
                return &visible;
            };
            cssdk::g_engine_funcs.set_fat_pvs = cssdk::g_engine_funcs.set_fat_pas;
            cssdk::g_engine_funcs.check_visibility = [](cssdk::Edict* edict, unsigned char*) {
                return g_Visible.at(core::type_conversion::IndexOfEntity(edict)) ? 1 : 0;
            };
            events.on_server_activated()(ServerActivatedEvent{edicts.data(), 8, max_clients});
            for (int id = 1; id <= max_clients; ++id)
            {
                events.on_client_connecting()(ClientConnectingEvent{id, "client", "local"});
                if (first_frame)
                {
                    events.on_client_first_frame()(id);
                }
            }
        }

        void Frame()
        {
            server_data.time += 1.0;
            events.on_frame()();
        }
    };

    void InvalidIndex()
    {
        Fixture fixture;
        for (int index : {-1, 0, 8, 9, INT_MAX})
        {
            Require(EntityOf(index) == nullptr, "material native must reject invalid index before conversion");
        }
        Require(EntityOf(7) == &fixture.edicts[7], "last valid edict index is accepted");
    }

    void RegistrationBoundary()
    {
        Fixture fixture;
        const uint16_t valid = fixture.strings.GetOrRegister(std::string(189, 'a'));
        Require(valid == 1, "189-byte string accepted");
        fixture.strings.EnsureSent(1, valid);
        Require(g_Messages.back().bytes.size() == 192, "registration exactly fills user message");
        Require(fixture.strings.GetOrRegister(std::string(190, 'b')) == 0, "190-byte string rejected");
        Require(fixture.strings.GetOrRegister("next") == 2, "rejection does not consume string id");
    }

    void BindingAdmission()
    {
        Fixture fixture;
        Require(!fixture.materials.Bind(&fixture.edicts[2], "preset", std::string(190, 'm')), "oversized material rejected");
        Require(!fixture.sync.Exists(1), "rejected material creates no entity");
        Require(fixture.strings.GetOrRegister("marker") == 1, "rejected material registers no preset");
        Require(!fixture.materials.Bind(&fixture.edicts[2], std::string(190, 'p'), "material"), "oversized preset rejected");
        Require(!fixture.materials.Bind(&fixture.edicts[2], "", "material"), "empty binding rejected before ownership");
        Require(!fixture.sync.Exists(1), "rejected preset creates no entity");
        Require(fixture.materials.Bind(&fixture.edicts[2], std::string(189, 'p'), std::string(189, 'm')), "boundary binding accepted");
        for (const Message& message : g_Messages)
        {
            Require(message.bytes.size() <= 192, "all binding registration messages fit");
        }
    }

    void ParameterAdmission()
    {
        Fixture fixture;
        Require(!fixture.materials.SetParam(&fixture.edicts[2], "", std::string(190, 'n'), 1.0f), "oversized global key rejected");
        Require(!fixture.sync.Exists(1), "rejected global key creates no entity");
        Require(
            !fixture.materials.SetParam(&fixture.edicts[2], std::string(100, 't'), std::string(89, 'n'), 1.0f),
            "oversized scoped key rejected"
        );
        Require(!fixture.sync.Exists(1), "rejected scoped key creates no entity");
        Require(fixture.strings.GetOrRegister("marker") == 1, "rejected keys consume no registrations");
        Require(
            fixture.materials.SetParam(&fixture.edicts[2], std::string(100, 't'), std::string(88, 'n'), 1.0f),
            "189-byte scoped key accepted"
        );
        for (const Message& message : g_Messages)
        {
            Require(message.bytes.size() <= 192, "all scoped registration messages fit");
        }
    }

    void SyncIdentity()
    {
        Fixture fixture;
        cssdk::Edict* entity = &fixture.edicts[2];
        const uint8_t type = static_cast<uint8_t>(ncl_entity::EntityTypeId::Material);
        const uint16_t first = fixture.sync.Create(type, entity, {}, ncl_entity::VisibilityReference::Broadcast());
        Require(
            fixture.sync.Create(type, entity, {}, ncl_entity::VisibilityReference::Broadcast()) == first, "same identity retains sync id"
        );
        ++entity->serial_number;
        const uint16_t second = fixture.sync.Create(type, entity, {}, ncl_entity::VisibilityReference::Broadcast());
        Require(second != 0 && second != first, "reused edict receives fresh sync id before frame");
        Require(!fixture.sync.Exists(first), "stale sync entity destroyed immediately");
        fixture.Frame();
        Require(fixture.sync.Exists(second), "replacement survives frame");
    }

    void Reuse(bool frame_before, bool bind_first)
    {
        Fixture fixture;
        cssdk::Edict* entity = &fixture.edicts[2];
        Require(fixture.materials.Bind(entity, "old-preset", "old-material"), "old binding accepted");
        Require(fixture.materials.SetParam(entity, "", "old-param", 4.0f), "old parameter accepted");
        Require(fixture.materials.SetThroughWalls(entity, true), "old visibility enabled");
        ++entity->serial_number;
        if (frame_before)
        {
            fixture.Frame();
        }
        g_Messages.clear();
        const bool accepted = bind_first ? fixture.materials.Bind(entity, "new-preset", "new-material")
                                         : fixture.materials.SetParam(entity, "", "new-param", 2.0f);
        Require(accepted, "replacement operation accepted");
        Require(!fixture.materials.SetThroughWalls(entity, true) || bind_first, "parameter-only replacement inherits no binding");
        fixture.Frame();
        Require(fixture.sync.Exists(2), "replacement has fresh live sync entity");
        fixture.events.on_client_disconnected()(1);
        g_Messages.clear();
        fixture.events.on_client_first_frame()(1);
        TransportDecoder decoder;
        decoder.Read();
        const MaterialState& snapshot = decoder.clients.at(1).entities.at(2);
        Require(snapshot.entity_index == 2, "replacement snapshot has the correct rendered entity");
        Require(
            snapshot.bindings == (bind_first ? IdPairs{{4, 5}} : IdPairs{}), "replacement snapshot contains exactly its own material pairs"
        );
        Require(
            snapshot.params == (bind_first ? std::map<uint16_t, uint32_t>{} : std::map<uint16_t, uint32_t>{{4, Bits(2.0f)}}),
            "replacement snapshot contains exactly its own parameters"
        );
    }

    void StaleUnbind()
    {
        Fixture fixture;
        cssdk::Edict* entity = &fixture.edicts[2];
        Require(fixture.materials.Bind(entity, "preset", "material"), "initial binding accepted");
        ++entity->serial_number;
        Require(!fixture.materials.Unbind(entity, "preset", "material"), "replacement cannot unbind the previous identity");
        Require(!fixture.materials.SetThroughWalls(entity, true), "replacement cannot enable previous binding visibility");
    }

    void UnbindAdmission()
    {
        Fixture fixture;
        Require(fixture.materials.Bind(&fixture.edicts[2], "preset", "material"), "initial binding accepted");
        Require(!fixture.materials.Unbind(&fixture.edicts[2], "unknown", std::string(190, 'm')), "oversized unbind rejected");
        Require(fixture.strings.GetOrRegister("marker") == 3, "rejected unbind registers neither argument");
    }
    enum class OwnershipAction
    {
        Bind,
        Param,
        Clear,
        Unbind,
        EnableVisibility,
        DisableVisibility,
        RefreshVisibility
    };

    void RecycledId(bool new_serial, OwnershipAction action, bool other_type = false)
    {
        Fixture fixture;
        cssdk::Edict* source = &fixture.edicts[2];
        Require(fixture.materials.Bind(source, "old-preset", "old-material"), "initial material entity uses id one");
        Require(fixture.materials.SetParam(source, "", "old-param", 1.0f), "initial material parameter accepted");
        Require(fixture.materials.SetThroughWalls(source, true), "initial material visibility enabled");
        fixture.events.on_client_disconnected()(1);

        if (new_serial)
        {
            ++source->serial_number;
            fixture.Frame();
        }
        else
        {
            fixture.sync.Destroy(1);
        }
        Require(!fixture.sync.Exists(1), "original sync id released");

        const uint8_t material_type = static_cast<uint8_t>(ncl_entity::EntityTypeId::Material);
        cssdk::Edict* foreign = &fixture.edicts[3];
        for (uint32_t expected = 2; expected <= 65535; ++expected)
        {
            const uint16_t id = fixture.sync.Create(material_type, foreign, {}, ncl_entity::VisibilityReference::Broadcast());
            Require(id == expected, "production id allocator reaches its wire limit");
            fixture.sync.Destroy(id);
        }

        uint8_t foreign_type = material_type;
        if (other_type)
        {
            ncl_entity::EntityTypeDescriptor descriptor;
            descriptor.type_id = 254;
            fixture.sync.RegisterType(descriptor);
            foreign_type = 254;
            foreign = source;
        }
        const uint16_t foreign_id = fixture.sync.Create(foreign_type, foreign, {}, ncl_entity::VisibilityReference::Broadcast());
        Require(foreign_id == 1, "wire id one reused by a different sync owner");
        g_Messages.clear();

        switch (action)
        {
            case OwnershipAction::Bind:
                Require(fixture.materials.Bind(source, "new-preset", "new-material"), "new binding accepted after id reuse");
                Require(fixture.sync.Exists(2), "binding recreates the material owner's record");
                break;
            case OwnershipAction::Param:
                Require(fixture.materials.SetParam(source, "", "new-param", 2.0f), "new parameter accepted after id reuse");
                Require(fixture.sync.Exists(2), "parameter recreates the material owner's record");
                break;
            case OwnershipAction::Clear:
                fixture.materials.Clear(source);
                break;
            case OwnershipAction::Unbind:
                Require(!fixture.materials.Unbind(source, "old-preset", "old-material"), "unbind rejects another owner's record");
                break;
            case OwnershipAction::EnableVisibility:
                Require(!fixture.materials.SetThroughWalls(source, true), "visibility enable rejects another owner's record");
                break;
            case OwnershipAction::DisableVisibility:
                Require(fixture.materials.SetThroughWalls(source, false), "local visibility disable accepted");
                cssdk::g_engine_funcs.check_visibility = [](cssdk::Edict*, unsigned char*) { return 0; };
                fixture.events.on_client_first_frame()(1);
                Require(
                    std::any_of(
                        g_Messages.begin(),
                        g_Messages.end(),
                        [](const Message& message) {
                            return message.id == g_MessageIds["nsync_create"] && message.bytes.size() >= 3 && message.bytes[1] == 1 &&
                                   message.bytes[2] == 0;
                        }
                    ),
                    "visibility disable preserves the foreign broadcast anchor"
                );
                break;
            case OwnershipAction::RefreshVisibility:
                {
                    metamod::gamedll::detail::dll_hooks->add_to_full_pack(nullptr, 2, source, &fixture.edicts[1], 0, 0, nullptr);
                    metamod::engine::detail::engine_hooks->check_visibility(source, nullptr);
                    const metamod::Result result = fixture.meta_globals.result;
                    metamod::gamedll::detail::dll_post_hooks->add_to_full_pack(nullptr, 2, source, &fixture.edicts[1], 0, 0, nullptr);
                    Require(result == metamod::Result::Ignored, "pack refresh revokes visibility without its material sync owner");
                    break;
                }
        }

        Require(fixture.sync.Exists(foreign_id), "material operation preserves the foreign sync entity");
    }
    void RepeatedPresetSnapshot()
    {
        Fixture fixture(2, false);
        cssdk::Edict* entity = &fixture.edicts[3];
        IdPairs expected;
        for (uint16_t i = 0; i < 96; ++i)
        {
            Require(fixture.materials.Bind(entity, "shared-preset", "material-" + std::to_string(i)), "repeated preset binding accepted");
            expected.emplace_back(1, i + 2);
        }
        Require(fixture.materials.SetParam(entity, "", "uWear", 0.1234567f), "fractional parameter accepted");
        Require(g_Messages.empty(), "no material packet precedes a recipient's first frame");
        fixture.events.on_client_first_frame()(1);
        Require(
            std::count_if(
                g_Messages.begin(), g_Messages.end(), [](const Message& message) { return message.id == g_MessageIds.at("nsync_update"); }
            ) >= 4,
            "large production snapshot spans multiple collection chunks"
        );
        TransportDecoder decoder;
        decoder.Read();
        const auto check = [&](int client) {
            const MaterialState& state = decoder.clients.at(client).entities.at(1);
            Require(
                state.entity_index == 3 && state.bindings == expected, "complete repeated-preset snapshot preserves every pair in order"
            );
            Require(state.params == std::map<uint16_t, uint32_t>{{98, Bits(0.1234567f)}}, "snapshot preserves exact parameter bits");
        };
        check(1);

        Require(fixture.materials.Unbind(entity, "shared-preset", "material-47"), "one repeated-preset material can be removed");
        expected.erase(expected.begin() + 47);
        decoder.Read();
        check(1);
        Require(
            fixture.materials.Bind(entity, "shared-preset", "replacement"), "full replacement adds another material from the same preset"
        );
        expected.emplace_back(1, 99);
        decoder.Read();
        check(1);
        fixture.events.on_client_first_frame()(2);
        decoder.Read();
        check(1);
        check(2);
        Require(
            decoder.clients.at(2).strings.size() == 98 && !decoder.clients.at(2).strings.count(49) &&
                decoder.clients.at(2).strings.at(99) == "replacement",
            "late join independently registers the current snapshot's strings"
        );
    }

    void RecipientRouting()
    {
        Fixture fixture(6, false);
        fixture.client.clients[3].ready = false;
        fixture.client.clients[4].version = NextClientVersion{2, 5, 0};
        fixture.client.clients[5].version = NextClientVersion{2, 4, 0};
        fixture.client.clients[6].known = false;
        g_Visible[2] = false;
        cssdk::Edict* entity = &fixture.edicts[7];
        Require(fixture.materials.Bind(entity, "preset", "first"), "first material accepted");
        Require(fixture.materials.Bind(entity, "preset", "second"), "second material accepted");
        Require(fixture.materials.SetParam(entity, "", "uWear", 0.5f), "initial parameter accepted");
        Require(g_Messages.empty(), "clients receive nothing before first frame");
        TransportDecoder decoder;
        for (int client = 1; client <= 6; ++client)
        {
            fixture.events.on_client_first_frame()(client);
        }
        decoder.Read();
        const auto check = [&](int client, uint32_t wear, bool extra) {
            const MaterialState& state = decoder.clients.at(client).entities.at(1);
            Require(
                state.entity_index == 7 && state.bindings == IdPairs{{1, 2}, {1, 3}}, "recipient reconstructs the complete material pairs"
            );
            std::map<uint16_t, uint32_t> expected{{4, wear}};
            if (extra)
            {
                expected.emplace(5, Bits(0.25f));
            }
            Require(state.params == expected, "recipient reconstructs all current parameters");
        };
        Require(decoder.clients.size() == 3, "only visible known clients at version 2.5 or newer receive entity packets");
        check(1, Bits(0.5f), false);
        check(3, Bits(0.5f), false);
        check(4, Bits(0.5f), false);
        Require(
            !decoder.clients.count(2) && !decoder.clients.count(5) && !decoder.clients.count(6),
            "invisible and incompatible recipients remain independent"
        );
        fixture.events.on_client_first_frame()(1);
        Require(g_Messages.empty(), "repeated first frame does not duplicate an announced create");

        g_Visible[2] = true;
        fixture.Frame();
        decoder.Read();
        check(2, Bits(0.5f), false);
        g_Visible[1] = false;
        fixture.Frame();
        Require(
            g_Messages.size() == 1 && g_Messages.front().recipient == &fixture.edicts[1] &&
                g_Messages.front().id == g_MessageIds.at("nsync_destroy"),
            "visibility exit destroys only the entity announced to the departing recipient"
        );
        decoder.Read();
        Require(decoder.clients.at(1).entities.empty(), "visibility exit removes recipient state");
        Require(fixture.materials.SetParam(entity, "", "uWear", 0.75f), "visible recipients get a parameter replacement");
        Require(fixture.materials.SetParam(entity, "", "extra", 0.25f), "new key registers independently for visible recipients");
        decoder.Read();
        check(2, Bits(0.75f), true);
        check(3, Bits(0.75f), true);
        check(4, Bits(0.75f), true);
        Require(!decoder.clients.at(1).strings.count(5), "invisible recipient does not borrow another recipient's registration");
        g_Visible[1] = true;
        fixture.Frame();
        decoder.Read();
        check(1, Bits(0.75f), true);

        fixture.events.on_client_disconnected()(2);
        decoder.clients.erase(2);
        Require(fixture.materials.SetParam(entity, "", "uWear", 1.0f), "connected recipients continue receiving updates");
        Require(
            std::none_of(
                g_Messages.begin(), g_Messages.end(), [&](const Message& message) { return message.recipient == &fixture.edicts[2]; }
            ),
            "disconnect removes the recipient from incremental delivery"
        );
        decoder.Read();
        fixture.Frame();
        Require(g_Messages.empty(), "disconnected recipient receives no frame snapshot");
        fixture.events.on_client_connecting()(ClientConnectingEvent{2, "reconnected", "local"});
        fixture.events.on_client_first_frame()(2);
        decoder.Read();
        for (int client : {1, 2, 3, 4})
        {
            check(client, Bits(1.0f), true);
        }
        Require(
            !decoder.clients.count(5) && !decoder.clients.count(6), "incompatible clients stay excluded through updates and reconnects"
        );
    }

    void RecipientCompatibility()
    {
        Fixture fixture(6, false);
        fixture.client.clients[3].ready = false;
        fixture.client.clients[4].version = NextClientVersion{2, 5, 0};
        fixture.client.clients[5].version = NextClientVersion{2, 4, 0};
        fixture.client.clients[6].known = false;
        cssdk::Edict* entity = &fixture.edicts[7];
        entity->vars.model_index = 1;
        Require(fixture.materials.Bind(entity, "preset", "material"), "through-wall source has a binding");
        Require(fixture.materials.SetThroughWalls(entity, true), "through-wall source enabled");
        const auto authorized = [&](int client) {
            metamod::gamedll::detail::dll_hooks->add_to_full_pack(nullptr, 7, entity, &fixture.edicts[client], 0, 0, nullptr);
            metamod::engine::detail::engine_hooks->check_visibility(entity, nullptr);
            const bool result = fixture.meta_globals.result == metamod::Result::Supercede;
            metamod::gamedll::detail::dll_post_hooks->add_to_full_pack(nullptr, 7, entity, &fixture.edicts[client], 0, 0, nullptr);
            return result;
        };
        for (int client = 1; client <= 6; ++client)
        {
            Require(authorized(client) == (client <= 2), "only ready known version-2.6 recipients receive the visibility override");
        }
        fixture.client.clients[3].ready = true;
        Require(authorized(3), "readiness transition enables a compatible recipient");
        fixture.client.clients[2].ready = false;
        fixture.events.on_client_disconnected()(2);
        Require(!authorized(2), "disconnected unready recipient loses the visibility override");
        fixture.edicts[1].free = true;
        Require(!authorized(1), "free recipient edict cannot receive the visibility override");
        fixture.edicts[1].free = false;
        Require(authorized(1), "another valid ready recipient remains independent");
    }

    void NativeFloatCells()
    {
        Fixture fixture;
        std::array<cell, 64> memory{};
        AmxHeader header{};
        header.dat = sizeof(header);
        std::memcpy(memory.data(), &header, sizeof(header));
        const std::array<cell, 6> name{'u', 'W', 'e', 'a', 'r', 0};
        std::memcpy(reinterpret_cast<unsigned char*>(memory.data()) + header.dat, name.data(), sizeof(name));
        Amx amx{};
        amx.base = reinterpret_cast<unsigned char*>(memory.data());
        TransportDecoder decoder;
        for (float value : {0.5f, 0.1234567f, -0.1257f, 0.0f, 1.0f})
        {
            cell params[]{3 * sizeof(cell), 2, 0, amx::FloatToCell(value)};
            Require(ncl_mat_param_all(&amx, params) == TRUE, "native accepts a Float-tagged material value");
            decoder.Read();
            Require(
                decoder.clients.at(1).entities.at(1).params == std::map<uint16_t, uint32_t>{{1, Bits(value)}},
                "native Float cells reach the production serializer without numeric conversion or quantization"
            );
        }
        cell integer_params[]{3 * sizeof(cell), 2, 0, 32};
        Require(ncl_mat_param_all(&amx, integer_params) == TRUE, "raw integer cell is a finite denormal to the native");
        decoder.Read();
        Require(
            decoder.clients.at(1).entities.at(1).params.at(1) == 32 && Bits(1.0f) != 32,
            "integer-cell tag mismatch cannot represent full wear"
        );
    }

    void SameIdentity()
    {
        Fixture fixture;
        cssdk::Edict* entity = &fixture.edicts[2];
        Require(fixture.materials.Bind(entity, "preset", "material"), "binding accepted");
        Require(fixture.materials.SetParam(entity, "", "wear", 2.0f), "parameter accepted");
        fixture.Frame();
        Require(fixture.sync.Exists(1) && !fixture.sync.Exists(2), "same identity keeps one sync entity");
        Require(fixture.materials.Unbind(entity, "preset", "material"), "same identity retains binding");
    }
} // namespace

MaterialEntitySync& GetMaterialNclEntitySync()
{
    return *g_Materials;
}

namespace msg_ex
{
    int RegUserMsgSafe(const char* name, int)
    {
        const int id = static_cast<int>(g_MessageIds.size()) + 1;
        return g_MessageIds.emplace(name, id).first->second;
    }
    void MessageBegin(cssdk::MessageType type, int id, const float*, cssdk::Edict* recipient)
    {
        g_Messages.push_back({id, type, recipient, {}});
    }
    void MessageEnd() {}
    void WriteByte(uint8_t value)
    {
        g_Messages.back().bytes.push_back(value);
    }
    void WriteUShort(uint16_t value)
    {
        WriteByte(value & 255);
        WriteByte(value >> 8);
    }
    void WriteString(const char* value)
    {
        do
        {
            WriteByte(static_cast<uint8_t>(*value));
        } while (*value++);
    }
} // namespace msg_ex

int main(int argc, char** argv)
{
    const std::map<std::string, void (*)()> scenarios{
        {"ownership-new-bind", [] { RecycledId(true, OwnershipAction::Bind); }},
        {"ownership-new-param", [] { RecycledId(true, OwnershipAction::Param); }},
        {"ownership-new-clear", [] { RecycledId(true, OwnershipAction::Clear); }},
        {"ownership-new-unbind", [] { RecycledId(true, OwnershipAction::Unbind); }},
        {"ownership-new-enable", [] { RecycledId(true, OwnershipAction::EnableVisibility); }},
        {"ownership-new-disable", [] { RecycledId(true, OwnershipAction::DisableVisibility); }},
        {"ownership-new-refresh", [] { RecycledId(true, OwnershipAction::RefreshVisibility); }},
        {"ownership-same-bind", [] { RecycledId(false, OwnershipAction::Bind); }},
        {"ownership-same-param", [] { RecycledId(false, OwnershipAction::Param); }},
        {"ownership-same-clear", [] { RecycledId(false, OwnershipAction::Clear); }},
        {"ownership-same-unbind", [] { RecycledId(false, OwnershipAction::Unbind); }},
        {"ownership-same-enable", [] { RecycledId(false, OwnershipAction::EnableVisibility); }},
        {"ownership-same-disable", [] { RecycledId(false, OwnershipAction::DisableVisibility); }},
        {"ownership-same-refresh", [] { RecycledId(false, OwnershipAction::RefreshVisibility); }},
        {"ownership-other-type", [] { RecycledId(false, OwnershipAction::Bind, true); }},
        {"repeated-preset-snapshot", RepeatedPresetSnapshot},
        {"recipient-routing", RecipientRouting},
        {"recipient-compatibility", RecipientCompatibility},
        {"native-float-cells", NativeFloatCells},
        {"invalid-index", InvalidIndex},
        {"registration-boundary", RegistrationBoundary},
        {"binding-admission", BindingAdmission},
        {"parameter-admission", ParameterAdmission},
        {"stale-unbind", StaleUnbind},
        {"unbind-admission", UnbindAdmission},
        {"sync-identity", SyncIdentity},
        {"same-identity", SameIdentity},
        {"reuse-before-bind", [] { Reuse(false, true); }},
        {"reuse-before-param", [] { Reuse(false, false); }},
        {"reuse-after-bind", [] { Reuse(true, true); }},
        {"reuse-after-param", [] { Reuse(true, false); }}
    };
    if (argc != 2 || !scenarios.count(argv[1]))
    {
        return 2;
    }
    try
    {
        scenarios.at(argv[1])();
        std::cout << "PASSED: " << argv[1] << '\n';
        return 0;
    }
    catch (const std::exception& error)
    {
        std::cerr << "FAILED: " << argv[1] << ": " << error.what() << '\n';
        return 1;
    }
}
