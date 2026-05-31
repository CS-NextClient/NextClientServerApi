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

namespace cssdk
{
    enum class Decal
    {
        /**
         * @brief N/D
        */
        None = -1,

        /**
         * @brief N/D
        */
        Gunshot1 = 0,

        /**
         * @brief N/D
        */
        Gunshot2,

        /**
         * @brief N/D
        */
        Gunshot3,

        /**
         * @brief N/D
        */
        Gunshot4,

        /**
         * @brief N/D
        */
        Gunshot5,

        /**
         * @brief N/D
        */
        Lambda1,

        /**
         * @brief N/D
        */
        Lambda2,

        /**
         * @brief N/D
        */
        Lambda3,

        /**
         * @brief N/D
        */
        Lambda4,

        /**
         * @brief N/D
        */
        Lambda5,

        /**
         * @brief N/D
        */
        Lambda6,

        /**
         * @brief N/D
        */
        Scorch1,

        /**
         * @brief N/D
        */
        Scorch2,

        /**
         * @brief N/D
        */
        Blood1,

        /**
         * @brief N/D
        */
        Blood2,

        /**
         * @brief N/D
        */
        Blood3,

        /**
         * @brief N/D
        */
        Blood4,

        /**
         * @brief N/D
        */
        Blood5,

        /**
         * @brief N/D
        */
        Blood6,

        /**
         * @brief N/D
        */
        YBlood1,

        /**
         * @brief N/D
        */
        YBlood2,

        /**
         * @brief N/D
        */
        YBlood3,

        /**
         * @brief N/D
        */
        YBlood4,

        /**
         * @brief N/D
        */
        YBlood5,

        /**
         * @brief N/D
        */
        YBlood6,

        /**
         * @brief N/D
        */
        GlassBreak1,

        /**
         * @brief N/D
        */
        GlassBreak2,

        /**
         * @brief N/D
        */
        GlassBreak3,

        /**
         * @brief N/D
        */
        BigShot1,

        /**
         * @brief N/D
        */
        BigShot2,

        /**
         * @brief N/D
        */
        BigShot3,

        /**
         * @brief N/D
        */
        BigShot4,

        /**
         * @brief N/D
        */
        BigShot5,

        /**
         * @brief N/D
        */
        Spit1,

        /**
         * @brief N/D
        */
        Spit2,

        /**
         * @brief Bulletproof glass decal.
        */
        BProof1,

        /**
         * @brief Gargantua stomp crack.
        */
        GargStomp1,

        /**
         * @brief Small scorch mark.
        */
        SmallScorch1,

        /**
         * @brief Small scorch mark.
        */
        SmallScorch2,

        /**
         * @brief Small scorch mark.
        */
        SmallScorch3,

        /**
         * @brief Big momma birth splatter.
        */
        MommaBirth,

        /**
         * @brief N/D
        */
        MommaSplat,

        /**
         * @brief N/D
        */
        End
    };

    struct DllDecalList
    {
        /**
         * @brief N/D
        */
        char* name{};

        /**
         * @brief N/D
        */
        int index{};
    };
}
