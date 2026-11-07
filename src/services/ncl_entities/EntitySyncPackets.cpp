#include "EntitySyncPackets.h"

#include <algorithm>
#include <cmath>
#include <cstring>
#include <limits>
#include <type_traits>

using namespace ncl_entity;

namespace
{
    using IdPairs = std::vector<std::pair<uint16_t, uint16_t>>;
    using FloatPairs = std::vector<std::pair<uint16_t, float>>;

    constexpr uint8_t kClear = 255;
    constexpr size_t kUpdateHeaderSize = 5;

    template <typename Delta>
    constexpr size_t kAdditionSize = std::is_same_v<Delta, ArrayStringIdPairsDelta> ? 4 : 6;

    template <typename Delta>
    constexpr size_t kRemovalSize = std::is_same_v<Delta, ArrayStringIdPairsDelta> ? 4 : 2;

    void WriteInteger(std::vector<uint8_t>& bytes, uint32_t value, size_t size)
    {
        for (size_t i = 0; i < size; ++i)
        {
            bytes.push_back(static_cast<uint8_t>(value >> (i * 8)));
        }
    }

    uint32_t FloatBits(float value)
    {
        uint32_t bits;
        std::memcpy(&bits, &value, sizeof(bits));
        return bits;
    }

    bool EqualValue(uint16_t left, uint16_t right)
    {
        return left == right;
    }

    bool EqualValue(float left, float right)
    {
        return FloatBits(left) == FloatBits(right);
    }

    template <typename Pairs>
    bool EqualPairs(const Pairs& left, const Pairs& right)
    {
        return left.size() == right.size() && std::equal(left.begin(), left.end(), right.begin(), [](const auto& a, const auto& b) {
                   return a.first == b.first && EqualValue(a.second, b.second);
               });
    }

    uint16_t RemovedKey(uint16_t key)
    {
        return key;
    }

    uint16_t RemovedKey(const std::pair<uint16_t, uint16_t>& pair)
    {
        return pair.first;
    }

    template <typename Pairs, typename Delta>
    EntitySyncPackets::Mutation ApplyCollection(
        const FieldValue* current,
        const FieldValue& requested,
        FieldValue& full,
        FieldValue& pending
    )
    {
        Pairs before;

        if (current)
        {
            const Pairs* values = std::get_if<Pairs>(&current->value);
            if (!values)
            {
                return EntitySyncPackets::Mutation::Invalid;
            }

            before = *values;
        }

        Pairs after;
        Delta delta;

        if (const Pairs* values = std::get_if<Pairs>(&requested.value))
        {
            after = *values;
            delta.clear = true;
            delta.added = after;
        }
        else
        {
            delta = std::get<Delta>(requested.value);
            after = delta.clear ? Pairs{} : before;

            for (const auto& addition : delta.added)
            {
                auto entry =
                    std::find_if(after.begin(), after.end(), [&addition](const auto& pair) { return pair.first == addition.first; });

                if (entry == after.end())
                {
                    after.push_back(addition);
                }
                else
                {
                    *entry = addition;
                }
            }

            for (const auto& removal : delta.removed)
            {
                after.erase(
                    std::remove_if(after.begin(), after.end(), [&removal](const auto& pair) { return pair.first == RemovedKey(removal); }),
                    after.end()
                );
            }
        }

        if (EqualPairs(before, after))
        {
            return EntitySyncPackets::Mutation::Unchanged;
        }

        bool reset = delta.clear;

        for (const auto& addition : delta.added)
        {
            reset |= std::any_of(delta.removed.begin(), delta.removed.end(), [&addition](const auto& removal) {
                return RemovedKey(removal) == addition.first;
            });
            if constexpr (std::is_same_v<Pairs, IdPairs>)
            {
                reset |= std::any_of(before.begin(), before.end(), [&addition](const auto& pair) {
                    return pair.first == addition.first && pair.second != addition.second;
                });
            }
        }

        if (reset)
        {
            delta.clear = true;
            delta.added = after;
            delta.removed.clear();
        }

        full = FieldValue{std::move(after)};
        pending = FieldValue{std::move(delta)};

        return EntitySyncPackets::Mutation::Changed;
    }

