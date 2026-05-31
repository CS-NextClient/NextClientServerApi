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
#include <cssdk/common/model.h>

namespace cssdk
{
    /**
     * @brief Must be power of 2.
    */
    constexpr auto HISTORY_MAX = 64;

    /**
     * @brief N/D
    */
    constexpr auto HISTORY_MASK = HISTORY_MAX - 1;

    struct Mouth
    {
        /**
         * @brief 0 = mouth closed, 255 = mouth agape.
        */
        byte mouth_open{};

        /**
         * @brief Counter for running average.
        */
        byte snd_count{};

        /**
         * @brief Running average.
        */
        int snd_avg{};
    };

    struct LatchedVars
    {
        /**
         * @brief N/D
        */
        float prev_anim_time{};

        /**
         * @brief N/D
        */
        float sequence_time{};

        /**
         * @brief N/D
        */
        byte prev_seq_blending[2]{};

        /**
         * @brief N/D
        */
        Vector prev_origin{};

        /**
         * @brief N/D
        */
        Vector prev_angles{};

        /**
         * @brief N/D
        */
        int prev_sequence{};

        /**
         * @brief N/D
        */
        float prev_frame{};

        /**
         * @brief N/D
        */
        byte prev_controller[4]{};

        /**
         * @brief N/D
        */
        byte prev_blending[2]{};
    };

    struct PositionHistory
    {
        /**
         * @brief Time stamp for this movement.
        */
        float anim_time{};

        /**
         * @brief N/D
        */
        Vector origin{};

        /**
         * @brief N/D
        */
        Vector angles{};
    };

    struct ClEntity
    {
        /**
         * @brief Index into cl_entities (should match actual slot, but not necessarily).
        */
        int index{};

        /**
         * @brief True if this entity is a "player".
        */
        qboolean player{};

        /**
         * @brief The original state from which to delta during an uncompressed message.
        */
        EntityState baseline{};

        /**
         * @brief The state information from the penultimate message received from the server.
        */
        EntityState prev_state{};

        /**
         * @brief The state information from the last message received from server.
        */
        EntityState cur_state{};

        /**
         * @brief Last received history update index.
        */
        int current_position{};

        /**
         * @brief History of position and angle updates for this player.
        */
        PositionHistory position_history[HISTORY_MAX]{};

        /**
         * @brief For synchronizing mouth movements.
        */
        Mouth mouth{};

        /**
         * @brief Variables used by studio model rendering routines.
        */
        LatchedVars latched{};

        /**
         * @brief Information based on interplocation, extrapolation, prediction, or just copied from last msg received.
        */
        float last_move{};

        /**
         * @brief Actual render position and angles.
        */
        Vector origin{};

        /**
         * @brief N/D
        */
        Vector angles{};

        /**
         * @brief Attachment points.
        */
        Vector attachment[4]{};

        /**
         * @brief Other entity local information.
        */
        int trivial_accept{};

        /**
         * @brief cl.model_precache[curstate.modelindes]; all visible entities have a model.
        */
        Model* model{};

        /**
         * @brief linked list of EFrag.
        */
        struct EFrag* e_frag{};

        /**
         * @brief For bmodels, first world node that splits bmodel, or NULL if not split.
        */
        struct MNode* top_node{};

        /**
         * @brief For client-side animations -- used by obsolete alias animation system, remove?
        */
        float sync_base{};

        /**
         * @brief Last frame this entity was found in an active leaf.
        */
        int vis_frame{};

        /**
         * @brief N/D
        */
        ColorVec floor_color{};
    };
}
