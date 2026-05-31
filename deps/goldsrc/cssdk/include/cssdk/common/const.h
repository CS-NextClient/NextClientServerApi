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

#include <climits>
#include <cstddef>
#include <cstdint>
#include <limits>

namespace cssdk
{
    /**
     * @brief N/D
     */
    using int8 = std::int8_t;

    /**
     * @brief N/D
     */
    using uint8 = std::uint8_t;

    /**
     * @brief N/D
     */
    using int16 = std::int16_t;

    /**
     * @brief N/D
     */
    using uint16 = std::uint16_t;

    /**
     * @brief N/D
     */
    using int32 = std::int32_t;

    /**
     * @brief N/D
     */
    using uint32 = std::uint32_t;

    /**
     * @brief N/D
     */
    using int64 = std::int64_t;

    /**
     * @brief N/D
     */
    using uint64 = std::uint64_t;

    /**
     * @brief N/D
     */
    using qboolean = int;

    /**
     * @brief N/D
     */
    using byte = unsigned char;

    /**
     * @brief N/D
     */
    using crc32 = unsigned int;

    /**
     * @brief Byte offset of an \c Edict in the engine's list of entities.
     * More explicit than \c int.
     */
    using eoffset = int;

    /**
     * @brief N/D
     */
    constexpr auto DOUBLE_PI = 3.141592653589793;

    /**
     * @brief N/D
     */
    constexpr auto DOUBLE_EPSILON = std::numeric_limits<double>::epsilon();

    /**
     * @brief N/D
     */
    constexpr auto FLOAT_PI = static_cast<float>(DOUBLE_PI);

    /**
     * @brief N/D
     */
    constexpr auto FLOAT_EPSILON = std::numeric_limits<float>::epsilon();

    /**
     * @brief N/D
     */
    constexpr auto DEGREES_PER_RADIAN = static_cast<float>(180. / DOUBLE_PI);

    /**
     * @brief N/D
     */
    constexpr auto RADIANS_PER_DEGREE = static_cast<float>(DOUBLE_PI / 180.);

    /**
     * @brief Max # of clients allowed in a server.
     */
    constexpr auto MAX_CLIENTS = 32;

    /**
     * @brief The maximum entity leafs.
     */
    constexpr auto MAX_ENT_LEAFS = 48;

    /**
     * @brief N/D
     */
    constexpr auto MAX_RESOURCE_PATH_LENGTH = 64;

    /**
     * @brief N/D
     */
    constexpr auto INVALID_INDEX = -1;

    /**
     * @brief N/D
     */
    constexpr auto TR_IGNORE_NONE = 0;

    /**
     * @brief Ignore monsters (entities that don't have \c MoveTypeEntity::PushStep).
     */
    constexpr auto TR_IGNORE_MONSTERS = 1;

    /**
     * @brief Use missile bounds (-15 -15 -15, 15, 15, 15).
     */
    constexpr auto TR_IGNORE_MISSILE = 2;

    /**
     * @brief Ignore transparent entities.
     * Transparent entities have a render mode other than \c RENDER_NORMAL and
     * don't have the flag \c FL_WORLD_BRUSH set.
     *
     * @note Aside from TR_IGNORE_GLASS, all flags are mutually exclusive and
     * cannot be used in combination with each other.
     */
    constexpr auto TR_IGNORE_GLASS = 0x100;

    /**
     * @brief N/D
     */
    constexpr auto MAX_PHYS_INFO_STRING = 256;

    /**
     * @brief N/D
     */
    constexpr auto MAX_LIGHT_STYLE_INDEX_BITS = 6;

    /**
     * @brief N/D
     */
    constexpr auto MAX_LIGHT_STYLES = 1 << MAX_LIGHT_STYLE_INDEX_BITS;

    /**
     * @brief N/D
     */
    constexpr auto MAX_LIGHT_STYLE_SIZE = std::size_t{64};

    /**
     * @brief N/D
     */
    constexpr auto MAX_MODEL_INDEX_BITS = 9;

    /**
     * @brief N/D
     */
    constexpr auto MAX_MODELS = 1 << MAX_MODEL_INDEX_BITS;

    /**
     * @brief N/D
     */
    constexpr auto MAX_SOUND_INDEX_BITS = 9;

    /**
     * @brief N/D
     */
    constexpr auto MAX_SOUNDS = 1 << MAX_SOUND_INDEX_BITS;

    /**
     * @brief N/D
     */
    constexpr auto MAX_SOUNDS_HASH_LOOKUP_SIZE = MAX_SOUNDS * 2 - 1;

    /**
     * @brief N/D
     */
    constexpr auto MAX_GENERIC_INDEX_BITS = 9;

    /**
     * @brief N/D
     */
    constexpr auto MAX_GENERIC = 1 << MAX_GENERIC_INDEX_BITS;

    /**
     * @brief N/D
     */
    constexpr auto MAX_DECAL_INDEX_BITS = 9;

    /**
     * @brief N/D
     */
    constexpr auto MAX_BASE_DECALS = 1 << MAX_DECAL_INDEX_BITS;

    /**
     * @brief N/D
     */
    constexpr auto MAX_EVENTS = 256;

    /**
     * @brief Visible entities per frame.
     */
    constexpr auto MAX_PACKET_ENTITIES = 256;

    /**
     * @brief Half-Life regular version.
     */
    constexpr auto BSP_VERSION = 30;

    /**
     * @brief N/D
     */
    constexpr auto MAX_MAP_HULLS = 4;

