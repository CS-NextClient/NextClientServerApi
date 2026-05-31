#pragma once
#include <cstdint>

#include <cssdk/common/const.h>
#include <cssdk/engine/edict.h>

namespace msg_ex
{
    int RegUserMsgSafe(const char* name, int size);

    void MessageBegin(cssdk::MessageType msg_type, int msg_id, const float* origin = nullptr, cssdk::Edict* client = nullptr);
    void MessageBegin(cssdk::MessageType msg_type, int msg_id, const cssdk::Vector& origin, cssdk::Edict* client);
    void MessageEnd();

    void WriteByte(uint8_t data);
    void WriteShort(int16_t data);
    void WriteUShort(uint16_t data);
    void WriteInt(int32_t data);
    void WriteUInt(uint32_t data);
    void WriteFloat(float data);
    void WriteCoord(float data);
    void WriteString(const char* data);
} // namespace msg_ex
