#include <amxmodx>
#include <amxmisc>
#include <fakemeta>
#include <reapi>

#include <next_client_api>

new LOG_FILE[] = "test_nextclient_api.log";

// Automated testing of natives where no human visual control is needed
// It is done in the ncl_client_api_ready() forward.
// #define AUTOTESTS

// Uncomment this if you do not want to check the values of the sandbox CVars yourself
#define AUTO_RESTORE_CVAR_VALUES

// ncl_precache_model() for default, already exists on client models like default weapon models
#define TEST_PRECACHE_AND_REPLACE_DEFAULT_MODELS

// ncl_precache_sound() for default, already exists on client sounds like steps
#define TEST_PRECACHE_AND_REPLACE_DEFAULT_SOUNDS

// Test of replace default hud.txt and HUD sprites
// ncl_precache_hudtxt() & ncl_precache_client_only()
#define TEST_PRECACHE_AND_REPLACE_HUD

// ncl_precache_model() for custom model
#define TEST_PRECACHE_AND_REPLACE_CUSTOM_MODELS

// ncl_precache_sound() for custom sound
#define TEST_PRECACHE_AND_REPLACE_CUSTOM_SOUNDS

new const HUD_SPRITE_KILL[] = "sprites/test_nextclient/hud_sprites/kill.spr"
new const HUD_SPRITE_BLACK_HOLE[] = "sprites/test_nextclient/hud_sprites/ef_blackhole_loop.spr"

public plugin_init() {
    register_plugin("Test NCL API", "1.3.0", "Nordic Warrior");

    // Cmds for testing natives
    // look at next_client_api.inc
    register_concmd("ncl_is_client_api_ready",       "cmd_ncl_is_client_api_ready",      ADMIN_ALL);
    register_concmd("ncl_is_using_nextclient",       "cmd_ncl_is_using_nextclient",      ADMIN_ALL);
    register_concmd("ncl_get_nextclient_version",    "cmd_ncl_get_nextclient_version",   ADMIN_ALL);
    register_concmd("ncl_get_supported_features",    "cmd_ncl_get_supported_features",   ADMIN_ALL);
    register_concmd("ncl_test_sandbox_cvars",        "cmd_ncl_test_sandbox_cvars",       ADMIN_ALL);
    register_concmd("ncl_test_viewmodelfx_skin",     "cmd_ncl_test_viewmodelfx_skin",    ADMIN_ALL);
    register_concmd("ncl_test_viewmodelfx_body",     "cmd_ncl_test_viewmodelfx_body",    ADMIN_ALL);
    register_concmd("ncl_test_viewmodelfx_render",   "cmd_ncl_test_viewmodelfx_render",  ADMIN_ALL);
    register_concmd("ncl_restore_viewmodelfx",       "cmd_ncl_restore_viewmodelfx",      ADMIN_ALL);
    register_concmd("ncl_setfov",                    "cmd_ncl_setfov",                   ADMIN_ALL);
    register_concmd("ncl_hudsprite_set",             "cmd_ncl_hudsprite_set",            ADMIN_ALL); // ncl_send_hud_sprite(), ncl_send_hud_sprite_full_screen()
    register_concmd("ncl_hudsprite_clear",           "cmd_ncl_hudsprite_clear",          ADMIN_ALL); // ncl_clear_hud_sprite()

    // Other cmds
    // For ncl_test_sandbox_cvars() if AUTO_RESTORE_CVAR_VALUES is disabled
    register_concmd("ncl_restore_cvars_values", "cmd_ncl_restore_cvars_values", ADMIN_ALL);
    // For testing HUD limit health
    register_concmd("ncl_add_health", "cmd_ncl_add_health", ADMIN_ALL);
}

/* <== FORWARDS ==> */

public ncl_client_api_ready(id) {
    log_to_file(LOG_FILE, "FORWARD <ncl_client_api_ready> called for player: %n", id);

    #if defined AUTOTESTS
    start_autotests(id);
    #endif

    return PLUGIN_HANDLED;
}

/* <=== END FORWARDS ===> */

/* <== NATIVES ==> */

