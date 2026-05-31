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

#include <cssdk/dll/decals.h>
#include <cssdk/dll/ext_defs.h>
#include <cssdk/dll/monster_event.h>
#include <cssdk/engine/eiface.h>
#include <cssdk/public/os_defs.h>
#include <cssdk/public/regamedll/regamedll_consts.h>
#include <cassert>
#include <cstddef>

namespace cssdk
{
    /**
     * @brief Maximum number of targets a single multi source entity may be assigned.
    */
    constexpr auto MAX_MS_TARGETS = 32;

    /**
     * @brief N/D
    */
    constexpr auto SF_MULTI_INIT = 1 << 0;

    /**
     * @brief N/D
    */
    constexpr auto SF_BUTTON_DONT_MOVE = 1 << 0;

    /**
     * @brief Button stays pushed until reactivated.
    */
    constexpr auto SF_BUTTON_TOGGLE = 1 << 5;

    /**
     * @brief Button sparks in OFF state.
    */
    constexpr auto SF_BUTTON_SPARK_IF_OFF = 1 << 6;

    /**
     * @brief Button only fires as a result of USE key.
    */
    constexpr auto SF_BUTTON_TOUCH_ONLY = 1 << 8;

    enum class ButtonCode
    {
        /**
         * @brief N/D
        */
        ButtonNothing = 0,

        /**
         * @brief N/D
        */
        ButtonActivate,

        /**
         * @brief N/D
        */
        ButtonReturn
    };

    /**
     * @brief N/D
    */
    class MonsterBase;

    /**
     * @brief N/D
    */
    class SquadMonster;