    bool IsDelta(FieldType type)
    {
        return type == FieldType::ARRAY_STRING_ID_PAIRS_DELTA || type == FieldType::ARRAY_STRING_ID_FLOAT_PAIRS_DELTA;
    }

    FieldValue DefaultValue(FieldType type)
    {
        switch (type)
        {
            case FieldType::BYTE:
                return FieldValue{uint8_t{}};
            case FieldType::USHORT:
            case FieldType::STRING_ID:
                return FieldValue{uint16_t{}};
            case FieldType::UINT:
                return FieldValue{uint32_t{}};
            case FieldType::FLOAT:
            case FieldType::COORD:
                return FieldValue{0.0f};
            case FieldType::ARRAY_STRING_ID_FLOAT_PAIRS_DELTA:
                return FieldValue{FloatPairs{}};
            default:
                return FieldValue{IdPairs{}};
        }
    }

    bool WriteValue(std::vector<uint8_t>& bytes, FieldType type, const FieldValue& value)
    {
        switch (type)
        {
            case FieldType::BYTE:
                WriteInteger(bytes, std::get<uint8_t>(value.value), 1);
                return true;
            case FieldType::USHORT:
            case FieldType::STRING_ID:
                WriteInteger(bytes, std::get<uint16_t>(value.value), 2);
                return true;
            case FieldType::UINT:
                WriteInteger(bytes, std::get<uint32_t>(value.value), 4);
                return true;
            case FieldType::FLOAT:
                WriteInteger(bytes, FloatBits(std::get<float>(value.value)), 4);
                return true;
            case FieldType::COORD:
                {
                    float scaled = std::get<float>(value.value) * 8.0f;
                    if (!std::isfinite(scaled) || scaled < std::numeric_limits<int>::min() ||
                        static_cast<double>(scaled) > std::numeric_limits<int>::max())
                    {
                        return false;
                    }

                    WriteInteger(bytes, static_cast<uint16_t>(static_cast<int>(scaled)), 2);
                    return true;
                }
            case FieldType::ARRAY_STRING_ID_PAIRS:
                {
                    const IdPairs& pairs = std::get<IdPairs>(value.value);
                    if (pairs.size() > 254)
                    {
                        return false;
                    }

                    WriteInteger(bytes, static_cast<uint32_t>(pairs.size()), 1);

                    for (const auto& pair : pairs)
                    {
                        WriteInteger(bytes, pair.first, 2);
                        WriteInteger(bytes, pair.second, 2);
                    }

                    WriteInteger(bytes, 0, 1);

                    return true;
                }
            default:
                return false;
        }
    }

    EntitySyncPackets::Packet UpdatePacket(uint8_t type_id, uint16_t entity_id, uint16_t bit)
    {
        EntitySyncPackets::Packet packet;
        WriteInteger(packet.bytes, type_id, 1);
        WriteInteger(packet.bytes, entity_id, 2);
        WriteInteger(packet.bytes, bit, 2);
        return packet;
    }

    void AddStrings(std::vector<uint16_t>& ids, const IdPairs& pairs)
    {
        for (const auto& pair : pairs)
        {
            ids.push_back(pair.first);
            ids.push_back(pair.second);
        }
    }

    void AddStrings(std::vector<uint16_t>& ids, const FloatPairs& pairs)
    {
        for (const auto& pair : pairs)
        {
            ids.push_back(pair.first);
        }
    }

    void AddRemovalStrings(std::vector<uint16_t>& ids, const std::vector<uint16_t>& keys)
    {
        ids.insert(ids.end(), keys.begin(), keys.end());
    }

