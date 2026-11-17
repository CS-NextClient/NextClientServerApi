#if defined _next_client_gloves_included
    #endinput
#endif
#define _next_client_gloves_included

#include <amxmodx>
#include <fakemeta>
#include <reapi>
#include <next_client_api>

#define NCL_GLOVES_MAX_MATERIALS 16
#define NCL_GLOVES_PRESET_LENGTH 128
#define NCL_GLOVES_MATERIAL_LENGTH 189

enum _:NclGlovesProfile
{
    NclGlovesPreset[NCL_GLOVES_PRESET_LENGTH + 1],
    Array:NclGlovesMaterials
}

enum _:NclGlovesWeapon
{
    NclGlovesSerial,
    NclGlovesSelection
}

new Array:g_NclGlovesProfiles;
new Array:g_NclGlovesWeapons;
new g_NclGlovesUserId[33];
new g_NclGlovesPlayer[33];
new g_NclGlovesApplied[33];
new g_NclGlovesMaxPlayers;
new g_NclGlovesMaxEntities;
new bool:g_NclGlovesInitialized;
new HookChain:g_NclGlovesDeployHook;
new HookChain:g_NclGlovesSpawnHook;
new HookChain:g_NclGlovesRemoveHook;
new g_NclGlovesFreeForward;
new g_NclGlovesDisconnectForward;

// WeaponList registration can occur after profiles are assigned to map entities.
new const g_NclGlovesWeaponClasses[][] = {
    "weapon_p228", "weapon_scout", "weapon_hegrenade", "weapon_xm1014", "weapon_c4",
    "weapon_mac10", "weapon_aug", "weapon_smokegrenade", "weapon_elite", "weapon_fiveseven",
    "weapon_ump45", "weapon_sg550", "weapon_galil", "weapon_famas", "weapon_usp",
    "weapon_glock18", "weapon_awp", "weapon_mp5navy", "weapon_m249", "weapon_m3",
    "weapon_m4a1", "weapon_tmp", "weapon_g3sg1", "weapon_flashbang", "weapon_deagle",
    "weapon_sg552", "weapon_ak47", "weapon_knife", "weapon_p90"
};

// Registration is allowed in plugin_precache, before initialization in plugin_init.
stock ncl_gloves_register(const preset[], const materials[][], count = sizeof materials)
{
    if (!preset[0] || strlen(preset) > NCL_GLOVES_PRESET_LENGTH ||
        count < 1 || count > NCL_GLOVES_MAX_MATERIALS)
    {
        return 0;
    }
    for (new index = 0; index < count; index++)
    {
        if (!materials[index][0] || strlen(materials[index]) > NCL_GLOVES_MATERIAL_LENGTH)
        {
            return 0;
        }
        for (new previous = 0; previous < index; previous++)
        {
            if (equali(materials[previous], materials[index]))
            {
                return 0;
            }
        }
    }

    if (!g_NclGlovesProfiles)
    {
        g_NclGlovesProfiles = ArrayCreate(NclGlovesProfile);
    }
    new profile[NclGlovesProfile];
    copy(profile[NclGlovesPreset], NCL_GLOVES_PRESET_LENGTH, preset);
    profile[NclGlovesMaterials] = ArrayCreate(NCL_GLOVES_MATERIAL_LENGTH + 1);
    for (new index = 0; index < count; index++)
    {
        ArrayPushString(profile[NclGlovesMaterials], materials[index]);
    }
    return ArrayPushArray(g_NclGlovesProfiles, profile) + 1;
}

stock bool:ncl_gloves_init()
{
    if (g_NclGlovesInitialized)
    {
        return true;
    }
    g_NclGlovesMaxPlayers = get_maxplayers();
    g_NclGlovesMaxEntities = global_get(glb_maxEntities);
    g_NclGlovesWeapons = ArrayCreate(NclGlovesWeapon, g_NclGlovesMaxEntities);
    new empty[NclGlovesWeapon];
    for (new entity = 0; entity < g_NclGlovesMaxEntities; entity++)
    {
        ArrayPushArray(g_NclGlovesWeapons, empty);
    }
    if (g_NclGlovesDeployHook)
    {
        EnableHookChain(g_NclGlovesDeployHook);
        EnableHookChain(g_NclGlovesSpawnHook);
        EnableHookChain(g_NclGlovesRemoveHook);
    }
    else
    {
        g_NclGlovesDeployHook = RegisterHookChain(RG_CBasePlayerWeapon_DefaultDeploy, "_NclGlovesDeploy", true);
        g_NclGlovesSpawnHook = RegisterHookChain(RG_CBasePlayer_Spawn, "_NclGlovesSpawn", true);
        g_NclGlovesRemoveHook = RegisterHookChain(RG_CBasePlayer_RemovePlayerItem, "_NclGlovesRemove", true);
    }
    g_NclGlovesFreeForward = register_forward(FM_OnFreeEntPrivateData, "_NclGlovesFree");
    g_NclGlovesDisconnectForward = register_forward(FM_ClientDisconnect, "_NclGlovesDisconnect");
    g_NclGlovesInitialized = true;
    return true;
}