    /**
     * @brief N/D
    */
    class PlayerItemBase;

#ifdef REGAMEDLL_API
    /**
     * @brief N/D
    */
    class CsEntity;
#endif

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class EntityBase // NOLINT(clang-diagnostic-non-virtual-dtor)
    {
    public:
        /**
         * @brief N/D
        */
        virtual void Spawn() = 0;

        /**
         * @brief N/D
        */
        virtual void Precache() = 0;

        /**
         * @brief N/D
        */
        virtual void Restart() = 0;

        /**
         * @brief N/D
        */
        virtual void KeyValue(KeyValueData* data) = 0;

        /**
         * @brief N/D
        */
        virtual qboolean SaveData(Save& save) = 0;

        /**
         * @brief N/D
        */
        virtual qboolean RestoreData(Restore& restore) = 0;

        /**
         * @brief N/D
        */
        virtual int ObjectCaps() = 0;

        /**
         * @brief N/D
        */
        virtual void Activate() = 0;

        /**
         * @brief Setup the object->object collision box
         * (\c EntityVars->min_size / \c EntityVars->max_size is the \c object->world collision box).
        */
        virtual void SetObjectCollisionBox() = 0;

        /**
         * @brief Returns the type of group (i.e, "houndeye", or "human military") so that monsters
         * with different class names still realize that they are teammates (overridden for monsters that form groups).
        */
        virtual Classify GetClassify() = 0;

        /**
         * @brief N/D
        */
        virtual void DeathNotice(EntityVars* child) = 0;

#ifdef _WIN32
        /**
         * @brief N/D
        */
        virtual void TraceAttack(EntityVars* attacker, float damage, Vector direction, TraceResult* result,
                                 int damage_type) = 0;
#else
        //
        // Actually in ReGameDLL 'Vector direction' declared by value.
        // But it seems like compiler on Linux is doing it by reference (for optimization purposes).
        // This should be fixed in ReGameDLL. There is no reasons for a 'Direction Vector' by value.
        //

        /**
         * @brief N/D
        */
        virtual void TraceAttack(EntityVars* attacker, float damage, Vector& direction, TraceResult* result,
                                 int damage_type) = 0;
#endif

        /**
         * @brief N/D
        */
        virtual qboolean TakeDamage(EntityVars* inflictor, EntityVars* attacker, float damage, int damage_type) = 0;

        /**
         * @brief N/D
        */
        virtual qboolean TakeHealth(float health, int damage_type) = 0;

        /**
         * @brief N/D
        */
        virtual void Killed(EntityVars* attacker, int gib) = 0;

        /**
         * @brief N/D
        */
        virtual int BloodColor() = 0;

        /**
         * @brief N/D
        */
        virtual void TraceBleed(float damage, Vector direction, TraceResult* result, int damage_type) = 0;

        /**
         * @brief N/D
        */
        virtual qboolean IsTriggered(EntityBase* activator) = 0;

        /**
         * @brief N/D
        */
        virtual MonsterBase* MyMonsterPointer() = 0;

        /**
         * @brief N/D
        */
        virtual SquadMonster* MySquadMonsterPointer() = 0;

        /**
         * @brief N/D
        */
        virtual ToggleState GetToggleState() = 0;

        /**
         * @brief N/D
        */
        virtual void AddPoints(int score, qboolean allow_negative_score) = 0;

        /**
         * @brief N/D
        */
        virtual void AddPointsToTeam(int score, qboolean allow_negative_score) = 0;

        /**
         * @brief N/D
        */
        virtual qboolean AddPlayerItem(PlayerItemBase* item) = 0;

        /**
         * @brief N/D
        */
        virtual qboolean RemovePlayerItem(PlayerItemBase* item) = 0;

        /**
         * @brief N/D
        */
        virtual int GiveAmmo(int amount, const char* name, int max = -1) = 0;

        /**
         * @brief N/D
        */
        virtual float GetDelay() = 0;

        /**
         * @brief N/D
        */
        virtual qboolean IsMoving() = 0;

        /**
         * @brief N/D
        */
        virtual void OverrideReset() = 0;

        /**
         * @brief N/D
        */
        virtual Decal DamageDecal(int damage_type) = 0;

        /**
         * @brief N/D
        */
        virtual void SetToggleState(int state) = 0;

#ifndef REGAMEDLL_API
        /**
         * @brief N/D
        */
        virtual void StartSneaking() = 0;

        /**
         * @brief N/D
        */
        virtual void StopSneaking() = 0;
#else
        /**
         * @brief N/D
        */
        virtual void OnCreate() = 0;

        /**
         * @brief N/D
        */
        virtual void OnDestroy() = 0;
#endif

        /**
         * @brief N/D
        */
        virtual qboolean OnControls(EntityVars* on_ev) = 0;

        /**
         * @brief N/D
        */
        virtual qboolean IsSneaking() = 0;

        /**
         * @brief N/D
        */
        virtual qboolean IsAlive() = 0;

        /**
         * @brief N/D
        */
        virtual qboolean IsBspModel() = 0;

        /**
         * @brief N/D
        */
        virtual qboolean ReflectGauss() = 0;

        /**
         * @brief N/D
        */
        virtual qboolean HasTarget(Strind target_name) = 0;

        /**
         * @brief N/D
        */
        virtual qboolean IsInWorld() = 0;

        /**
         * @brief N/D
        */
        virtual qboolean IsPlayer() = 0;

        /**
         * @brief N/D
        */
        virtual qboolean IsNetClient() = 0;

        /**
         * @brief N/D
        */
        virtual const char* TeamId() = 0;

        /**
         * @brief N/D
        */
        virtual EntityBase* GetNextTarget() = 0;

        /**
         * @brief N/D
        */
        virtual void Think() = 0;

        /**
         * @brief N/D
        */
        virtual void Touch(EntityBase* other) = 0;

        /**
         * @brief N/D
        */
        virtual void Use(EntityBase* activator, EntityBase* caller, UseType type = UseType::UseOff, float value = 0.0f) = 0;

        /**
         * @brief N/D
        */
        virtual void Blocked(EntityBase* other) = 0;

        /**
         * @brief N/D
        */
        virtual EntityBase* Respawn() = 0;

        /**
         * @brief Used by monsters that are created by the MonsterMaker.
        */
        virtual void UpdateOwner() = 0;

        /**
         * @brief N/D
        */
        virtual qboolean BecomeProne() = 0;

        /**
         * @brief Center point of entity.
        */
        virtual Vector Center() = 0;

        /**
         * @brief Position of eyes.
        */
        virtual Vector EyePosition() = 0;

        /**
         * @brief Position of ears.
        */
        virtual Vector EarPosition() = 0;

        /**
         * @brief Position to shoot at.
        */
        virtual Vector BodyTarget(const Vector& pos_src) = 0;

        /**
         * @brief N/D
        */
        virtual int Illumination() = 0;

        /**
         * @brief N/D
        */
        virtual qboolean Visible(EntityBase* entity) = 0;

        /**
         * @brief N/D
        */
        virtual qboolean Visible(const Vector& origin) = 0;

        /**
         * @brief N/D
        */
        EntityVars* vars{};

        /**
         * @brief N/D
        */
        EntityBase* goal_ent{};

        /**
         * @brief N/D
        */
        EntityBase* link{};

        /**
         * @brief N/D
        */
        void (EntityBase::*think_callback)();

        /**
         * @brief N/D
        */
        void (EntityBase::*touch_callback)(EntityBase* other);

        /**
         * @brief N/D
        */
        void (EntityBase::*use_callback)(EntityBase* activator, EntityBase* caller, UseType type, float value);

        /**
         * @brief N/D
        */
        void (EntityBase::*blocked_callback)(EntityBase* other);

#ifdef REGAMEDLL_API
        /**
         * @brief N/D
        */
        CsEntity* entity{};
#else
        /**
         * @brief N/D
        */
        int* current_ammo{};
#endif

        /**
         * @brief N/D
        */
        float cur_ent_ammo{};

        /**
         * @brief N/D
        */
        int max_ammo_buckshot{};

        /**
         * @brief N/D
        */
        int ammo_buckshot{};

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        int max_ammo_9mm{};

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        int ammo_9mm{};

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        int max_ammo_556nato{};

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        int ammo_556nato{};

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        int max_ammo_556natobox{};

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        int ammo_556natobox{};

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        int max_ammo_762nato{};

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        int ammo_762nato{};

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        int max_ammo_45acp{};

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        int ammo_45acp{};

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        int max_ammo_50ae{};

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        int ammo_50ae{};

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        int max_ammo_338mag{};

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        int ammo_338mag{};

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        int max_ammo_57mm{};

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        int ammo_57mm{};

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        int max_ammo_357sig{};

        /**
         * @brief N/D
        */
        // ReSharper disable once CppInconsistentNaming
        int ammo_357sig{};

        /**
         * @brief N/D
        */
        float start_throw{};

        /**
         * @brief N/D
        */
        float release_throw{};

        /**
         * @brief N/D
        */
        int swing{};

        /**
         * @brief N/D
        */
        bool has_disconnected{};

        /**
         * @brief N/D
        */
        static EntityBase* Instance(const Edict* edict)
        {
            if (!edict) {
                edict = g_engine_funcs.entity_of_ent_index(0);
            }

            return static_cast<EntityBase*>(edict->private_data);
        }

        using UseCallbackFn = decltype(use_callback);
        using ThinkCallbackFn = decltype(think_callback);
        using TouchCallbackFn = decltype(touch_callback);
        using BlockedCallbackFn = decltype(blocked_callback);

        /**
         * @brief N/D
        */
        template <typename T>
        void SetThink(void (T::*callback)())
        {
            think_callback = static_cast<ThinkCallbackFn>(callback);
        }

        /**
         * @brief N/D
        */
        void SetThink(std::nullptr_t)
        {
            think_callback = nullptr;
        }

        /**
         * @brief N/D
        */
        template <typename T>
        void SetTouch(void (T::*callback)(EntityBase* other))
        {
            touch_callback = static_cast<TouchCallbackFn>(callback);
        }

        /**
         * @brief N/D
        */
        void SetTouch(std::nullptr_t)
        {
            touch_callback = nullptr;
        }

        /**
         * @brief N/D
        */
        template <typename T>
        void SetUse(void (T::*callback)(EntityBase* activator, EntityBase* caller, UseType type, float value))
        {
            use_callback = static_cast<UseCallbackFn>(callback);
        }

        /**
         * @brief N/D
        */
        void SetUse(std::nullptr_t)
        {
            use_callback = nullptr;
        }

        /**
         * @brief N/D
        */
        template <typename T>
        void SetBlocked(void (T::*callback)(EntityBase* other))
        {
            blocked_callback = static_cast<BlockedCallbackFn>(callback);
        }

        /**
         * @brief N/D
        */
        void SetBlocked(std::nullptr_t)
        {
            blocked_callback = nullptr;
        }

        /**
         * @brief N/D
        */
        [[nodiscard]] Edict* GetEdict() const
        {
            return vars->containing_entity;
        }

        /**
         * @brief N/D
        */
        [[nodiscard]] int EdictIndex() const
        {
            return g_engine_funcs.index_of_edict(vars->containing_entity);
        }

        /**
         * @brief N/D
        */
        [[nodiscard]] eoffset EdictOffset() const
        {
            return g_engine_funcs.ent_offset_of_entity(vars->containing_entity);
        }

        /**
         * @brief N/D
        */
        [[nodiscard]] bool IsProxy() const
        {
            return (vars->flags & FL_PROXY) == FL_PROXY;
        }

        /**
         * @brief N/D
        */
        [[nodiscard]] bool IsDormant() const
        {
            return (vars->flags & FL_DORMANT) == FL_DORMANT;
        }

        /**
         * @brief N/D
        */
        void FORCE_STACK_ALIGN DLLEXPORT SubUse(EntityBase* activator, EntityBase* caller, UseType use_type, float value);

        /**
         * @brief N/D
        */
        void FORCE_STACK_ALIGN DLLEXPORT SubThink();

        /**
         * @brief N/D
        */
        void FORCE_STACK_ALIGN DLLEXPORT SubTouch(EntityBase* other);

        /**
         * @brief N/D
        */
        void FORCE_STACK_ALIGN DLLEXPORT SubBlocked(EntityBase* other);
    };