    /**
     * @brief N/D
     */
    constexpr auto CONTENTS_EMPTY = -1;

    /**
     * @brief N/D
     */
    constexpr auto CONTENTS_SOLID = -2;

    /**
     * @brief N/D
     */
    constexpr auto CONTENTS_WATER = -3;

    /**
     * @brief N/D
     */
    constexpr auto CONTENTS_SLIME = -4;

    /**
     * @brief N/D
     */
    constexpr auto CONTENTS_LAVA = -5;

    /**
     * @brief N/D
     */
    constexpr auto CONTENTS_SKY = -6;

    /**
     * @brief Removed at csg time.
     */
    constexpr auto CONTENTS_ORIGIN = -7;

    /**
     * @brief Changed to \c CONTENTS_SOLID.
     */
    constexpr auto CONTENTS_CLIP = -8;

    /**
     * @brief N/D
     */
    constexpr auto CONTENTS_CURRENT_0 = -9;

    /**
     * @brief N/D
     */
    constexpr auto CONTENTS_CURRENT_90 = -10;

    /**
     * @brief N/D
     */
    constexpr auto CONTENTS_CURRENT_180 = -11;

    /**
     * @brief N/D
     */
    constexpr auto CONTENTS_CURRENT_270 = -12;

    /**
     * @brief N/D
     */
    constexpr auto CONTENTS_CURRENT_UP = -13;

    /**
     * @brief N/D
     */
    constexpr auto CONTENTS_CURRENT_DOWN = -14;

    /**
     * @brief N/D
     */
    constexpr auto CONTENTS_TRANSLUCENT = -15;

    /**
     * @brief N/D
     */
    constexpr auto CONTENTS_LADDER = -16;

    /**
     * @brief N/D
     */
    constexpr auto CONTENTS_FLY_FIELD = -17;

    /**
     * @brief N/D
     */
    constexpr auto CONTENTS_GRAVITY_FLY_FIELD = -18;

    /**
     * @brief N/D
     */
    constexpr auto CONTENTS_FOG = -19;

    /**
     * @brief N/D
     */
    constexpr auto LUMP_ENTITIES = 0;

    /**
     * @brief N/D
     */
    constexpr auto LUMP_PLANES = 1;

    /**
     * @brief N/D
     */
    constexpr auto LUMP_TEXTURES = 2;

    /**
     * @brief N/D
     */
    constexpr auto LUMP_VERTEXES = 3;

    /**
     * @brief N/D
     */
    constexpr auto LUMP_VISIBILITY = 4;

    /**
     * @brief N/D
     */
    constexpr auto LUMP_NODES = 5;

    /**
     * @brief N/D
     */
    constexpr auto LUMP_TEX_INFO = 6;

    /**
     * @brief N/D
     */
    constexpr auto LUMP_FACES = 7;

    /**
     * @brief N/D
     */
    constexpr auto LUMP_LIGHTING = 8;

    /**
     * @brief N/D
     */
    constexpr auto LUMP_CLIP_NODES = 9;

    /**
     * @brief N/D
     */
    constexpr auto LUMP_LEAFS = 10;

    /**
     * @brief N/D
     */
    constexpr auto LUMP_MARK_SURFACES = 11;

    /**
     * @brief N/D
     */
    constexpr auto LUMP_EDGES = 12;

    /**
     * @brief N/D
     */
    constexpr auto LUMP_SURF_EDGES = 13;

    /**
     * @brief N/D
     */
    constexpr auto LUMP_MODELS = 14;

    /**
     * @brief N/D
     */
    constexpr auto HEADER_LUMPS = 15;

    /**
     * @brief N/D
     */
    constexpr auto MIP_LEVELS = 4;

    /**
     * @brief N/D
     */
    constexpr auto MAX_LIGHT_MAPS = 4;

    /**
     * @brief Automatic ambient sounds.
     */
    constexpr auto NUM_AMBIENTS = 4;

    //
    //    Volume values.
    //

    /**
     * @brief N/D
     */
    constexpr auto VOL_NORM = 1.F;

    //
    //    Attenuation values.
    //

    /**
     * @brief N/D
     */
    constexpr auto ATTN_NONE = 0.F;

    /**
     * @brief N/D
     */
    constexpr auto ATTN_NORM = 0.8F;

    /**
     * @brief N/D
     */
    constexpr auto ATTN_STATIC = 1.25F;

    /**
     * @brief N/D
     */
    constexpr auto ATTN_IDLE = 2.F;

    //
    //    Pitch values.
    //

    /**
     * @brief N/D
     */
    constexpr auto PITCH_LOW = 95;

    /**
     * @brief N/D
     */
    constexpr auto PITCH_NORM = 100;

    /**
     * @brief N/D
     */
    constexpr auto PITCH_HIGH = 120;

    //
    //    Temp entity events.
    //

    /**
     * @brief Beam effect between two points.
     */
    constexpr auto TE_BEAM_POINTS = 0;

    /**
     * @brief Beam effect between point and entity.
     */
    constexpr auto TE_BEAM_ENT_POINT = 1;

    /**
     * @brief Particle effect plus ricochet sound.
     */
    constexpr auto TE_GUNSHOT = 2;

    /**
     * @brief Additive sprite, 2 dynamic lights, flickering particles, explosion sound, move vertically 8 pps.
     */
    constexpr auto TE_EXPLOSION = 3;

