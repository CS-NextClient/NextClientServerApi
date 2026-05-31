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

namespace cssdk
{
    /**
     * @brief This many shards spawned when breakable objects break.
    */
    constexpr auto NUM_SHARDS = 6;

    /**
     * @brief May only be broken by trigger.
    */
    constexpr auto SF_BREAK_TRIGGER_ONLY = 1 << 0;

    /**
     * @brief Can be 'crashed through' by running player (plate glass).
    */
    constexpr auto SF_BREAK_TOUCH = 1 << 1;

    /**
     * @brief Can be broken by a player standing on it.
    */
    constexpr auto SF_BREAK_PRESSURE = 1 << 2;

    /**
     * @brief func_pushable (it's also func_breakable, so don't collide with those flags).
    */
    constexpr auto SF_PUSH_BREAKABLE = 1 << 7;

    /**
     * @brief Instant break if hit with crowbar.
    */
    constexpr auto SF_BREAK_CROWBAR = 1 << 8;

    enum class Explosions
    {
        /**
         * @brief N/D
        */
        Random = 0,

        /**
         * @brief N/D
        */
        Directed
    };

    enum class Materials
    {
        /**
         * @brief N/D
        */
        Glass = 0,

        /**
         * @brief N/D
        */
        Wood,

        /**
         * @brief N/D
        */
        Metal,

        /**
         * @brief N/D
        */
        Flesh,

        /**
         * @brief N/D
        */
        CinderBlock,

        /**
         * @brief N/D
        */
        CeilingTile,

        /**
         * @brief N/D
        */
        Computer,

        /**
         * @brief N/D
        */
        UnbreakableGlass,

        /**
         * @brief N/D
        */
        Rocks,

        /**
         * @brief N/D
        */
        None
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class Breakable : public DelayBase // NOLINT(clang-diagnostic-non-virtual-dtor, cppcoreguidelines-pro-type-member-init)
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

#ifdef _WIN32
        /**
         * @brief To spark when hit.
        */
        void TraceAttack(EntityVars* attacker, float damage, Vector direction, TraceResult* result,
                         int damage_type) override = 0;
#else
        /**
         * @brief To spark when hit.
        */
        void TraceAttack(EntityVars* attacker, float damage, Vector& direction, TraceResult* result,
                         int damage_type) override = 0;
#endif
        /**
         * @brief Breakables use an overridden take damage.
        */
        qboolean TakeDamage(EntityVars* inflictor, EntityVars* attacker, float damage, int damage_type) override = 0;

        /**
         * @brief N/D
        */
        Decal DamageDecal(int damage_type) override = 0;

        /**
         * @brief N/D
        */
        void Use(EntityBase* activator, EntityBase* caller, UseType type, float value) override = 0;

        /**
         * @brief N/D
        */
        Materials material;

        /**
         * @brief N/D
        */
        Explosions explosion;

        /**
         * @brief N/D
        */
        int id_shard;

        /**
         * @brief N/D
        */
        float angle;

        /**
         * @brief N/D
        */
        int gib_model;

        /**
         * @brief N/D
        */
        int spawn_object;

        /**
         * @brief N/D
        */
        float health;
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class Pushable : public Breakable // NOLINT(clang-diagnostic-non-virtual-dtor, cppcoreguidelines-pro-type-member-init)
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
        qboolean TakeDamage(EntityVars* inflictor, EntityVars* attacker, float damage, int damage_type) override = 0;

        /**
         * @brief N/D
        */
        void Touch(EntityBase* other) override = 0;

        /**
         * @brief N/D
        */
        void Use(EntityBase* activator, EntityBase* caller, UseType type, float value) override = 0;

#ifdef REGAMEDLL_FIXES
        /**
         * @brief N/D
        */
        void Restart() override = 0;
#endif
        /**
         * @brief N/D
        */
        int last_sound;

        /**
         * @brief N/D
        */
        float max_speed;

        /**
         * @brief N/D
        */
        float sound_time;
    };
}
