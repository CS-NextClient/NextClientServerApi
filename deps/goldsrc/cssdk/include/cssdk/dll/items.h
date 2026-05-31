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

namespace cssdk
{
    /**
     * @brief N/D
    */
    constexpr auto ITEM_ID_ANTIDOTE = 2;

    /**
     * @brief N/D
    */
    constexpr auto ITEM_ID_SECURITY = 3;

    enum class ItemRestType
    {
        /**
         * @brief When a player is buying items.
        */
        Buying = 0,

        /**
         * @brief When the player touches with a WeaponBox or armoury_entity.
        */
        Touched,

        /**
         * @brief When an entity game_player_equip gives item to player or default items on player spawn.
        */
        Equipped
    };

    enum class ItemId
    {
        /**
         * @brief N/D
        */
        None = -1,

        /**
         * @brief N/D
        */
        ShieldGun,

        /**
         * @brief N/D
        */
        P228,

        /**
         * @brief N/D
        */
        Glock,

        /**
         * @brief N/D
        */
        Scout,

        /**
         * @brief N/D
        */
        HeGrenade,

        /**
         * @brief N/D
        */
        Xm1014,

        /**
         * @brief N/D
        */
        C4,

        /**
         * @brief N/D
        */
        Mac10,

        /**
         * @brief N/D
        */
        Aug,

        /**
         * @brief N/D
        */
        SmokeGrenade,

        /**
         * @brief N/D
        */
        Elite,

        /**
         * @brief N/D
        */
        Fiveseven,

        /**
         * @brief N/D
        */
        Ump45,

        /**
         * @brief N/D
        */
        Sg550,

        /**
         * @brief N/D
        */
        Galil,

        /**
         * @brief N/D
        */
        Famas,

        /**
         * @brief N/D
        */
        Usp,

        /**
         * @brief N/D
        */
        Glock18,

        /**
         * @brief N/D
        */
        Awp,

        /**
         * @brief N/D
        */
        Mp5Navy,

        /**
         * @brief N/D
        */
        M249,

        /**
         * @brief N/D
        */
        M3,

        /**
         * @brief N/D
        */
        M4A1,

        /**
         * @brief N/D
        */
        Tmp,

        /**
         * @brief N/D
        */
        G3Sg1,

        /**
         * @brief N/D
        */
        FlashBang,

        /**
         * @brief N/D
        */
        Deagle,

        /**
         * @brief N/D
        */
        Sg552,

        /**
         * @brief N/D
        */
        Ak47,

        /**
         * @brief N/D
        */
        Knife,

        /**
         * @brief N/D
        */
        P90,

        /**
         * @brief N/D
        */
        NightVision,

        /**
         * @brief N/D
        */
        DefuseKit,

        /**
         * @brief N/D
        */
        Kevlar,

        /**
         * @brief N/D
        */
        Assault,

        /**
         * @brief N/D
        */
        LongJump,

        /**
         * @brief N/D
        */
        SodaCan,

        /**
         * @brief N/D
        */
        HealthKit,

        /**
         * @brief N/D
        */
        Antidote,

        /**
         * @brief N/D
        */
        Battery
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class Item : public EntityBase // NOLINT(clang-diagnostic-non-virtual-dtor)
    {
    public:
        /**
         * @brief N/D
        */
        void Spawn() override = 0;

        /**
         * @brief N/D
        */
        EntityBase* Respawn() override = 0;

        /**
         * @brief N/D
        */
        virtual qboolean MyTouch(PlayerBase* player) = 0;
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class WorldItem : public EntityBase // NOLINT(clang-diagnostic-non-virtual-dtor)
    {
    public:
        /**
         * @brief N/D
        */
        void Spawn() override = 0;

        /**
         * @brief N/D
        */
        void KeyValue(KeyValueData* data) override = 0;

        /**
         * @brief N/D
        */
        int type{};
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class ItemSuit : public Item // NOLINT(clang-diagnostic-non-virtual-dtor)
    {
    public:
        /**
         * @brief N/D
        */
        void Spawn() override = 0;

        /**
         * @brief N/D
        */
        void Precache() override = 0;

        /**
         * @brief N/D
        */
        qboolean MyTouch(PlayerBase* player) override = 0;
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class ItemBattery : public Item // NOLINT(clang-diagnostic-non-virtual-dtor)
    {
    public:
        /**
         * @brief N/D
        */
        void Spawn() override = 0;

        /**
         * @brief N/D
        */
        void Precache() override = 0;

        /**
         * @brief N/D
        */
        qboolean MyTouch(PlayerBase* player) override = 0;
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class ItemAntidote : public Item // NOLINT(clang-diagnostic-non-virtual-dtor)
    {
    public:
        /**
         * @brief N/D
        */
        void Spawn() override = 0;

        /**
         * @brief N/D
        */
        void Precache() override = 0;

        /**
         * @brief N/D
        */
        qboolean MyTouch(PlayerBase* player) override = 0;
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class ItemSecurity : public Item // NOLINT(clang-diagnostic-non-virtual-dtor)
    {
    public:
        /**
         * @brief N/D
        */
        void Spawn() override = 0;

        /**
         * @brief N/D
        */
        void Precache() override = 0;

        /**
         * @brief N/D
        */
        qboolean MyTouch(PlayerBase* player) override = 0;
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class ItemLongJump : public Item // NOLINT(clang-diagnostic-non-virtual-dtor)
    {
    public:
        /**
         * @brief N/D
        */
        void Spawn() override = 0;

        /**
         * @brief N/D
        */
        void Precache() override = 0;

        /**
         * @brief N/D
        */
        qboolean MyTouch(PlayerBase* player) override = 0;
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class ItemKevlar : public Item // NOLINT(clang-diagnostic-non-virtual-dtor)
    {
    public:
        /**
         * @brief N/D
        */
        void Spawn() override = 0;

        /**
         * @brief N/D
        */
        void Precache() override = 0;

        /**
         * @brief N/D
        */
        qboolean MyTouch(PlayerBase* player) override = 0;
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class ItemAssaultSuit : public Item // NOLINT(clang-diagnostic-non-virtual-dtor)
    {
    public:
        /**
         * @brief N/D
        */
        void Spawn() override = 0;

        /**
         * @brief N/D
        */
        void Precache() override = 0;

        /**
         * @brief N/D
        */
        qboolean MyTouch(PlayerBase* player) override = 0;
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class ItemThighPack : public Item // NOLINT(clang-diagnostic-non-virtual-dtor)
    {
    public:
        /**
         * @brief N/D
        */
        void Spawn() override = 0;

        /**
         * @brief N/D
        */
        void Precache() override = 0;

        /**
         * @brief N/D
        */
        qboolean MyTouch(PlayerBase* player) override = 0;
    };
}