    /**
     * @brief Quake 1 "tarbaby" explosion with sound.
     */
    constexpr auto TE_TAR_EXPLOSION = 4;

    /**
     * @brief Alphablend sprite, move vertically 30 pps.
     */
    constexpr auto TE_SMOKE = 5;

    /**
     * @brief Tracer effect from point to point.
     */
    constexpr auto TE_TRACER = 6;

    /**
     * @brief TE_BEAM_POINTS with simplified parameters.
     */
    constexpr auto TE_LIGHTNING = 7;

    /**
     * @brief N/D
     */
    constexpr auto TE_BEAM_ENTITIES = 8;

    /**
     * @brief 8 random tracers with gravity, ricochet sprite.
     */
    constexpr auto TE_SPARKS = 9;

    /**
     * @brief Quake 1 lava splash.
     */
    constexpr auto TE_LAVA_SPLASH = 10;

    /**
     * @brief Quake 1 teleport splash.
     */
    constexpr auto TE_TELEPORT = 11;

    /**
     * @brief Quake 1 colormaped (base palette) particle explosion with sound.
     */
    constexpr auto TE_EXPLOSION2 = 12;

    /**
     * @brief Decal from the .BSP file.
     */
    constexpr auto TE_BSP_DECAL = 13;

    /**
     * @brief Tracers moving toward a point.
     */
    constexpr auto TE_IMPLOSION = 14;

    /**
     * @brief Line of moving glow sprites with gravity, fadeout, and collisions.
     */
    constexpr auto TE_SPRITE_TRAIL = 15;

    /**
     * @brief Obsolete.
     */
    constexpr auto TE_BEAM = 16;

    /**
     * @brief Additive sprite, plays 1 cycle.
     */
    constexpr auto TE_SPRITE = 17;

    /**
     * @brief A beam with a sprite at the end.
     */
    constexpr auto TE_BEAM_SPRITE = 18;

    /**
     * @brief Screen aligned beam ring, expands to max radius over lifetime.
     */
    constexpr auto TE_BEAM_TORUS = 19;

    /**
     * @brief Disk that expands to max radius over lifetime.
     */
    constexpr auto TE_BEAM_DISK = 20;

    /**
     * @brief Cylinder that expands to max radius over lifetime.
     */
    constexpr auto TE_BEAM_CYLINDER = 21;

    /**
     * @brief Create a line of decaying beam segments until entity stops moving.
     */
    constexpr auto TE_BEAM_FOLLOW = 22;

    /**
     * @brief N/D
     */
    constexpr auto TE_GLOW_SPRITE = 23;

    /**
     * @brief Connect a beam ring to two entities.
     */
    constexpr auto TE_BEAM_RING = 24;

    /**
     * @brief Oriented shower of tracers.
     */
    constexpr auto TE_STREAK_SPLASH = 25;

    /**
     * @brief Obsolete.
     */
    constexpr auto TE_BEAM_HOSE = 26;

    /**
     * @brief Dynamic light, effect world, minor entity effect.
     */
    constexpr auto TE_DYN_LIGHT = 27;

    /**
     * @brief Point entity light, no world effect.
     */
    constexpr auto TE_ENT_LIGHT = 28;

    /**
     * @brief N/D
     */
    constexpr auto TE_TEXT_MESSAGE = 29;

    /**
     * @brief N/D
     */
    constexpr auto TE_LINE = 30;

    /**
     * @brief N/D
     */
    constexpr auto TE_BOX = 31;

    /**
     * @brief Kill all beams attached to entity.
     */
    constexpr auto TE_KILL_BEAM = 99;

    /**
     * @brief N/D
     */
    constexpr auto TE_LARGE_FUNNEL = 100;

    /**
     * @brief Particle spray.
     */
    constexpr auto TE_BLOODSTREAM = 101;

    /**
     * @brief Line of particles every 5 units, dies in 30 seconds.
     */
    constexpr auto TE_SHOW_LINE = 102;

    /**
     * @brief Particle spray.
     */
    constexpr auto TE_BLOOD = 103;

    /**
     * @brief Decal applied to a brush entity (not the world).
     */
    constexpr auto TE_DECAL = 104;

    /**
     * @brief Create alpha sprites inside of entity, float upwards.
     */
    constexpr auto TE_FIZZ = 105;

    /**
     * @brief Create a moving model that bounces and makes a sound when it hits.
     */
    constexpr auto TE_MODEL = 106;

    /**
     * @brief Spherical shower of models, picks from set.
     */
    constexpr auto TE_EXPLODE_MODEL = 107;

    /**
     * @brief Box of models or sprites.
     */
    constexpr auto TE_BREAK_MODEL = 108;

    /**
     * @brief Decal and ricochet sound.
     */
    constexpr auto TE_GUNSHOT_DECAL = 109;

    /**
     * @brief Spray of alpha sprites.
     */
    constexpr auto TE_SPRITE_SPRAY = 110;

    /**
     * @brief Quick spark sprite, client ricochet sound.
     */
    constexpr auto TE_ARMOR_RICOCHET = 111;

    /**
     * @brief N/D
     */
    constexpr auto TE_PLAYER_DECAL = 112;

    /**
     * @brief Create alpha sprites inside of box, float upwards.
     */
    constexpr auto TE_BUBBLES = 113;

    /**
     * @brief Create alpha sprites along a line, float upwards.
     */
    constexpr auto TE_BUBBLE_TRAIL = 114;