public cmd_ncl_is_client_api_ready(id) {
    if (id == 0) {
        id = find_player_ex(FindPlayer_MatchUserId, read_argv_int(1));

        if (id == 0) {
            log_amx("Player with userid #%i not found.", read_argv_int(1));
            return PLUGIN_HANDLED;
        }
    }

    log_to_file(LOG_FILE, "NATIVE <ncl_is_client_api_ready> testing called for player: %n", id);
    log_to_file(LOG_FILE, "Result: API ready? %s.", ncl_is_client_api_ready(id)  ? "Yes" : "No");
    return PLUGIN_HANDLED;
}

/* <=======> */

public cmd_ncl_is_using_nextclient(id) {
    if (id == 0) {
        id = find_player_ex(FindPlayer_MatchUserId, read_argv_int(1));

        if (id == 0) {
            log_amx("Player with userid #%i not found.", read_argv_int(1));
            return PLUGIN_HANDLED;
        }
    }

    log_to_file(LOG_FILE, "NATIVE <ncl_is_using_nextclient> testing called for player: %n", id);

    new result[32];
    new eNclUsing:is_using_next_client = ncl_is_using_nextclient(id);

    if (is_using_next_client == NCL_NOT_USING) { 
        result = "NCL_NOT_USING";
    } else if (is_using_next_client == NCL_DECLARE_USING) {
        result = "NCL_DECLARE_USING";
    } else if (is_using_next_client == NCL_USING_VERIFICATED) {
        result = "NCL_USING_VERIFICATED";
    } else {
        result = "UNEXPECTED RESULT"
    }

    log_to_file(LOG_FILE, "Result: %s", result);
    return PLUGIN_HANDLED;
}

/* <=======> */

public cmd_ncl_get_nextclient_version(id) {
    if (id == 0) {
        id = find_player_ex(FindPlayer_MatchUserId, read_argv_int(1));

        if (id == 0) {
            log_amx("Player with userid #%i not found.", read_argv_int(1));
            return PLUGIN_HANDLED;
        }
    }

    log_to_file(LOG_FILE, "NATIVE <ncl_get_nextclient_version> testing called for player: %n", id);

    new major_version, minor_version, patch_version;
    ncl_get_nextclient_version(id, major_version, minor_version, patch_version);

    log_to_file(LOG_FILE, "Result: NextClient version = %i.%i.%i", major_version, minor_version, patch_version);
    return PLUGIN_HANDLED;
}

/* <=======> */

public cmd_ncl_get_supported_features(id) {
    if (id == 0) {
        id = find_player_ex(FindPlayer_MatchUserId, read_argv_int(1));

        if (id == 0) {
            log_amx("Player with userid #%i not found.", read_argv_int(1));
            return PLUGIN_HANDLED;
        }
    }

    log_to_file(LOG_FILE, "NATIVE <ncl_get_supported_features> testing called for player: %n", id);

    new eFeaturesFlags:bitsum = ncl_get_supported_features(id);
    new result[256];

    if (bitsum & NCL_FEATURE_CVARS_SANDBOX) {
        add(result, charsmax(result), "NCL_FEATURE_CVARS_SANDBOX");
        bitsum &= ~NCL_FEATURE_CVARS_SANDBOX;

        if (bitsum > any:0) {
            add(result, charsmax(result), " | ");
        }
    }

    if (bitsum & NCL_FEATURE_VIEWMODEL_FX) {
        add(result, charsmax(result), "NCL_FEATURE_VIEWMODEL_FX");
        bitsum &= ~NCL_FEATURE_VIEWMODEL_FX;

        if (bitsum > any:0) {
            add(result, charsmax(result), " | ");
        }
    }

    if (bitsum & NCL_FEATURE_PRIVATE_PRECACHE) {
        add(result, charsmax(result), "NCL_FEATURE_PRIVATE_PRECACHE");
        bitsum &= ~NCL_FEATURE_PRIVATE_PRECACHE;

        if (bitsum > any:0) {
            add(result, charsmax(result), " | ");
        }
    }

    if (bitsum & NCL_FEATURE_VERIFICATION) {
        add(result, charsmax(result), "NCL_FEATURE_VERIFICATION");
        bitsum &= ~NCL_FEATURE_VERIFICATION;

        if (bitsum > any:0) {
            add(result, charsmax(result), " | ");
        }
    }

    if (bitsum & NCL_FEATURE_HUD_SPRITE) {
        add(result, charsmax(result), "NCL_FEATURE_HUD_SPRITE");
        bitsum &= ~NCL_FEATURE_HUD_SPRITE;

        if (bitsum > any:0) {
            add(result, charsmax(result), " | ");
        }
    }

    if (bitsum & NCL_FEATURE_HUD_SPRITE_RENDERMODE) {
        add(result, charsmax(result), "NCL_FEATURE_HUD_SPRITE_RENDERMODE");
        bitsum &= ~NCL_FEATURE_HUD_SPRITE_RENDERMODE;

        if (bitsum > any:0) {
            add(result, charsmax(result), " | ");
        }
    }

    if (bitsum & NCL_FEATURE_DEATHMSG_WPN_ICON) {
        add(result, charsmax(result), "NCL_FEATURE_DEATHMSG_WPN_ICON");
        bitsum &= ~NCL_FEATURE_DEATHMSG_WPN_ICON;

        if (bitsum > any:0) {
            add(result, charsmax(result), " | ");
        }
    }

    log_to_file(LOG_FILE, "Result: %s", result);
    return PLUGIN_HANDLED;
}

