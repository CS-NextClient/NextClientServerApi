#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <limits>
#include <map>

#include "services/ncl_entities/EntitySyncPackets.h"

using namespace ncl_entity;

namespace
{
    using FloatPairs = std::vector<std::pair<uint16_t, float>>;
    using IdPairs = std::vector<std::pair<uint16_t, uint16_t>>;

    void Require(bool condition, const char* scenario)
    {
        if (!condition)
        {
            std::cerr << "FAILED: " << scenario << '\n';
            std::exit(EXIT_FAILURE);
        }
    }

    uint32_t Bits(float value)
    {
        uint32_t bits;
        std::memcpy(&bits, &value, sizeof(bits));
        return bits;
    }

    void CheckFieldValueTransitions()
    {
        const std::vector<FieldValue> alternatives{
            FieldValue{uint8_t{9}},
            FieldValue{uint16_t{99}},
            FieldValue{uint32_t{999}},
            FieldValue{-0.125f},
            FieldValue{IdPairs{{1, 2}}},
            FieldValue{ArrayStringIdPairsDelta{{{1, 2}}, {{3, 4}}, true}},
            FieldValue{FloatPairs{{1, 0.1234567f}}},
            FieldValue{ArrayStringIdFloatPairsDelta{{{1, -0.1234567f}}, {3}, true}}
        };

        FieldValue default_value;
        Require(default_value.value.index() == 0, "default variant type");
        Require(std::get<uint8_t>(default_value.value) == 0, "default variant value");

        for (const FieldValue& initial : alternatives)
        {
            for (const FieldValue& requested : alternatives)
            {
                FieldValue copied = initial;
                copied = requested;
                Require(copied == requested, "copy assignment across every variant alternative");

                FieldValue moved = initial;
                FieldValue replacement = requested;
                moved = std::move(replacement);
                Require(moved == requested, "move assignment across every variant alternative");
            }
        }
    }

    struct Decoder
    {
        uint32_t scalar{};
        IdPairs bindings;
        std::map<uint16_t, uint32_t> params;

        void Read(const EntitySyncPackets::Result& result)
        {
            Require(static_cast<bool>(result), "successful preparation");
            for (const EntitySyncPackets::Packet& packet : result.packets)
            {
                Require(packet.bytes.size() <= 192, "bounded packet");
                size_t offset = 0;
                const auto word = [&](size_t count) {
                    Require(offset + count <= packet.bytes.size(), "complete independent decode");
                    uint32_t value = 0;
                    for (size_t i = 0; i < count; ++i)
                    {
                        value |= static_cast<uint32_t>(packet.bytes[offset++]) << (8 * i);
                    }
                    return value;
                };
                Require(word(1) == 3 && word(2) == 41, "entity identity");
                uint16_t mask = packet.create ? 7 : static_cast<uint16_t>(word(2));
                if (packet.create)
                {
                    bindings.clear();
                    params.clear();
                }
                if (mask & 1)
                {
                    scalar = word(4);
                }
                for (uint16_t bit : {2, 4})
                {
                    if (!(mask & bit))
                    {
                        continue;
                    }
                    uint32_t added = word(1);
                    if (added == 255)
                    {
                        Require(!packet.create, "clear only in updates");
                        if (bit == 2)
                        {
                            bindings.clear();
                        }
                        else
                        {
                            params.clear();
                        }
                        continue;
                    }
                    for (uint32_t i = 0; i < added; ++i)
                    {
                        uint16_t key = static_cast<uint16_t>(word(2));
                        uint32_t value = word(bit == 2 ? 2 : 4);
                        if (bit == 2)
                        {
                            const std::pair<uint16_t, uint16_t> pair{key, static_cast<uint16_t>(value)};
                            if (std::find(bindings.begin(), bindings.end(), pair) == bindings.end())
                            {
                                bindings.push_back(pair);
                            }
                        }
                        else
                        {
                            params[key] = value;
                        }
                    }
                    uint32_t removed = word(1);
                    for (uint32_t i = 0; i < removed; ++i)
                    {
                        uint16_t key = static_cast<uint16_t>(word(2));
                        if (bit == 2)
                        {
                            const std::pair<uint16_t, uint16_t> pair{key, static_cast<uint16_t>(word(2))};
                            bindings.erase(std::remove(bindings.begin(), bindings.end(), pair), bindings.end());
                        }
                        else
                        {
                            params.erase(key);
                        }
                    }
                }
                Require(offset == packet.bytes.size(), "no ignored bytes");
            }
        }
    };
} // namespace

