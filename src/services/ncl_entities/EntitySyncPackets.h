#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <nextclientapi_amxx/ncl_entity/FieldType.h>
#include <nextclientapi_amxx/ncl_entity/FieldValue.h>

#include "utils/UserMessageLimits.h"

namespace EntitySyncPackets
{
    constexpr size_t kMaxPayload = msg_ex::kMaxPayload;

    struct Field
    {
        uint16_t bit{};
        ncl_entity::FieldType type{};
    };

    using Fields = std::unordered_map<uint16_t, ncl_entity::FieldValue>;

    struct Packet
    {
        bool create{};
        std::vector<uint8_t> bytes;
    };

    struct Result
    {
        std::vector<Packet> packets;
        std::vector<uint16_t> string_ids;
        std::string error;

        explicit operator bool() const
        {
            return error.empty();
        }
    };

    enum class Mutation
    {
        Invalid,
        Unchanged,
        Changed
    };

    bool IsValueValid(ncl_entity::FieldType type, const ncl_entity::FieldValue& value, bool allow_delta);
    bool PublishCreate(
        const Result& prepared,
        uint16_t entity_id,
        std::unordered_set<uint16_t>& visible,
        const std::function<void(const Result&)>& send
    );
    Mutation ApplyUpdate(
        ncl_entity::FieldType type,
        const ncl_entity::FieldValue* current,
        const ncl_entity::FieldValue& requested,
        ncl_entity::FieldValue& full,
        ncl_entity::FieldValue& pending
    );

    Result PrepareCreate(uint8_t type_id, uint16_t entity_id, const std::vector<Field>& schema, const Fields& cache);
    Result PrepareUpdate(
        uint8_t type_id,
        uint16_t entity_id,
        const std::vector<Field>& schema,
        const Fields& cache,
        const Fields& pending,
        uint16_t field_mask
    );
} // namespace EntitySyncPackets
