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
    enum class Activity
    {
        /**
         * @brief N/D
        */
        Invalid = -1,

        /**
         * @brief Set activity to this invalid value to force a reset to ideal_activity.
        */
        Reset = 0,

        /**
         * @brief N/D
        */
        Idle,

        /**
         * @brief N/D
        */
        Guard,

        /**
         * @brief N/D
        */
        Walk,

        /**
         * @brief N/D
        */
        Run,

        /**
         * @brief Fly (and flap if appropriate).
        */
        Fly,

        /**
         * @brief N/D
        */
        Swim,

        /**
         * @brief Vertical jump.
        */
        Hop,

        /**
         * @brief Long forward jump.
        */
        Leap,

        /**
         * @brief N/D
        */
        Fall,

        /**
         * @brief N/D
        */
        Land,

        /**
         * @brief N/D
        */
        StrafeLeft,

        /**
         * @brief N/D
        */
        StrafeRight,

        /**
         * @brief Tuck and roll, left.
        */
        RollLeft,

        /**
         * @brief Tuck and roll, right.
        */
        RollRight,

        /**
         * @brief Turn quickly left (stationary).
        */
        TurnLeft,

        /**
         * @brief Turn quickly right (stationary).
        */
        TurnRight,

        /**
         * @brief The act of crouching down from a standing position.
        */
        Crouch,

        /**
         * @brief Holding body in crouched position (loops).
        */
        CrouchIdle,

        /**
         * @brief The act of standing from a crouched position.
        */
        Stand,

        /**
         * @brief N/D
        */
        Use,

        /**
         * @brief N/D
        */
        Signal1,

        /**
         * @brief N/D
        */
        Signal2,

        /**
         * @brief N/D
        */
        Signal3,

        /**
         * @brief N/D
        */
        Twitch,

        /**
         * @brief N/D
        */
        Cower,

        /**
         * @brief N/D
        */
        SmallFlinch,

        /**
         * @brief N/D
        */
        BigFlinch,

        /**
         * @brief N/D
        */
        RangeAttack1,

        /**
         * @brief N/D
        */
        RangeAttack2,

        /**
         * @brief N/D
        */
        MeleeAttack1,

        /**
         * @brief N/D
        */
        MeleeAttack2,

        /**
         * @brief N/D
        */
        Reload,

        /**
         * @brief Pull out gun, for instance.
        */
        Arm,

        /**
         * @brief Reholster gun.
        */
        Disarm,

        /**
         * @brief Monster chowing on a large food item (loop).
        */
        Eat,

        /**
         * @brief N/D
        */
        DieSimple,

        /**
         * @brief N/D
        */
        DieBackward,

        /**
         * @brief N/D
        */
        DieForward,

        /**
         * @brief N/D
        */
        DieViolent,

        /**
         * @brief Barnacle tongue hits a monster.
        */
        BarnacleHit,

        /**
         * @brief Barnacle is lifting the monster (loop).
        */
        BarnaclePull,

        /**
         * @brief Barnacle latches on to the monster.
        */
        BarnacleChomp,

        /**
         * @brief Barnacle is holding the monster in its mouth (loop).
        */
        BarnacleChew,

        /**
         * @brief N/D
        */
        Sleep,

        /**
         * @brief For active idles, look at something on or near the floor.
        */
        InspectFloor,

        /**
         * @brief For active idles, look at something directly ahead of you (doesn't HAVE to be a wall or on a wall).
        */
        InspectWall,

        /**
         * @brief Alternate idle animation in which the monster is clearly agitated. (loop).
        */
        IdleAngry,

        /**
         * @brief Limp (loop).
        */
        WalkHurt,

        /**
         * @brief Limp (loop).
        */
        RunHurt,

        /**
         * @brief Idle while in flight.
        */
        Hover,

        /**
         * @brief Fly (don't flap).
        */
        Glide,

        /**
         * @brief Turn left in flight.
        */
        FlyLeft,

        /**
         * @brief Turn right in flight.
        */
        FlyRight,

        /**
         * @brief This means the monster smells a scent carried by the air.
        */
        DetectScent,

        /**
         * @brief This is the act of actually sniffing an item in front of the monster.
        */
        Sniff,

        /**
         * @brief Some large monsters can eat small things in one bite. This plays one time, EAT loops.
        */
        Bite,

        /**
         * @brief Without attacking, monster demonstrates that it is angry. (Yell, stick out chest, etc).
        */
        ThreatDisplay,

        /**
         * @brief Monster just saw something that it is afraid of.
        */
        FearDisplay,

        /**
         * @brief For some reason, monster is excited. Sees something he really likes to eat, or whatever.
        */
        Excited,

        /**
         * @brief Very monster specific special attacks.
        */
        SpecialAttack1,

        /**
         * @brief N/D
        */
        SpecialAttack2,

        /**
         * @brief Agitated idle.
        */
        CombatIdle,

        /**
         * @brief N/D
        */
        WalkScared,

        /**
         * @brief N/D
        */
        RunScared,

        /**
         * @brief Killed a player, do a victory dance.
        */
        VictoryDance,

        /**
         * @brief Die, hit in head.
        */
        DieHeadShot,

        /**
         * @brief Die, hit in chest.
        */
        DieChestShot,

        /**
         * @brief Die, hit in gut.
        */
        DieGutShot,

        /**
         * @brief Die, hit in back.
        */
        DieBackShot,

        /**
         * @brief N/D
        */
        FlinchHead,

        /**
         * @brief N/D
        */
        FlinchChest,

        /**
         * @brief N/D
        */
        FlinchStomach,

        /**
         * @brief N/D
        */
        FlinchLeftArm,

        /**
         * @brief N/D
        */
        FlinchRightArm,

        /**
         * @brief N/D
        */
        FlinchLeftLeg,

        /**
         * @brief N/D
        */
        FlinchRightLeg,

        /**
         * @brief N/D
        */
        Flinch,

        /**
         * @brief N/D
        */
        LargeFlinch,

        /**
         * @brief N/D
        */
        HoldBomb,

        /**
         * @brief N/D
        */
        IdleFidget,

        /**
         * @brief N/D
        */
        IdleScared,

        /**
         * @brief N/D
        */
        IdleScaredFidget,

        /**
         * @brief N/D
        */
        FollowIdle,

        /**
         * @brief N/D
        */
        FollowIdleFidget,

        /**
         * @brief N/D
        */
        FollowIdleScared,

        /**
         * @brief N/D
        */
        FollowIdleScaredFidget,

        /**
         * @brief N/D
        */
        CrouchIdle2,

        /**
         * @brief N/D
        */
        CrouchIdleFidget,

        /**
         * @brief N/D
        */
        CrouchIdleScared,

        /**
         * @brief N/D
        */
        CrouchIdleScaredFidget,

        /**
         * @brief N/D
        */
        CrouchWalk,

        /**
         * @brief N/D
        */
        CrouchWalkScared,

        /**
         * @brief N/D
        */
        CrouchDie,

        /**
         * @brief N/D
        */
        WalkBack,

        /**
         * @brief N/D
        */
        IdleSneaky,

        /**
         * @brief N/D
        */
        IdleSneakyFidget,

        /**
         * @brief N/D
        */
        WalkSneaky,

        /**
         * @brief N/D
        */
        Wave,

        /**
         * @brief N/D
        */
        Yes,

        /**
         * @brief N/D
        */
        No
    };
}
