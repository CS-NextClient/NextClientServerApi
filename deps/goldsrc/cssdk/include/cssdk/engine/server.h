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
#include <cssdk/common/entity_state.h>
#include <cssdk/common/user_cmd.h>
#include <cssdk/common/weapon_data.h>
#include <cssdk/engine/custom.h>
#include <cssdk/engine/delta_packet.h>
#include <cssdk/engine/edict.h>
#include <cssdk/engine/net.h>
#include <cssdk/engine/prog_defs.h>
#include <cssdk/public/rehlds/common_rehlds.h>
#include <cssdk/public/rehlds/userid_rehlds.h>
#include <cstdio>

namespace cssdk
{
    enum class SvDelta
    {
        /**
         * @brief N/D
        */
        PacketNoDelta = 0,

        /**
         * @brief N/D
        */
        PacketDelta
    };

    enum class ServerState
    {
        /**
         * @brief N/D
        */
        Dead = 0,

        /**
         * @brief N/D
        */
        Loading,

        /**
         * @brief N/D
        */
        Active
    };

    struct ClientFrame
    {
        /**
         * @brief N/D
        */
        double sent_time{};

        /**
         * @brief N/D
        */
        float ping_time{};

        /**
         * @brief N/D
        */
        ClientData client_data{};

        /**
         * @brief N/D
        */
        WeaponData weapon_data[64]{};

        /**
         * @brief N/D
        */
        PacketEntities entities{};
    };

    struct Client
    {
        /**
         * @brief N/D
        */
        qboolean active{};

        /**
         * @brief N/D
        */
        qboolean spawned{};

        /**
         * @brief N/D
        */
        qboolean fully_connected{};

        /**
         * @brief N/D
        */
        qboolean connected{};

        /**
         * @brief N/D
        */
        qboolean uploading{};

        /**
         * @brief N/D
        */
        qboolean has_usr_msgs{};

        /**
         * @brief N/D
        */
        qboolean has_force_unmodified{};

        /**
         * @brief N/D
        */
        NetChan net_chan{};

        /**
         * @brief N/D
        */
        int choke_count{};

        /**
         * @brief N/D
        */
        int delta_sequence{};

        /**
         * @brief N/D
        */
        qboolean fake_client{};

        /**
         * @brief N/D
        */
        qboolean proxy{};

        /**
         * @brief N/D
        */
        UserCmd last_cmd{};

        /**
         * @brief N/D
        */
        double connect_time{};

        /**
         * @brief N/D
        */
        double cmd_time{};

        /**
         * @brief N/D
        */
        double ignore_cmd_time{};

        /**
         * @brief N/D
        */
        float latency{};

        /**
         * @brief N/D
        */
        float packet_loss{};

        /**
         * @brief N/D
        */
        double localtime{};

        /**
         * @brief N/D
        */
        double next_ping{};

        /**
         * @brief N/D
        */
        double sv_time_base{};

        /**
         * @brief N/D
        */
        SizeBuf datagram{};

        /**
         * @brief N/D
        */
        byte datagram_buf[MAX_DATAGRAM]{};

        /**
         * @brief N/D
        */
        double connection_started{};

        /**
         * @brief N/D
        */
        double next_message_time{};

        /**
         * @brief N/D
        */
        double next_message_interval{};

        /**
         * @brief N/D
        */
        qboolean send_message{};

        /**
         * @brief N/D
        */
        qboolean skip_message{};

        /**
         * @brief N/D
        */
        ClientFrame* frames{};

        /**
         * @brief N/D
        */
        EventState events{};

        /**
         * @brief N/D
        */
        Edict* edict{};

        /**
         * @brief N/D
        */
        const Edict* view_entity{};

        /**
         * @brief N/D
        */
        int user_id{};

        /**
         * @brief N/D
        */
        UserId network_user_id{};

        /**
         * @brief N/D
        */
        char user_info[MAX_INFO_STRING]{};

        /**
         * @brief N/D
        */
        qboolean send_info{};

        /**
         * @brief N/D
        */
        float send_info_time{};

        /**
         * @brief N/D
        */
        char hashed_cd_key[64]{};

        /**
         * @brief N/D
        */
        char name[32]{};

        /**
         * @brief N/D
        */
        int top_color{};

        /**
         * @brief N/D
        */
        int bottom_color{};

        /**
         * @brief N/D
        */
        int entity_id{};

        /**
         * @brief N/D
        */
        Resource resources_on_hand{};

        /**
         * @brief N/D
        */
        Resource resources_needed{};

        /**
         * @brief N/D
        */
        std::FILE* upload{};

        /**
         * @brief N/D
        */
        qboolean upload_done_registering{};

        /**
         * @brief N/D
        */
        Customization custom_data{};

        /**
         * @brief N/D
        */
        int crc_value{};

        /**
         * @brief N/D
        */
        int lw{};

        /**
         * @brief N/D
        */
        int lc{};

        /**
         * @brief N/D
        */
        char phys_info[MAX_INFO_STRING]{};

        /**
         * @brief N/D
        */
        qboolean loopback{};

        /**
         * @brief N/D
        */
        uint32 voice_streams[2]{};

        /**
         * @brief N/D
        */
        double last_voice_time{};

        /**
         * @brief N/D
        */
        int send_res_count{};

        /**
         * @brief N/D
        */
        qboolean sent_new_response{};
    };
}