    /**
     * @brief Safe way to point to entities who may die between frames.
    */
    template <typename T = EntityBase>
    class EntityHandle
    {
    public:
        /**
         * @brief Constructor.
        */
        EntityHandle() noexcept = default;

        /**
         * @brief Constructor.
        */
        explicit EntityHandle(T* const entity) // cppcheck-suppress noExplicitConstructor
        {
            *this = entity;
        }

        /**
         * @brief Constructor.
        */
        explicit EntityHandle(Edict* const edict) // cppcheck-suppress noExplicitConstructor
        {
            *this = edict;
        }

        /**
         * @brief N/D
        */
        [[nodiscard]] bool IsValid() const noexcept
        {
            return edict_ && !edict_->free && edict_->private_data && !(edict_->vars.flags & FL_KILL_ME) &&
                edict_->serial_number == serial_number_;
        }

        /**
         * @brief N/D
        */
        [[nodiscard]] int GetSerialNumber() const noexcept
        {
            return serial_number_;
        }

        /**
         * @brief N/D
        */
        [[nodiscard]] Edict* Get() const noexcept
        {
            return IsValid() ? edict_ : nullptr;
        }

        /**
         * @brief N/D
        */
        template <typename U>
        [[nodiscard]] U* Get() const noexcept
        {
            return IsValid() ? static_cast<U>(edict_->private_data) : nullptr;
        }