/* <=======> */

new const CVAR_STRING[eSandboxCvar][] = {
    "cl_forwardspeed",          "cl_backspeed",         "cl_sidespeed",
    "sensitivity",              "gl_fog",               "cl_minmodels",
    "viewmodel_disable_shift",  "viewmodel_offset_x",   "viewmodel_offset_y",
    "viewmodel_offset_z",       "cl_bobstyle",          "cl_bobcycle",
    "cl_bobup",                 "cl_bob",               "cl_bobamt_vert",
    "cl_bobamt_lat",            "cl_bob_lower_amt",     "cl_rollangle",
    "cl_rollspeed",             "viewmodel_lag_scale",  "viewmodel_lag_speed",
    "cl_crosshair_type",        "cl_crosshair_size",    "cl_crosshair_color",
    "cl_crosshair_translucent", "cl_weather",           "cl_min_t",
    "cl_min_ct",                "cl_corpsestay",        "r_decals",
    "cl_yawspeed",              "cl_pitchspeed",        "cl_fog_density",
    "cl_fog_r",                 "cl_fog_g",             "cl_fog_b",
    "viewmodel_fov"
};

new const CVAR_VALUES[eSandboxCvar][] = {
    "888",      "888",      "888",
    "3.33",     "2",        "1",
    "1",        "1.11",     "1.11",
    "1.11",     "1",        "0.888",
    "0.66",     "0.011",    "0.333",
    "0.444",    "10",       "5",
    "300",      "6.66",     "9.99",
    "2",        "auto",     "177 177 177",
    "1",        "3",        "2",
    "2",        "17",       "0",
    "110",      "120",      "0",
    "177",      "177",      "177",
    "80"
};

public cmd_ncl_test_sandbox_cvars(id) {
    if (id == 0) {
        id = find_player_ex(FindPlayer_MatchUserId, read_argv_int(1));

        if (id == 0) {
            log_amx("Player with userid #%i not found.", read_argv_int(1));
            return PLUGIN_HANDLED;
        }
    }

    log_to_file(LOG_FILE, "SANDBOX CVAR testing called for player: %n", id);

    ncl_sandbox_cvar_begin(id);
    for (new eSandboxCvar:i; i < eSandboxCvar; i++) {
        ncl_write_sandbox_cvar(i, CVAR_VALUES[any:i]);
    }
    ncl_sandbox_cvar_end();

    for (new eSandboxCvar:i; i < eSandboxCvar; i++) {
        query_client_cvar(id, CVAR_STRING[i], "checkCvarValue");
    }

    return PLUGIN_HANDLED;
}

