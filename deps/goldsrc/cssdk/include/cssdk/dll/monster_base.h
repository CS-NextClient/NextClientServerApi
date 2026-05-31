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

#include <cssdk/dll/activity.h>
#include <cssdk/dll/entity_base.h>

namespace cssdk
{
    enum class TimeBasedDamage
    {
        /**
         * @brief N/D
        */
        Paralyze = 0,

        /**
         * @brief N/D
        */
        NerveGas,

        /**
         * @brief N/D
        */
        Poison,

        /**
         * @brief N/D
        */
        Radiation,

        /**
         * @brief N/D
        */
        DrownRecover,

        /**
         * @brief N/D
        */
        Acid,

        /**
         * @brief N/D
        */
        SlowBurn,

        /**
         * @brief N/D
        */
        SlowFreeze,

        /**
         * @brief N/D
        */
        End
    };

    enum class MonsterState
    {
        /**
         * @brief N/D
        */
        None = 0,

        /**
         * @brief N/D
        */
        Idle,

        /**
         * @brief N/D
        */
        Combat,

        /**
         * @brief N/D
        */
        Alert,

        /**
         * @brief N/D
        */
        Hunt,

        /**
         * @brief N/D
        */
        Prone,

        /**
         * @brief N/D
        */
        Script,

        /**
         * @brief N/D
        */
        PlayDead,

        /**
         * @brief N/D
        */
        Dead
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class MonsterBase : public ToggleBase // NOLINT(clang-diagnostic-non-virtual-dtor)
    {
    public:
        /**
         * @brief N/D
        */
        void KeyValue(KeyValueData* data) override = 0;

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
        int BloodColor() override = 0;

        /**
         * @brief N/D
        */
        qboolean IsAlive() override = 0;

        /**
         * @brief N/D
        */
        virtual float ChangeYaw(int speed) = 0;

        /**
         * @brief N/D
        */
        virtual qboolean HasHumanGibs() = 0;

        /**
         * @brief N/D
        */
        virtual qboolean HasAlienGibs() = 0;

        /**
         * @brief N/D
        */
        virtual void FadeMonster() = 0;

        /**
         * @brief N/D
        */
        virtual void GibMonster() = 0;

        /**
         * @brief N/D
        */
        virtual Activity GetDeathActivity() = 0;

        /**
         * @brief N/D
        */
        virtual void BecomeDead() = 0;

        /**
         * @brief N/D
        */
        virtual qboolean ShouldFadeOnDeath() = 0;

        /**
         * @brief N/D
        */
        virtual int Relationship(EntityBase* target) = 0;

        /**
         * @brief N/D
        */
        virtual void PainSound() = 0;

        /**
         * @brief N/D
        */
        virtual void ResetMaxSpeed() = 0;

        /**
         * @brief N/D
        */
        virtual void ReportAiState() = 0;

        /**
         * @brief N/D
        */
        virtual void MonsterInitDead() = 0;

        /**
         * @brief N/D
        */
        virtual void Look(int distance) = 0;

        /**
         * @brief N/D
        */
        virtual EntityBase* BestVisibleEnemy() = 0;

        /**
         * @brief N/D
        */
        virtual qboolean InViewCone(EntityBase* entity) = 0;

        /**
         * @brief N/D
        */
        virtual qboolean InViewCone(const Vector* origin) = 0;

        /**
         * @brief What the monster is doing (animation).
        */
        Activity cur_activity{};

        /**
         * @brief Monster should switch to this activity.
        */
        Activity ideal_activity{};

        /**
         * @brief The last body region that took damage.
        */
        HitBoxGroup last_hit_group{};

        /**
         * @brief What types of damage has monster (player) taken.
        */
        int damage_type{};

        /**
         * @brief N/D
        */
        byte time_based_damage[static_cast<int>(TimeBasedDamage::End)]{};

        /**
         * @brief Monster's current state.
        */
        MonsterState monster_state{};

        /**
         * @brief Monster should change to this state.
        */
        MonsterState ideal_monster_state{};

        /**
         * @brief N/D
        */
        int conditions{};

        /**
         * @brief N/D
        */
        int memory{};

        /**
         * @brief Cannot attack again until this time.
        */
        float next_attack{};

        /**
         * @brief The entity that the monster is fighting.
        */
        EntityHandle<> enemy{};

        /**
         * @brief The entity that the monster is trying to reach.
        */
        EntityHandle<> target_ent{};

        /**
         * @brief Width of monster's field of view (dot product).
        */
        float field_of_view{};

        /**
         * @brief Color of blood particles.
        */
        int blood_color_value{};

        /**
         * @brief HACK until we can query end of gun.
        */
        Vector hacked_gun_pos{};

        /**
         * @brief Last known position of enemy (enemy's origin).
        */
        Vector enemy_last_known_position{};
    };
}