    void AddRemovalStrings(std::vector<uint16_t>& ids, const IdPairs& pairs)
    {
        AddStrings(ids, pairs);
    }

    void WriteAddition(std::vector<uint8_t>& bytes, const std::pair<uint16_t, uint16_t>& pair)
    {
        WriteInteger(bytes, pair.first, 2);
        WriteInteger(bytes, pair.second, 2);
    }

    void WriteAddition(std::vector<uint8_t>& bytes, const std::pair<uint16_t, float>& pair)
    {
        WriteInteger(bytes, pair.first, 2);
        WriteInteger(bytes, FloatBits(pair.second), 4);
    }

    void WriteRemoval(std::vector<uint8_t>& bytes, uint16_t key)
    {
        WriteInteger(bytes, key, 2);
    }

    void WriteRemoval(std::vector<uint8_t>& bytes, const std::pair<uint16_t, uint16_t>& pair)
    {
        WriteAddition(bytes, pair);
    }

    template <typename Delta>
    void AppendDelta(EntitySyncPackets::Result& result, uint8_t type_id, uint16_t entity_id, uint16_t bit, const Delta& delta)
    {
        if (delta.clear)
        {
            EntitySyncPackets::Packet packet = UpdatePacket(type_id, entity_id, bit);
            packet.bytes.push_back(kClear);
            result.packets.push_back(std::move(packet));
        }

        size_t added = 0;
        size_t removed = 0;

        while (added < delta.added.size() || removed < delta.removed.size())
        {
            EntitySyncPackets::Packet packet = UpdatePacket(type_id, entity_id, bit);
            size_t capacity = EntitySyncPackets::kMaxPayload - kUpdateHeaderSize - 2;
            size_t added_count = std::min({delta.added.size() - added, capacity / kAdditionSize<Delta>, size_t{254}});

            packet.bytes.push_back(static_cast<uint8_t>(added_count));

            for (size_t i = 0; i < added_count; ++i)
            {
                WriteAddition(packet.bytes, delta.added[added++]);
            }

            capacity -= added_count * kAdditionSize<Delta>;

            size_t removed_count =
                added_count == 0 ? std::min({delta.removed.size() - removed, capacity / kRemovalSize<Delta>, size_t{255}}) : 0;

            packet.bytes.push_back(static_cast<uint8_t>(removed_count));

            for (size_t i = 0; i < removed_count; ++i)
            {
                WriteRemoval(packet.bytes, delta.removed[removed++]);
            }

            result.packets.push_back(std::move(packet));
        }

        AddStrings(result.string_ids, delta.added);
        AddRemovalStrings(result.string_ids, delta.removed);
    }

    EntitySyncPackets::Result Failure(const char* message)
    {
        EntitySyncPackets::Result result;
        result.error = message;
        return result;
    }

    bool ValidateSchema(const std::vector<EntitySyncPackets::Field>& schema, const EntitySyncPackets::Fields& cache)
    {
        uint16_t bits = 0;

        for (const EntitySyncPackets::Field& field : schema)
        {
            if (field.bit == 0 || (field.bit & (field.bit - 1)) != 0 || (bits & field.bit))
            {
                return false;
            }

            bits |= field.bit;
            FieldValue value = DefaultValue(field.type);

            auto entry = cache.find(field.bit);
            if (entry != cache.end())
            {
                value = entry->second;
            }

            if (!EntitySyncPackets::IsValueValid(field.type, value, false))
            {
                return false;
            }
        }

        for (const auto& entry : cache)
        {
            if (!(bits & entry.first) || (entry.first & (entry.first - 1)) != 0)
            {
                return false;
            }
        }
        return true;
    }
} // namespace

bool EntitySyncPackets::PublishCreate(
    const Result& prepared,
    uint16_t entity_id,
    std::unordered_set<uint16_t>& visible,
    const std::function<void(const Result&)>& send
)
{
    if (!prepared || prepared.packets.empty() || !prepared.packets.front().create)
    {
        return false;
    }

    send(prepared);
    visible.insert(entity_id);

    return true;
}