    /**
     * @brief Spray of opaque sprite1's that fall, single sprite2 for 1..2 secs (this is a high-priority temp entity).
     */
    constexpr auto TE_BLOOD_SPRITE = 115;

    /**
     * @brief Decal applied to the world brush.
     */
    constexpr auto TE_WORLD_DECAL = 116;

    /**
     * @brief Decal (with texture index > 256) applied to world brush.
     */
    constexpr auto TE_WORLD_DECAL_HIGH = 117;

    /**
     * @brief Same as TE_DECAL, but the texture index was greater than 256.
     */
    constexpr auto TE_DECAL_HIGH = 118;

    /**
     * @brief Makes a projectile (like a nail) (this is a high-priority temp entity).
     */
    constexpr auto TE_PROJECTILE = 119;

    /**
     * @brief Throws a shower of sprites or models.
     */
    constexpr auto TE_SPRAY = 120;

    /**
     * @brief Sprites emit from a player's bounding box (ONLY use for players!).
     */
    constexpr auto TE_PLAYER_SPRITES = 121;

    /**
     * @brief Very similar to \c TE_LAVA_SPLASH.
     */
    constexpr auto TE_PARTICLE_BURST = 122;

    /**
     * @brief Makes a field of fire.
     */
    constexpr auto TE_FIRE_FIELD = 123;

    /**
     * @brief Attaches a temp entity to a player (this is a high-priority temp entity).
     */
    constexpr auto TE_PLAYER_ATTACHMENT = 124;

    /**
     * @brief Will expire all TENTS attached to a player.
     */
    constexpr auto TE_KILL_PLAYER_ATTACHMENTS = 125;

    /**
     * @brief Much more compact shotgun message.
     */
    constexpr auto TE_MULTI_GUNSHOT = 126;

    /**
     * @brief Larger message than the standard tracer, but allows some customization.
     */
    constexpr auto TE_USER_TRACER = 127;

    //
    //    Temp entity bounce sound types.
    //

    /**
     * @brief N/D
     */
    constexpr auto TE_BOUNCE_NULL = 0;

    /**
     * @brief N/D
     */
    constexpr auto TE_BOUNCE_SHELL = 1;

    /**
     * @brief N/D
     */
    constexpr auto TE_BOUNCE_SHOT_SHELL = 2;

    //
    //    The explosion effect has some flags to control performance/aesthetic features.
    //

    /**
     * @brief All flags clear makes default Half-Life explosion.
     */
    constexpr auto TE_EXPL_FLAG_NONE = 0;

    /**
     * @brief Sprite will be drawn opaque (ensure that the sprite you send is a non-additive sprite).
     */
    constexpr auto TE_EXPL_FLAG_NO_ADDITIVE = 1;

    /**
     * @brief Do not render dynamic lights.
     */
    constexpr auto TE_EXPL_FLAG_NO_DYN_LIGHTS = 2;

    /**
     * @brief Do not play client explosion sound.
     */
    constexpr auto TE_EXPL_FLAG_NO_SOUND = 4;

    /**
     * @brief Do not draw particles.
     */
    constexpr auto TE_EXPL_FLAG_NO_PARTICLES = 8;

    //
    // Event flags.
    //

    /**
     * @brief Skip local host for event send.
     */
    constexpr auto FEV_NOT_HOST = 1 << 0;

    /**
     * @brief Send the event reliably.
     * You must specify the origin and angles and use \c playback_event
     * for this to work correctly on the server for anything that depends on the event origin/angles.
     * I.e., the origin/angles are not taken from the invoking edict for reliable events.
     */
    constexpr auto FEV_RELIABLE = 1 << 1;

    /**
     * @brief Don't restrict to PAS/PVS, send this event to _everybody_ on the server
     * (useful for stopping \c SoundChannel::Static sounds started by client event
     * when client is not in PVS anymore (hwguy in TFC e.g.).
     */
    constexpr auto FEV_GLOBAL = 1 << 2;

    /**
     * @brief If this client already has one of these events in its queue,
     * just update the event instead of sending it as a duplicate.
     */
    constexpr auto FEV_UPDATE = 1 << 3;

    /**
     * @brief Only send to entity specified as the invoker.
     */
    constexpr auto FEV_HOST_ONLY = 1 << 4;

    /**
     * @brief Only send if the event was created on the server.
     */
    constexpr auto FEV_SERVER = 1 << 5;

    /**
     * @brief Only issue event client side (from shared code).
     */
    constexpr auto FEV_CLIENT = 1 << 6;

    //
    //    Entity effects.
    //

    /**
     * @brief Swirling cloud of particles.
     */
    constexpr auto EF_BRIGHT_FIELD = 1 << 0;

    /**
     * @brief Single frame ELIGHT on entity attachment 0.
     */
    constexpr auto EF_MUZZLE_FLASH = 1 << 1;

    /**
     * @brief DLIGHT centered at entity origin.
     */
    constexpr auto EF_BRIGHT_LIGHT = 1 << 2;

    /**
     * @brief Player flashlight.
     */
    constexpr auto EF_DIM_LIGHT = 1 << 3;

    /**
     * @brief Get lighting from ceiling.
     */
    constexpr auto EF_INV_LIGHT = 1 << 4;

    /**
     * @brief Don't interpolate the next frame.
     */
    constexpr auto EF_NO_INTERPOLATE = 1 << 5;

    /**
     * @brief Rocket flare glow sprite.
     */
    constexpr auto EF_LIGHT = 1 << 6;

