#if defined _next_client_api_included
    #endinput
#endif
#define _next_client_api_included

#if AMXX_VERSION_NUM >= 175
#pragma reqlib nextclientapi
 #if !defined AMXMODX_NOAUTOLOAD
  #pragma loadlib nextclientapi
 #endif
#else
#pragma library nextclientapi
#endif

enum eSandboxCvar
{
    SC_cl_forwardspeed = 0,
    SC_cl_backspeed,
    SC_cl_sidespeed,
    SC_sensitivity,
    SC_gl_fog,
    SC_cl_minmodels,
    SC_viewmodel_disable_shift,
    SC_viewmodel_offset_x,
    SC_viewmodel_offset_y,
    SC_viewmodel_offset_z,
    SC_cl_bobstyle,
    SC_cl_bobcycle,
    SC_cl_bobup,
    SC_cl_bob,
    SC_cl_bobamt_vert,
    SC_cl_bobamt_lat,
    SC_cl_bob_lower_amt,
    SC_cl_rollangle,
    SC_cl_rollspeed,
    SC_viewmodel_lag_scale,
    SC_viewmodel_lag_speed,
    // since Next Client v2.1.4
    SC_cl_crosshair_type,
    SC_cl_crosshair_size,
    SC_cl_crosshair_color,
    SC_cl_crosshair_translucent,
    // since Next Client v2.1.8
    SC_cl_weather,
    // since Next Client v2.1.10
    SC_cl_min_t,
    SC_cl_min_ct,
    SC_cl_corpsestay,
    SC_r_decals,
    // since Next Client v2.2.0
    SC_cl_yawspeed,
    SC_cl_pitchspeed,
    // since Next Client v2.4.0
    SC_cl_fog_density,
    SC_cl_fog_r,
    SC_cl_fog_g,
    SC_cl_fog_b,
    SC_viewmodel_fov,
    // since Next Client v2.5.0
    SC_camera_movement_scale,
    SC_camera_movement_interp,
    SC_cl_bob_camera,
    SC_viewmodel_lag_style,
    SC_hud_deathnotice_max
}

enum eNclUsing {
    NCL_NOT_USING,
    NCL_DECLARE_USING,
    NCL_USING_VERIFICATED
}

enum eFeaturesFlags (<<= 1) {
    NCL_FEATURE_CVARS_SANDBOX = 1,
    NCL_FEATURE_VIEWMODEL_FX,
    NCL_FEATURE_PRIVATE_PRECACHE,
    NCL_FEATURE_VERIFICATION,
    NCL_FEATURE_HUD_SPRITE,
    NCL_FEATURE_HUD_SPRITE_RENDERMODE,
    NCL_FEATURE_DEATHMSG_WPN_ICON,
    NCL_FEATURE_WEAPON_SOUND_OVERRIDE,
    FEATURE_INVERT_MOUSE
}

/**
 * Called once, when all api functionality is ready to use. Called only for Next Clients.
 *
 * At the moment this forward is called the client's NCLM negotiation is already complete:
 * the verification result is final (see ncl_is_using_nextclient) and, for verified players,
 * the HWID has already been received (see ncl_get_client_hwid). The whole identification state is
 * settled and available here, so it can be used directly without waiting for any other event.
 *
 * @param id    Client index
 *
 * @noreturn
 */
forward ncl_client_api_ready(id);

/**
 * Called when a verified player's hardware id (HWID) has been received and validated.
 * Called once per connection and only for verified players (see ncl_is_using_nextclient).
 *
 * Client state at the moment of this call: the HWID arrives during the connection handshake, so
 * this forward fires BEFORE ncl_client_api_ready and before the player has fully entered the game.
 * The API is not ready yet (ncl_is_client_api_ready returns false), and functions that send data to
 * the client - sandbox cvars, viewmodelfx, hud sprites, fov, etc. - will NOT work here. Use this
 * forward only for early HWID-based logic (logging, bans, kicks). For anything that sends data to the
 * client, use ncl_client_api_ready, where the HWID is already available as well.
 *
 * @param id    Client index
 * @param hwid  Player's HWID, a NCL_HWID_LENGTH-character lowercase hex string (SHA-256)
 *
 * @noreturn
 */