bool EntitySyncPackets::IsValueValid(FieldType type, const FieldValue& value, bool allow_delta)
{
    switch (type)
    {
        case FieldType::BYTE:
            return std::holds_alternative<uint8_t>(value.value);
        case FieldType::USHORT:
        case FieldType::STRING_ID:
            return std::holds_alternative<uint16_t>(value.value);
        case FieldType::UINT:
            return std::holds_alternative<uint32_t>(value.value);
        case FieldType::FLOAT:
        case FieldType::COORD:
            return std::holds_alternative<float>(value.value);
        case FieldType::ARRAY_STRING_ID_PAIRS:
            return std::holds_alternative<IdPairs>(value.value);
        case FieldType::ARRAY_STRING_ID_PAIRS_DELTA:
            return std::holds_alternative<IdPairs>(value.value) ||
                   (allow_delta && std::holds_alternative<ArrayStringIdPairsDelta>(value.value));
        case FieldType::ARRAY_STRING_ID_FLOAT_PAIRS_DELTA:
            {
                const FloatPairs* pairs = std::get_if<FloatPairs>(&value.value);
                if (!pairs && allow_delta)
                {
                    const ArrayStringIdFloatPairsDelta* delta = std::get_if<ArrayStringIdFloatPairsDelta>(&value.value);
                    pairs = delta ? &delta->added : nullptr;
                }

                return pairs && std::all_of(pairs->begin(), pairs->end(), [](const auto& pair) { return std::isfinite(pair.second); });
            }
    }
    return false;
}

EntitySyncPackets::Mutation EntitySyncPackets::ApplyUpdate(
    FieldType type,
    const FieldValue* current,
    const FieldValue& requested,
    FieldValue& full,
    FieldValue& pending
)
{
    if (!IsValueValid(type, requested, true) || (current && !IsValueValid(type, *current, false)))
    {
        return Mutation::Invalid;
    }

    if (type == FieldType::ARRAY_STRING_ID_PAIRS_DELTA)
    {
        return ApplyCollection<IdPairs, ArrayStringIdPairsDelta>(current, requested, full, pending);
    }

    if (type == FieldType::ARRAY_STRING_ID_FLOAT_PAIRS_DELTA)
    {
        return ApplyCollection<FloatPairs, ArrayStringIdFloatPairsDelta>(current, requested, full, pending);
    }

    if (current && *current == requested)
    {
        return Mutation::Unchanged;
    }

    full = requested;

    return Mutation::Changed;
}

EntitySyncPackets::Result EntitySyncPackets::PrepareCreate(
    uint8_t type_id,
    uint16_t entity_id,
    const std::vector<Field>& schema,
    const Fields& cache
)
{
    if (type_id == 0 || entity_id == 0 || !ValidateSchema(schema, cache))
    {
        return Failure("Invalid create schema or field value");
    }

    Result result;
    Packet create;
    create.create = true;

    WriteInteger(create.bytes, type_id, 1);
    WriteInteger(create.bytes, entity_id, 2);

    for (const Field& field : schema)
    {
        auto entry = cache.find(field.bit);
        FieldValue value = entry == cache.end() ? DefaultValue(field.type) : entry->second;

        if (IsDelta(field.type))
        {
            create.bytes.insert(create.bytes.end(), {0, 0});
        }
        else if (!WriteValue(create.bytes, field.type, value))
        {
            return Failure("Unrepresentable create field");
        }

        if (field.type == FieldType::STRING_ID)
        {
            result.string_ids.push_back(std::get<uint16_t>(value.value));
        }
        else if (field.type == FieldType::ARRAY_STRING_ID_PAIRS)
        {
            AddStrings(result.string_ids, std::get<IdPairs>(value.value));
        }
    }

    if (create.bytes.size() > kMaxPayload)
    {
        return Failure("Create exceeds payload capacity");
    }

    result.packets.push_back(std::move(create));

    for (const Field& field : schema)
    {
        auto entry = cache.find(field.bit);
        if (entry == cache.end())
        {
            continue;
        }

        if (field.type == FieldType::ARRAY_STRING_ID_PAIRS_DELTA)
        {
            ArrayStringIdPairsDelta delta;
            delta.added = std::get<IdPairs>(entry->second.value);
            AppendDelta(result, type_id, entity_id, field.bit, delta);
        }
        else if (field.type == FieldType::ARRAY_STRING_ID_FLOAT_PAIRS_DELTA)
        {
            ArrayStringIdFloatPairsDelta delta;
            delta.added = std::get<FloatPairs>(entry->second.value);
            AppendDelta(result, type_id, entity_id, field.bit, delta);
        }
    }

    return result;
}