public checkCvarValue(id, const cvar[], const value[], const param[]) {
    static any:successfulTest;
    static any:testsPassed;

    for (new eSandboxCvar:i; i < eSandboxCvar; i++) {
        if (strcmp(cvar, CVAR_STRING[i]) == 0) {
            log_to_file(LOG_FILE, "CVAR <%s> EXPECTED VALUE: %s ACTUAL VALUE: %s.", cvar, CVAR_VALUES[i], value);

            if (strcmp(value, CVAR_VALUES[i]) == 0) {
                successfulTest++;
            }
        }
    }

    testsPassed++;

    if (successfulTest == eSandboxCvar && testsPassed == eSandboxCvar) {
        log_to_file(LOG_FILE, "<SANDBOX CVAR testing was SUCCESSFUL>", id);
        successfulTest = 0;
        testsPassed = 0;

        #if defined AUTO_RESTORE_CVAR_VALUES
        cmd_ncl_restore_cvars_values(id);
        #endif
    }
    else if (successfulTest != eSandboxCvar && testsPassed == eSandboxCvar) {
        log_to_file(LOG_FILE, "[!] SANDBOX CVAR testing FAILED [!]", id);
        successfulTest = 0;
        testsPassed = 0;

        #if defined AUTO_RESTORE_CVAR_VALUES
        cmd_ncl_restore_cvars_values(id);
        #endif
    }
}

public cmd_ncl_restore_cvars_values(id) {
    if (id == 0) {
        id = find_player_ex(FindPlayer_MatchUserId, read_argv_int(1));

        if (id == 0) {
            log_amx("Player with userid #%i not found.", read_argv_int(1));
            return PLUGIN_HANDLED;
        }
    }

    log_to_file(LOG_FILE, "CVARS from SANDBOX are restored for player: %n", id);

    ncl_sandbox_cvar_begin(id);
    for (new eSandboxCvar:i; i < eSandboxCvar; i++) {
        ncl_write_sandbox_cvar(i, "");
    }
    ncl_sandbox_cvar_end();

    return PLUGIN_HANDLED;
}

/* <=======> */

new const TEST_SKIN_MODEL[] = "models/v_ak47_with_skins.mdl";
const SKIN = 1;

public cmd_ncl_test_viewmodelfx_skin(id) {
    if (id == 0) {
        id = find_player_ex(FindPlayer_MatchUserId, read_argv_int(1));

        if (id == 0) {
            log_amx("Player with userid #%i not found.", read_argv_int(1));
            return PLUGIN_HANDLED;
        }
    }

    log_to_file(LOG_FILE, "NATIVE <ncl_write_renderbody> testing called for player: %n", id);
    log_to_file(LOG_FILE, "* You should manually check a skin changing of view model. If you see not a standart model, the test was successful.");

    rg_give_item(id, "weapon_ak47");
    engclient_cmd(id, "weapon_ak47");
    set_entvar(id, var_viewmodel, TEST_SKIN_MODEL);

    ncl_viewmodelfx_begin(id);
    ncl_write_renderskin(SKIN);
    ncl_viewmodelfx_end();

    return PLUGIN_HANDLED;
}

/* <=======> */

new const TEST_BODY_MODEL[] = "models/v_m4a1_with_body.mdl";
const BODY = 7;

public cmd_ncl_test_viewmodelfx_body(id) {
    if (id == 0) {
        id = find_player_ex(FindPlayer_MatchUserId, read_argv_int(1));

        if (id == 0) {
            log_amx("Player with userid #%i not found.", read_argv_int(1));
            return PLUGIN_HANDLED;
        }
    }

    log_to_file(LOG_FILE, "NATIVE <ncl_write_renderbody> testing called for player: %n", id);
    log_to_file(LOG_FILE, "* You should manually check a body changing of view model. If you see not a standart model, the test was successful.");

    rg_give_item(id, "weapon_m4a1");
    engclient_cmd(id, "weapon_m4a1");
    set_entvar(id, var_viewmodel, TEST_BODY_MODEL);

    ncl_viewmodelfx_begin(id);
    ncl_write_renderbody(BODY);
    ncl_viewmodelfx_end();

    return PLUGIN_HANDLED;
}

