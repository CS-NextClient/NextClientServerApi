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

#include <cssdk/dll/cdll_dll.h>
#include <cssdk/dll/entity_base.h>
#include <cssdk/dll/monster_base.h>
#include <cssdk/dll/weapon_type.h>

namespace cssdk
{
    /**
     * @brief N/D
    */
    class PlayerBase;

#ifdef REGAMEDLL_API
    /**
     * @brief N/D
    */
    class CsPlayerItem;

    /**
     * @brief N/D
    */
    class CsPlayerWeapon;
#endif

    /**
     * @brief N/D
    */
    constexpr auto MAX_NORMAL_BATTERY = 100.0f;

    /**
     * @brief N/D
    */
    constexpr auto MAX_DIST_RELOAD_SOUND = 512.0f;

    /**
     * @brief N/D
    */
    constexpr auto MAX_WEAPONS = 32;

    /**
     * @brief N/D
    */
    constexpr auto ITEM_FLAG_SELECT_ON_EMPTY = 1 << 0;

    /**
     * @brief N/D
    */
    constexpr auto ITEM_FLAG_NO_AUTO_RELOAD = 1 << 1;

    /**
     * @brief N/D
    */
    constexpr auto ITEM_FLAG_NO_AUTO_SWITCH_EMPTY = 1 << 2;

    /**
     * @brief N/D
    */
    constexpr auto ITEM_FLAG_LIMIT_IN_WORLD = 1 << 3;

    /**
     * @brief A player can totally exhaust their ammo supply and lose this weapon.
    */
    constexpr auto ITEM_FLAG_EXHAUSTIBLE = 1 << 4;

    /**
     * @brief N/D
    */
    constexpr auto ITEM_FLAG_NO_FIRE_UNDER_WATER = 1 << 5;

    /**
     * @brief N/D
    */
    constexpr auto WEAPON_IS_ON_TARGET = 0x40;

    /**
     * @brief The maximum amount of ammo each weapon's clip can hold.
    */
    constexpr auto WEAPON_NO_CLIP = -1;

    /**
     * @brief N/D
    */
    constexpr auto LOUD_GUN_VOLUME = 1000;

    /**
     * @brief N/D
    */
    constexpr auto NORMAL_GUN_VOLUME = 600;

    /**
     * @brief N/D
    */
    constexpr auto QUIET_GUN_VOLUME = 200;

    /**
     * @brief N/D
    */
    constexpr auto BRIGHT_GUN_FLASH = 512;

    /**
     * @brief N/D
    */
    constexpr auto NORMAL_GUN_FLASH = 256;

    /**
     * @brief N/D
    */
    constexpr auto DIM_GUN_FLASH = 128;

    /**
     * @brief N/D
    */
    constexpr auto BIG_EXPLOSION_VOLUME = 2048;

    /**
     * @brief N/D
    */
    constexpr auto NORMAL_EXPLOSION_VOLUME = 1024;

    /**
     * @brief N/D
    */
    constexpr auto SMALL_EXPLOSION_VOLUME = 512;

    /**
     * @brief N/D
    */
    constexpr auto WEAPON_ACTIVITY_VOLUME = 64;

    /**
     * @brief Grenades flagged with this will be triggered when the owner calls \c detonate_satchel_charges.
    */
    constexpr auto SF_DETONATE = 1 << 0;

    enum class ArmorType
    {
        /**
         * @brief No armor.
        */
        None = 0,

        /**
         * @brief Body vest only.
        */
        Kevlar,

        /**
         * @brief Vest and helmet.
        */
        VestHelm
    };

    enum class ArmouryItemPack
    {
        /**
         * @brief N/D
        */
        Mp5Navy = 0,

        /**
         * @brief N/D
        */
        Tmp,

        /**
         * @brief N/D
        */
        P90,

        /**
         * @brief N/D
        */
        Mac10,

        /**
         * @brief N/D
        */
        Ak47,

        /**
         * @brief N/D
        */
        Sg552,

        /**
         * @brief N/D
        */
        M4A1,

        /**
         * @brief N/D
        */
        Aug,

        /**
         * @brief N/D
        */
        Scout,

        /**
         * @brief N/D
        */
        G3Sg1,

        /**
         * @brief N/D
        */
        Awp,

        /**
         * @brief N/D
        */
        M3,

        /**
         * @brief N/D
        */
        Xm1014,

        /**
         * @brief N/D
        */
        M249,

        /**
         * @brief N/D
        */
        FlashBang,

        /**
         * @brief N/D
        */
        HeGrenade,

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
        SmokeGrenade,

        /**
         * @brief N/D
        */
        Shield,

        /**
         * @brief N/D
        */
        Famas,

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
        Ump45,

        /**
         * @brief N/D
        */
        Glock18,

        /**
         * @brief N/D
        */
        Usp,

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
        P228,

        /**
         * @brief N/D
        */
        Deagle
    };

    struct ItemInfo
    {
        /**
         * @brief N/D
        */
        int slot{};

        /**
         * @brief N/D
        */
        int position{};

        /**
         * @brief N/D
        */
        const char* ammo1{};

        /**
         * @brief N/D
        */
        int max_ammo1{};

        /**
         * @brief N/D
        */
        const char* ammo2{};

        /**
         * @brief N/D
        */
        int max_ammo2{};

        /**
         * @brief N/D
        */
        const char* name{};

        /**
         * @brief N/D
        */
        int max_clip{};

        /**
         * @brief N/D
        */
        WeaponId id{};

        /**
         * @brief N/D
        */
        int flags{};

        /**
         * @brief N/D
        */
        int weight{};
    };

    struct AmmoInfo
    {
        /**
         * @brief N/D
        */
        const char* name{};

        /**
         * @brief N/D
        */
        int id{};
    };

    struct MultiDamage
    {
        /**
         * @brief N/D
        */
        EntityBase* entity{};

        /**
         * @brief N/D
        */
        float amount{};

        /**
         * @brief N/D
        */
        int type{};
    };

    //
    // Armoury.
    //

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class Armoury : public EntityBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        void Restart() override = 0;

        /**
         * @brief N/D
        */
        void KeyValue(KeyValueData* data) override = 0;

#ifdef REGAMEDLL_FIXES
        /**
         * @brief Setup the object->object collision box
         * (\c EntityVars->min_size / \c EntityVars->max_size is the \c object->world collision box).
        */
        void SetObjectCollisionBox() override = 0;
#endif
        /**
         * @brief N/D
        */
        ArmouryItemPack item{};

        /**
         * @brief N/D
        */
        int count{};

        /**
         * @brief N/D
        */
        int initial_count{};

