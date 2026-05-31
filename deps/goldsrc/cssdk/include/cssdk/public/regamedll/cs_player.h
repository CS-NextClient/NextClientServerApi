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

#include <cssdk/common/vector.h>
#include <cssdk/dll/player.h>
#include <cssdk/public/regamedll/cs_entity.h>

namespace cssdk
{
    enum class WeaponInfiniteAmmoMode {
        Clip = 1,
        BackpackAmmo,
    };

    enum class ProtectionState {
        NoSet = 0,
        Active,
        Expired,
    };

    class CsPlayer : public CsMonster {
      public:
        [[nodiscard]] virtual bool IsConnected() const = 0;
        virtual void SetAnimation(PlayerAnim playerAnim) = 0;
        virtual void AddAccount(int amount, RewardType type = RewardType::None, bool trackChange = true) = 0;
        virtual EntityBase* GiveNamedItem(const char* name) = 0;
        virtual EntityBase* GiveNamedItemEx(const char* name) = 0;
        virtual void GiveDefaultItems() = 0;
        virtual void GiveShield(bool deploy = true) = 0;
        virtual void DropShield(bool deploy = true) = 0;
        virtual void DropPlayerItem(const char* itemName) = 0;
        virtual bool RemoveShield() = 0;
        virtual void RemoveAllItems(bool removeSuit) = 0;
        virtual bool RemovePlayerItem(const char* itemName) = 0;
        virtual void SetPlayerModel(bool hasC4) = 0;
        virtual void SetPlayerModelEx(const char* modelName) = 0;
        virtual void SetNewPlayerModel(const char* modelName) = 0;
        virtual void ClientCommand(
            const char* cmd,
            const char* arg1 = nullptr,
            const char* arg2 = nullptr,
            const char* arg3 = nullptr
        ) = 0;
        virtual void SetProgressBarTime(int time) = 0;
        virtual void SetProgressBarTime2(int time, float timeElapsed) = 0;
        virtual Edict* EntSelectSpawnPoint() = 0;
        virtual void SetBombIcon(bool flash = false) = 0;
        virtual void SetScoreAttribute(PlayerBase* dest) = 0;
        virtual void SendItemStatus() = 0;
        virtual void ReloadWeapons(
            PlayerItemBase* weapon = nullptr,
            bool forceReload = false,
            bool forceRefill = false
        ) = 0;
        virtual void ObserverSetMode(int mode) = 0;
        virtual bool SelectSpawnSpot(const char* entityClassName, EntityBase*& spot) = 0;
        virtual bool SwitchWeapon(PlayerItemBase* weapon) = 0;
        virtual void SwitchTeam() = 0;
        virtual bool JoinTeam(TeamName team) = 0;
        virtual void StartObserver(Vector& position, Vector& viewAngle) = 0;
        virtual void TeamChangeUpdate() = 0;
        virtual void DropSecondary() = 0;
        virtual void DropPrimary() = 0;
        virtual bool HasPlayerItem(PlayerItemBase* checkItem) = 0;
        virtual bool HasNamedPlayerItem(const char* itemName) = 0;
        virtual PlayerItemBase* GetItemById(WeaponId weapon) = 0;
        virtual PlayerItemBase* GetItemByName(const char* itemName) = 0;
        virtual void Disappear() = 0;
        virtual void MakeVip() = 0;
        virtual bool MakeBomber() = 0;
        virtual void ResetSequenceInfo() = 0;
        virtual void StartDeathCam() = 0;
        virtual bool RemovePlayerItemEx(const char* itemName, bool removeAmmo) = 0;
        virtual void SetSpawnProtection(float protectionTime) = 0;
        virtual void RemoveSpawnProtection() = 0;
        virtual bool HintMessageEx(
            const char* message,
            float duration = 6.F,
            bool displayIfPlayerDead = false,
            bool override = false
        ) = 0;
        virtual void Reset() = 0;
        virtual void OnSpawnEquip(bool addDefault = true, bool equipGame = true) = 0;
        virtual void SetScoreboardAttributes(PlayerBase* destination = nullptr) = 0;

        char model[32]{};
        bool force_show_menu{};
        float respawn_pending{};
        float spawn_protection_end_time{};
        Vector old_viewing_angle{};
        WeaponInfiniteAmmoMode infinite_ammo_mode{};
        int weapon_infinite_ids{};
        bool can_shoot_override{};
        bool game_forcing_respawn{};
        bool auto_bunny_hopping{};
        bool mega_bunny_jumping{};
        bool plant_c4_anywhere{};

        bool spawn_protection_effects{};
        double jump_height{};
        double long_jump_height{};
        double long_jump_force{};
        double duck_speed_multiplier{};

        int userId;
        struct DamageRecord {
            float damage = 0.0f;
            float flashDurationTime = 0.0f;
            int userId = -1;
        };
        using DamageList = DamageRecord[MAX_CLIENTS];
        //using DamageList = CUtlArray<DamageRecord, MAX_CLIENTS>;
        DamageList damageList;
        int numKilledByUnanswered[MAX_CLIENTS];
        bool playerDominated[MAX_CLIENTS];
        int gibDamageThreshold;

        [[nodiscard]] PlayerBase* GetPlayerBase() const {
            return reinterpret_cast<PlayerBase*>(this->containing_entity);
        }

        [[nodiscard]] ProtectionState GetProtectionState() const {
            if (spawn_protection_end_time <= 0.0f) {
                return ProtectionState::NoSet;
            }
            if (spawn_protection_end_time >= g_global_vars->time) {
                return ProtectionState::Active;
            }
            return ProtectionState::Expired;
        }
    };
}