    /**
     * @brief Don't draw entity.
     */
    constexpr auto EF_NO_DRAW = 1 << 7;

    /**
     * @brief Player night vision.
     */
    constexpr auto EF_NIGHT_VISION = 1 << 8;

    /**
     * @brief Sniper laser effect.
     */
    constexpr auto EF_SNIPER_LASER = 1 << 9;

    /**
     * @brief Fiber camera.
     */
    constexpr auto EF_FIBER_CAMERA = 1 << 10;

    /**
     * @brief N/D
     */
    constexpr auto EF_FORCE_VISIBILITY = 1 << 11;

    /**
     * @brief N/D
     */
    constexpr auto EF_OWNER_VISIBILITY = 1 << 12;

    /**
     * @brief N/D
     */
    constexpr auto EF_OWNER_NO_VISIBILITY = 1 << 13;

    //
    //    Take damage mode.
    //

    /**
     * @brief Don't take damage.
     */
    constexpr auto DAMAGE_NO = 0;

    /**
     * @brief Take damage.
     */
    constexpr auto DAMAGE_YES = 1;

    /**
     * @brief Take damage, auto aim should snap to this target.
     */
    constexpr auto DAMAGE_AIM = 2;

    //
    //    Buttons.
    //

    /**
     * @brief N/D
     */
    constexpr auto IN_ATTACK = 1 << 0;

    /**
     * @brief N/D
     */
    constexpr auto IN_JUMP = 1 << 1;

    /**
     * @brief N/D
     */
    constexpr auto IN_DUCK = 1 << 2;

    /**
     * @brief N/D
     */
    constexpr auto IN_FORWARD = 1 << 3;

    /**
     * @brief N/D
     */
    constexpr auto IN_BACK = 1 << 4;

    /**
     * @brief N/D
     */
    constexpr auto IN_USE = 1 << 5;

    /**
     * @brief N/D
     */
    constexpr auto IN_CANCEL = 1 << 6;

    /**
     * @brief N/D
     */
    constexpr auto IN_LEFT = 1 << 7;

    /**
     * @brief N/D
     */
    constexpr auto IN_RIGHT = 1 << 8;

    /**
     * @brief N/D
     */
    constexpr auto IN_MOVE_LEFT = 1 << 9;

    /**
     * @brief N/D
     */
    constexpr auto IN_MOVE_RIGHT = 1 << 10;

    /**
     * @brief N/D
     */
    constexpr auto IN_ATTACK2 = 1 << 11;

    /**
     * @brief N/D
     */
    constexpr auto IN_RUN = 1 << 12;

    /**
     * @brief N/D
     */
    constexpr auto IN_RELOAD = 1 << 13;

    /**
     * @brief N/D
     */
    constexpr auto IN_ALT1 = 1 << 14;

    /**
     * @brief Used by client.dll for when scoreboard is held down.
     */
    constexpr auto IN_SCORE = 1 << 15;

    //
    //    Entity flags.
    //

    /**
     * @brief Changes the \c SV_Movestep() behavior to not need to be on ground.
     */
    constexpr auto FL_FLY = 1 << 0;

    /**
     * @brief Changes the \c SV_Movestep() behavior to not need to be on ground (but stay in water).
     */
    constexpr auto FL_SWIM = 1 << 1;

    /**
     * @brief N/D
     */
    constexpr auto FL_CONVEYOR = 1 << 2;

    /**
     * @brief N/D
     */
    constexpr auto FL_CLIENT = 1 << 3;

    /**
     * @brief N/D
     */
    constexpr auto FL_IN_WATER = 1 << 4;

    /**
     * @brief N/D
     */
    constexpr auto FL_MONSTER = 1 << 5;

    /**
     * @brief N/D
     */
    constexpr auto FL_GOD_MODE = 1 << 6;

    /**
     * @brief N/D
     */
    constexpr auto FL_NO_TARGET = 1 << 7;

    /**
     * @brief Don't send entity to local host, it's predicting this entity itself.
     */
    constexpr auto FL_SKIP_LOCAL_HOST = 1 << 8;

    /**
     * @brief At rest / on the ground.
     */
    constexpr auto FL_ON_GROUND = 1 << 9;

    /**
     * @brief Not all corners are valid.
     */
    constexpr auto FL_PARTIAL_GROUND = 1 << 10;

    /**
     * @brief Player jumping out of water.
     */
    constexpr auto FL_WATER_JUMP = 1 << 11;

    /**
     * @brief Player is frozen for 3rd person camera.
     */
    constexpr auto FL_FROZEN = 1 << 12;

    /**
     * @brief Fake client, simulated server side; don't send network messages to them.
     */
    constexpr auto FL_FAKE_CLIENT = 1 << 13;

    /**
     * @brief Player flag -- Player is fully crouched.
     */
    constexpr auto FL_DUCKING = 1 << 14;

    /**
     * @brief Apply floating force to this entity when in water.
     */
    constexpr auto FL_FLOAT = 1 << 15;

    /**
     * @brief World graph has this entity listed as something that blocks a connection.
     */
    constexpr auto FL_GRAPHED = 1 << 16;

    /**
     * @brief N/D
     */
    constexpr auto FL_IMMUNE_WATER = 1 << 17;

    /**
     * @brief N/D
     */
    constexpr auto FL_IMMUNE_SLIME = 1 << 18;

    /**
     * @brief N/D
     */
    constexpr auto FL_IMMUNE_LAVA = 1 << 19;