int main()
{
    CheckFieldValueTransitions();

    const std::vector<EntitySyncPackets::Field> schema{
        {1, FieldType::UINT}, {2, FieldType::ARRAY_STRING_ID_PAIRS_DELTA}, {4, FieldType::ARRAY_STRING_ID_FLOAT_PAIRS_DELTA}
    };
    FloatPairs values{{501, 0.1234567f}, {502, -0.1257f}, {503, std::numeric_limits<float>::denorm_min()}, {504, -0.0f}};
    for (uint16_t i = 0; i < 125; ++i)
    {
        values.emplace_back(600 + i, i * 0.0034567f);
    }
    IdPairs bindings;
    for (uint16_t i = 0; i < 94; ++i)
    {
        bindings.emplace_back(100 + i % 3, 300 + i);
    }
    EntitySyncPackets::Fields cache{{1, FieldValue{uint32_t{77}}}, {2, FieldValue{bindings}}, {4, FieldValue{values}}};
    EntitySyncPackets::Result created = EntitySyncPackets::PrepareCreate(3, 41, schema, cache);
    std::unordered_set<uint16_t> visible;
    size_t delivered = 0;
    Require(
        EntitySyncPackets::PublishCreate(
            created,
            41,
            visible,
            [&](const EntitySyncPackets::Result& prepared) {
                Require(visible.empty(), "visibility commits after delivery");
                delivered = prepared.packets.size();
            }
        ),
        "successful create publishes"
    );
    Require(visible.count(41) && delivered == created.packets.size(), "complete delivery commits visibility");
    Decoder state;
    state.Read(created);
    Require(state.scalar == 77 && state.bindings.size() == bindings.size() && state.params.size() == values.size(), "complete create");
    Require(created.packets.front().create && created.packets.front().bytes.size() == 11, "scalar stays in create");
    for (const auto& pair : values)
    {
        Require(state.params.at(pair.first) == Bits(pair.second), "exact float bits");
    }
    Require(state.bindings == bindings, "complete pairs and order survive create chunks with repeated presets");
    Decoder late_join;
    late_join.Read(EntitySyncPackets::PrepareCreate(3, 41, schema, cache));
    Require(late_join.params == state.params && late_join.bindings == state.bindings, "late join complete snapshot");
    Decoder reentry;
    reentry.params[999] = 123;
    reentry.Read(EntitySyncPackets::PrepareCreate(3, 41, schema, cache));
    Require(reentry.params == state.params && reentry.bindings == state.bindings, "reentry resets and restores snapshot");
    Require(std::find(created.string_ids.begin(), created.string_ids.end(), 501) != created.string_ids.end(), "float key registry ID");
    Require(std::find(created.string_ids.begin(), created.string_ids.end(), 300) != created.string_ids.end(), "pair value registry ID");
    Require(
        std::find(created.string_ids.begin(), created.string_ids.end(), static_cast<uint16_t>(Bits(values[0].second))) ==
            created.string_ids.end(),
        "float bits are not registry IDs"
    );
    Require(created.string_ids.size() == 2 * bindings.size() + values.size(), "registry contains precisely both pair IDs and float keys");
    for (size_t i = 0; i < values.size(); ++i)
    {
        Require(created.string_ids[2 * bindings.size() + i] == values[i].first, "float registry sequence contains only keys");
    }

    IdPairs replacement = bindings;
    std::reverse(replacement.begin(), replacement.end());
    replacement.erase(replacement.begin() + 10);
    FieldValue replacement_full;
    FieldValue replacement_pending;
    FieldValue previous_bindings{bindings};
    FieldValue requested_bindings{replacement};
    const EntitySyncPackets::Mutation binding_replacement_mutation = EntitySyncPackets::ApplyUpdate(
        FieldType::ARRAY_STRING_ID_PAIRS_DELTA, &previous_bindings, requested_bindings, replacement_full, replacement_pending
    );
    Require(binding_replacement_mutation == EntitySyncPackets::Mutation::Changed, "repeated-preset full replacement changes the cache");
    EntitySyncPackets::Fields replacement_cache = cache;
    replacement_cache[2] = replacement_full;
    state.Read(EntitySyncPackets::PrepareUpdate(3, 41, schema, replacement_cache, {{2, replacement_pending}}, 2));
    Require(state.bindings == replacement, "complete repeated-preset replacement preserves every pair and its order");

    const IdPairs removed_pairs{replacement[0], replacement[46]};
    ArrayStringIdPairsDelta binding_removal;
    binding_removal.removed = removed_pairs;
    state.Read(EntitySyncPackets::PrepareUpdate(3, 41, schema, replacement_cache, {{2, FieldValue{binding_removal}}}, 2));
    for (const auto& pair : removed_pairs)
    {
        replacement.erase(std::remove(replacement.begin(), replacement.end(), pair), replacement.end());
    }
    Require(state.bindings == replacement, "removal matches the complete pair and retains sibling materials");
    replacement_cache[2] = FieldValue{replacement};
    Decoder replacement_late_join;
    replacement_late_join.Read(EntitySyncPackets::PrepareCreate(3, 41, schema, replacement_cache));
    Require(
        replacement_late_join.bindings == replacement && replacement_late_join.params == late_join.params &&
            replacement_late_join.scalar == 77,
        "late join reconstructs the complete state after replacement and removal"
    );

    for (size_t count : {size_t{30}, size_t{31}})
    {
        ArrayStringIdFloatPairsDelta delta;
        delta.added.assign(values.begin(), values.begin() + count);
        EntitySyncPackets::Result result = EntitySyncPackets::PrepareUpdate(3, 41, schema, cache, {{4, FieldValue{delta}}}, 4);
        Require(result.packets.size() == (count == 30 ? 1 : 2), "float max entries and max plus one");
        Require(result.packets.front().bytes.size() == 187, "float maximum addition chunk bytes");
    }
    for (size_t count : {size_t{46}, size_t{47}})
    {
        ArrayStringIdPairsDelta delta;
        delta.added.assign(bindings.begin(), bindings.begin() + count);
        EntitySyncPackets::Result result = EntitySyncPackets::PrepareUpdate(3, 41, schema, cache, {{2, FieldValue{delta}}}, 2);
        Require(result.packets.size() == (count == 46 ? 1 : 2), "pair max entries and max plus one");
        Require(result.packets.front().bytes.size() == 191, "pair maximum addition chunk bytes");
    }
    ArrayStringIdFloatPairsDelta reset;
    reset.clear = true;
    reset.added = values;
    state.params[999] = 1;
    state.Read(EntitySyncPackets::PrepareUpdate(3, 41, schema, cache, {{4, FieldValue{reset}}}, 4));
    Require(state.params == late_join.params, "clear happens once before all additions");
    ArrayStringIdFloatPairsDelta remove;
    for (const auto& value : values)
    {
        remove.removed.push_back(value.first);
    }
    state.Read(EntitySyncPackets::PrepareUpdate(3, 41, schema, cache, {{4, FieldValue{remove}}}, 4));
    Require(state.params.empty(), "removals span chunks");
    state.params[999] = 1;
    state.Read(EntitySyncPackets::PrepareUpdate(3, 41, schema, cache, {}, 4));
    Require(state.params == late_join.params, "fallback snapshot replaces complete collection");

    FieldValue full;
    FieldValue pending;
    FieldValue old{FloatPairs{{1, 0.25f}}};
    EntitySyncPackets::Mutation snapshot_mutation =
        EntitySyncPackets::ApplyUpdate(FieldType::ARRAY_STRING_ID_FLOAT_PAIRS_DELTA, &old, old, full, pending);
    Require(snapshot_mutation == EntitySyncPackets::Mutation::Unchanged, "unchanged snapshot has no delta");

    EntitySyncPackets::Mutation delta_mutation = EntitySyncPackets::ApplyUpdate(
        FieldType::ARRAY_STRING_ID_FLOAT_PAIRS_DELTA, &old, FieldValue{ArrayStringIdFloatPairsDelta{{{1, 0.25f}}, {}, false}}, full, pending
    );
    Require(delta_mutation == EntitySyncPackets::Mutation::Unchanged, "unchanged explicit delta has no delta");

    EntitySyncPackets::Mutation replacement_mutation = EntitySyncPackets::ApplyUpdate(
        FieldType::ARRAY_STRING_ID_FLOAT_PAIRS_DELTA, &old, FieldValue{FloatPairs{{1, 0.75f}}}, full, pending
    );
    Require(replacement_mutation == EntitySyncPackets::Mutation::Changed, "same key replacement changes");
    Require(std::get<FloatPairs>(full.value).front().second == 0.75f, "replacement retained in full cache");
    Require(std::get<ArrayStringIdFloatPairsDelta>(pending.value).clear, "full replacement resets ordered state");

    for (float invalid :
         {std::numeric_limits<float>::quiet_NaN(), std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity()})
    {
        EntitySyncPackets::Fields broken = cache;
        broken[4] = FieldValue{FloatPairs{{1, invalid}}};
        EntitySyncPackets::Result failed = EntitySyncPackets::PrepareCreate(3, 41, schema, broken);
        Require(!failed && failed.packets.empty(), "nonfinite preparation produces no partial packets");
        visible.clear();
        delivered = 0;
        Require(
            !EntitySyncPackets::PublishCreate(failed, 41, visible, [&](const EntitySyncPackets::Result&) { ++delivered; }),
            "failed preparation cannot publish"
        );
        Require(visible.empty() && delivered == 0, "failed create leaves visibility and delivery unchanged");
        full = FieldValue{uint8_t{88}};
        EntitySyncPackets::Mutation invalid_mutation =
            EntitySyncPackets::ApplyUpdate(FieldType::ARRAY_STRING_ID_FLOAT_PAIRS_DELTA, &old, broken[4], full, pending);
        Require(invalid_mutation == EntitySyncPackets::Mutation::Invalid, "nonfinite rejected before cache mutation");
        Require(std::get<uint8_t>(full.value) == 88, "invalid mutation preserves output");
        EntitySyncPackets::Fields changes{{4, FieldValue{ArrayStringIdFloatPairsDelta{{{1, invalid}}, {}, false}}}};
        EntitySyncPackets::Result failed_update = EntitySyncPackets::PrepareUpdate(3, 41, schema, cache, changes, 4);
        Require(!failed_update && failed_update.packets.empty(), "nonfinite pending delta rejects entire packet sequence");
    }
    EntitySyncPackets::Fields broken = cache;
    broken[4] = FieldValue{uint16_t{2}};
    Require(!EntitySyncPackets::PrepareCreate(3, 41, schema, broken), "variant mismatch rejected");
    Require(!EntitySyncPackets::PrepareCreate(3, 41, {{1, static_cast<FieldType>(99)}}, {}), "unknown type rejected");
    Require(
        !EntitySyncPackets::PrepareCreate(3, 41, {{2, FieldType::ARRAY_STRING_ID_PAIRS}}, {{2, FieldValue{bindings}}}),
        "oversized full-only replacement rejected"
    );
    for (size_t count : {size_t{46}, size_t{47}})
    {
        IdPairs pairs(bindings.begin(), bindings.begin() + count);
        EntitySyncPackets::Result result =
            EntitySyncPackets::PrepareUpdate(3, 41, {{2, FieldType::ARRAY_STRING_ID_PAIRS}}, {{2, FieldValue{pairs}}}, {}, 2);
        Require(static_cast<bool>(result) == (count == 46), "full-only exact capacity");
    }
    const IdPairs exact(bindings.begin(), bindings.begin() + 46);
    std::vector<EntitySyncPackets::Field> capacity_schema{
        {1, FieldType::BYTE}, {2, FieldType::USHORT}, {4, FieldType::ARRAY_STRING_ID_PAIRS}
    };
    EntitySyncPackets::Result maximum = EntitySyncPackets::PrepareCreate(3, 41, capacity_schema, {{4, FieldValue{exact}}});
    Require(maximum && maximum.packets.front().bytes.size() == 192, "exactly 192 bytes accepted");
    capacity_schema.push_back({8, FieldType::BYTE});
    EntitySyncPackets::Result over = EntitySyncPackets::PrepareCreate(3, 41, capacity_schema, {{4, FieldValue{exact}}});
    Require(!over && over.packets.empty(), "193 bytes rejected before delivery");
    FieldValue old_bindings{IdPairs{{1, 2}, {3, 4}}};
    EntitySyncPackets::Mutation binding_mutation = EntitySyncPackets::ApplyUpdate(
        FieldType::ARRAY_STRING_ID_PAIRS_DELTA, &old_bindings, FieldValue{ArrayStringIdPairsDelta{{{1, 5}}, {}, false}}, full, pending
    );
    Require(binding_mutation == EntitySyncPackets::Mutation::Changed, "pair replacement updates cache");
    Require(std::get<ArrayStringIdPairsDelta>(pending.value).clear, "pair replacement resets consumers with pair matching");
    Require(std::get<IdPairs>(full.value) == IdPairs{{1, 5}, {3, 4}}, "pair replacement retains order");
    FieldValue positive_zero{FloatPairs{{1, 0.0f}}};
    EntitySyncPackets::Mutation zero_mutation = EntitySyncPackets::ApplyUpdate(
        FieldType::ARRAY_STRING_ID_FLOAT_PAIRS_DELTA, &positive_zero, FieldValue{FloatPairs{{1, -0.0f}}}, full, pending
    );
    Require(zero_mutation == EntitySyncPackets::Mutation::Changed, "signed zero bit change is retained");
    Require(Bits(std::get<FloatPairs>(full.value).front().second) == 0x80000000u, "negative zero remains in cache");
    EntitySyncPackets::Fields incompatible_pending{{4, FieldValue{uint16_t{2}}}};
    Require(!EntitySyncPackets::PrepareUpdate(3, 41, schema, cache, incompatible_pending, 4), "pending variant mismatch rejected");
    std::cout << "Entity sync packets: all scenarios passed\n";
}