stock bool:_NclGlovesProfileValid(profile)
{
    return profile > 0 && g_NclGlovesProfiles && profile <= ArraySize(g_NclGlovesProfiles);
}

stock bool:_NclGlovesPlayerValid(player)
{
    if (!g_NclGlovesInitialized || player < 1 || player > g_NclGlovesMaxPlayers || !is_user_connected(player))
    {
        return false;
    }
    new userid = get_user_userid(player);
    if (userid != g_NclGlovesUserId[player])
    {
        // Player slots can keep their edict serial across connections.
        _NclGlovesApply(player, 0);
        g_NclGlovesUserId[player] = userid;
        g_NclGlovesPlayer[player] = 0;
        g_NclGlovesApplied[player] = 0;
    }
    return true;
}

stock bool:_NclGlovesWeaponValid(weapon)
{
    if (!g_NclGlovesInitialized || weapon <= g_NclGlovesMaxPlayers ||
        weapon >= g_NclGlovesMaxEntities || pev_valid(weapon) != 2)
    {
        return false;
    }
    new classname[32];
    pev(weapon, pev_classname, classname, charsmax(classname));
    for (new index = 0; index < sizeof g_NclGlovesWeaponClasses; index++)
    {
        if (equal(classname, g_NclGlovesWeaponClasses[index]))
        {
            return true;
        }
    }
    return false;
}

stock _NclGlovesFindMaterial(Array:materials, const material[])
{
    if (!materials)
    {
        return -1;
    }

    new name[NCL_GLOVES_MATERIAL_LENGTH + 1];
    new count = ArraySize(materials);
    for (new index = 0; index < count; index++)
    {
        ArrayGetString(materials, index, name, charsmax(name));
        if (equal(name, material))
        {
            return index;
        }
    }

    return -1;
}

stock bool:_NclGlovesApply(player, profile_id)
{
    new previous = g_NclGlovesApplied[player];
    if (previous == profile_id)
    {
        return true;
    }

    new previous_profile[NclGlovesProfile];
    new previous_count;
    if (previous)
    {
        ArrayGetArray(g_NclGlovesProfiles, previous - 1, previous_profile);
        previous_count = ArraySize(previous_profile[NclGlovesMaterials]);
    }

    new bool:retained[NCL_GLOVES_MAX_MATERIALS];
    new name[NCL_GLOVES_MATERIAL_LENGTH + 1];
    if (profile_id)
    {
        new profile[NclGlovesProfile];
        ArrayGetArray(g_NclGlovesProfiles, profile_id - 1, profile);
        new count = ArraySize(profile[NclGlovesMaterials]);

        new Array:shared_materials;
        if (previous && equal(previous_profile[NclGlovesPreset], profile[NclGlovesPreset]))
        {
            shared_materials = previous_profile[NclGlovesMaterials];
        }

        new bool:added[NCL_GLOVES_MAX_MATERIALS];
        new appended_position = previous_count;
        new last_position = -1;
        new kept_count;
        for (new index = 0; index < count; index++)
        {
            ArrayGetString(profile[NclGlovesMaterials], index, name, charsmax(name));
            new position = _NclGlovesFindMaterial(shared_materials, name);
            if (!ncl_mat_bind(player, profile[NclGlovesPreset], name))
            {
                for (new rollback = 0; rollback < index; rollback++)
                {
                    if (added[rollback])
                    {
                        ArrayGetString(profile[NclGlovesMaterials], rollback, name, charsmax(name));
                        ncl_mat_unbind(player, profile[NclGlovesPreset], name);
                    }
                }

                return false;
            }

            if (position < 0)
            {
                added[index] = true;
                position = appended_position++;
            }
            else
            {
                retained[position] = true;
            }

            if (kept_count == index && position > last_position)
            {
                kept_count++;
                last_position = position;
            }
        }

        // Bind keeps existing positions. Only the suffix after the first inversion needs to move.
        // These pairs have already been registered for the current material owner.
        for (new index = kept_count; index < count; index++)
        {
            ArrayGetString(profile[NclGlovesMaterials], index, name, charsmax(name));
            ncl_mat_unbind(player, profile[NclGlovesPreset], name);
            ncl_mat_bind(player, profile[NclGlovesPreset], name);
        }
    }

    for (new index = 0; index < previous_count; index++)
    {
        if (!retained[index])
        {
            ArrayGetString(previous_profile[NclGlovesMaterials], index, name, charsmax(name));
            ncl_mat_unbind(player, previous_profile[NclGlovesPreset], name);
        }
    }

    g_NclGlovesApplied[player] = profile_id;
    return true;
}