    /**
     * @brief This is a spectator proxy.
     */
    constexpr auto FL_PROXY = 1 << 20;

    /**
     * @brief Brush model flag - call think every frame regardless of
     * next_think - last_think (for constantly changing velocity/path).
     */
    constexpr auto FL_ALWAYS_THINK = 1 << 21;

    /**
     * @brief Base velocity has been applied this frame (used to convert base velocity into momentum).
     */
    constexpr auto FL_BASE_VELOCITY = 1 << 22;

    /**
     * @brief Only collide in with monsters who have FL_MONSTER_CLIP set.
     */
    constexpr auto FL_MONSTER_CLIP = 1 << 23;

    /**
     * @brief Player is _controlling_ a train, so movement commands should be ignored on client during prediction.
     */
    constexpr auto FL_ON_TRAIN = 1 << 24;

    /**
     * @brief Not moveable/removeable brush entity (really part of the world,
     * but represented as an entity for transparency or something).
     */
    constexpr auto FL_WORLD_BRUSH = 1 << 25;

    /**
     * @brief This client is a spectator, don't run touch functions, etc.
     */
    constexpr auto FL_SPECTATOR = 1 << 26;

    /**
     * @brief This is a custom entity.
     */
    constexpr auto FL_CUSTOM_ENTITY = 1 << 29;

    /**
     * @brief This entity is marked for death -- This allows the engine to kill entities at the appropriate time.
     */
    constexpr auto FL_KILL_ME = 1 << 30;

    /**
     * @brief Entity is dormant, no updates to client.
     */
    constexpr auto FL_DORMANT = INT_MIN;

    enum class HitBoxGroup : int
    {
        /**
         * @brief N/D
         */
        Generic = 0,

        /**
         * @brief N/D
         */
        Head,

        /**
         * @brief N/D
         */
        Chest,

        /**
         * @brief N/D
         */
        Stomach,

        /**
         * @brief N/D
         */
        LeftArm,

        /**
         * @brief N/D
         */
        RightArm,

        /**
         * @brief N/D
         */
        LeftLeg,

        /**
         * @brief N/D
         */
        RightLeg,

        /**
         * @brief N/D
         */
        Shield,

        /**
         * @brief N/D
         */
        NumHitGroups
    };

    enum class MoveTypeNpc
    {
        /**
         * @brief Normal move in the direction monster is facing.
         */
        Normal = 0,

        /**
         * @brief Moves in direction specified, no matter which way monster is facing.
         */
        Strafe
    };

    enum class SoundChannel
    {
        /**
         * @brief N/D
         */
        Auto = 0,

        /**
         * @brief N/D
         */
        Weapon,

        /**
         * @brief N/D
         */
        Voice,

        /**
         * @brief N/D
         */
        Item,

        /**
         * @brief N/D
         */
        Body,

        /**
         * @brief Allocate stream channel from the static or dynamic area.
         */
        Stream,

        /**
         * @brief Allocate channel from the static area.
         */
        Static,

        /**
         * @brief Voice data coming across the network.
         */
        NetworkVoiceBase,

        /**
         * @brief Network voice data reserves slots (c_network_voice_base through c_network_voice_end).
         */
        NetworkVoiceEnd = 500,

        /**
         * @brief N/D
         */
        Bot
    };

    enum class WalkMoveMode
    {
        /**
         * @brief Normal walk move.
         */
        Normal = 0,

        /**
         * @brief Doesn't hit ANY entities, no matter what the solid type.
         */
        WorldOnly,

        /**
         * @brief Move, but don't touch triggers.
         */
        CheckOnly
    };

    enum class MoveTypeEntity
    {
        /**
         * @brief Never moves.
         */
        None = 0,

        // AngleNoClip,
        // AngleClip,

        /**
         * @brief Player only - moving on the ground.
         */
        Walk = 3,

        /**
         * @brief Gravity, special edge handling - monsters use this.
         */
        Step,

        /**
         * @brief No gravity, but still collides with stuff.
         */
        Fly,

        /**
         * @brief Gravity/collisions.
         */
        Toss,

        /**
         * @brief No clip to world, push and crush.
         */
        Push,

        /**
         * @brief No gravity, no collisions, still do velocity.
         */
        NoClip,

        /**
         * @brief Extra size to monsters.
         */
        FlyMissile,

        /**
         * @brief Just like Toss, but reflect velocity when contacting surfaces.
         */
        Bounce,

        /**
         * @brief Bounce without gravity.
         */
        BounceMissile,

        /**
         * @brief Track movement of aim entity.
         */
        Follow,

        /**
         * @brief BSP model that needs physics/world collisions (uses nearest hull for world collision).
         */
        PushStep
    };

    enum class MessageType : int
    {
        /**
         * @brief Unreliable to all.
         */
        Broadcast = 0,

        /**
         * @brief Reliable to one (msg_entity).
         */
        One,

        /**
         * @brief Reliable to all.
         */
        All,

        /**
         * @brief Write to the init string.
         */
        Init,

        /**
         * @brief Entities in PVS of origin.
         */
        Pvs,

        /**
         * @brief Entities in PAS of origin.
         */
        Pas,

        /**
         * @brief Reliable to PVS.
         */
        PvsReliable,

        /**
         * @brief Reliable to PAS.
         */
        PasReliable,

        /**
         * @brief Send to one client, but don't put in reliable stream, put in unreliable datagram (could be dropped).
         */
        OneUnreliable,