        /**
         * @brief N/D
        */
        bool already_counted{};
    };

    //
    // Grenade.
    //

    enum class SatchelCode
    {
        Detonate = 0,
        Release
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class Grenade : public MonsterBase // NOLINT(clang-diagnostic-non-virtual-dtor)
    {
    public:
        /**
         * @brief N/D
        */
        void Spawn() override = 0;

        /**
         * @brief N/D
        */
        qboolean SaveData(Save& save) override = 0;

        /**
         * @brief N/D
        */
        qboolean RestoreData(Restore& restore) override = 0;

        /**
         * @brief N/D
        */
        int ObjectCaps() override = 0;

        /**
         * @brief N/D
        */
        void Killed(EntityVars* attacker, int gib) override = 0;

        /**
         * @brief N/D
        */
        int BloodColor() override = 0;

        /**
         * @brief N/D
        */
        void Use(EntityBase* activator, EntityBase* caller, UseType type, float value) override = 0;

        /**
         * @brief N/D
        */
        virtual void BounceSound() = 0;

        /**
         * @brief N/D
        */
        bool start_defuse{};

        /**
         * @brief N/D
        */
        bool is_c4{};

        /**
         * @brief N/D
        */
        EntityHandle<PlayerBase> bomb_defuser{};

        /**
         * @brief N/D
        */
        float defuse_count_down{};

        /**
         * @brief N/D
        */
        float c4_blow{};

        /**
         * @brief N/D
        */
        float next_freq_interval{};

        /**
         * @brief N/D
        */
        float next_beep{};

        /**
         * @brief N/D
        */
        float next_freq{};

        /**
         * @brief N/D
        */
        char* beep_name{};

        /**
         * @brief N/D
        */
        float attenuation{};

        /**
         * @brief N/D
        */
        float next_blink{};

        /**
         * @brief N/D
        */
        float next_defuse{};

        /**
         * @brief N/D
        */
        bool just_blew{};

        /**
         * @brief N/D
        */
        TeamName team{};

        /**
         * @brief N/D
        */
        int cur_wave{};

        /**
         * @brief N/D
        */
        Edict* cur_bomb_target{};

        /**
         * @brief N/D
        */
        int sg_smoke{};

        /**
         * @brief N/D
        */
        int angle{};

        /**
         * @brief N/D
        */
        unsigned short event{};

        /**
         * @brief N/D
        */
        bool light_smoke{};

        /**
         * @brief N/D
        */
        bool detonated{};

        /**
         * @brief N/D
        */
        Vector smoke_detonate{};

        /**
         * @brief N/D
        */
        int bounce_count{};

        /**
         * @brief N/D
        */
        qboolean registered_sound{};
    };

    //
    // Player item base.
    //

    /**
     * @brief Items that the player has in their inventory that they can use.
    */
    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class PlayerItemBase : public AnimatingBase // NOLINT(clang-diagnostic-non-virtual-dtor)
    {
    public:
        /**
         * @brief N/D
        */
        qboolean SaveData(Save& save) override = 0;

        /**
         * @brief N/D
        */
        qboolean RestoreData(Restore& restore) override = 0;

        /**
         * @brief N/D
        */
        void SetObjectCollisionBox() override = 0;

        /**
         * @brief N/D
        */
        EntityBase* Respawn() override = 0;

        /**
         * @brief Return true if the item you want the item added to the player inventory.
        */
        virtual qboolean AddToPlayer(PlayerBase* player) = 0;

        /**
         * @brief Return true if you want your duplicate removed from world.
        */
        virtual qboolean AddDuplicate(PlayerItemBase* item) = 0;

        /**
         * @brief Returns false if struct not filled out.
        */
        virtual qboolean GetItemInfo(ItemInfo* info) = 0;

        /**
         * @brief N/D
        */
        virtual qboolean CanDeploy() = 0;

        /**
         * @brief N/D
        */
        virtual qboolean CanDrop() = 0;

        /**
         * @brief N/D
        */
        virtual qboolean Deploy() = 0;

        /**
         * @brief N/D
        */
        virtual qboolean IsWeapon() = 0;

        /**
         * @brief Can this weapon be put away right now?.
        */
        virtual qboolean CanHolster() = 0;

        /**
         * @brief N/D
        */
        virtual void Holster(qboolean skip_local = false) = 0;

        /**
         * @brief N/D
        */
        virtual void UpdateItemInfo() = 0;

        /**
         * @brief Called each frame by the player \c pre_think.
        */
        virtual void ItemPreFrame() = 0;

        /**
         * @brief Called each frame by the player \c post_think.
        */
        virtual void ItemPostFrame() = 0;

        /**
         * @brief N/D
        */
        virtual void Drop() = 0;

        /**
         * @brief N/D
        */
        virtual void Kill() = 0;

        /**
         * @brief N/D
        */
        virtual void AttachToPlayer(PlayerBase* player) = 0;

        /**
         * @brief N/D
        */
        virtual int PrimaryAmmoIndex() = 0;

        /**
         * @brief N/D
        */
        virtual int SecondaryAmmoIndex() = 0;

        /**
         * @brief N/D
        */
        virtual int UpdateClientData(PlayerBase* player) = 0;

        /**
         * @brief N/D
        */
        virtual PlayerItemBase* GetWeaponPtr() = 0;

        /**
         * @brief N/D
        */
        virtual float GetMaxSpeed() = 0;

        /**
         * @brief N/D
        */
        virtual InventorySlot GetItemSlot() = 0;

        /**
         * @brief N/D
        */
        PlayerBase* player{};

        /**
         * @brief N/D
        */
        PlayerItemBase* next{};

        /**
         * @brief N/D
        */
        WeaponId id{};

#ifdef REGAMEDLL_API
        /**
         * @brief N/D
        */
        [[nodiscard]] CsPlayerItem* GetCsPlayerItem() const
        {
            return reinterpret_cast<CsPlayerItem*>(this->entity);
        }
#endif
    };

    //
    // Player weapon base.
    //

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class PlayerWeaponBase : public PlayerItemBase // NOLINT(clang-diagnostic-non-virtual-dtor)
    {
    public:
        /**
         * @brief N/D
        */
        void Spawn() override = 0;

        /**
         * @brief N/D
        */
        qboolean SaveData(Save& save) override = 0;

        /**
         * @brief N/D
        */
        qboolean RestoreData(Restore& restore) override = 0;

        /**
         * @brief N/D
        */
        qboolean AddToPlayer(PlayerBase* player) override = 0;

        /**
         * @brief N/D
        */
        qboolean AddDuplicate(PlayerItemBase* item) override = 0;

        /**
         * @brief N/D
        */
        qboolean CanDeploy() override = 0;

        /**
         * @brief N/D
        */
        qboolean IsWeapon() override = 0;

        /**
         * @brief N/D
        */
        void Holster(qboolean skip_local = false) override = 0;

        /**
         * @brief N/D
        */
        void UpdateItemInfo() override = 0;

        /**
         * @brief N/D
        */
        void ItemPostFrame() override = 0;

        /**
         * @brief N/D
        */
        int PrimaryAmmoIndex() override = 0;

        /**
         * @brief N/D
        */
        int SecondaryAmmoIndex() override = 0;

        /**
         * @brief N/D
        */
        int UpdateClientData(PlayerBase* player) override = 0;

        /**
         * @brief N/D
        */
        PlayerItemBase* GetWeaponPtr() override = 0;

        /**
         * @brief N/D
        */
        virtual int ExtractAmmo(PlayerWeaponBase* weapon) = 0;

        /**
         * @brief N/D
        */
        virtual int ExtractClipAmmo(PlayerWeaponBase* weapon) = 0;

        /**
         * @brief N/D
        */
        virtual int AddWeapon() = 0;

        /**
         * @brief N/D
        */
        virtual qboolean PlayEmptySound() = 0;

        /**
         * @brief N/D
        */
        virtual void ResetEmptySound() = 0;

        /**
         * @brief N/D
        */
        virtual void SendWeaponAnim(int anim, qboolean skip_local = false) = 0;

        /**
         * @brief N/D
        */
        virtual qboolean IsUseable() = 0;

        /**
         * @brief N/D
        */
        virtual void PrimaryAttack() = 0;

        /**
         * @brief N/D
        */
        virtual void SecondaryAttack() = 0;

        /**
         * @brief N/D
        */
        virtual void Reload() = 0;

        /**
         * @brief N/D
        */
        virtual void WeaponIdle() = 0;

        /**
         * @brief N/D
        */
        virtual void RetireWeapon() = 0;

        /**
         * @brief N/D
        */
        virtual qboolean ShouldWeaponIdle() = 0;

        /**
         * @brief N/D
        */
        virtual qboolean UseDecrement() = 0;

        /**
         * @brief N/D
        */
        qboolean can_play_empty_sound{};

        /**
         * @brief N/D
        */
        qboolean fire_on_empty{};

        /**
         * @brief Soonest time ItemPostFrame will call \c primary_attack.
        */
        float next_primary_attack{};

        /**
         * @brief Soonest time ItemPostFrame will call \c secondary_attack.
        */
        float next_secondary_attack{};

        /**
         * @brief Soonest time ItemPostFrame will call \c weapon_idle.
        */
        float time_weapon_idle{};

        /**
         * @brief Primary ammo index into players \c rg_ammo[].
        */
        int primary_ammo_type{};

        /**
         * @brief Secondary ammo index into players \c rg_ammo[].
        */
        int secondary_ammo_type{};

        /**
         * @brief Number of shots left in the primary weapon clip, -1 it not used.
        */
        int clip{};

        /**
         * @brief The last version of \c clip sent to hud dll.
        */
        int client_clip{};

        /**
         * @brief The last version of the weapon state sent to hud dll (is current weapon, is on target).
        */
        int client_weapon_state{};

        /**
         * @brief Are we in the middle of a reload.
        */
        qboolean in_reload{};

        /**
         * @brief Are we in the middle of a reload for the shotguns.
        */
        qboolean in_special_reload{};

        /**
         * @brief How much ammo you get when you pick up this weapon as placed by a level designer.
        */
        int default_ammo{};

        /**
         * @brief N/D
        */
        int shell_id{};

        /**
         * @brief N/D
        */
        float max_speed{};

        /**
         * @brief N/D
        */
        bool delay_fire{};

        /**
         * @brief N/D
        */
        qboolean direction{};

        /**
         * @brief N/D
        */
        bool secondary_silencer_on{};

        /**
         * @brief N/D
        */
        float accuracy{};

        /**
         * @brief N/D
        */
        float last_fire{};

        /**
         * @brief N/D
        */
        int shots_fired{};

        /**
         * @brief N/D
        */
        Vector aiming{};

        /**
         * @brief N/D
        */
        Strind model_name{};

        /**
         * @brief Time to shoot the remaining bullets of the Glock18 burst fire.
        */
        float glock18_shoot{};

        /**
         * @brief Used to keep track of the shots fired during the Glock18 burst fire mode.
        */
        int glock18_shots_fired{};

        /**
         * @brief Time to shoot the remaining bullets of the Famas burst fire.
        */
        float famas_shoot{};

        /**
         * @brief Used to keep track of the shots fired during the Famas burst fire mode.
        */
        int famas_shots_fired{};

        /**
         * @brief N/D
        */
        float burst_spread{};

        /**
         * @brief N/D
        */
        int weapon_state{};

        /**
         * @brief N/D
        */
        float next_reload{};

        /**
         * @brief N/D
        */
        float decrease_shots_fired{};

        /**
         * @brief N/D
        */
        unsigned short event_fire_glock18{};

        /**
         * @brief N/D
        */
        unsigned short event_fire_famas{};

        /**
         * @brief N/D
        */
        float prev_primary_attack{};

        /**
         * @brief N/D
        */
        float last_fire_time{};

#ifdef REGAMEDLL_API
        /**
         * @brief N/D
        */
        [[nodiscard]] CsPlayerWeapon* GetCsPlayerWeapon() const
        {
            return reinterpret_cast<CsPlayerWeapon*>(this->entity);
        }
#endif
    };

    //
    // Weapon box.
    //

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class WeaponBox : public EntityBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        void KeyValue(KeyValueData* data) override = 0;

        /**
         * @brief N/D
        */
        int SaveData(Save& save) override = 0;

        /**
         * @brief N/D
        */
        int RestoreData(Restore& restore) override = 0;

        /**
         * @brief N/D
        */
        void SetObjectCollisionBox() override = 0;

        /**
         * @brief N/D
        */
        void Touch(EntityBase* other) override = 0;

        /**
         * @brief N/D
        */
        PlayerItemBase* player_items[MAX_ITEM_TYPES]{};

        /**
         * @brief N/D
        */
        Strind ammo_names[MAX_AMMO_SLOTS]{};

        /**
         * @brief N/D
        */
        int ammo_count[MAX_AMMO_SLOTS]{};

        /**
         * @brief N/D
        */
        int ammo_types{};

        /**
         * @brief N/D
        */
        bool is_bomb{};
    };

    //
    // USP.
    //

    /**
     * @brief N/D
    */
    constexpr auto USP_MAX_SPEED = 250.0f;

    /**
     * @brief N/D
    */
    constexpr auto USP_DAMAGE = 34.0f;

    /**
     * @brief N/D
    */
    constexpr auto USP_DAMAGE_SIL = 30.0f;

    /**
     * @brief N/D
    */
    constexpr auto USP_RANGE_MODIFER = 0.79f;

    /**
     * @brief N/D
    */
    constexpr auto USP_RELOAD_TIME = 2.7f;