forward ncl_hwid_received(id, const hwid[]);

/**
 * Checks if client is Next Client and its ready to interact with server api.
 *
 * @param id    Client index
 *
 * @return      True or false
 */
native bool:ncl_is_client_api_ready(id);

/**
 * Checks if a player using Next Client. 
 *
 * @param id    Client index
 *
 * @return      Member of eNclUsing enum
 *                  NCL_NOT_USING - the player doesn't using nextclient
 *                  NCL_DECLARE_USING - the player declared they use nextclient via NCLM,
 *                      but this is unverified and could be forged by the player
 *                  NCL_USING_VERIFICATED - the module is verified that the player
 *                      using nextclient. From that moment, the player can be trusted
 *                      and, for example, granted privileges
 */
native eNclUsing:ncl_is_using_nextclient(id);

/**
 * Gets the specific version of nextclient 
 *
 * @param id        Client index
 * @param major     Major version
 * @param minor     Minor version
 * @param patch     Patch version
 *
 * @return          True if the player using nextclient v2.1.8 and higher, false otherwise
 */
native bool:ncl_get_nextclient_version(id, &major = 0, &minor = 0, &patch = 0);

/**
 * Checks which features of nextclient are supported by the player
 *
 * @param id        Client index
 *
 * @return          Member of eFeaturesFlags enum
 */
native eFeaturesFlags:ncl_get_supported_features(id);

/**
 * Length of a HWID string, without the null terminator (HWID is a SHA-256 hex digest).
 * Use a buffer of at least NCL_HWID_LENGTH + 1 to receive it.
 */
#define NCL_HWID_LENGTH 64

/**
 * Gets the hardware id (HWID) of a verified player.
 *
 * @note HWID is available only for verified players. It is delivered via the ncl_hwid_received()
 *       forward (during the connection handshake) and is also already final inside
 *       ncl_client_api_ready(); ncl_is_hwid_received() can be used to poll it.
 *
 * @param id    Client index
 * @param hwid  Buffer that receives the HWID (a NCL_HWID_LENGTH-character lowercase hex string)
 * @param len   Buffer size (NCL_HWID_LENGTH + 1 is recommended)
 *
 * @return      True if the HWID is available and was written, false otherwise
 */
native bool:ncl_get_client_hwid(id, hwid[], len);

/**
 * Checks whether the hardware id (HWID) of a player has been received.
 *
 * @param id    Client index
 *
 * @return      True if the HWID has been received, false otherwise
 */
native bool:ncl_is_hwid_received(id);

/**
 * Marks the beginning of a sandbox cvar message.
 *
 * @note Be careful, this function does not work in client_connect, client_putinserver, etc. If you want to change player cvars after connecting, call this function in forward ncl_client_api_ready.
 *
 * @param id    Client index
 *
 * @noreturn
 */
native ncl_sandbox_cvar_begin(id);

/**
 * Ends sandbox cvar message that was started with ncl_sandbox_cvar_begin().
 * If the function is called without using ncl_sandbox_cvar_begin() first, the server will crash immediately.
 *
 * @param id    Client index
 *
 * @noreturn
 */
native ncl_sandbox_cvar_end();

/**
 * Writes a cvar value to a sandbox cvar message.
 * To restore the user cvar value and unlock the client's ability to change cvar, pass in a value an empty string.
 *
 * @param cvar  Cvar index from eSandboxCvar
 * @param value Cvar value
 *
 * @noreturn
 */
native ncl_write_sandbox_cvar(eSandboxCvar:cvar, const value[]);


/**
 * Writes a render mode to a viewmodelfx message.
 *
 * @param rendermode One of kRender* constant
 *
 * @noreturn
 */
native ncl_write_rendermode(rendermode);

/**
 * Writes a render amount to a viewmodelfx message.
 *
 * @param renderamt Render amount (0 to 255)
 *
 * @noreturn
 */
native ncl_write_renderamt(renderamt);

/**
 * Writes a render color to a viewmodelfx message.
 *
 * @param r The amount of red color (0 to 255)
 * @param g The amount of green color (0 to 255)
 * @param b The amount of blue color (0 to 255)
 *
 * @noreturn
 */
