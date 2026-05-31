#pragma once

enum class NextClientUsing
{
    NOT_USING,
    DECLARE_USING,
    USING_VERIFIED
};

// clang-format off
enum NextClientFeatures
{
    FEATURE_CVARS_SANDBOX         = 1 << 0,
    FEATURE_VIEWMODEL_FX          = 1 << 1,
    FEATURE_PRIVATE_PRECACHE      = 1 << 2,
    FEATURE_VERIFICATION          = 1 << 3,
    FEATURE_HUD_SPRITE            = 1 << 4,
    FEATURE_HUD_SPRITE_RENDERMODE = 1 << 5,
    FEATURE_DEATHMSG_WPN_ICON     = 1 << 6,
    FEATURE_WEAPON_SOUND_OVERRIDE = 1 << 7,
    FEATURE_INVERT_MOUSE          = 1 << 8,
};
// clang-format on
