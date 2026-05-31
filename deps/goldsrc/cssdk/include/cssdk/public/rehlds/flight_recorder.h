/*
 *  Half Life 1 SDK Copyright(c) Valve Corp.
 *
 *  THIS DOCUMENT DESCRIBES A CONTRACT BETWEEN YOU AND VALVE CORPORATION ("Valve").
 *  PLEASE READ IT BEFORE DOWNLOADING OR USING THE HALF LIFE 1 SDK ("SDK"). BY
 *  DOWNLOADING AND/OR USING THE HALF LIFE 1 SDK YOU ACCEPT THIS LICENSE. IF YOU DO
 *  NOT AGREE TO THE TERMS OF THIS LICENSE PLEASE DON'T DOWNLOAD OR USE THE SDK.
 *
 *  You may, free of charge, download and use the SDK to develop a modified Valve
 *  game running on the Half-Life 1 engine. You may distribute your modified Valve
 *  game in source and object code form, but only for free. Terms of use for Valve
 *  games are found in the Steam Subscriber Agreement located here:
 *  http://store.steampowered.com/subscriber_agreement/
 *
 *  You may copy, modify, and distribute the SDK and any modifications you make to
 *  the SDK in source and object code form, but only for free. Any distribution of
 *  this SDK must include this LICENSE file.
 *
 *  Any distribution of the SDK or a substantial portion of the SDK must include
 *  the above copyright notice and the following:
 *
 *    DISCLAIMER OF WARRANTIES. THE HALF LIFE 1 SDK AND ANY OTHER MATERIAL
 *    DOWNLOADED BY LICENSEE IS PROVIDED "AS IS". VALVE AND ITS SUPPLIERS
 *    DISCLAIM ALL WARRANTIES WITH RESPECT TO THE SDK, EITHER EXPRESS OR IMPLIED,
 *    INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY,
 *    NON-INFRINGEMENT, TITLE AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *    LIMITATION OF LIABILITY. IN NO EVENT SHALL VALVE OR ITS SUPPLIERS BE LIABLE
 *    FOR ANY SPECIAL, INCIDENTAL, INDIRECT, OR CONSEQUENTIAL DAMAGES WHATSOEVER
 *    (INCLUDING, WITHOUT LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS,
 *    BUSINESS INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR ANY OTHER PECUNIARY
 *    LOSS) ARISING OUT OF THE USE OF OR INABILITY TO USE THE ENGINE AND/OR THE
 *    SDK, EVEN IF VALVE HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 *
 *  If you would like to use the SDK for a commercial purpose, please contact Valve
 *  at sourceengine@valvesoftware.com.
 */

#pragma once

#include <cssdk/common/const.h>

namespace cssdk
{
    class IReHldsFlightRecorder // NOLINT(cppcoreguidelines-special-member-functions)
    {
    public:
        /**
         * @brief N/D
        */
        virtual ~IReHldsFlightRecorder() = default;

        /**
         * @brief N/D
        */
        virtual uint16 RegisterMessage(const char* module, const char* message, unsigned int version, bool in_out) = 0;

        /**
         * @brief N/D
        */
        virtual void StartMessage(uint16 msg, bool entrance) = 0;

        /**
         * @brief N/D
        */
        virtual void EndMessage(uint16 msg, bool entrance) = 0;

        /**
         * @brief N/D
        */
        virtual void WriteInt8(int8 v) = 0;

        /**
         * @brief N/D
        */
        virtual void WriteUint8(uint8 v) = 0;

        /**
         * @brief N/D
        */
        virtual void WriteInt16(int16 v) = 0;

        /**
         * @brief N/D
        */
        virtual void WriteUint16(uint16 v) = 0;

        /**
         * @brief N/D
        */
        virtual void WriteInt32(int32 v) = 0;

        /**
         * @brief N/D
        */
        virtual void WriteUint32(uint32 v) = 0;

        /**
         * @brief N/D
        */
        virtual void WriteInt64(int64 v) = 0;

        /**
         * @brief N/D
        */
        virtual void WriteUint64(uint64 v) = 0;

        /**
         * @brief N/D
        */
        virtual void WriteFloat(float v) = 0;

        /**
         * @brief N/D
        */
        virtual void WriteDouble(double v) = 0;

        /**
         * @brief N/D
        */
        virtual void WriteString(const char* s) = 0;

        /**
         * @brief N/D
        */
        virtual void WriteBuffer(const void* data, unsigned int len) = 0;
    };
}