native ncl_write_rendercolor(r, g, b);

/**
 * Writes a rendering effect to a viewmodelfx message.
 *
 * @param renderfx One of kRenderFx* constants
 *
 * @noreturn
 */
native ncl_write_renderfx(renderfx);

/**
 * Writes a viewmodel skin to viewmodelfx message.
 *
 * @param renderskin     
 *
 * @noreturn
 */
native ncl_write_renderskin(renderskin);

/**
 * Writes a viewmodel body to viewmodelfx message.
 *
 * @param renderbody     
 *
 * @noreturn
 */
native ncl_write_renderbody(renderbody);

/**
 * Marks the beginning of a viewmodelfx message.
 * You can write the message parameters in any order. 
 * It is also not necessary to specify all the parameters, write down only those you want to change.
 *
 * @note Be careful, this function does not work in client_connect, client_putinserver, etc. If you want to change player viewmodelfx after connecting, call this function in forward ncl_client_api_ready.
 *
 * @param id    Client index
 *
 * @noreturn
 */
native ncl_viewmodelfx_begin(id);

/**
 * Ends viewmodelfx message that was started with ncl_viewmodelfx_begin().
 * If the function is called without using ncl_viewmodelfx_begin() error log will be printed.
 *
 * @param id    Client index
 *
 * @noreturn
 */
native ncl_viewmodelfx_end();

/**
 * This message sets the specified field of view and interpolate time.
 *
 * @note Be careful, this function does not work in client_connect, client_putinserver, etc. If you want to change player fov after connecting, call this function in forward ncl_client_api_ready.
 *
 * @param id    Client index
 * @param fov   FOV angle
 * @param time  Inertpolate time
 *
 * @noreturn
 */
native ncl_setfov(id, fov, Float:time);


/**
 * Inverts mouse axes (pitch and/or yaw) for the specified client.
 *
 * @param id            Client index
 * @param invert_pitch  true to invert pitch (look up/down), false to restore normal pitch
 * @param invert_yaw    true to invert yaw (look left/right), false to restore normal yaw
 *
 * @noreturn
 */
native ncl_invert_mouse(id, bool:invert_pitch, bool:invert_yaw);

/**
 * Separate precaching of the model for regular cs 1.6 client and NextClient.
 * For NextClient:
 * - uploading is done in a server's private directory;
 * - allows to overwrite default models;
 * - allows to update an existing model on the client when it changed on the server.
 *
 * @note Can only be used inside of the plugin_precache() forward.
 * 
 * @param filepath       Path to the model file
 * @param ncl_filepath   Path to the model file on server, which will be preached to NextClient players. On the client side, the file will be saved at filepath in the private directory of the server.
 *
 * @return               Unique cache id of the model
 * @error                If called outside of the plugin_precache() forward, an error is thrown.
 */
native ncl_precache_model(const filepath[], const ncl_filepath[]);

/**
 * Separate precaching of the sound for regular cs 1.6 client and NextClient. 
 * For NextClient:
 * - uploading is done in a server's private directory;
 * - allows to overwrite default sounds;
 * - allows to update an existing sound on the client when it changed on the server;
 * - supported audio formats: wav, flac, ogg, mp3
 *
 * @note Can only be used inside of the plugin_precache() forward.
 * 
 * @param filepath       Path to the sound file
 * @param ncl_filepath   Path to the sound file on server, which will be preached to NextClient players. On the client side, the file will be saved at filepath in the private directory of the server.
 *
 * @return               Unique cache id of the sound
 * @error                If called outside of the plugin_precache() forward, an error is thrown.
 */
native ncl_precache_sound(const filepath[], const ncl_filepath[]);


/**
 * Uploads a file for NextClient players, without a precache on the server.
 * Features:
 * - uploading is done in a server's private directory;
 * - allows to overwrite default files;
 * - allows to update an existing file on the client when it changed on the server.
 * Limitations:
 * - only spr, txt, wav, flac, ogg and mp3 files can be uploaded;
 * - spr and txt files can only be uploaded to the 'sprites/' directory;
 * - audio files can only be uploaded to the 'sound/' directory;
 * - spr files can NOT override standard sprites
 *
 * @param filepath_server   Path to the file on server (regarding the cstrike/ directory)
 * @param filepath_client   Path to the file on client (regarding the cstrike/ directory)
 *
 * @noreturn
 * @error                If called outside of the plugin_precache() forward, an error is thrown.
 */
