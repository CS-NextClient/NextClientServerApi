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
#include <cssdk/common/net_address.h>
#include <cssdk/engine/server.h>

namespace cssdk
{
    struct ServerLog
    {
        /**
         * @brief N/D
        */
        qboolean active{};

        /**
         * @brief N/D
        */
        qboolean net_log{};

        /**
         * @brief N/D
        */
        NetAddress net_address{};

        /**
         * @brief N/D
        */
        void* file{};
    };

    struct ServerStats
    {
        /**
         * @brief N/D
        */
        int num_samples{};

        /**
         * @brief N/D
        */
        int at_capacity{};

        /**
         * @brief N/D
        */
        int at_empty{};

        /**
         * @brief N/D
        */
        float capacity_percent{};

        /**
         * @brief N/D
        */
        float empty_percent{};

        /**
         * @brief N/D
        */
        int min_users{};

        /**
         * @brief N/D
        */
        int max_users{};

        /**
         * @brief N/D
        */
        float cumulative_occupancy{};

        /**
         * @brief N/D
        */
        float occupancy{};

        /**
         * @brief N/D
        */
        int num_sessions{};

        /**
         * @brief N/D
        */
        float cumulative_session_time{};

        /**
         * @brief N/D
        */
        float average_session_len{};

        /**
         * @brief N/D
        */
        float cumulative_latency{};

        /**
         * @brief N/D
        */
        float average_latency{};
    };

    struct ServerStatic
    {
        /**
         * @brief N/D
        */
        qboolean dll_initialized{};

        /**
         * @brief N/D
        */
        Client* clients{};

        /**
         * @brief N/D
        */
        int max_clients{};

        /**
         * @brief N/D
        */
        int max_clients_limit{};

        /**
         * @brief N/D
        */
        int spawn_count{};

        /**
         * @brief N/D
        */
        int server_flags{};

        /**
         * @brief N/D
        */
        ServerLog log{};

        /**
         * @brief N/D
        */
        double next_clear_time{};

        /**
         * @brief N/D
        */
        double next_sample_time{};

        /**
         * @brief N/D
        */
        ServerStats stats{};

        /**
         * @brief N/D
        */
        qboolean is_secure{};
    };
}