        /**
         * @brief N/D
        */
        Edict* Set(Edict* const edict) noexcept
        {
            edict_ = edict;

            if (edict_ && !edict_->free && edict_->private_data && !(edict_->vars.flags & FL_KILL_ME)) {
                serial_number_ = edict_->serial_number;
            }

            return edict_;
        }

        /**
         * @brief N/D
        */
        EntityHandle& operator=(Edict* const edict) noexcept
        {
            return Set(edict);
        }

        /**
         * @brief N/D
        */
        EntityHandle& operator=(T* const entity) noexcept
        {
            if (entity && entity->vars && entity->vars->containing_entity) {
                Set(entity->GetEdict());
            }
            else {
                edict_ = nullptr;
                serial_number_ = 0;
            }

            return *this;
        }

        /**
         * @brief N/D
        */
        T* operator->()
        {
            auto* entity = Get<T>();
            assert(entity != nullptr);

            return entity;
        }

        /**
         * @brief N/D
        */
        explicit operator bool() const
        {
            return IsValid();
        }

        /**
         * @brief N/D
        */
        bool operator==(const T* const entity)
        {
            assert(entity && entity->vars && entity->vars->containing_entity);
            const auto* const containing_entity = entity->GetEdict();

            return containing_entity->serial_number == serial_number_ && containing_entity == edict_;
        }

        /**
         * @brief N/D
        */
        bool operator!=(const T* const entity)
        {
            return !operator==(entity);
        }

        /**
         * @brief N/D
        */
        operator T*() noexcept
        {
            return Get<T>();
        }

    private:
        Edict* edict_{};
        int serial_number_{};
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class EntityPoint : public EntityBase // NOLINT(clang-diagnostic-non-virtual-dtor)
    {
    public:
        /**
         * @brief N/D
        */
        void Spawn() override = 0;

        /**
         * @brief N/D
        */
        int ObjectCaps() override = 0;
    };

    /**
     * @brief Generic delay entity.
    */
    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class DelayBase : public EntityBase // NOLINT(clang-diagnostic-non-virtual-dtor)
    {
    public:
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
        float delay{};

        /**
         * @brief N/D
        */
        Strind kill_target{};
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class AnimatingBase : public DelayBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        virtual void HandleAnimEvent(MonsterEvent* event) = 0;

        //
        // Animation needs.
        //

        /**
         * @brief Computed FPS for current sequence.
        */
        float frame_rate{};

        /**
         * @brief Computed linear movement rate for current sequence.
        */
        float ground_speed{};

        /**
         * @brief Last time the event list was checked.
        */
        float last_event_check{};

        /**
         * @brief Flag set when StudioAdvanceFrame moves across a frame boundry.
        */
        qboolean sequence_finished{};

        /**
         * @brief True if the sequence loops.
        */
        qboolean sequence_loops{};
    };