native ncl_upload_file(const filepath_server[], const filepath_client[]);

stock ncl_upload_hudtxt(const filepath_server[])
{
   ncl_upload_file("sprites/hud.txt", filepath_server);
}

stock const MAX_HUD_SPRITE_CHANNELS = 32;

const HUD_SPRITE_DEFAULT_ALPHA = 255;
const HUD_SPRITE_DEFAULT_FRAME = -1;
const Float:HUD_SPRITE_DEFAULT_FRAME_RATE = 1.0;
const Float:HUD_SPRITE_DEFAULT_IN_TIME = 0.0;
const Float:HUD_SPRITE_DEFAULT_HOLD_TIME = 3.0;
const Float:HUD_SPRITE_DEFAULT_OUT_TIME = 1.0;
const Float:HUD_SPRITE_DEFAULT_X = -1.0;
const Float:HUD_SPRITE_DEFAULT_Y = -1.0;
const Float:HUD_SPRITE_DEFAULT_SCALE_X = 1.0;
const Float:HUD_SPRITE_DEFAULT_SCALE_Y = 1.0;

/**
 * Displays a sprite on the client screen.
 *
 * @note Be careful, this function does not work in client_connect, client_putinserver, etc. If you want to set sprite after player connected, call this function in forward ncl_client_api_ready.
 *
 * @param id             Client index
 * @param channel        Channel to use on the client (from 0 to 31)
 * @param sprite_path    Path to the sprite file
 * @param sprite_color   Red, green, blue components of sprite color (each component from 0 to 255)
 * @param alpha          Alpha component of sprite color (from 0 to 255)
 * @param frame          Start frame (-1 for looping)
 * @param framerate      Frame rate (1.0 for default behavior)
 * @param in_time        Time it takes the sprite to fully appear (fade-in)
 * @param hold_time      Time the sprite stays on screen
 * @param out_time       Time it takes the sprite to fully disappear (fade-out)
 * @param x              Horizontal location (from 0.0 to 1.0 or -1.0 for centering)
 * @param y              Vertical location (from 0.0 to 1.0 or -1.0 for centering)
 * @param sprite_rect    Left, top, right and bottom pixel coordinates of sprite rectangle
 * @param scale_x        Horizontal scale (from 0.0; 1.0 without scale)
 * @param scale_y        Vertical scale (from 0.0; 1.0 without scale)
 * @param rendermode     Render mode, one of kRender const
 *
 * @return               1 on success, 0 otherwise
 * @error                If the parameters are invalid, an error is thrown.
 */
native ncl_send_hud_sprite(
    id,
    channel,
    const sprite_path[],
    sprite_color[3] = { 255, 255, 255 },
    alpha = HUD_SPRITE_DEFAULT_ALPHA,
    frame = HUD_SPRITE_DEFAULT_FRAME,
    Float:framerate = HUD_SPRITE_DEFAULT_FRAME_RATE,
    Float:in_time = HUD_SPRITE_DEFAULT_IN_TIME,
    Float:hold_time = HUD_SPRITE_DEFAULT_HOLD_TIME,
    Float:out_time = HUD_SPRITE_DEFAULT_OUT_TIME,
    Float:x = HUD_SPRITE_DEFAULT_X,
    Float:y = HUD_SPRITE_DEFAULT_Y,
    sprite_rect[4] = { 0, 0, 0, 0 },
    Float:scale_x = HUD_SPRITE_DEFAULT_SCALE_X,
    Float:scale_y = HUD_SPRITE_DEFAULT_SCALE_Y,
    rendermode = kRenderTransAdd
);

