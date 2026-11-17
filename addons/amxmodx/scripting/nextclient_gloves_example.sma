#include <amxmodx>
#include <amxmisc>
#include <next_client_gloves>

new const PRESET[] = "materials/test_nextclient/gloves.mat";
new const BLUE[][] = {"blue_gloves"};
new const RED[][] = {"red_gloves"};
new g_Profiles[2];

public plugin_precache()
{
    if (!file_exists(PRESET))
    {
        set_fail_state("Glove preset is missing: materials/test_nextclient/gloves.mat");
        return;
    }
    ncl_upload_file(PRESET, PRESET);
    g_Profiles[0] = ncl_gloves_register(PRESET, BLUE);
    g_Profiles[1] = ncl_gloves_register(PRESET, RED);
    if (!g_Profiles[0] || !g_Profiles[1])
    {
        set_fail_state("Could not register glove profiles");
    }
}

public plugin_init()
{
    register_plugin("NextClient Glove Profiles", "1.0.0", "NextClient");
    ncl_gloves_init();
    register_concmd("ncl_gloves_player", "CommandGloves", ADMIN_CFG, "<0: original | 1: blue | 2: red>");
    register_concmd("ncl_gloves_weapon", "CommandGloves", ADMIN_CFG, "<0: player default | 1: blue | 2: red>");
}

public plugin_end()
{
    ncl_gloves_shutdown();
}

public CommandGloves(player, level, command_id)
{
    if (!cmd_access(player, level, command_id, 2))
    {
        return PLUGIN_HANDLED;
    }
    if (!is_user_connected(player))
    {
        console_print(player, "Run this command from a connected player.");
        return PLUGIN_HANDLED;
    }
    new argument[16];
    read_argv(1, argument, charsmax(argument));
    new selection = str_to_num(argument);
    if (!is_str_num(argument) || selection < 0 || selection > sizeof g_Profiles)
    {
        console_print(player, "Choose 0, 1 or 2.");
        return PLUGIN_HANDLED;
    }

    new command[32];
    read_argv(0, command, charsmax(command));
    new bool:success;
    if (equal(command, "ncl_gloves_weapon"))
    {
        new weapon = get_member(player, m_pActiveItem);
        success = selection ? ncl_gloves_set_weapon(weapon, g_Profiles[selection - 1]) : ncl_gloves_reset_weapon(weapon);
    }
    else
    {
        success = selection ? ncl_gloves_set_player(player, g_Profiles[selection - 1]) : ncl_gloves_reset_player(player);
    }
    console_print(player, "Glove selection %s.", success ? "applied" : "failed");
    return PLUGIN_HANDLED;
}
