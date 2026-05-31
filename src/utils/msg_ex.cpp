#include "msg_ex.h"

#include <easylogging++.h>

#include <metamod/engine.h>
#include <metamod/utils.h>
#include <core/type_conversion.h>

using namespace metamod;
using namespace core;

namespace msg_ex
{
    int RegUserMsgSafe(const char* name, int size)
    {
        int message_id = utils::GetUserMsgId(name);

        if (message_id == 0)
        {
            message_id = engine::RegUserMessage(name, size);
        }

        if (message_id == 0)
        {
            LOG(ERROR) << "Unable to register message " << name;
        }

        return message_id;
    }

    void MessageBegin(cssdk::MessageType msg_type, int msg_id, const float* origin, cssdk::Edict* client)
    {
        engine::MessageBegin(msg_type, msg_id, origin, client);
    }

    void MessageBegin(cssdk::MessageType msg_type, int msg_id, const cssdk::Vector& origin, cssdk::Edict* client)
    {
        engine::MessageBegin(msg_type, msg_id, origin, client);
    }

    void MessageEnd()
    {
        engine::MessageEnd();
    }

    void WriteByte(uint8_t data)
    {
        engine::WriteByte(data);
    }

    void WriteShort(int16_t data)
    {
        engine::WriteShort(data);
    }

    void WriteUShort(uint16_t data)
    {
        engine::WriteShort(data);
    }

    void WriteInt(int32_t data)
    {
        engine::WriteLong(data);
    }

    void WriteUInt(uint32_t data)
    {
        engine::WriteLong(*reinterpret_cast<int32_t*>(&data));
    }

    void WriteFloat(float data)
    {
        engine::WriteLong(*reinterpret_cast<int32_t*>(&data));
    }

    void WriteCoord(float data)
    {
        engine::WriteCoord(data);
    }

    void WriteString(const char* data)
    {
        engine::WriteString(data);
    }
} // namespace msg_ex