/* <=======> */

public cmd_ncl_test_viewmodelfx_render(id) {
    if (id == 0) {
        id = find_player_ex(FindPlayer_MatchUserId, read_argv_int(1));

        if (id == 0) {
            log_amx("Player with userid #%i not found.", read_argv_int(1));
            return PLUGIN_HANDLED;
        }
    }

    log_to_file(LOG_FILE, "NATIVES <ncl_write_renderfx, ncl_write_rendercolor, ncl_write_rendermode, ncl_write_renderamt> testing called for player: %n", id);
    log_to_file(LOG_FILE, "* You should manually check the glowing of view model.");

    ncl_viewmodelfx_begin(id);
    ncl_write_renderfx(kRenderFxGlowShell);
    ncl_write_rendercolor(255, 0, 0);
    ncl_write_rendermode(kRenderNormal);
    ncl_write_renderamt(10);
    ncl_viewmodelfx_end();

    return PLUGIN_HANDLED;
}

/* <=======> */

public cmd_ncl_restore_viewmodelfx(id) {
    if (id == 0) {
        id = find_player_ex(FindPlayer_MatchUserId, read_argv_int(1));

        if (id == 0) {
            log_amx("Player with userid #%i not found.", read_argv_int(1));
            return PLUGIN_HANDLED;
        }
    }

    log_to_file(LOG_FILE, "All viewmodelfx have been reset for player: %n", id);

    ncl_viewmodelfx_begin(id);
    ncl_write_renderfx(kRenderFxNone);
    ncl_write_rendercolor(0, 0, 0);
    ncl_write_rendermode(kRenderNormal);
    ncl_write_renderamt(0);
    ncl_write_renderskin(0);
    ncl_write_renderbody(0);
    ncl_viewmodelfx_end();

    return PLUGIN_HANDLED;
}

/* <=======> */

const Float:FOV_TIME = 2.0;

public cmd_ncl_setfov(id) {
    if (id == 0) {
        id = find_player_ex(FindPlayer_MatchUserId, read_argv_int(1));

        if (id == 0) {
            log_amx("Player with userid #%i not found.", read_argv_int(1));
            return PLUGIN_HANDLED;
        }
    }

    log_to_file(LOG_FILE, "NATIVE <ncl_setfov> testing called for player: %n", id);
    log_to_file(LOG_FILE, "* You should manually check a FOV changing.");

    ncl_setfov(id, 120, FOV_TIME);
    set_task(FOV_TIME, "restore_fov", id);

    return PLUGIN_HANDLED;
}

public restore_fov(id) {
    log_to_file(LOG_FILE, "FOV automatically restored to 90 for player: %n", id);

    ncl_setfov(id, 90, FOV_TIME);
}

/* <=======> */

