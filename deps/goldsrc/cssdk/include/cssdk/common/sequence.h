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
    /**
     * @brief N/D
    */
    constexpr auto SEQUENCE_MODIFIER_EFFECT_BIT = 1 << 1;

    /**
     * @brief N/D
    */
    constexpr auto SEQUENCE_MODIFIER_POSITION_BIT = 1 << 2;

    /**
     * @brief N/D
    */
    constexpr auto SEQUENCE_MODIFIER_COLOR_BIT = 1 << 3;

    /**
     * @brief N/D
    */
    constexpr auto SEQUENCE_MODIFIER_COLOR2_BIT = 1 << 4;

    /**
     * @brief N/D
    */
    constexpr auto SEQUENCE_MODIFIER_FADE_IN_BIT = 1 << 5;

    /**
     * @brief N/D
    */
    constexpr auto SEQUENCE_MODIFIER_FADEOUT_BIT = 1 << 6;

    /**
     * @brief N/D
    */
    constexpr auto SEQUENCE_MODIFIER_HOLD_TIME_BIT = 1 << 7;

    /**
     * @brief N/D
    */
    constexpr auto SEQUENCE_MODIFIER_FX_TIME_BIT = 1 << 8;

    /**
     * @brief N/D
    */
    constexpr auto SEQUENCE_MODIFIER_SPEAKER_BIT = 1 << 9;

    /**
     * @brief N/D
    */
    constexpr auto SEQUENCE_MODIFIER_LISTENER_BIT = 1 << 10;

    /**
     * @brief N/D
    */
    constexpr auto SEQUENCE_MODIFIER_TEXT_CHANNEL_BIT = 1 << 11;

    enum class SequenceCommandType
    {
        /**
         * @brief N/D
        */
        Command,

        /**
         * @brief N/D
        */
        Modifier
    };

    struct ClientTextMessage
    {
        /**
         * @brief N/D
        */
        int effect{};

        /**
         * @brief N/D
        */
        byte red1{};

        /**
         * @brief N/D
        */
        byte green1{};

        /**
         * @brief N/D
        */
        byte blue1{};

        /**
         * @brief N/D
        */
        byte alpha1{};

        /**
         * @brief N/D
        */
        byte red2{};

        /**
         * @brief N/D
        */
        byte green2{};

        /**
         * @brief N/D
        */
        byte blue2{};

        /**
         * @brief N/D
        */
        byte alpha2{};

        /**
         * @brief N/D
        */
        float x{};

        /**
         * @brief N/D
        */
        float y{};

        /**
         * @brief N/D
        */
        float fade_in{};

        /**
         * @brief N/D
        */
        float fade_out{};

        /**
         * @brief N/D
        */
        float hold_time{};

        /**
         * @brief N/D
        */
        float fx_time{};

        /**
         * @brief N/D
        */
        const char* name{};

        /**
         * @brief N/D
        */
        const char* message{};
    };

    /**
     * @brief Structure representing a single command (usually 1 line) from a .SEQ file entry.
    */
    struct SequenceCommandLine
    {
        /**
         * @brief Specifies the type of command.
        */
        SequenceCommandType command_type{};

        /**
         * @brief Text HUD message struct.
        */
        ClientTextMessage client_message{};

        /**
         * @brief Target name of speaking entity.
        */
        char* speaker_name{};

        /**
         * @brief Target name of entity being spoken to.
        */
        char* listener_name{};

        /**
         * @brief Name of sound file to play.
        */
        char* sound_file_name{};

        /**
         * @brief Name of sentences.txt to play.
        */
        char* sentence_name{};

        /**
         * @brief List of target names to fire.
        */
        char* fire_target_names{};

        /**
         * @brief List of target names to remove.
        */
        char* kill_target_names{};

        /**
         * @brief Seconds 'till next command.
        */
        float delay{};

        /**
         * @brief If nonzero, reset execution pointer to top of block (N times, -1 = infinite).
        */
        int repeat_count{};

        /**
         * @brief Display channel on which text message is sent.
        */
        int text_channel{};

        /**
         * @brief Bit field to specify what client message fields are valid.
        */
        int modifier_bit_field{};

        /**
         * @brief Next command (linked list).
        */
        SequenceCommandLine* next_command_line{};
    };

    /**
     * @brief Structure representing a single command (usually 1 line) from a .SEQ file entry.
    */
    struct SequenceEntry
    {
        /**
         * @brief Name of sequence file without .SEQ extension.
        */
        char* file_name{};

        /**
         * @brief Name of entry label in file.
        */
        char* entry_name{};

        /**
         * @brief Linked list of commands in entry.
        */
        SequenceCommandLine* first_command{};

        /**
         * @brief Next loaded entry.
        */
        SequenceEntry* next_entry{};

        /**
         * @brief Is entry retained over level transitions?
        */
        qboolean is_global{};
    };

    /**
     * @brief Structure representing a single sentence of a group from a .SEQ file entry.
     * Sentences are identical to entries in sentences.txt, but can be unique per level and are
     * loaded/unloaded with the level.
    */
    struct SentenceEntry
    {
        /**
         * @brief Sentence data (ie "We have hostiles").
        */
        char* data{};

        /**
         * @brief Next loaded entry.
        */
        SentenceEntry* next_entry{};

        /**
         * @brief Is entry retained over level transitions?
        */
        qboolean is_global{};

        /**
         * @brief This entry's position in the file.
        */
        unsigned int index{};
    };
}