EntitySyncPackets::Result EntitySyncPackets::PrepareUpdate(
    uint8_t type_id,
    uint16_t entity_id,
    const std::vector<Field>& schema,
    const Fields& cache,
    const Fields& pending,
    uint16_t field_mask
)
{
    if (type_id == 0 || entity_id == 0 || !ValidateSchema(schema, cache))
    {
        return Failure("Invalid update schema or field value");
    }

    Result result;
    uint16_t remaining = field_mask;

    for (const Field& field : schema)
    {
        if (!(field_mask & field.bit))
        {
            continue;
        }

        remaining &= ~field.bit;

        auto entry = cache.find(field.bit);
        FieldValue value = entry == cache.end() ? DefaultValue(field.type) : entry->second;

        auto change = pending.find(field.bit);
        if (change != pending.end() && !IsValueValid(field.type, change->second, true))
        {
            return Failure("Invalid pending delta");
        }

        if (field.type == FieldType::ARRAY_STRING_ID_PAIRS_DELTA)
        {
            ArrayStringIdPairsDelta delta;

            if (change != pending.end())
            {
                const ArrayStringIdPairsDelta* supplied = std::get_if<ArrayStringIdPairsDelta>(&change->second.value);
                if (!supplied)
                {
                    return Failure("Pending field must be a delta");
                }

                delta = *supplied;
            }
            else
            {
                delta.clear = true;
                delta.added = std::get<IdPairs>(value.value);
            }

            AppendDelta(result, type_id, entity_id, field.bit, delta);
        }
        else if (field.type == FieldType::ARRAY_STRING_ID_FLOAT_PAIRS_DELTA)
        {
            ArrayStringIdFloatPairsDelta delta;

            if (change != pending.end())
            {
                const ArrayStringIdFloatPairsDelta* supplied = std::get_if<ArrayStringIdFloatPairsDelta>(&change->second.value);
                if (!supplied)
                {
                    return Failure("Pending field must be a float delta");
                }

                delta = *supplied;
            }
            else
            {
                delta.clear = true;
                delta.added = std::get<FloatPairs>(value.value);
            }

            AppendDelta(result, type_id, entity_id, field.bit, delta);
        }
        else
        {
            Packet packet = UpdatePacket(type_id, entity_id, field.bit);

            if (!WriteValue(packet.bytes, field.type, value) || packet.bytes.size() > kMaxPayload)
            {
                return Failure("Update field exceeds payload capacity");
            }

            result.packets.push_back(std::move(packet));

            if (field.type == FieldType::STRING_ID)
            {
                result.string_ids.push_back(std::get<uint16_t>(value.value));
            }
            else if (field.type == FieldType::ARRAY_STRING_ID_PAIRS)
            {
                AddStrings(result.string_ids, std::get<IdPairs>(value.value));
            }
        }
    }

    if (remaining)
    {
        return Failure("Unknown update field mask");
    }

    return result;
}