public cmd_ncl_hudsprite_set(id) {
    if (id == 0) {
        id = find_player_ex(FindPlayer_MatchUserId, read_argv_int(1));

        if (id == 0) {
            log_amx("Player with userid #%i not found.", read_argv_int(1));
            return PLUGIN_HANDLED;
        }
    }

    log_to_file(LOG_FILE, "NATIVE <ncl_send_hud_sprite> testing called for player: %n", id);
    log_to_file(LOG_FILE, "* You should manually check sprites on screen in game.");

    // left-top
    ncl_send_hud_sprite(
        .id = id,
        .channel = 0,
        .sprite_path = HUD_SPRITE_KILL,
        .sprite_color = _,
        .alpha = _,
        .frame = _,
        .framerate = _,
        .in_time = _,
        .hold_time = 5.0,
        .out_time = 1.0,
        .x = 0.0,
        .y = 0.0,
        .sprite_rect = { 100, 0, 200, 100 },
        .scale_x = _,
        .scale_y = _
    )

    // left-center x-scaled
    ncl_send_hud_sprite(
        .id = id,
        .channel = 1,
        .sprite_path = HUD_SPRITE_KILL,
        .sprite_color = _,
        .alpha = _,
        .frame = _,
        .framerate = _,
        .in_time = 3.0,
        .hold_time = 6.0,
        .out_time = 3.0,
        .x = 0.0,
        .y = -1.0,
        .sprite_rect = { 100, 0, 200, 100 },
        .scale_x = 2.0,
        .scale_y = _
    )

    // left-bottom y-scaled
    ncl_send_hud_sprite(
        .id = id,
        .channel = 2,
        .sprite_path = HUD_SPRITE_KILL,
        .sprite_color = _,
        .alpha = _,
        .frame = _,
        .framerate = _,
        .in_time = 1.0,
        .hold_time = _,
        .out_time = _,
        .x = 0.0,
        .y = 1.0,
        .sprite_rect = { 100, 0, 200, 100 },
        .scale_x = _,
        .scale_y = 4.0
    )

    // right-top-red
    ncl_send_hud_sprite(
        .id = id,
        .channel = 3,
        .sprite_path = HUD_SPRITE_KILL,
        .sprite_color = { 255, 0, 0 },
        .alpha = _,
        .frame = _,
        .framerate = _,
        .in_time = 1.0,
        .hold_time = _,
        .out_time = _,
        .x = 1.0,
        .y = 0.0,
        .sprite_rect = { 100, 0, 200, 100 },
        .scale_x = _,
        .scale_y = _
    )

    // center / auto-size
    ncl_send_hud_sprite(
        .id = id,
        .channel = 4,
        .sprite_path = HUD_SPRITE_BLACK_HOLE,
        .sprite_color = _,
        .alpha = _,
        .frame = _,
        .framerate = 2.0,
        .in_time = _,
        .hold_time = _,
        .out_time = _,
        .x = -1.0,
        .y = -1.0,
        .sprite_rect = _,
        .scale_x = _,
        .scale_y = _
    )

    // right-bottom + auto-size + alpha
    ncl_send_hud_sprite(
        .id = id,
        .channel = 5,
        .sprite_path = HUD_SPRITE_BLACK_HOLE,
        .sprite_color = _,
        .alpha = 127,
        .frame = _,
        .framerate = _,
        .in_time = 2.0,
        .hold_time = 2.0,
        .out_time = 2.0,
        .x = 1.0,
        .y = 1.0,
        .sprite_rect = _,
        .scale_x = _,
        .scale_y = _,
        .rendermode = kRenderNormal
    )

    // skip 6 channel

    // bottom-center
    ncl_send_hud_sprite_full_screen(
        .id = id,
        .channel = 7,
        .sprite_path = HUD_SPRITE_KILL,
        .sprite_color = _,
        .alpha = _,
        .frame = _,
        .framerate = _,
        .in_time = _,
        .hold_time = _,
        .out_time = _
    )

    return PLUGIN_HANDLED;
}

/* <=======> */

public cmd_ncl_hudsprite_clear(id) {
    if (id == 0) {
        id = find_player_ex(FindPlayer_MatchUserId, read_argv_int(1));

        if (id == 0) {
            log_amx("Player with userid #%i not found.", read_argv_int(1));
            return PLUGIN_HANDLED;
        }
    }

    log_to_file(LOG_FILE, "NATIVE <ncl_clear_hud_sprite> testing called for player: %n", id);
    log_to_file(LOG_FILE, "* You should manually check clearing sprites on screen in game.");

    for (new i = 0; i < MAX_HUD_SPRITE_CHANNELS; ++i) {
       ncl_clear_hud_sprite(id, i);
    }

    return PLUGIN_HANDLED;
}

/* <=== END NATIVES ===> */

/* <== PRECACHE ==> */

public plugin_precache() {
    precache_model(TEST_SKIN_MODEL);
    precache_model(TEST_BODY_MODEL);

    precache_model(HUD_SPRITE_KILL);
    precache_model(HUD_SPRITE_BLACK_HOLE);

#if defined TEST_PRECACHE_AND_REPLACE_DEFAULT_MODELS
    test_ncl_precache_and_replace_default_model();
#endif

#if defined TEST_PRECACHE_AND_REPLACE_DEFAULT_SOUNDS
    test_ncl_precache_and_replace_default_sound();
#endif

#if defined TEST_PRECACHE_AND_REPLACE_HUD
    test_ncl_precache_client_only();
#endif

#if defined TEST_PRECACHE_AND_REPLACE_CUSTOM_MODELS
    test_ncl_precache_and_replace_custom_model();
#endif

#if defined TEST_PRECACHE_AND_REPLACE_CUSTOM_SOUNDS
    test_ncl_precache_and_replace_custom_sound();
#endif
}