#ifdef REGAMEDLL_FIXES
    /**
     * @brief N/D
    */
    constexpr auto USP_ADJUST_SIL_TIME = 3.13f;
#else
    /**
     * @brief N/D
    */
    constexpr auto USP_ADJUST_SIL_TIME = 3.0f;
#endif

    enum class UspAnimSeq
    {
        /**
         * @brief N/D
        */
        Idle = 0,

        /**
         * @brief N/D
        */
        Shoot1,

        /**
         * @brief N/D
        */
        Shoot2,

        /**
         * @brief N/D
        */
        Shoot3,

        /**
         * @brief N/D
        */
        ShootEmpty,

        /**
         * @brief N/D
        */
        Reload,

        /**
         * @brief N/D
        */
        Draw,

        /**
         * @brief N/D
        */
        AttachSilencer,

        /**
         * @brief N/D
        */
        UnsilIdle,

        /**
         * @brief N/D
        */
        UnsilShoot1,

        /**
         * @brief N/D
        */
        UnsilShoot2,

        /**
         * @brief N/D
        */
        UnsilShoot3,

        /**
         * @brief N/D
        */
        UnsilShootEmpty,

        /**
         * @brief N/D
        */
        UnsilReload,

        /**
         * @brief N/D
        */
        UnsilDraw,

        /**
         * @brief N/D
        */
        DetachSilencer
    };

    enum class UspShieldAnimSeq
    {
        /**
         * @brief N/D
        */
        ShieldIdle = 0,

        /**
         * @brief N/D
        */
        ShieldShoot1,

        /**
         * @brief N/D
        */
        ShieldShoot2,

        /**
         * @brief N/D
        */
        ShieldShootEmpty,

        /**
         * @brief N/D
        */
        ShieldReload,

        /**
         * @brief N/D
        */
        ShieldDraw,

        /**
         * @brief N/D
        */
        ShieldUpIdle,

        /**
         * @brief N/D
        */
        ShieldUp,

        /**
         * @brief N/D
        */
        ShieldDown
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class Usp : public PlayerWeaponBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        qboolean GetItemInfo(ItemInfo* info) override = 0;

        /**
         * @brief N/D
        */
        qboolean Deploy() override = 0;

        /**
         * @brief N/D
        */
        float GetMaxSpeed() override = 0;

        /**
         * @brief N/D
        */
        InventorySlot GetItemSlot() override = 0;

        /**
         * @brief N/D
        */
        void PrimaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void SecondaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void Reload() override = 0;

        /**
         * @brief N/D
        */
        void WeaponIdle() override = 0;

        /**
         * @brief N/D
        */
        qboolean UseDecrement() override = 0;

        /**
         * @brief N/D
        */
        virtual qboolean IsPistol() = 0;

        /**
         * @brief N/D
        */
        int shell_model{};

        // private:
        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        unsigned short event_fire_{};

#ifdef REGAMEDLL_API
        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        float base_damage_sil_{};
#endif
    };

    //
    // MP5Navy.
    //

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto MP5N_MAX_SPEED = 250.0f;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto MP5N_DAMAGE = 26.0f;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto MP5N_RANGE_MODIFER = 0.84f;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto MP5N_RELOAD_TIME = 2.63f;

    enum class Mp5NavyAnimSeq
    {
        /**
         * @brief N/D
        */
        Idle1,

        /**
         * @brief N/D
        */
        Reload,

        /**
         * @brief N/D
        */
        Draw,

        /**
         * @brief N/D
        */
        Shoot1,

        /**
         * @brief N/D
        */
        Shoot2,

        /**
         * @brief N/D
        */
        Shoot3
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class Mp5Navy : public PlayerWeaponBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        qboolean GetItemInfo(ItemInfo* info) override = 0;

        /**
         * @brief N/D
        */
        qboolean Deploy() override = 0;

        /**
         * @brief N/D
        */
        float GetMaxSpeed() override = 0;

        /**
         * @brief N/D
        */
        InventorySlot GetItemSlot() override = 0;

        /**
         * @brief N/D
        */
        void PrimaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void Reload() override = 0;

        /**
         * @brief N/D
        */
        void WeaponIdle() override = 0;

        /**
         * @brief N/D
        */
        qboolean UseDecrement() override = 0;

        /**
         * @brief N/D
        */
        int shell_model{};

        /**
         * @brief N/D
        */
        qboolean shell_on{};

        // private:
        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        unsigned short event_fire_{};
    };

    //
    // SG552.
    //

    /**
     * @brief N/D
    */
    constexpr auto SG552_MAX_SPEED = 235.0f;

    /**
     * @brief N/D
    */
    constexpr auto SG552_MAX_SPEED_ZOOM = 200.0f;

    /**
     * @brief N/D
    */
    constexpr auto SG552_DAMAGE = 33.0f;

    /**
     * @brief N/D
    */
    constexpr auto SG552_RANGE_MODIFER = 0.955f;

    /**
     * @brief N/D
    */
    constexpr auto SG552_RELOAD_TIME = 3.0f;

    enum class Sg552AnimSeq
    {
        /**
         * @brief N/D
        */
        Idle1,

        /**
         * @brief N/D
        */
        Reload,

        /**
         * @brief N/D
        */
        Draw,

        /**
         * @brief N/D
        */
        Shoot1,

        /**
         * @brief N/D
        */
        Shoot2,

        /**
         * @brief N/D
        */
        Shoot3
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class Sg552 : public PlayerWeaponBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        qboolean GetItemInfo(ItemInfo* info) override = 0;

        /**
         * @brief N/D
        */
        qboolean Deploy() override = 0;

        /**
         * @brief N/D
        */
        float GetMaxSpeed() override = 0;

        /**
         * @brief N/D
        */
        InventorySlot GetItemSlot() override = 0;

        /**
         * @brief N/D
        */
        void PrimaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void SecondaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void Reload() override = 0;

        /**
         * @brief N/D
        */
        void WeaponIdle() override = 0;

        /**
         * @brief N/D
        */
        qboolean UseDecrement() override = 0;

        /**
         * @brief N/D
        */
        int shell_model{};

        /**
         * @brief N/D
        */
        qboolean shell_on{};

        // private:
        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        unsigned short event_fire_{};
    };

    //
    // AK47.
    //

    /**
     * @brief N/D
    */
    constexpr auto AK47_MAX_SPEED = 221.0f;

    /**
     * @brief N/D
    */
    constexpr auto AK47_DAMAGE = 36.0f;

    /**
     * @brief N/D
    */
    constexpr auto AK47_RANGE_MODIFER = 0.98f;

    /**
     * @brief N/D
    */
    constexpr auto AK47_RELOAD_TIME = 2.45f;

    enum class Ak47AnimSeq
    {
        /**
         * @brief N/D
        */
        Idle1,

        /**
         * @brief N/D
        */
        Reload,

        /**
         * @brief N/D
        */
        Draw,

        /**
         * @brief N/D
        */
        Shoot1,

        /**
         * @brief N/D
        */
        Shoot2,

        /**
         * @brief N/D
        */
        Shoot3
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class Ak47 : public PlayerWeaponBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        qboolean GetItemInfo(ItemInfo* info) override = 0;

        /**
         * @brief N/D
        */
        qboolean Deploy() override = 0;

        /**
         * @brief N/D
        */
        float GetMaxSpeed() override = 0;

        /**
         * @brief N/D
        */
        InventorySlot GetItemSlot() override = 0;

        /**
         * @brief N/D
        */
        void PrimaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void SecondaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void Reload() override = 0;

        /**
         * @brief N/D
        */
        void WeaponIdle() override = 0;

        /**
         * @brief N/D
        */
        qboolean UseDecrement() override = 0;

        /**
         * @brief N/D
        */
        int shell_model{};

        /**
         * @brief N/D
        */
        qboolean shell_on{};

        // private:
        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        unsigned short event_fire_{};
    };

    //
    // AUG.
    //

    /**
     * @brief N/D
    */
    constexpr auto AUG_MAX_SPEED = 240.0f;

    /**
     * @brief N/D
    */
    constexpr auto AUG_DAMAGE = 32.0f;

    /**
     * @brief N/D
    */
    constexpr auto AUG_RANGE_MODIFER = 0.96f;

    /**
     * @brief N/D
    */
    constexpr auto AUG_RELOAD_TIME = 3.3f;

    enum class AugAnimSeq
    {
        /**
         * @brief N/D
        */
        Idle1,

        /**
         * @brief N/D
        */
        Reload,

        /**
         * @brief N/D
        */
        Draw,

        /**
         * @brief N/D
        */
        Shoot1,

        /**
         * @brief N/D
        */
        Shoot2,

        /**
         * @brief N/D
        */
        Shoot3
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class Aug : public PlayerWeaponBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        qboolean GetItemInfo(ItemInfo* info) override = 0;

        /**
         * @brief N/D
        */
        qboolean Deploy() override = 0;

        /**
         * @brief N/D
        */
        float GetMaxSpeed() override = 0;

        /**
         * @brief N/D
        */
        InventorySlot GetItemSlot() override = 0;

        /**
         * @brief N/D
        */
        void PrimaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void SecondaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void Reload() override = 0;

        /**
         * @brief N/D
        */
        void WeaponIdle() override = 0;

        /**
         * @brief N/D
        */
        qboolean UseDecrement() override = 0;

        /**
         * @brief N/D
        */
        int shell_model{};

        /**
         * @brief N/D
        */
        qboolean shell_on{};

        // private:
        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        unsigned short event_fire_{};
    };

    //
    // AWP.
    //

    /**
     * @brief N/D
    */
    constexpr auto AWP_MAX_SPEED = 210.0f;

    /**
     * @brief N/D
    */
    constexpr auto AWP_MAX_SPEED_ZOOM = 150.0f;

    /**
     * @brief N/D
    */
    constexpr auto AWP_DAMAGE = 115.0f;

    /**
     * @brief N/D
    */
    constexpr auto AWP_RANGE_MODIFER = 0.99f;

    /**
     * @brief N/D
    */
    constexpr auto AWP_RELOAD_TIME = 2.5f;

    enum class AwpAnimSeq
    {
        /**
         * @brief N/D
        */
        Idle,

        /**
         * @brief N/D
        */
        Shoot,

        /**
         * @brief N/D
        */
        Shoot2,

        /**
         * @brief N/D
        */
        Shoot3,

        /**
         * @brief N/D
        */
        Reload,

        /**
         * @brief N/D
        */
        Draw
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class Awp : public PlayerWeaponBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        qboolean GetItemInfo(ItemInfo* info) override = 0;

        /**
         * @brief N/D
        */
        qboolean Deploy() override = 0;

        /**
         * @brief N/D
        */
        float GetMaxSpeed() override = 0;

        /**
         * @brief N/D
        */
        InventorySlot GetItemSlot() override = 0;

        /**
         * @brief N/D
        */
        void PrimaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void SecondaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void Reload() override = 0;

        /**
         * @brief N/D
        */
        void WeaponIdle() override = 0;

        /**
         * @brief N/D
        */
        qboolean UseDecrement() override = 0;

        /**
         * @brief N/D
        */
        int shell_model{};

        // private:
        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        unsigned short event_fire_{};
    };

    //
    // C4.
    //

    /**
     * @brief If the bomb was dropped due to voluntary dropping or death/disconnect.
    */
    constexpr auto BOMB_FLAG_DROPPED = 0;

    /**
     * @brief If the bomb has been planted will also trigger the round timer to hide
     * will also show where the dropped bomb on the Terrorist team's radar.
    */
    constexpr auto BOMB_FLAG_PLANTED = 1;

    /**
     * @brief N/D
    */
    constexpr auto C4_MAX_SPEED = 250.0f;

    /**
     * @brief N/D
    */
    constexpr auto C4_ARMING_ON_TIME = 3.0f;

    enum class C4AnimSeq
    {
        /**
         * @brief N/D
        */
        Idle1,

        /**
         * @brief N/D
        */
        Draw,

        /**
         * @brief N/D
        */
        Drop,

        /**
         * @brief N/D
        */
        Arm
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class C4 : public PlayerWeaponBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        void KeyValue(KeyValueData* data) override = 0;

        /**
         * @brief N/D
        */
        void Use(EntityBase* activator, EntityBase* caller, UseType type, float value) override = 0;

        /**
         * @brief N/D
        */
        qboolean GetItemInfo(ItemInfo* info) override = 0;

        /**
         * @brief N/D
        */
        qboolean Deploy() override = 0;

        /**
         * @brief N/D
        */
        void Holster(qboolean skip_local) override = 0;

        /**
         * @brief N/D
        */
        float GetMaxSpeed() override = 0;

        /**
         * @brief N/D
        */
        InventorySlot GetItemSlot() override = 0;

        /**
         * @brief N/D
        */
        void PrimaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void WeaponIdle() override = 0;

        /**
         * @brief N/D
        */
        qboolean UseDecrement() override = 0;

        /**
         * @brief N/D
        */
        bool started_arming{};

        /**
         * @brief N/D
        */
        bool bomb_placed_animation{};

        /**
         * @brief N/D
        */
        float armed_time{};

        // private:
        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        bool has_shield_{};
    };

    //
    // Deagle.
    //

    /**
     * @brief N/D
    */
    constexpr auto DEAGLE_MAX_SPEED = 250.0f;

    /**
     * @brief N/D
    */
    constexpr auto DEAGLE_DAMAGE = 54.0f;

    /**
     * @brief N/D
    */
    constexpr auto DEAGLE_RANGE_MODIFER = 0.81f;

    /**
     * @brief N/D
    */
    constexpr auto DEAGLE_RELOAD_TIME = 2.2f;

    enum class DeagleAnimSeq
    {
        /**
         * @brief N/D
        */
        Idle1,

        /**
         * @brief N/D
        */
        Shoot1,

        /**
         * @brief N/D
        */
        Shoot2,

        /**
         * @brief N/D
        */
        ShootEmpty,

        /**
         * @brief N/D
        */
        Reload,

        /**
         * @brief N/D
        */
        Draw
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class Deagle : public PlayerWeaponBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        qboolean GetItemInfo(ItemInfo* info) override = 0;

        /**
         * @brief N/D
        */
        qboolean Deploy() override = 0;

        /**
         * @brief N/D
        */
        float GetMaxSpeed() override = 0;

        /**
         * @brief N/D
        */
        InventorySlot GetItemSlot() override = 0;

        /**
         * @brief N/D
        */
        void PrimaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void SecondaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void Reload() override = 0;

        /**
         * @brief N/D
        */
        void WeaponIdle() override = 0;

        /**
         * @brief N/D
        */
        qboolean UseDecrement() override = 0;

        /**
         * @brief N/D
        */
        virtual qboolean IsPistol() = 0;

        /**
         * @brief N/D
        */
        int shell_model{};

        // private:
        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        unsigned short event_fire_{};
    };

    //
    // Flash bang.
    //

    /**
     * @brief N/D
    */
    constexpr auto FLASH_BANG_MAX_SPEED = 250.0f;

    /**
     * @brief N/D
    */
    constexpr auto FLASH_BANG_MAX_SPEED_SHIELD = 180.0f;

    enum class FlashBangAnimSeq
    {
        /**
         * @brief N/D
        */
        Idle,

        /**
         * @brief N/D
        */
        PullPin,

        /**
         * @brief N/D
        */
        ThrowGrenade,

        /**
         * @brief N/D
        */
        Draw
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class FlashBang : public PlayerWeaponBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        qboolean GetItemInfo(ItemInfo* info) override = 0;

        /**
         * @brief N/D
        */
        qboolean CanDeploy() override = 0;

        /**
         * @brief N/D
        */
        qboolean CanDrop() override = 0;

        /**
         * @brief N/D
        */
        qboolean Deploy() override = 0;

        /**
         * @brief N/D
        */
        void Holster(qboolean skip_local) override = 0;

        /**
         * @brief N/D
        */
        float GetMaxSpeed() override = 0;

        /**
         * @brief N/D
        */
        InventorySlot GetItemSlot() override = 0;

        /**
         * @brief N/D
        */
        void PrimaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void SecondaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void WeaponIdle() override = 0;

        /**
         * @brief N/D
        */
        qboolean UseDecrement() override = 0;

        /**
         * @brief N/D
        */
        virtual qboolean IsPistol() = 0;
    };

    //
    // G3SG1.
    //

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto G3SG1_MAX_SPEED = 210.0f;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto G3SG1_MAX_SPEED_ZOOM = 150.0f;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto G3SG1_DAMAGE = 80.0f;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto G3SG1_RANGE_MODIFER = 0.98f;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto G3SG1_RELOAD_TIME = 3.5f;

    enum class G3Sg1AnimSeq
    {
        /**
         * @brief N/D
        */
        Idle,

        /**
         * @brief N/D
        */
        Shoot,

        /**
         * @brief N/D
        */
        Shoot2,

        /**
         * @brief N/D
        */
        Reload,

        /**
         * @brief N/D
        */
        Draw
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class G3Sg1 : public PlayerWeaponBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        qboolean GetItemInfo(ItemInfo* info) override = 0;

        /**
         * @brief N/D
        */
        qboolean Deploy() override = 0;

        /**
         * @brief N/D
        */
        float GetMaxSpeed() override = 0;

        /**
         * @brief N/D
        */
        InventorySlot GetItemSlot() override = 0;

        /**
         * @brief N/D
        */
        void PrimaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void SecondaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void Reload() override = 0;

        /**
         * @brief N/D
        */
        void WeaponIdle() override = 0;

        /**
         * @brief N/D
        */
        qboolean UseDecrement() override = 0;

        /**
         * @brief N/D
        */
        int shell_model{};

        // private:
        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        unsigned short event_fire_{};
    };

    //
    // Glock18.
    //

    /**
     * @brief N/D
    */
    constexpr auto GLOCK18_MAX_SPEED = 250.0f;

    /**
     * @brief N/D
    */
    constexpr auto GLOCK18_DAMAGE = 25.0f;

    /**
     * @brief N/D
    */
    constexpr auto GLOCK18_RANGE_MODIFER = 0.75f;

    /**
     * @brief N/D
    */
    constexpr auto GLOCK18_RELOAD_TIME = 2.2f;

    enum class Glock18AnimSeq
    {
        /**
         * @brief N/D
        */
        Idle1,

        /**
         * @brief N/D
        */
        Idle2,

        /**
         * @brief N/D
        */
        Idle3,

        /**
         * @brief N/D
        */
        Shoot,

        /**
         * @brief N/D
        */
        Shoot2,

        /**
         * @brief N/D
        */
        Shoot3,

        /**
         * @brief N/D
        */
        ShootEmpty,

        /**
         * @brief N/D
        */
        Reload,

        /**
         * @brief N/D
        */
        Draw,

        /**
         * @brief N/D
        */
        Holster,

        /**
         * @brief N/D
        */
        AddSilencer,

        /**
         * @brief N/D
        */
        Draw2,

        /**
         * @brief N/D
        */
        Reload2
    };

    enum class Glock18ShieldAnimSeq
    {
        /**
         * @brief N/D
        */
        Idle1,

        /**
         * @brief N/D
        */
        Shoot,

        /**
         * @brief N/D
        */
        Shoot2,

        /**
         * @brief N/D
        */
        ShootEmpty,

        /**
         * @brief N/D
        */
        Reload,

        /**
         * @brief N/D
        */
        Draw,

        /**
         * @brief N/D
        */
        Idle,

        /**
         * @brief N/D
        */
        Up,

        /**
         * @brief N/D
        */
        Down
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class Glock18 : public PlayerWeaponBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        qboolean GetItemInfo(ItemInfo* info) override = 0;

        /**
         * @brief N/D
        */
        qboolean Deploy() override = 0;

        /**
         * @brief N/D
        */
        float GetMaxSpeed() override = 0;

        /**
         * @brief N/D
        */
        InventorySlot GetItemSlot() override = 0;

        /**
         * @brief N/D
        */
        void PrimaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void SecondaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void Reload() override = 0;

        /**
         * @brief N/D
        */
        void WeaponIdle() override = 0;

        /**
         * @brief N/D
        */
        qboolean UseDecrement() override = 0;

        /**
         * @brief N/D
        */
        virtual qboolean IsPistol() = 0;

        /**
         * @brief N/D
        */
        int shell_model{};

        /**
         * @brief N/D
        */
        bool burst_fire{};
    };

    //
    // HE grenade.
    //

    /**
     * @brief N/D
    */
    constexpr auto HE_GRENADE_MAX_SPEED = 250.0f;

    /**
     * @brief N/D
    */
    constexpr auto HE_GRENADE_MAX_SPEED_SHIELD = 180.0f;

    enum class HeGrenadeAnimSeq
    {
        /**
         * @brief N/D
        */
        Idle,

        /**
         * @brief N/D
        */
        PullPin,

        /**
         * @brief N/D
        */
        ThrowGrenade,

        /**
         * @brief N/D
        */
        Draw
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class HeGrenade : public PlayerWeaponBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        qboolean GetItemInfo(ItemInfo* info) override = 0;

        /**
         * @brief N/D
        */
        qboolean CanDeploy() override = 0;

        /**
         * @brief N/D
        */
        qboolean CanDrop() override = 0;

        /**
         * @brief N/D
        */
        qboolean Deploy() override = 0;

        /**
         * @brief N/D
        */
        void Holster(qboolean skip_local) override = 0;

        /**
         * @brief N/D
        */
        float GetMaxSpeed() override = 0;

        /**
         * @brief N/D
        */
        InventorySlot GetItemSlot() override = 0;

        /**
         * @brief N/D
        */
        void PrimaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void SecondaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void WeaponIdle() override = 0;

        /**
         * @brief N/D
        */
        qboolean UseDecrement() override = 0;

        /**
         * @brief N/D
        */
        unsigned short event_create_explosion{};
    };

    //
    // Knife.
    //

    /**
     * @brief N/D
    */
    constexpr auto KNIFE_BODY_HIT_VOLUME = 128.0f;

    /**
     * @brief N/D
    */
    constexpr auto KNIFE_WALL_HIT_VOLUME = 512.0f;

    /**
     * @brief N/D
    */
    constexpr auto KNIFE_MAX_SPEED = 250.0f;

    /**
     * @brief N/D
    */
    constexpr auto KNIFE_MAX_SPEED_SHIELD = 180.0f;

    /**
     * @brief N/D
    */
    constexpr auto KNIFE_STAB_DAMAGE = 65.0f;

    /**
     * @brief N/D
    */
    constexpr auto KNIFE_SWING_DAMAGE = 15.0f;

    /**
     * @brief N/D
    */
    constexpr auto KNIFE_SWING_DAMAGE_FAST = 20.0f;

    /**
     * @brief N/D
    */
    constexpr auto KNIFE_STAB_DISTANCE = 32.0f;

    /**
     * @brief N/D
    */
    constexpr auto KNIFE_SWING_DISTANCE = 48.0f;

    enum class KnifeAnimSeq
    {
        /**
         * @brief N/D
        */
        Idle,

        /**
         * @brief N/D
        */
        Attack1Hit,

        /**
         * @brief N/D
        */
        Attack2Hit,

        /**
         * @brief N/D
        */
        Draw,

        /**
         * @brief N/D
        */
        StabHit,

        /**
         * @brief N/D
        */
        StabMiss,

        /**
         * @brief N/D
        */
        MidAttack1Hit,

        /**
         * @brief N/D
        */
        MidAttack2Hit
    };

    enum class KnifeShieldAnimSeq
    {
        /**
         * @brief N/D
        */
        Idle,

        /**
         * @brief N/D
        */
        Slash,

        /**
         * @brief N/D
        */
        AttackHit,

        /**
         * @brief N/D
        */
        Draw,

        /**
         * @brief N/D
        */
        UpIdle,

        /**
         * @brief N/D
        */
        Up,

        /**
         * @brief N/D
        */
        Down
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class Knife : public PlayerWeaponBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        qboolean GetItemInfo(ItemInfo* info) override = 0;

        /**
         * @brief N/D
        */
        qboolean CanDrop() override = 0;

        /**
         * @brief N/D
        */
        qboolean Deploy() override = 0;

        /**
         * @brief N/D
        */
        void Holster(qboolean skip_local) override = 0;

        /**
         * @brief N/D
        */
        float GetMaxSpeed() override = 0;

        /**
         * @brief N/D
        */
        InventorySlot GetItemSlot() override = 0;

        /**
         * @brief N/D
        */
        void PrimaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void SecondaryAttack() override = 0;

        /**
         * @brief N/D
        */
        qboolean UseDecrement() override = 0;

        /**
         * @brief N/D
        */
        void WeaponIdle() override = 0;

        // private:
        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        TraceResult trace_hit_{};

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        unsigned short event_fire_{};

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        float stab_base_damage_{};

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        float swing_base_damage_{};

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        float swing_base_damage_fast_{};

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        float stab_distance_{};

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        float swing_distance_{};
    };

    //
    // M249.
    //

    /**
     * @brief N/D
    */
    constexpr auto M249_MAX_SPEED = 220.0f;

    /**
     * @brief N/D
    */
    constexpr auto M249_DAMAGE = 32.0f;

    /**
     * @brief N/D
    */
    constexpr auto M249_RANGE_MODIFER = 0.97f;

    /**
     * @brief N/D
    */
    constexpr auto M249_RELOAD_TIME = 4.7f;

    enum class M249AnimSeq
    {
        /**
         * @brief N/D
        */
        Idle1,

        /**
         * @brief N/D
        */
        Shoot1,

        /**
         * @brief N/D
        */
        Shoot2,

        /**
         * @brief N/D
        */
        Reload,

        /**
         * @brief N/D
        */
        Draw
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class M249 : public PlayerWeaponBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        qboolean GetItemInfo(ItemInfo* info) override = 0;

        /**
         * @brief N/D
        */
        qboolean Deploy() override = 0;

        /**
         * @brief N/D
        */
        float GetMaxSpeed() override = 0;

        /**
         * @brief N/D
        */
        InventorySlot GetItemSlot() override = 0;

        /**
         * @brief N/D
        */
        void PrimaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void Reload() override = 0;

        /**
         * @brief N/D
        */
        void WeaponIdle() override = 0;

        /**
         * @brief N/D
        */
        qboolean UseDecrement() override = 0;

        /**
         * @brief N/D
        */
        int shell_model{};

        /**
         * @brief N/D
        */
        qboolean shell_on{};

        // private:
        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        unsigned short event_fire_{};
    };

    //
    // M3.
    //

    /**
     * @brief N/D
    */
    constexpr auto M3_MAX_SPEED = 230.0f;

    /**
     * @brief N/D
    */
    constexpr auto M3_DAMAGE = 20.0f;

    /**
     * @brief Special shotgun spreads.
    */
    const auto M3_CONE_VECTOR = Vector(0.0675f, 0.0675f, 0.0f);

    enum class M3AnimSeq
    {
        /**
         * @brief N/D
        */
        Idle,

        /**
         * @brief N/D
        */
        Fire1,

        /**
         * @brief N/D
        */
        Fire2,

        /**
         * @brief N/D
        */
        Reload,

        /**
         * @brief N/D
        */
        Pump,

        /**
         * @brief N/D
        */
        StartReload,

        /**
         * @brief N/D
        */
        Draw,

        /**
         * @brief N/D
        */
        Holster
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class M3 : public PlayerWeaponBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        qboolean GetItemInfo(ItemInfo* info) override = 0;

        /**
         * @brief N/D
        */
        qboolean Deploy() override = 0;

        /**
         * @brief N/D
        */
        float GetMaxSpeed() override = 0;

        /**
         * @brief N/D
        */
        InventorySlot GetItemSlot() override = 0;

        /**
         * @brief N/D
        */
        qboolean PlayEmptySound() override = 0;

        /**
         * @brief N/D
        */
        void PrimaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void Reload() override = 0;

        /**
         * @brief N/D
        */
        void WeaponIdle() override = 0;

        /**
         * @brief N/D
        */
        qboolean UseDecrement() override = 0;

        /**
         * @brief N/D
        */
        int shell_model{};

        /**
         * @brief N/D
        */
        float pump_time{};

        // private:
        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        unsigned short event_fire_{};
    };

    //
    // M4A1.
    //

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto M4A1_MAX_SPEED = 230.0f;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto M4A1_DAMAGE = 32.0f;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto M4A1_DAMAGE_SIL = 33.0f;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto M4A1_RANGE_MODIFER = 0.97f;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto M4A1_RANGE_MODIFER_SIL = 0.95f;

    /**
     * @brief N/D
    */
    // ReSharper disable once CppInconsistentNaming
    constexpr auto M4A1_RELOAD_TIME = 3.05f;

    enum class M4A1AnimSeq
    {
        /**
         * @brief N/D
        */
        Idle,

        /**
         * @brief N/D
        */
        Shoot1,

        /**
         * @brief N/D
        */
        Shoot2,

        /**
         * @brief N/D
        */
        Shoot3,

        /**
         * @brief N/D
        */
        Reload,

        /**
         * @brief N/D
        */
        Draw,

        /**
         * @brief N/D
        */
        AttachSilencer,

        /**
         * @brief N/D
        */
        UnsilIdle,

        /**
         * @brief N/D
        */
        UnsilShoot1,

        /**
         * @brief N/D
        */
        UnsilShoot2,

        /**
         * @brief N/D
        */
        UnsilShoot3,

        /**
         * @brief N/D
        */
        UnsilReload,

        /**
         * @brief N/D
        */
        UnsilDraw,

        /**
         * @brief N/D
        */
        DetachSilencer
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class M4A1 : public PlayerWeaponBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        qboolean GetItemInfo(ItemInfo* info) override = 0;

        /**
         * @brief N/D
        */
        qboolean Deploy() override = 0;

        /**
         * @brief N/D
        */
        float GetMaxSpeed() override = 0;

        /**
         * @brief N/D
        */
        InventorySlot GetItemSlot() override = 0;

        /**
         * @brief N/D
        */
        void PrimaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void SecondaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void Reload() override = 0;

        /**
         * @brief N/D
        */
        void WeaponIdle() override = 0;

        /**
         * @brief N/D
        */
        qboolean UseDecrement() override = 0;

        /**
         * @brief N/D
        */
        int shell_model{};

        /**
         * @brief N/D
        */
        qboolean shell_on{};

        // private:
        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        unsigned short event_fire_{};

#ifdef REGAMEDLL_API
        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        float base_damage_sil_{};
#endif
    };

    //
    // MAC10.
    //

    /**
     * @brief N/D
    */
    constexpr auto MAC10_MAX_SPEED = 250.0f;

    /**
     * @brief N/D
    */
    constexpr auto MAC10_DAMAGE = 29.0f;

    /**
     * @brief N/D
    */
    constexpr auto MAC10_RANGE_MODIFER = 0.82f;

    /**
     * @brief N/D
    */
    constexpr auto MAC10_RELOAD_TIME = 3.15f;

    enum class Mac10AnimSeq
    {
        /**
         * @brief N/D
        */
        Idle1,

        /**
         * @brief N/D
        */
        Reload,

        /**
         * @brief N/D
        */
        Draw,

        /**
         * @brief N/D
        */
        Shoot1,

        /**
         * @brief N/D
        */
        Shoot2,

        /**
         * @brief N/D
        */
        Shoot3
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class Mac10 : public PlayerWeaponBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        qboolean GetItemInfo(ItemInfo* info) override = 0;

        /**
         * @brief N/D
        */
        qboolean Deploy() override = 0;

        /**
         * @brief N/D
        */
        float GetMaxSpeed() override = 0;

        /**
         * @brief N/D
        */
        InventorySlot GetItemSlot() override = 0;

        /**
         * @brief N/D
        */
        void PrimaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void Reload() override = 0;

        /**
         * @brief N/D
        */
        void WeaponIdle() override = 0;

        /**
         * @brief N/D
        */
        qboolean UseDecrement() override = 0;

        /**
         * @brief N/D
        */
        int shell_model{};

        /**
         * @brief N/D
        */
        qboolean shell_on{};

        // private:
        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        unsigned short event_fire_{};
    };

    //
    // P228.
    //

    /**
     * @brief N/D
    */
    constexpr auto P228_MAX_SPEED = 250.0f;

    /**
     * @brief N/D
    */
    constexpr auto P228_DAMAGE = 32.0f;

    /**
     * @brief N/D
    */
    constexpr auto P228_RANGE_MODIFER = 0.8f;

    /**
     * @brief N/D
    */
    constexpr auto P228_RELOAD_TIME = 2.7f;

    enum class P228AnimSeq
    {
        /**
         * @brief N/D
        */
        Idle,

        /**
         * @brief N/D
        */
        Shoot1,

        /**
         * @brief N/D
        */
        Shoot2,

        /**
         * @brief N/D
        */
        Shoot3,

        /**
         * @brief N/D
        */
        ShootEmpty,

        /**
         * @brief N/D
        */
        Reload,

        /**
         * @brief N/D
        */
        Draw
    };

    enum class P228ShieldAnimSeq
    {
        /**
         * @brief N/D
        */
        Idle,

        /**
         * @brief N/D
        */
        Shoot1,

        /**
         * @brief N/D
        */
        Shoot2,

        /**
         * @brief N/D
        */
        ShootEmpty,

        /**
         * @brief N/D
        */
        Reload,

        /**
         * @brief N/D
        */
        Draw,

        /**
         * @brief N/D
        */
        IdleUp,

        /**
         * @brief N/D
        */
        Up,

        /**
         * @brief N/D
        */
        Down
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class P228 : public PlayerWeaponBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        qboolean GetItemInfo(ItemInfo* info) override = 0;

        /**
         * @brief N/D
        */
        qboolean Deploy() override = 0;

        /**
         * @brief N/D
        */
        float GetMaxSpeed() override = 0;

        /**
         * @brief N/D
        */
        InventorySlot GetItemSlot() override = 0;

        /**
         * @brief N/D
        */
        void PrimaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void SecondaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void Reload() override = 0;

        /**
         * @brief N/D
        */
        void WeaponIdle() override = 0;

        /**
         * @brief N/D
        */
        qboolean UseDecrement() override = 0;

        /**
         * @brief N/D
        */
        virtual qboolean IsPistol() = 0;

        /**
         * @brief N/D
        */
        int shell_model{};

        // private:
        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        unsigned short event_fire_{};
    };

    //
    // P90.
    //

    /**
     * @brief N/D
    */
    constexpr auto P90_MAX_SPEED = 245.0f;

    /**
     * @brief N/D
    */
    constexpr auto P90_DAMAGE = 21.0f;

    /**
     * @brief N/D
    */
    constexpr auto P90_RANGE_MODIFER = 0.885f;

    /**
     * @brief N/D
    */
    constexpr auto P90_RELOAD_TIME = 3.4f;

    enum class P90AnimSeq
    {
        /**
         * @brief N/D
        */
        Idle1,

        /**
         * @brief N/D
        */
        Reload,

        /**
         * @brief N/D
        */
        Draw,

        /**
         * @brief N/D
        */
        Shoot1,

        /**
         * @brief N/D
        */
        Shoot2,

        /**
         * @brief N/D
        */
        Shoot3
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class P90 : public PlayerWeaponBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        qboolean GetItemInfo(ItemInfo* info) override = 0;

        /**
         * @brief N/D
        */
        qboolean Deploy() override = 0;

        /**
         * @brief N/D
        */
        float GetMaxSpeed() override = 0;

        /**
         * @brief N/D
        */
        InventorySlot GetItemSlot() override = 0;

        /**
         * @brief N/D
        */
        void PrimaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void Reload() override = 0;

        /**
         * @brief N/D
        */
        void WeaponIdle() override = 0;

        /**
         * @brief N/D
        */
        qboolean UseDecrement() override = 0;

        /**
         * @brief N/D
        */
        int shell_model{};

        /**
         * @brief N/D
        */
        qboolean shell_on{};

        // private:
        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        unsigned short event_fire_{};
    };

    //
    // Scout.
    //

    /**
     * @brief N/D
    */
    constexpr auto SCOUT_MAX_SPEED = 260.0f;

    /**
     * @brief N/D
    */
    constexpr auto SCOUT_MAX_SPEED_ZOOM = 220.0f;

    /**
     * @brief N/D
    */
    constexpr auto SCOUT_DAMAGE = 75.0f;

    /**
     * @brief N/D
    */
    constexpr auto SCOUT_RANGE_MODIFER = 0.98f;

    /**
     * @brief N/D
    */
    constexpr auto SCOUT_RELOAD_TIME = 2.0f;

    enum class ScoutAnimSeq
    {
        /**
         * @brief N/D
        */
        Idle,

        /**
         * @brief N/D
        */
        Shoot,

        /**
         * @brief N/D
        */
        Shoot2,

        /**
         * @brief N/D
        */
        Reload,

        /**
         * @brief N/D
        */
        Draw
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class Scout : public PlayerWeaponBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        qboolean GetItemInfo(ItemInfo* info) override = 0;

        /**
         * @brief N/D
        */
        qboolean Deploy() override = 0;

        /**
         * @brief N/D
        */
        float GetMaxSpeed() override = 0;

        /**
         * @brief N/D
        */
        InventorySlot GetItemSlot() override = 0;

        /**
         * @brief N/D
        */
        void PrimaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void SecondaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void Reload() override = 0;

        /**
         * @brief N/D
        */
        void WeaponIdle() override = 0;

        /**
         * @brief N/D
        */
        qboolean UseDecrement() override = 0;

        /**
         * @brief N/D
        */
        int shell_model{};

        // private:
        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        unsigned short event_fire_{};
    };

    //
    // Smoke grenade.
    //

    /**
     * @brief N/D
    */
    constexpr auto SMOKE_GRENADE_MAX_SPEED = 250.0f;

    /**
     * @brief N/D
    */
    constexpr auto SMOKE_GRENADE_MAX_SPEED_SHIELD = 180.0f;

    enum class SmokeGrenadeAnimSeq
    {
        /**
         * @brief N/D
        */
        Idle,

        /**
         * @brief N/D
        */
        PullPin,

        /**
         * @brief N/D
        */
        ThrowGrenade,

        /**
         * @brief N/D
        */
        Draw
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class SmokeGrenade : public PlayerWeaponBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        qboolean GetItemInfo(ItemInfo* info) override = 0;

        /**
         * @brief N/D
        */
        qboolean CanDeploy() override = 0;

        /**
         * @brief N/D
        */
        qboolean CanDrop() override = 0;

        /**
         * @brief N/D
        */
        qboolean Deploy() override = 0;

        /**
         * @brief N/D
        */
        void Holster(qboolean skip_local) override = 0;

        /**
         * @brief N/D
        */
        float GetMaxSpeed() override = 0;

        /**
         * @brief N/D
        */
        InventorySlot GetItemSlot() override = 0;

        /**
         * @brief N/D
        */
        void PrimaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void SecondaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void WeaponIdle() override = 0;

        /**
         * @brief N/D
        */
        qboolean UseDecrement() override = 0;
    };

    //
    // TMP.
    //

    /**
     * @brief N/D
    */
    constexpr auto TMP_MAX_SPEED = 250.0f;

    /**
     * @brief N/D
    */
    constexpr auto TMP_DAMAGE = 20.0f;

    /**
     * @brief N/D
    */
    constexpr auto TMP_RANGE_MODIFER = 0.85f;

    /**
     * @brief N/D
    */
    constexpr auto TMP_RELOAD_TIME = 2.12f;

    enum class TmpAnimSeq
    {
        /**
         * @brief N/D
        */
        Idle1,

        /**
         * @brief N/D
        */
        Reload,

        /**
         * @brief N/D
        */
        Draw,

        /**
         * @brief N/D
        */
        Shoot1,

        /**
         * @brief N/D
        */
        Shoot2,

        /**
         * @brief N/D
        */
        Shoot3
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class Tmp : public PlayerWeaponBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        qboolean GetItemInfo(ItemInfo* info) override = 0;

        /**
         * @brief N/D
        */
        qboolean Deploy() override = 0;

        /**
         * @brief N/D
        */
        float GetMaxSpeed() override = 0;

        /**
         * @brief N/D
        */
        InventorySlot GetItemSlot() override = 0;

        /**
         * @brief N/D
        */
        void PrimaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void Reload() override = 0;

        /**
         * @brief N/D
        */
        void WeaponIdle() override = 0;

        /**
         * @brief N/D
        */
        qboolean UseDecrement() override = 0;

        /**
         * @brief N/D
        */
        int shell_model{};

        /**
         * @brief N/D
        */
        qboolean shell_on{};

        // private:
        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        unsigned short event_fire_{};
    };

    //
    // XM1014.
    //

    /**
     * @brief N/D
    */
    constexpr auto XM1014_MAX_SPEED = 240.0f;

    /**
     * @brief N/D
    */
    constexpr auto XM1014_DAMAGE = 20.0f;

    /**
     * @brief Special shotgun spreads.
    */
    const auto XM1014_CONE_VECTOR = Vector(0.0725f, 0.0725f, 0.0f);

    enum class Xm1014AnimSeq
    {
        /**
         * @brief N/D
        */
        Idle,

        /**
         * @brief N/D
        */
        Fire1,

        /**
         * @brief N/D
        */
        Fire2,

        /**
         * @brief N/D
        */
        Reload,

        /**
         * @brief N/D
        */
        Pump,

        /**
         * @brief N/D
        */
        StartReload,

        /**
         * @brief N/D
        */
        Draw
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class Xm1014 : public PlayerWeaponBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        qboolean GetItemInfo(ItemInfo* info) override = 0;

        /**
         * @brief N/D
        */
        qboolean Deploy() override = 0;

        /**
         * @brief N/D
        */
        float GetMaxSpeed() override = 0;

        /**
         * @brief N/D
        */
        InventorySlot GetItemSlot() override = 0;

        /**
         * @brief N/D
        */
        qboolean PlayEmptySound() override = 0;

        /**
         * @brief N/D
        */
        void PrimaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void Reload() override = 0;

        /**
         * @brief N/D
        */
        void WeaponIdle() override = 0;

        /**
         * @brief N/D
        */
        qboolean UseDecrement() override = 0;

        /**
         * @brief N/D
        */
        int shell_model{};

        /**
         * @brief N/D
        */
        float pump_time{};

        // private:
        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        unsigned short event_fire_{};
    };

    //
    // Elite.
    //

    /**
     * @brief N/D
    */
    constexpr auto ELITE_MAX_SPEED = 250.0f;

    /**
     * @brief N/D
    */
    constexpr auto ELITE_RELOAD_TIME = 4.5f;

    /**
     * @brief N/D
    */
    constexpr auto ELITE_DAMAGE = 36.0f;

    /**
     * @brief N/D
    */
    constexpr auto ELITE_RANGE_MODIFER = 0.75f;

    enum class EliteAnimSeq
    {
        /**
         * @brief N/D
        */
        Idle,

        /**
         * @brief N/D
        */
        IdleLeftEmpty,

        /**
         * @brief N/D
        */
        ShootLeft1,

        /**
         * @brief N/D
        */
        ShootLeft2,

        /**
         * @brief N/D
        */
        ShootLeft3,

        /**
         * @brief N/D
        */
        ShootLeft4,

        /**
         * @brief N/D
        */
        ShootLeft5,

        /**
         * @brief N/D
        */
        ShootLeftLast,

        /**
         * @brief N/D
        */
        ShootRight1,

        /**
         * @brief N/D
        */
        ShootRight2,

        /**
         * @brief N/D
        */
        ShootRight3,

        /**
         * @brief N/D
        */
        ShootRight4,

        /**
         * @brief N/D
        */
        ShootRight5,

        /**
         * @brief N/D
        */
        ShootRightLast,

        /**
         * @brief N/D
        */
        Reload,

        /**
         * @brief N/D
        */
        Draw
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class Elite : public PlayerWeaponBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        qboolean GetItemInfo(ItemInfo* info) override = 0;

        /**
         * @brief N/D
        */
        qboolean Deploy() override = 0;

        /**
         * @brief N/D
        */
        float GetMaxSpeed() override = 0;

        /**
         * @brief N/D
        */
        InventorySlot GetItemSlot() override = 0;

        /**
         * @brief N/D
        */
        void PrimaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void Reload() override = 0;

        /**
         * @brief N/D
        */
        void WeaponIdle() override = 0;

        /**
         * @brief N/D
        */
        qboolean UseDecrement() override = 0;

        /**
         * @brief N/D
        */
        virtual qboolean IsPistol() = 0;

        /**
         * @brief N/D
        */
        int shell_model{};

        // private:
        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        unsigned short event_fire_left_{};

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        unsigned short event_fire_right_{};
    };

    //
    // FiveSeven.
    //

    /**
     * @brief N/D
    */
    constexpr auto FIVESEVEN_MAX_SPEED = 250.0f;

    /**
     * @brief N/D
    */
    constexpr auto FIVESEVEN_DAMAGE = 20.0f;

    /**
     * @brief N/D
    */
    constexpr auto FIVESEVEN_RANGE_MODIFER = 0.885f;

    /**
     * @brief N/D
    */
    constexpr auto FIVESEVEN_RELOAD_TIME = 2.7f;

    enum class FiveSevenAnimSeq
    {
        /**
         * @brief N/D
        */
        Idle,

        /**
         * @brief N/D
        */
        Shoot1,

        /**
         * @brief N/D
        */
        Shoot2,

        /**
         * @brief N/D
        */
        ShootEmpty,

        /**
         * @brief N/D
        */
        Reload,

        /**
         * @brief N/D
        */
        Draw
    };

    enum class FiveSevenShieldAnimSeq
    {
        /**
         * @brief N/D
        */
        Idle,

        /**
         * @brief N/D
        */
        Shoot1,

        /**
         * @brief N/D
        */
        Shoot2,

        /**
         * @brief N/D
        */
        ShootEmpty,

        /**
         * @brief N/D
        */
        Reload,

        /**
         * @brief N/D
        */
        Draw,

        /**
         * @brief N/D
        */
        ShieldIdle,

        /**
         * @brief N/D
        */
        ShieldUp,

        /**
         * @brief N/D
        */
        ShieldDown
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class FiveSeven : public PlayerWeaponBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        qboolean GetItemInfo(ItemInfo* info) override = 0;

        /**
         * @brief N/D
        */
        qboolean Deploy() override = 0;

        /**
         * @brief N/D
        */
        float GetMaxSpeed() override = 0;

        /**
         * @brief N/D
        */
        InventorySlot GetItemSlot() override = 0;

        /**
         * @brief N/D
        */
        void PrimaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void SecondaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void Reload() override = 0;

        /**
         * @brief N/D
        */
        void WeaponIdle() override = 0;

        /**
         * @brief N/D
        */
        qboolean UseDecrement() override = 0;

        /**
         * @brief N/D
        */
        virtual qboolean IsPistol() = 0;

        /**
         * @brief N/D
        */
        int shell_model{};

        // private:
        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        unsigned short event_fire_{};
    };

    //
    // UMP45.
    //

    /**
     * @brief N/D
    */
    constexpr auto UMP45_MAX_SPEED = 250.0f;

    /**
     * @brief N/D
    */
    constexpr auto UMP45_DAMAGE = 30.0f;

    /**
     * @brief N/D
    */
    constexpr auto UMP45_RANGE_MODIFER = 0.82f;

    /**
     * @brief N/D
    */
    constexpr auto UMP45_RELOAD_TIME = 3.5f;

    enum class Ump45AnimSeq
    {
        /**
         * @brief N/D
        */
        Idle1,

        /**
         * @brief N/D
        */
        Reload,

        /**
         * @brief N/D
        */
        Draw,

        /**
         * @brief N/D
        */
        Shoot1,

        /**
         * @brief N/D
        */
        Shoot2,

        /**
         * @brief N/D
        */
        Shoot3
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class Ump45 : public PlayerWeaponBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        qboolean GetItemInfo(ItemInfo* info) override = 0;

        /**
         * @brief N/D
        */
        qboolean Deploy() override = 0;

        /**
         * @brief N/D
        */
        float GetMaxSpeed() override = 0;

        /**
         * @brief N/D
        */
        InventorySlot GetItemSlot() override = 0;

        /**
         * @brief N/D
        */
        void PrimaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void Reload() override = 0;

        /**
         * @brief N/D
        */
        void WeaponIdle() override = 0;

        /**
         * @brief N/D
        */
        qboolean UseDecrement() override = 0;

        /**
         * @brief N/D
        */
        int shell_model{};

        /**
         * @brief N/D
        */
        qboolean shell_on{};

        // private:
        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        unsigned short event_fire_{};
    };

    //
    // SG550.
    //

    /**
     * @brief N/D
    */
    constexpr auto SG550_MAX_SPEED = 210.0f;

    /**
     * @brief N/D
    */
    constexpr auto SG550_MAX_SPEED_ZOOM = 150.0f;

    /**
     * @brief N/D
    */
    constexpr auto SG550_DAMAGE = 70.0f;

    /**
     * @brief N/D
    */
    constexpr auto SG550_RANGE_MODIFER = 0.98f;

    /**
     * @brief N/D
    */
    constexpr auto SG550_RELOAD_TIME = 3.35f;

    enum class Sg550AnimSeq
    {
        /**
         * @brief N/D
        */
        Idle,

        /**
         * @brief N/D
        */
        Shoot,

        /**
         * @brief N/D
        */
        Shoot2,

        /**
         * @brief N/D
        */
        Reload,

        /**
         * @brief N/D
        */
        Draw
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class Sg550 : public PlayerWeaponBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        qboolean GetItemInfo(ItemInfo* info) override = 0;

        /**
         * @brief N/D
        */
        qboolean Deploy() override = 0;

        /**
         * @brief N/D
        */
        float GetMaxSpeed() override = 0;

        /**
         * @brief N/D
        */
        InventorySlot GetItemSlot() override = 0;

        /**
         * @brief N/D
        */
        void PrimaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void SecondaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void Reload() override = 0;

        /**
         * @brief N/D
        */
        void WeaponIdle() override = 0;

        /**
         * @brief N/D
        */
        qboolean UseDecrement() override = 0;

        /**
         * @brief N/D
        */
        int shell_model{};

        // private:
        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        unsigned short event_fire_{};
    };

    //
    // Galil.
    //

    /**
     * @brief N/D
    */
    constexpr auto GALIL_MAX_SPEED = 240.0f;

    /**
     * @brief N/D
    */
    constexpr auto GALIL_DAMAGE = 30.0f;

    /**
     * @brief N/D
    */
    constexpr auto GALIL_RANGE_MODIFER = 0.98f;

    /**
     * @brief N/D
    */
    constexpr auto GALIL_RELOAD_TIME = 2.45f;

    enum class GalilAnimSeq
    {
        /**
         * @brief N/D
        */
        Idle1,

        /**
         * @brief N/D
        */
        Reload,

        /**
         * @brief N/D
        */
        Draw,

        /**
         * @brief N/D
        */
        Shoot1,

        /**
         * @brief N/D
        */
        Shoot2,

        /**
         * @brief N/D
        */
        Shoot3
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class Galil : public PlayerWeaponBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        qboolean GetItemInfo(ItemInfo* info) override = 0;

        /**
         * @brief N/D
        */
        qboolean Deploy() override = 0;

        /**
         * @brief N/D
        */
        float GetMaxSpeed() override = 0;

        /**
         * @brief N/D
        */
        InventorySlot GetItemSlot() override = 0;

        /**
         * @brief N/D
        */
        void PrimaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void SecondaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void Reload() override = 0;

        /**
         * @brief N/D
        */
        void WeaponIdle() override = 0;

        /**
         * @brief N/D
        */
        qboolean UseDecrement() override = 0;

        /**
         * @brief N/D
        */
        int shell_model{};

        /**
         * @brief N/D
        */
        qboolean shell_on{};

        // private:
        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        unsigned short event_fire_{};
    };

    //
    // Famas.
    //

    /**
     * @brief N/D
    */
    constexpr auto FAMAS_MAX_SPEED = 240.0f;

    /**
     * @brief N/D
    */
    constexpr auto FAMAS_RELOAD_TIME = 3.3f;

    /**
     * @brief N/D
    */
    constexpr auto FAMAS_DAMAGE = 30.0f;

    /**
     * @brief N/D
    */
    constexpr auto FAMAS_DAMAGE_BURST = 34.0f;

    /**
     * @brief N/D
    */
    constexpr auto FAMAS_RANGE_MODIFER = 0.96f;

    enum class FamasAnimSeq
    {
        /**
         * @brief N/D
        */
        Idle1,

        /**
         * @brief N/D
        */
        Reload,

        /**
         * @brief N/D
        */
        Draw,

        /**
         * @brief N/D
        */
        Shoot1,

        /**
         * @brief N/D
        */
        Shoot2,

        /**
         * @brief N/D
        */
        Shoot3
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class Famas : public PlayerWeaponBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        qboolean GetItemInfo(ItemInfo* info) override = 0;

        /**
         * @brief N/D
        */
        qboolean Deploy() override = 0;

        /**
         * @brief N/D
        */
        float GetMaxSpeed() override = 0;

        /**
         * @brief N/D
        */
        InventorySlot GetItemSlot() override = 0;

        /**
         * @brief N/D
        */
        void PrimaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void SecondaryAttack() override = 0;

        /**
         * @brief N/D
        */
        void Reload() override = 0;

        /**
         * @brief N/D
        */
        void WeaponIdle() override = 0;

        /**
         * @brief N/D
        */
        qboolean UseDecrement() override = 0;

        /**
         * @brief N/D
        */
        int shell_model{};

        /**
         * @brief N/D
        */
        qboolean shell_on{};

#ifdef REGAMEDLL_API
        /**
         * @brief N/D
        */
        float base_damage_burst{};
#endif
    };
}