        /**
         * @brief Sends to all spectator proxies.
         */
        Spec
    };

    enum class SvcMessage : int
    {
        /**
         * @brief N/D
         */
        Bad = 0,

        /**
         * @brief N/D
         */
        Nop,

        /**
         * @brief N/D
         */
        Disconnect,

        /**
         * @brief N/D
         */
        Event,

        /**
         * @brief N/D
         */
        Version,

        /**
         * @brief N/D
         */
        SetView,

        /**
         * @brief N/D
         */
        Sound,

        /**
         * @brief N/D
         */
        Time,

        /**
         * @brief N/D
         */
        Print,

        /**
         * @brief N/D
         */
        StuffText,

        /**
         * @brief N/D
         */
        SetAngle,

        /**
         * @brief N/D
         */
        ServerInfo,

        /**
         * @brief N/D
         */
        LightStyle,

        /**
         * @brief N/D
         */
        UpdateUserInfo,

        /**
         * @brief N/D
         */
        DeltaDescription,

        /**
         * @brief N/D
         */
        ClientData,

        /**
         * @brief N/D
         */
        StopSound,

        /**
         * @brief N/D
         */
        Pings,

        /**
         * @brief N/D
         */
        Particle,

        /**
         * @brief N/D
         */
        Damage,

        /**
         * @brief N/D
         */
        SpawnStatic,

        /**
         * @brief N/D
         */
        EventReliable,

        /**
         * @brief N/D
         */
        SpawnBaseline,

        /**
         * @brief N/D
         */
        TempEntity,

        /**
         * @brief N/D
         */
        SetPause,

        /**
         * @brief N/D
         */
        SignonNum,

        /**
         * @brief N/D
         */
        CenterPrint,

        /**
         * @brief N/D
         */
        KilledMonster,

        /**
         * @brief N/D
         */
        FoundSecret,

        /**
         * @brief N/D
         */
        SpawnStaticSound,

        /**
         * @brief N/D
         */
        Intermission,

        /**
         * @brief N/D
         */
        Finale,

        /**
         * @brief N/D
         */
        CdTrack,

        /**
         * @brief N/D
         */
        Restore,

        /**
         * @brief N/D
         */
        CutScene,

        /**
         * @brief N/D
         */
        WeaponAnim,

        /**
         * @brief N/D
         */
        DecalName,

        /**
         * @brief N/D
         */
        RoomType,

        /**
         * @brief N/D
         */
        AddAngle,

        /**
         * @brief N/D
         */
        NewUserMsg,

        /**
         * @brief N/D
         */
        PacketEntities,

        /**
         * @brief N/D
         */
        DeltaPacketEntities,

        /**
         * @brief N/D
         */
        Choke,

        /**
         * @brief N/D
         */
        ResourceList,

        /**
         * @brief N/D
         */
        NewMoveVars,

        /**
         * @brief N/D
         */
        ResourceRequest,

        /**
         * @brief N/D
         */
        Customization,

        /**
         * @brief N/D
         */
        CrosshairAngle,

        /**
         * @brief N/D
         */
        SoundFade,

        /**
         * @brief N/D
         */
        FileTxferFailed,

        /**
         * @brief N/D
         */
        Hltv,

        /**
         * @brief N/D
         */
        Director,

        /**
         * @brief N/D
         */
        VoiceInit,

        /**
         * @brief N/D
         */
        VoiceData,

        /**
         * @brief N/D
         */
        SendExtraInfo,

        /**
         * @brief N/D
         */
        Timescale,

        /**
         * @brief N/D
         */
        ResourceLocation,

        /**
         * @brief N/D
         */
        SendCvarValue,

        /**
         * @brief N/D
         */
        SendCvarValue2,

        /**
         * @brief N/D
         */
        Exec,

        /**
         * @brief N/D
         */
        Reserve60,

        /**
         * @brief N/D
         */
        Reserve61,

        /**
         * @brief N/D
         */
        Reserve62,

        /**
         * @brief N/D
         */
        Reserve63,

#ifdef REHLDS_FIXES
        /**
         * @brief N/D
         */
        StartOfUserMessages,
#else
        /**
         * @brief N/D
         */
        StartOfUserMessages = Exec,
#endif

        /**
         * @brief N/D
         */
        EndOfList = 255
    };

#ifdef REHLDS_FIXES
    static_assert(static_cast<int>(SvcMessage::StartOfUserMessages) == 64,
                  "SvcMessage::StartOfUserMessages should be equal to 64 for backward and forward compatibility.");
#endif

    enum class FixAngleMode
    {
        /**
         * @brief Do nothing.
         */
        Nothing = 0,

        /**
         * @brief Set view angles to \c EntityVars::angles.
         */
        ForceViewAngles,

        /**
         * @brief Add angle velocity yaw value to view angles.
         * Angle velocity yaw value is set to 0 after this.
         */
        AddAngleVelocity
    };

    /**
     * @brief Some move types will cause collisions independent of NotSolid/Trigger when the entity moves.
     * SOLID only effects OTHER entities colliding with this one when they move - UGH!
     */
    enum class SolidType
    {
        /**
         * @brief No interaction with other objects.
         */
        NotSolid = 0,

        /**
         * @brief Touch on edge, but not blocking.
         */
        Trigger,

        /**
         * @brief Touch on edge, block.
         */
        BoundingBox,

        /**
         * @brief Touch on edge, but not an on ground.
         */
        SlideBox,