/* <=======> */

public test_ncl_precache_and_replace_default_model() {
    log_to_file(LOG_FILE, "~ Testing ncl_precache_model() for DEFAULT models is active.");

    ncl_precache_model("models/v_glock18.mdl",  "models/test_nextclient/v_glock18.mdl"  );
    ncl_precache_model("models/v_usp.mdl",      "models/test_nextclient/v_usp.mdl"      );
}

/* <=======> */

public test_ncl_precache_and_replace_default_sound() {
    log_to_file(LOG_FILE, "~ Testing ncl_precache_sound() for DEFAULT sounds is active.");

    ncl_precache_sound("weapons/glock18-1.wav",   "weapons/test_nextclient/glock18-1.wav"   );
    ncl_precache_sound("weapons/glock18-2.wav",   "weapons/test_nextclient/glock18-2.wav"   );
    ncl_precache_sound("weapons/usp_unsil-1.wav", "weapons/test_nextclient/usp_unsil-1.wav" );
    ncl_precache_sound("weapons/usp_unsil-2.wav", "weapons/test_nextclient/usp_unsil-2.wav" );
    ncl_precache_sound("weapons/usp1.wav",        "weapons/test_nextclient/usp1.wav"        );
    ncl_precache_sound("weapons/usp2.wav",        "weapons/test_nextclient/usp2.wav"        );

    ncl_precache_sound("player/pl_step1.wav", "player/test_nextclient/pl_step1.wav" );
    ncl_precache_sound("player/pl_step2.wav", "player/test_nextclient/pl_step2.wav" );
    ncl_precache_sound("player/pl_step3.wav", "player/test_nextclient/pl_step3.wav" );
    ncl_precache_sound("player/pl_step4.wav", "player/test_nextclient/pl_step4.wav" );
}

/* <=======> */

public test_ncl_precache_client_only() {
    log_to_file(LOG_FILE, "~ Testing ncl_precache_client_only() for hud.txt and HUD sprites is active.");

    ncl_precache_client_only("sprites/TBW1.spr",    "sprites/test_nextclient/TBW1.spr"  );
    ncl_precache_client_only("sprites/TBW2.spr",    "sprites/test_nextclient/TBW2.spr"  );
    ncl_precache_client_only("sprites/TBW3.spr",    "sprites/test_nextclient/TBW3.spr"  );
    ncl_precache_client_only("sprites/TBW4.spr",    "sprites/test_nextclient/TBW4.spr"  );
    ncl_precache_client_only("sprites/TBW5.spr",    "sprites/test_nextclient/TBW5.spr"  );
    ncl_precache_client_only("sprites/TBW6.spr",    "sprites/test_nextclient/TBW6.spr"  );
    ncl_precache_client_only("sprites/TBW7.spr",    "sprites/test_nextclient/TBW7.spr"  );
    ncl_precache_client_only("sprites/TDW.spr",     "sprites/test_nextclient/TDW.spr"   );
    ncl_precache_client_only("sprites/THUD.spr",    "sprites/test_nextclient/THUD.spr"  );

    ncl_precache_client_only("sprites/radar640.spr",        "sprites/test_nextclient/radar640.spr"          ); 
    ncl_precache_client_only("sprites/radaropaque640.spr",  "sprites/test_nextclient/radaropaque640.spr"    );

    for (new WeaponIdType:weaponID = WEAPON_P228; weaponID <= WEAPON_P90; weaponID++) {
        if (weaponID == WEAPON_GLOCK) {
            continue;
        }

        new weaponName[MAX_NAME_LENGTH];
        rg_get_weapon_info(weaponID, WI_NAME, weaponName, charsmax(weaponName));

        ncl_precache_client_only(fmt("sprites/%s.txt", weaponName), fmt("sprites/test_nextclient/%s.txt", weaponName));\
    }

    ncl_precache_client_only("sprites/weapon_shieldgun.txt", "sprites/test_nextclient/weapon_shieldgun.txt");

    ncl_precache_hudtxt("sprites/test_nextclient/hud.txt");
}

