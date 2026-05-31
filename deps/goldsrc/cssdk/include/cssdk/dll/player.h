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

#include <cssdk/dll/entity_base.h>
#include <cssdk/dll/hint_message.h>
#include <cssdk/dll/monster_base.h>
#include <cssdk/dll/player_consts.h>
#include <cssdk/dll/unified_signals.h>
#include <cssdk/dll/weapons.h>
#include <cssdk/pm_shared/pm_materials.h>

namespace cssdk
{
#ifdef REGAMEDLL_API
    /**
     * @brief N/D
    */
    class CsPlayer;
#endif

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class StripWeapons : public EntityPoint // NOLINT(clang-diagnostic-non-virtual-dtor)
    {
    public:
        /**
         * @brief N/D
        */
        void Use(EntityBase* activator, EntityBase* caller, UseType type, float value) override = 0;

        /**
         * @brief N/D
        */
        void KeyValue(KeyValueData* data) override = 0;

#ifdef REGAMEDLL_ADD
        /**
         * @brief N/D
        */
        int ignore_slots{};

        /**
         * @brief N/D
        */
        int special_item{};
#endif
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class DeadHev : public MonsterBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        Classify GetClassify() override = 0;

        /**
         * @brief Which sequence to display -- temporary, don't need to save.
        */
        int pose{};
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class SprayCan : public EntityBase // NOLINT(clang-diagnostic-non-virtual-dtor)
    {
    public:
        /**
         * @brief N/D
        */
        void Think() override = 0;

        /**
         * @brief N/D
        */
        int ObjectCaps() override = 0;
    };

    struct RebuyStruct
    {
        /**
         * @brief N/D
        */
        WeaponId primary_weapon{};

        /**
         * @brief N/D
        */
        int primary_ammo{};

        /**
         * @brief N/D
        */
        WeaponId secondary_weapon{};

        /**
         * @brief N/D
        */
        int secondary_ammo{};

        /**
         * @brief N/D
        */
        int he_grenade{};

        /**
         * @brief N/D
        */
        int flash_bang{};

        /**
         * @brief N/D
        */
        int smoke_grenade{};

        /**
         * @brief N/D
        */
        qboolean defuser{};

        /**
         * @brief N/D
        */
        qboolean night_vision{};

        /**
         * @brief N/D
        */
        ArmorType armor{};
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class PlayerBase : public MonsterBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        Classify GetClassify() override = 0;

#ifdef _WIN32
        /**
         * @brief N/D
        */
        void TraceAttack(EntityVars* attacker, float damage, Vector direction, TraceResult* result,
                         int damage_type) override = 0;
#else
        /**
         * @brief N/D
        */
        void TraceAttack(EntityVars* attacker, float damage, Vector& direction, TraceResult* result,
                         int damage_type) override = 0;
#endif

        /**
         * @brief N/D
        */
        qboolean TakeDamage(EntityVars* inflictor, EntityVars* attacker, float damage, int damage_type) override = 0;

        /**
         * @brief N/D
        */
        qboolean TakeHealth(float health, int damage_type) override = 0;

        /**
         * @brief N/D
        */
        void Killed(EntityVars* attacker, int gib) override = 0;

        /**
         * @brief N/D
        */
        void AddPoints(int score, qboolean allow_negative_score) override = 0;

        /**
         * @brief N/D
        */
        void AddPointsToTeam(int score, qboolean allow_negative_score) override = 0;

        /**
         * @brief N/D
        */
        qboolean AddPlayerItem(PlayerItemBase* item) override = 0;

        /**
         * @brief N/D
        */
        qboolean RemovePlayerItem(PlayerItemBase* item) override = 0;

        /**
         * @brief Returns the unique ID for the ammo, or -1 if error.
        */
        int GiveAmmo(int amount, const char* name, int max = -1) override = 0;

#ifndef REGAMEDLL_API
        /**
         * @brief N/D
        */
        void StartSneaking() override = 0;

        /**
         * @brief N/D
        */
        void StopSneaking() override = 0;
#else
        /**
         * @brief N/D
        */
        void OnCreate() override = 0;

        /**
         * @brief N/D
        */
        void OnDestroy() override = 0;
#endif

        /**
         * @brief N/D
        */
        qboolean IsSneaking() override = 0;

        /**
         * @brief N/D
        */
        qboolean IsAlive() override = 0;

        /**
         * @brief N/D
        */
        qboolean IsPlayer() override = 0;

        /**
         * @brief N/D
        */
        qboolean IsNetClient() override = 0;

        /**
         * @brief N/D
        */
        const char* TeamId() override = 0;

        /**
         * @brief N/D
        */
        qboolean BecomeProne() override = 0;

        /**
         * @brief N/D
        */
        Vector BodyTarget(const Vector& src_pos) override = 0;

        /**
         * @brief N/D
        */
        int Illumination() override = 0;

        /**
         * @brief N/D
        */
        qboolean ShouldFadeOnDeath() override = 0;

        /**
         * @brief N/D
        */
        void ResetMaxSpeed() override = 0;

        /**
         * @brief N/D
        */
        virtual void Jump() = 0;

        /**
         * @brief N/D
        */
        virtual void Duck() = 0;

        /**
         * @brief N/D
        */
        virtual void PreThink() = 0;

        /**
         * @brief N/D
        */
        virtual void PostThink() = 0;

        /**
         * @brief N/D
        */
        virtual Vector GetGunPosition() = 0;

        /**
         * @brief N/D
        */
        virtual qboolean IsBot() = 0;

        /**
         * @brief N/D
        */
        virtual void UpdateClientData() = 0;

        /**
         * @brief N/D
        */
        virtual void ImpulseCommands() = 0;

        /**
         * @brief N/D
        */
        virtual void RoundRespawn() = 0;

        /**
         * @brief N/D
        */
        virtual Vector GetAutoAimVector(float delta) = 0;

        /**
         * @brief N/D
        */
        virtual void Blind(float until_time, float hold_time, float fade_time, int alpha) = 0;

        /**
         * @brief N/D
        */
        virtual void OnTouchingWeapon(WeaponBox* weapon) = 0;

        /**
         * @brief N/D
        */
        int random_seed{};

        /**
         * @brief N/D
        */
        unsigned short event_player_bleed{};

        /**
         * @brief N/D
        */
        EntityHandle<PlayerBase> observer_target{};

        /**
         * @brief N/D
        */
        float next_observer_input{};

        /**
         * @brief N/D
        */
        WeaponId observer_weapon{};

        /**
         * @brief N/D
        */
        int observer_c4_state{};

        /**
         * @brief N/D
        */
        bool observer_has_defuser{};

        /**
         * @brief N/D
        */
        ObserverMode observer_last_mode{};

        /**
         * @brief N/D
        */
        float flinch_time{};

        /**
         * @brief N/D
        */
        float anim_time{};

        /**
         * @brief N/D
        */
        bool high_damage{};

        /**
         * @brief N/D
        */
        float velocity_modifier{};

        /**
         * @brief N/D
        */
        int last_zoom{};

        /**
         * @brief N/D
        */
        bool resume_zoom{};

        /**
         * @brief N/D
        */
        float eject_brass{};

        /**
         * @brief N/D
        */
        ArmorType kevlar{};

        /**
         * @brief N/D
        */
        bool not_killed{};

        /**
         * @brief N/D
        */
        TeamName team{};

        /**
         * @brief N/D
        */
        int account{};

        /**
         * @brief N/D
        */
        bool has_primary{};

        /**
         * @brief N/D
        */
        float death_throw_time{};

        /**
         * @brief N/D
        */
        ThrowDirection throw_direction{};

        /**
         * @brief N/D
        */
        float last_talk{};

        /**
         * @brief N/D
        */
        bool just_connected{};

        /**
         * @brief N/D
        */
        bool context_help{};

        /**
         * @brief N/D
        */
        JoinState joining_state{};

        /**
         * @brief N/D
        */
        EntityBase* intro_camera{};

        /**
         * @brief N/D
        */
        float intro_cam_time{};

        /**
         * @brief N/D
        */
        float last_movement{};

        /**
         * @brief N/D
        */
        bool mission_briefing{};

        /**
         * @brief N/D
        */
        bool team_changed{};

        /**
         * @brief N/D
        */
        ModelName model_name{};

        /**
         * @brief N/D
        */
        int team_kills{};

        /**
         * @brief N/D
        */
        IgnoreChatMsg ignore_global_chat{};

        /**
         * @brief N/D
        */
        bool has_night_vision{};

        /**
         * @brief N/D
        */
        bool night_vision_on{};

        /**
         * @brief N/D
        */
        Vector recent_path[MAX_RECENT_PATH]{};

        /**
         * @brief N/D
        */
        float idle_check_time{};

        /**
         * @brief N/D
        */
        float radio_time{};

        /**
         * @brief N/D
        */
        int radio_messages{};

        /**
         * @brief N/D
        */
        bool ignore_radio{};

        /**
         * @brief N/D
        */
        bool has_c4{};

        /**
         * @brief N/D
        */
        bool has_defuser{};

        /**
         * @brief N/D
        */
        bool killed_by_bomb{};

        /**
         * @brief N/D
        */
        Vector blast_vector{};

        /**
         * @brief N/D
        */
        bool killed_by_grenade{};

        /**
         * @brief N/D
        */
        HintMessageQueue hint_message_queue{};

        /**
         * @brief N/D
        */
        int display_history{};

        /**
         * @brief N/D
        */
        MenuName menu{};

        /**
         * @brief N/D
        */
        qboolean chase_target{};

        /**
         * @brief N/D
        */
        EntityBase* chase_target_entity{};

        /**
         * @brief N/D
        */
        float cam_switch{};

        /**
         * @brief N/D
        */
        bool escaped{};

        /**
         * @brief N/D
        */
        bool is_vip{};

        /**
         * @brief N/D
        */
        float next_radar_update{};

        /**
         * @brief N/D
        */
        Vector last_origin{};

        /**
         * @brief N/D
        */
        int current_kick_vote{};

        /**
         * @brief N/D
        */
        float next_vote_time{};

        /**
         * @brief N/D
        */
        bool just_killed_teammate{};

        /**
         * @brief N/D
        */
        int hostages_killed{};

        /**
         * @brief N/D
        */
        int map_vote{};

        /**
         * @brief N/D
        */
        bool can_shoot{};

        /**
         * @brief N/D
        */
        float last_fired{};

        /**
         * @brief N/D
        */
        float last_attacked_teammate{};

        /**
         * @brief N/D
        */
        bool headshot_killed{};

        /**
         * @brief N/D
        */
        bool punished_for_tk{};

        /**
         * @brief N/D
        */
        bool receives_no_money_next_round{};

        /**
         * @brief N/D
        */
        int time_check_allowed{};

        /**
         * @brief N/D
        */
        bool has_changed_name{};

        /**
         * @brief N/D
        */
        char new_name[MAX_PLAYER_NAME_LENGTH]{};

        /**
         * @brief N/D
        */
        bool is_defusing{};

        /**
         * @brief N/D
        */
        float handle_signals{};

        /**
         * @brief N/D
        */
        UnifiedSignals signals{};

        /**
         * @brief N/D
        */
        Edict* cur_bomb_target{};

        /**
         * @brief N/D
        */
        int player_sound{};

        /**
         * @brief N/D
        */
        int target_volume{};

        /**
         * @brief N/D
        */
        int weapon_volume{};

        /**
         * @brief N/D
        */
        int extra_sound_types{};

        /**
         * @brief N/D
        */
        int weapon_flash{};

        /**
         * @brief N/D
        */
        float stop_extra_sound_time{};

        /**
         * @brief N/D
        */
        float flash_light_time{};

        /**
         * @brief N/D
        */
        int flash_battery{};

        /**
         * @brief N/D
        */
        int button_last{};

        /**
         * @brief N/D
        */
        int button_pressed{};

        /**
         * @brief N/D
        */
        int button_released{};

        /**
         * @brief N/D
        */
        Edict* snd_last{};

        /**
         * @brief N/D
        */
        float snd_room_type{};

        /**
         * @brief N/D
        */
        float snd_range{};

        /**
         * @brief N/D
        */
        float fall_velocity{};

        /**
         * @brief N/D
        */
        int items[MAX_ITEMS]{};

        /**
         * @brief N/D
        */
        int new_ammo{};

        /**
         * @brief N/D
        */
        unsigned int physics_flags{};

        /**
         * @brief N/D
        */
        float next_suicide_time{};

        /**
         * @brief N/D
        */
        float time_step_sound{};

        /**
         * @brief N/D
        */
        float time_weapon_idle{};

        /**
         * @brief N/D
        */
        float swim_time{};

        /**
         * @brief N/D
        */
        float duck_time{};

        /**
         * @brief N/D
        */
        float wall_jump_time{};

        /**
         * @brief N/D
        */
        float suit_update{};

        /**
         * @brief N/D
        */
        int suit_play_list[MAX_SUIT_PLAYLIST]{};

        /**
         * @brief N/D
        */
        int suit_play_next{};

        /**
         * @brief N/D
        */
        int suit_no_repeat[MAX_SUIT_NO_REPEAT]{};

        /**
         * @brief N/D
        */
        float suit_no_repeat_time[MAX_SUIT_NO_REPEAT]{};

        /**
         * @brief N/D
        */
        int last_damage_amount{};

        /**
         * @brief N/D
        */
        float time_based_damage_prev{};

        /**
         * @brief N/D
        */
        float geiger_range{};

        /**
         * @brief N/D
        */
        float geiger_delay{};

        /**
         * @brief N/D
        */
        int geiger_range_prev{};

        /**
         * @brief N/D
        */
        int step_left{};

        /**
         * @brief N/D
        */
        char texture_name[MAX_TEXTURE_NAME_LENGTH]{};

        /**
         * @brief N/D
        */
        char texture_type{};

        /**
         * @brief N/D
        */
        int drown_dmg{};

        /**
         * @brief N/D
        */
        int drown_restored{};

        /**
         * @brief N/D
        */
        int hud_damage{};

        /**
         * @brief N/D
        */
        qboolean init_hud{};

        /**
         * @brief N/D
        */
        qboolean game_hud_initialized{};

        /**
         * @brief N/D
        */
        int train{};

        /**
         * @brief N/D
        */
        qboolean weapon{};

        /**
         * @brief N/D
        */
        EntityHandle<> tank{};

        /**
         * @brief N/D
        */
        float dead_time{};

        /**
         * @brief N/D
        */
        qboolean no_player_sound{};

        /**
         * @brief N/D
        */
        qboolean long_jump{};

        /**
         * @brief N/D
        */
        float sneaking{};

        /**
         * @brief N/D
        */
        int update_time{};

        /**
         * @brief N/D
        */
        int client_health{};

        /**
         * @brief N/D
        */
        int client_battery{};

        /**
         * @brief N/D
        */
        int hide_hud{};

        /**
         * @brief N/D
        */
        int client_hide_hud{};

        /**
         * @brief N/D
        */
        int fov{};

        /**
         * @brief N/D
        */
        int client_fov{};

        /**
         * @brief N/D
        */
        int num_spawns{};

        /**
         * @brief N/D
        */
        EntityBase* observer{};

        /**
         * @brief N/D
        */
        PlayerItemBase* player_items[MAX_ITEM_TYPES]{};

        /**
         * @brief N/D
        */
        PlayerItemBase* active_item{};

        /**
         * @brief N/D
        */
        PlayerItemBase* client_active_item{};

        /**
         * @brief N/D
        */
        PlayerItemBase* last_item{};

        /**
         * @brief N/D
        */
        int ammo[MAX_AMMO_SLOTS]{};

        /**
         * @brief N/D
        */
        int ammo_last[MAX_AMMO_SLOTS]{};

        /**
         * @brief N/D
        */
        Vector auto_aim{};

        /**
         * @brief N/D
        */
        qboolean on_target{};

        /**
         * @brief N/D
        */
        int deaths{};

        /**
         * @brief N/D
        */
        int sbar_state[static_cast<int>(SBarData::End)]{};

        /**
         * @brief N/D
        */
        float next_sbar_update_time{};

        /**
         * @brief N/D
        */
        float status_bar_disappear_delay{};

        /**
         * @brief N/D
        */
        char sbar_string0[MAX_SBAR_STRING]{};

        /**
         * @brief N/D
        */
        int last_x{};

        /**
         * @brief N/D
        */
        int last_y{};

        /**
         * @brief N/D
        */
        int custom_spray_frames{};

        /**
         * @brief N/D
        */
        float next_decal_time{};

        /**
         * @brief N/D
        */
        char team_name_string[MAX_TEAM_NAME_LENGTH]{};

        /**
         * @brief N/D
        */
        int model_index_player{};

        /**
         * @brief N/D
        */
        char anim_extension[32]{};

        /**
         * @brief N/D
        */
        int gait_sequence{};

        /**
         * @brief N/D
        */
        float gait_frame{};

        /**
         * @brief N/D
        */
        float gait_yaw{};

        /**
         * @brief N/D
        */
        Vector prev_gait_origin{};

        /**
         * @brief N/D
        */
        float pitch{};

        /**
         * @brief N/D
        */
        float yaw{};

        /**
         * @brief N/D
        */
        float gait_movement{};

        /**
         * @brief N/D
        */
        int auto_wep_switch{};

        /**
         * @brief N/D
        */
        bool vgui_menus{};

        /**
         * @brief N/D
        */
        bool show_hints{};

        /**
         * @brief N/D
        */
        bool shield_drawn{};

        /**
         * @brief N/D
        */
        bool owns_shield{};

        /**
         * @brief N/D
        */
        bool was_following{};

        /**
         * @brief N/D
        */
        float next_follow_time{};

        /**
         * @brief N/D
        */
        float yaw_modifier{};

        /**
         * @brief N/D
        */
        float blind_until_time{};

        /**
         * @brief N/D
        */
        float blind_start_time{};

        /**
         * @brief N/D
        */
        float blind_hold_time{};

        /**
         * @brief N/D
        */
        float blind_fade_time{};

        /**
         * @brief N/D
        */
        int blind_alpha{};

        /**
         * @brief N/D
        */
        float allow_auto_follow_time{};

        /**
         * @brief N/D
        */
        char auto_buy_string[MAX_AUTO_BUY_LENGTH]{};

        /**
         * @brief N/D
        */
        char* rebuy_string{};

        /**
         * @brief N/D
        */
        RebuyStruct rebuy_struct{};

        /**
         * @brief N/D
        */
        bool is_in_rebuy{};

        /**
         * @brief N/D
        */
        float last_update_time{};

        /**
         * @brief N/D
        */
        char last_location[MAX_LOCATION_LEN]{};

        /**
         * @brief N/D
        */
        float progress_start{};

        /**
         * @brief N/D
        */
        float progress_end{};

        /**
         * @brief N/D
        */
        bool observer_auto_director{};

        /**
         * @brief N/D
        */
        bool can_switch_observer_modes{};

        /**
         * @brief N/D
        */
        float heart_beat_time{};

        /**
         * @brief N/D
        */
        float intense_timestamp{};

        /**
         * @brief N/D
        */
        float silent_timestamp{};

        /**
         * @brief N/D
        */
        MusicState music_state{};

        /**
         * @brief N/D
        */
        float last_command_time[static_cast<int>(TrackCommands::CommandsToTrack)]{};

        /**
         * @brief N/D
        */
        int last_account{};

        /**
         * @brief N/D
        */
        int last_client_health{};

        /**
         * @brief N/D
        */
        float next_account_health_update{};

#ifdef REGAMEDLL_API
        /**
         * @brief N/D
        */
        [[nodiscard]] CsPlayer* GetCsPlayer() const
        {
            return reinterpret_cast<CsPlayer*>(this->entity);
        }
#endif

        /**
         * @brief N/D
        */
        template <typename T = PlayerItemBase, typename Functor>
        T* ForEachItem(const int slot, const Functor& func) const
        {
            auto* item = player_items[slot];

            while (item) {
                auto* const next = item->next;

                if (func(static_cast<T*>(item))) {
                    return static_cast<T*>(item);
                }

                item = next;
            }

            return nullptr;
        }

        /**
         * @brief N/D
        */
        template <typename T = PlayerItemBase, typename Functor>
        T* ForEachItem(const InventorySlot slot, const Functor& func) const
        {
            return ForEachItem<T>(static_cast<int>(slot), func);
        }

        /**
         * @brief N/D
        */
        template <typename T = PlayerItemBase, typename Functor>
        T* ForEachItem(const Functor& func) const
        {
            for (auto* item : player_items) {
                while (item) {
                    auto* const next = item->next;

                    if (func(static_cast<T*>(item))) {
                        return static_cast<T*>(item);
                    }

                    item = next;
                }
            }

            return nullptr;
        }

        /**
         * @brief N/D
        */
        template <typename T = PlayerItemBase, typename Functor>
        T* ForEachItem(const char* item_name, const Functor& func) const
        {
            if (!item_name) {
                return nullptr;
            }

            for (auto* item : player_items) {
                while (item) {
                    if (item->vars->class_name == item_name && func(static_cast<T*>(item))) {
                        return static_cast<T*>(item);
                    }

                    item = item->next;
                }
            }

            return nullptr;
        }
    };
}