    /**
     * @brief Generic Toggle entity.
    */
    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class ToggleBase : public AnimatingBase // NOLINT(clang-diagnostic-non-virtual-dtor)
    {
    public:
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
        ToggleState GetToggleState() override = 0;

        /**
         * @brief N/D
        */
        float GetDelay() override = 0;

        /**
         * @brief N/D
        */
        ToggleState state{};

        /**
         * @brief Like attack_finished, but for doors.
        */
        float activate_finished{};

        /**
         * @brief How far a door should slide or rotate.
        */
        float move_distance{};

        /**
         * @brief N/D
        */
        float wait{};

        /**
         * @brief N/D
        */
        float lip{};

        /**
         * @brief For plats.
        */
        float width{};

        /**
         * @brief For plats.
        */
        float length{};

        /**
         * @brief N/D
        */
        Vector position1{};

        /**
         * @brief N/D
        */
        Vector position2{};

        /**
         * @brief N/D
        */
        Vector angle1{};

        /**
         * @brief N/D
        */
        Vector angle2{};

        /**
         * @brief trigger_counter only, # of activations remaining.
        */
        int triggers_left{};

        /**
         * @brief N/D
        */
        float height{};

        /**
         * @brief N/D
        */
        EntityHandle<> activator{};

        /**
         * @brief N/D
        */
        void (ToggleBase::*move_done_callback)();

        /**
         * @brief N/D
        */
        Vector final_dest{};

        /**
         * @brief N/D
        */
        Vector final_angle{};

        /**
         * @brief DMG_ damage type that the door or trigger does.
        */
        int damage_inflict{};

        /**
         * @brief If this button has a master switch, this is the target name.
         * A master switch must be of the \c MultiSource type.
         * If all of the switches in the multi source have been triggered,
         * then the button will be allowed to operate. Otherwise, it will be deactivated.
        */
        Strind master{};

        using MoveDoneCallbackFn = decltype(move_done_callback);

        /**
         * @brief N/D
        */
        template <typename T>
        void SetMoveDone(void (T::*callback)())
        {
            move_done_callback = static_cast<MoveDoneCallbackFn>(callback);
        }

        /**
         * @brief N/D
        */
        void SetMoveDone(std::nullptr_t)
        {
            move_done_callback = nullptr;
        }

        /**
         * @brief N/D
        */
        void FORCE_STACK_ALIGN DLLEXPORT SubMoveDone();
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class ButtonBase : public ToggleBase // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        qboolean TakeDamage(EntityVars* inflictor, EntityVars* attacker, float damage, int damage_type) override = 0;

        /**
         * @brief N/D
        */
        qboolean SaveData(Save& save) override = 0;

        /**
         * @brief N/D
        */
        qboolean RestoreData(Restore& restore) override = 0;

        /**
         * @brief Buttons that don't take damage can be IMPULSE used.
        */
        int ObjectCaps() override = 0;

#ifdef REGAMEDLL_FIXES
        /**
         * @brief N/D
        */
        void Restart() override = 0;
#endif
        /**
         * @brief Button stays pushed in until touched again?
        */
        qboolean stay_pushed{};

        /**
         * @brief A rotating button?
         * Default is a sliding button.
        */
        qboolean rotating{};

        /**
         * @brief If this field is not null, this is an index into the engine string array.
         * When this button is touched, it's target entity's TARGET field will be set to the button's ChangeTarget.
         * This allows you to make a func_train switch paths, etc.
        */
        Strind change_target{};

        /**
         * @brief Door lock sounds.
        */
        LockSound lock_snd{};

        /**
         * @brief N/D
        */
        byte locked_sound{};

        /**
         * @brief N/D
        */
        byte locked_sentence{};

        /**
         * @brief N/D
        */
        byte unlocked_sound{};

        /**
         * @brief N/D
        */
        byte unlocked_sentence{};

        /**
         * @brief N/D
        */
        int sounds{};
    };

    // ReSharper disable once CppPolymorphicClassWithNonVirtualPublicDestructor
    class MultiSource : public EntityPoint // NOLINT(clang-diagnostic-non-virtual-dtor)
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
        qboolean IsTriggered(EntityBase* activator) override = 0;

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
        EntityHandle<> entities[MAX_MS_TARGETS]{};

        /**
         * @brief N/D
        */
        int triggered[MAX_MS_TARGETS]{};

        /**
         * @brief N/D
        */
        int total{};

        /**
         * @brief N/D
        */
        Strind global_state{};
    };
}