        /**
         * @brief BSP clip, touch on edge, block.
         */
        Bsp
    };

    enum class Rendering
    {
        /**
         * @brief src.
         */
        Normal = 0,

        /**
         * @brief c * a + dest * (1 - a).
         */
        TransColor,

        /**
         * @brief src * a + dest * (1 - a).
         */
        TransTexture,

        /**
         * @brief src * a + dest -- No Z buffer checks.
         */
        Glow,

        /**
         * @brief src* srca + dest * (1 - srca).
         */
        TransAlpha,

        /**
         * @brief src * a + dest.
         */
        TransAdd
    };

    enum class RenderingFx
    {
        /**
         * @brief N/D
         */
        None = 0,

        /**
         * @brief N/D
         */
        PulseSlow,

        /**
         * @brief N/D
         */
        PulseFast,

        /**
         * @brief N/D
         */
        PulseSlowWide,

        /**
         * @brief N/D
         */
        PulseFastWide,

        /**
         * @brief N/D
         */
        FadeSlow,

        /**
         * @brief N/D
         */
        FadeFast,

        /**
         * @brief N/D
         */
        SolidSlow,

        /**
         * @brief N/D
         */
        SolidFast,

        /**
         * @brief N/D
         */
        StrobeSlow,

        /**
         * @brief N/D
         */
        StrobeFast,

        /**
         * @brief N/D
         */
        StrobeFaster,

        /**
         * @brief N/D
         */
        FlickerSlow,

        /**
         * @brief N/D
         */
        FlickerFast,

        /**
         * @brief N/D
         */
        NoDissipation,

        /**
         * @brief Distort/scale/translate flicker.
         */
        Distort,

        /**
         * @brief distort + distance fade.
         */
        Hologram,

        /**
         * @brief N/D
         */
        DeadPlayer,

        /**
         * @brief Scale up really big!
         */
        Explode,

        /**
         * @brief Glowing shell.
         */
        GlowShell,

        /**
         * @brief Keep this sprite from getting very small (SPRITES only!).
         */
        ClampMinScale,

        /**
         * @brief CTM !!! CZERO added to tell the studio render that the value in i_user2 is a light_multiplier.
         */
        LightMultiplier
    };

    enum class DeathState
    {
        /**
         * @brief Alive.
         */
        Alive = 0,

        /**
         * @brief Playing death animation or still falling off of a ledge waiting to hit ground.
         */
        Dying,

        /**
         * @brief Dead. Lying still.
         */
        Dead,

        /**
         * @brief Dead, and can be respawned.
         */
        Respawnable,

        /**
         * @brief Not used in the SDK, used by TFC for spies feigning death.
         */
        DiscardBody
    };

    enum class ObserverMode
    {
        /**
         * @brief N/D
         */
        None = 0,

        /**
         * @brief N/D
         */
        ChaseLocked,

        /**
         * @brief N/D
         */
        ChaseFree,

        /**
         * @brief N/D
         */
        Roaming,

        /**
         * @brief N/D
         */
        InEye,

        /**
         * @brief N/D
         */
        MapFree,

        /**
         * @brief N/D
         */
        MapChase
    };

    enum class PrintType
    {
        /**
         * @brief N/D
         */
        Console,

        /**
         * @brief N/D
         */
        Center,

        /**
         * @brief N/D
         */
        Chat
    };

    enum class AlertType
    {
        /**
         * @brief N/D
         */
        Notice,

        /**
         * @brief Same as \c Notice, but forces a \c con_print, not a message box.
         */
        Console,

        /**
         * @brief Same as \c console, but only shown if developer level is 2!
         */
        DevConsole,

        /**
         * @brief N/D
         */
        Warning,

        /**
         * @brief N/D
         */
        Error,

        /**
         * @brief Server print to console (only in multiplayer games).
         */
        Logged
    };

    /**
     * @brief For integrity checking of content on clients.
     */
    enum class ForceType
    {
        /**
         * @brief File on client must exactly match server's file.
         */
        ExactFile,

        /**
         * @brief For model files only, the geometry must fit in the same bounding box.
         */
        ModelSameBounds,

        /**
         * @brief For model files only, the geometry must fit in the specified bounding box.
         */
        ModelSpecifyBounds,

        /**
         * @brief For Steam model files only, the geometry must fit in the
         * specified bounding box (if the file is available).
         */
        ModelSpecifyBoundsIfAvail
    };

    struct Color24
    {
        /**
         * @brief N/D
         */
        byte red{};

        /**
         * @brief N/D
         */
        byte green{};

        /**
         * @brief N/D
         */
        byte blue{};

        /**
         * @brief N/D
         */
        [[nodiscard]] bool IsNull() const noexcept
        {
            return red == 0 && green == 0 && blue == 0;
        }
    };

    struct ColorVec
    {
        /**
         * @brief N/D
         */
        unsigned red{};

        /**
         * @brief N/D
         */
        unsigned green{};

        /**
         * @brief N/D
         */
        unsigned blue{};

        /**
         * @brief N/D
         */
        unsigned alpha{};

        /**
         * @brief N/D
         */
        [[nodiscard]] bool IsNull(const bool ignore_alpha = true) const noexcept
        {
            return red == 0 && green == 0 && blue == 0 && (ignore_alpha || alpha == 0);
        }
    };

    struct HudTextParams
    {
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
        float fade_in_time{};

        /**
         * @brief N/D
         */
        float fade_out_time{};

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
        int channel{};
    };
}
