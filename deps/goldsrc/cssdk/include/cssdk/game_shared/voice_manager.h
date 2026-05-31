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

#include <cssdk/dll/player.h>

#ifdef __INTEL_COMPILER
#pragma warning(push)
#pragma warning(disable : 2021)
#endif

namespace cssdk
{
    class IVoiceGameMgrHelper // NOLINT(cppcoreguidelines-special-member-functions)
    {
    public:
        /**
         * @brief N/D
        */
        virtual ~IVoiceGameMgrHelper() = 0;

        /**
         * @brief Called each frame to determine which players are allowed to hear each other.
         * This overrides whatever squelch settings players have.
        */
        virtual bool CanPlayerHearPlayer(PlayerBase* listener, PlayerBase* talker) = 0;

#ifdef REGAMEDLL_ADD
        /**
         * @brief N/D
        */
        virtual void ResetCanHearPlayer(Edict* edict) = 0;

        /**
         * @brief N/D
        */
        virtual void SetCanHearPlayer(PlayerBase* listener, PlayerBase* sender, bool can_hear) = 0;

        /**
         * @brief N/D
        */
        virtual bool GetCanHearPlayer(PlayerBase* listener, PlayerBase* sender) = 0;
#endif
    };

    // ReSharper disable once CppClassCanBeFinal
    class VoiceGameMgr // NOLINT(cppcoreguidelines-special-member-functions)
    {
    public:
        /**
         * @brief N/D
        */
        virtual ~VoiceGameMgr() = default;

        // private:
        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        int msg_player_voice_mask_{}; // NOLINT(clang-diagnostic-unused-private-field)

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        int msg_request_state_{}; // NOLINT(clang-diagnostic-unused-private-field)

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        IVoiceGameMgrHelper* helper_{}; // NOLINT(clang-diagnostic-unused-private-field)

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        int max_players_{}; // NOLINT(clang-diagnostic-unused-private-field)

        /**
         * @brief How long since the last update.
        */
        // ReSharper disable once CppInconsistentNaming
        double update_interval_{}; // NOLINT(clang-diagnostic-unused-private-field)
    };
}

#ifdef __INTEL_COMPILER
#pragma warning(pop)
#endif