/**
 * Displays a sprite on the client full-screen.
 *
 * @note Be careful, this function does not work in client_connect, client_putinserver, etc. If you want to set sprite after player connected, call this function in forward ncl_client_api_ready.
 *
 * @param id             Client index
 * @param channel        Channel to use on the client (from 0 to 31)
 * @param sprite_path    Path to the sprite file
 * @param sprite_color   Red, green, blue components of sprite color (each component from 0 to 255)
 * @param alpha          Alpha component of sprite color (from 0 to 255)
 * @param frame          Start frame (-1 for looping)
 * @param framerate      Frame rate (1.0 for default behavior)
 * @param in_time        Time it takes the sprite to fully appear (fade-in)
 * @param hold_time      Time the sprite stays on screen
 * @param out_time       Time it takes the sprite to fully disappear (fade-out)
 * @param rendermode     Render mode, one of kRender const
 *
 * @return               1 on success, 0 otherwise
 * @error                If the parameters are invalid, an error is thrown.
 */
native ncl_send_hud_sprite_full_screen(
    id,
    channel,
    const sprite_path[],
    sprite_color[3] = { 255, 255, 255 },
    alpha = HUD_SPRITE_DEFAULT_ALPHA,
    frame = HUD_SPRITE_DEFAULT_FRAME,
    Float:framerate = HUD_SPRITE_DEFAULT_FRAME_RATE,
    Float:in_time = HUD_SPRITE_DEFAULT_IN_TIME,
    Float:hold_time = HUD_SPRITE_DEFAULT_HOLD_TIME,
    Float:out_time = HUD_SPRITE_DEFAULT_OUT_TIME,
    rendermode = kRenderTransAdd
);

/**
 * Clears the display a sprite on a client screen.
 *
 * @note Be careful, this function does not work in client_connect, client_putinserver, etc. If you want to set/clear sprite after player connected, call this function in forward ncl_client_api_ready.
 *
 * @param id        Client index
 * @param channel   Channel to use on the client (from 0 to 31)
 *
 * @return               1 on success, 0 otherwise
 * @error                If the parameters are invalid, an error is thrown.
 */
native ncl_clear_hud_sprite(id, channel);

/**
 * Overrides death message weapon icon for the next message to be sent by the server
 * Specified sprite will be adjusted in scale to match death notice box. A width of the sprite is not limited
 *
 * @note                Best practice: call this function only before before the player's death event occurs
 *                      For example: with Ham_Killed in pre 
 *
 * @param sprite_path   Path to the sprite file
 * @param frame         Frame in the sprite
 * @param rendermode    Rendermode for the sprite
 * @param color         Red, green, blue components of sprite color (each component from 0 to 255)
 * @param alpha         Alpha component of sprite color (from 0 to 255)
 *
 * @noreturn
 * @error               If the parameters are invalid, an error is thrown.
 */
native ncl_set_wpn_icon_for_next_deathmsg(const sprite_path[], frame = 0, rendermode = kRenderTransAdd, color[] = { 255, 255, 255 }, alpha = 255, recipient_id = 0);

/**
 * Overrides a sound of the specified weapon entity.
 * The override is bound to the weapon entity and synchronized to every NextClient
 * client that can see the weapon: when such a client would play the original sound
 * for this weapon, the replacement sound is played instead.
 *
 * @note The replacement sound is not precached on the server: the client hot-precaches it on demand when the override is applied, so no scarce server precache slot is consumed.
 *       Make sure the file is available on the client beforehand - either it is a default game sound, or it is delivered to clients via ncl_upload_file (which does not use a server precache slot).
 *       This avoids a missing sound and reduces potential client hitches/freezes when the sound is first loaded at play time.
 * @note weapon_id must reference a valid weapon entity (classname starting with "weapon_").
 *
 * @param weapon_id     Weapon entity index (entnum) whose sound will be overridden
 * @param original      Original sound path (e.g. "weapons/glock18-1.wav")
 * @param replacement   Replacement sound path (e.g. "weapons/test_nextclient/glock18-1.wav")
 *
 * @return              1 on success, 0 if the weapon entity is invalid
 */
native ncl_override_weapon_sound(weapon_id, const original[], const replacement[]);

/**
 * Clears all sound overrides previously set for the specified weapon entity.
 *
 * @param weapon_id     Weapon entity index (entnum)
 *
 * @return              1 on success, 0 if the weapon entity is invalid
 */
native ncl_override_weapon_sound_clear(weapon_id);