/* <=======> */

new g_chickModelIndex;

public test_ncl_precache_and_replace_custom_model() {
    log_to_file(LOG_FILE, "~ Testing ncl_precache_model() for CUSTOM models is active.");

    g_chickModelIndex = ncl_precache_model("models/test_nextclient/chick.mdl", "models/test_nextclient/chick_HD.mdl");

    RegisterHookChain(RG_CBasePlayer_Spawn, "RG_CBasePlayer_Spawn_post", true);
}

public RG_CBasePlayer_Spawn_post(id) {
    if (!is_user_alive(id)) {
        return;
    }

    CreateChick(id);
}

CreateChick(id) {
    new chick = rg_create_entity("info_target");

    set_entvar(chick, var_modelindex, g_chickModelIndex);

    new Float:origin[3];
    get_CoordPointInDirView(id, 64.0, origin);

    engfunc(EngFunc_SetOrigin, chick, origin);
    engfunc(EngFunc_DropToFloor, chick);
}

// https://dev-cs.ru/threads/222/page-9#post-81453
stock get_CoordPointInDirView(const index, const Float:dist, Float:output[3]) {
    new Float:start_origins[3];
    pev(index, pev_origin, start_origins);

    new Float:angles[3];
    pev(index, pev_v_angle, angles);

    new Float:end_origins[3];
    end_origins[0] = start_origins[0] + dist * floatcos(angles[1], degrees) * floatabs(floatcos(angles[0], degrees));
    end_origins[1] = start_origins[1] + dist * floatsin(angles[1], degrees) * floatabs(floatcos(angles[0], degrees));
    end_origins[2] = start_origins[2];

    engfunc(EngFunc_TraceLine, start_origins, end_origins, DONT_IGNORE_MONSTERS, index, 0);
    get_tr2(0, TR_vecEndPos, end_origins);

    output[0] = end_origins[0];
    output[1] = end_origins[1];
    output[2] = end_origins[2];
}

/* <=======> */

public test_ncl_precache_and_replace_custom_sound() {
    log_to_file(LOG_FILE, "~ Testing ncl_precache_sound() for CUSTOM sounds is active.");
    
    ncl_precache_sound("test_nextclient/sound_for_all.wav", "test_nextclient/sound_for_nextclient.wav");

    set_task_ex(3.0, "sendSound", .flags = SetTask_Repeat);
}

public sendSound() {
    for (new player = 1; player <= MaxClients; player++) {
        if (!is_user_connected(player)) {
            continue;
        }

        rg_send_audio(player, "test_nextclient/sound_for_all.wav");
    }
}

/* <=== END PRECACHE ===> */

/* <== OTHER TEST FUNCS ==> */

public cmd_ncl_add_health(id) {
    if (id == 0) {
        id = find_player_ex(FindPlayer_MatchUserId, read_argv_int(1));

        if (id == 0) {
            log_amx("Player with userid #%i not found.", read_argv_int(1));
            return PLUGIN_HANDLED;
        }
    }

    if (!is_user_alive(id)) {
        return PLUGIN_HANDLED;
    }

    log_to_file(LOG_FILE, "Testing HUD limit health for player: %n", id);
    log_to_file(LOG_FILE, "* You should manually check a visual health in game.");

    set_entvar(id, var_health, 99999999.0);
    return PLUGIN_HANDLED;
}

/* <=======> */

public start_autotests(id) {
    cmd_ncl_is_client_api_ready(id);
    cmd_ncl_is_using_nextclient(id);
    cmd_ncl_get_nextclient_version(id);
    cmd_ncl_get_supported_features(id);
    cmd_ncl_test_sandbox_cvars(id);
}

/* <=== END OTHER FUNCS ===> */