// Custom weapon code that bypasses DefaultDeploy calls this after changing m_pActiveItem.
stock bool:ncl_gloves_refresh(player)
{
    if (!_NclGlovesPlayerValid(player))
    {
        return false;
    }
    new profile = g_NclGlovesPlayer[player];
    new weapon = get_member(player, m_pActiveItem);
    if (_NclGlovesWeaponValid(weapon))
    {
        new assignment[NclGlovesWeapon];
        ArrayGetArray(g_NclGlovesWeapons, weapon, assignment);
        if (assignment[NclGlovesSelection] && assignment[NclGlovesSerial] == pev_serial(weapon))
        {
            profile = assignment[NclGlovesSelection];
        }
    }
    return _NclGlovesApply(player, profile);
}

stock bool:_NclGlovesAssignPlayer(player, profile)
{
    if (!_NclGlovesPlayerValid(player))
    {
        return false;
    }
    new previous = g_NclGlovesPlayer[player];
    g_NclGlovesPlayer[player] = profile;
    if (!ncl_gloves_refresh(player))
    {
        g_NclGlovesPlayer[player] = previous;
        return false;
    }
    return true;
}

stock bool:ncl_gloves_set_player(player, profile)
{
    return _NclGlovesProfileValid(profile) && _NclGlovesAssignPlayer(player, profile);
}

stock bool:ncl_gloves_reset_player(player)
{
    return _NclGlovesAssignPlayer(player, 0);
}

stock bool:_NclGlovesAssignWeapon(weapon, profile)
{
    if (!_NclGlovesWeaponValid(weapon))
    {
        return false;
    }
    new previous[NclGlovesWeapon];
    new assignment[NclGlovesWeapon];
    ArrayGetArray(g_NclGlovesWeapons, weapon, previous);
    assignment[NclGlovesSerial] = pev_serial(weapon);
    assignment[NclGlovesSelection] = profile;
    ArraySetArray(g_NclGlovesWeapons, weapon, assignment);
    new player = get_member(weapon, m_pPlayer);
    if (_NclGlovesPlayerValid(player) && get_member(player, m_pActiveItem) == weapon && !ncl_gloves_refresh(player))
    {
        ArraySetArray(g_NclGlovesWeapons, weapon, previous);
        return false;
    }
    return true;
}

stock bool:ncl_gloves_set_weapon(weapon, profile)
{
    return _NclGlovesProfileValid(profile) && _NclGlovesAssignWeapon(weapon, profile);
}

stock bool:ncl_gloves_reset_weapon(weapon)
{
    return _NclGlovesAssignWeapon(weapon, 0);
}

public _NclGlovesDeploy(weapon)
{
    if (g_NclGlovesInitialized && GetHookChainReturn(ATYPE_INTEGER))
    {
        ncl_gloves_refresh(get_member(weapon, m_pPlayer));
    }
    return HC_CONTINUE;
}

public _NclGlovesSpawn(player)
{
    ncl_gloves_refresh(player);
    return HC_CONTINUE;
}

public _NclGlovesRemove(player)
{
    ncl_gloves_refresh(player);
    return HC_CONTINUE;
}

public _NclGlovesFree(entity)
{
    if (g_NclGlovesInitialized && entity > g_NclGlovesMaxPlayers && entity < g_NclGlovesMaxEntities)
    {
        // Clear before the GameDLL can retire the item and enter nested deployment hooks.
        new empty[NclGlovesWeapon];
        ArraySetArray(g_NclGlovesWeapons, entity, empty);
    }
    return FMRES_IGNORED;
}

public _NclGlovesDisconnect(player)
{
    if (g_NclGlovesInitialized && player >= 1 && player <= g_NclGlovesMaxPlayers)
    {
        // AMXX can clear its connected flag before Fakemeta runs this forward.
        if (pev_valid(player))
        {
            _NclGlovesApply(player, 0);
        }
        g_NclGlovesUserId[player] = 0;
        g_NclGlovesPlayer[player] = 0;
        g_NclGlovesApplied[player] = 0;
    }
    return FMRES_IGNORED;
}

stock ncl_gloves_shutdown()
{
    if (g_NclGlovesInitialized)
    {
        DisableHookChain(g_NclGlovesDeployHook);
        DisableHookChain(g_NclGlovesSpawnHook);
        DisableHookChain(g_NclGlovesRemoveHook);
        unregister_forward(FM_OnFreeEntPrivateData, g_NclGlovesFreeForward);
        unregister_forward(FM_ClientDisconnect, g_NclGlovesDisconnectForward);
        for (new player = 1; player <= g_NclGlovesMaxPlayers; player++)
        {
            _NclGlovesDisconnect(player);
            g_NclGlovesUserId[player] = 0;
            g_NclGlovesPlayer[player] = 0;
            g_NclGlovesApplied[player] = 0;
        }
        ArrayDestroy(g_NclGlovesWeapons);
        g_NclGlovesInitialized = false;
    }
    if (g_NclGlovesProfiles)
    {
        new profile[NclGlovesProfile];
        for (new index = 0; index < ArraySize(g_NclGlovesProfiles); index++)
        {
            ArrayGetArray(g_NclGlovesProfiles, index, profile);
            ArrayDestroy(profile[NclGlovesMaterials]);
        }
        ArrayDestroy(g_NclGlovesProfiles);
    }
}
