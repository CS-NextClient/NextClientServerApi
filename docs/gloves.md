# Player and weapon gloves

[Russian version](gloves.ru.md)

Include `next_client_gloves.inc` to select glove materials with Pawn stocks over the existing material natives. Requirements: AMX Mod X 1.9+, Fakemeta, ReAPI with ReGameDLL, a NextClientServerApi module providing `ncl_mat_bind` and `ncl_mat_unbind`, and a compatible NextClient with shaders and materials enabled. ReAPI is required by this optional helper only.

## Register and assign profiles

Register profiles in `plugin_precache` with `ncl_gloves_register(preset, materials, count)`. `preset` is the client-relative `.mat` path; `materials` is a two-dimensional array of material names from that preset. `count` defaults to the array length and, when supplied, must not exceed it. A profile contains 1 to 16 distinct names. Paths are limited to 128 bytes and names to 189 bytes. Registration returns a positive handle or zero on invalid input. Profiles are immutable and belong to the plugin registering them.

Deliver the preset and its custom PNG/TGA files through `ncl_upload_file` in `plugin_precache`. Material entries target the actual model texture names. Stock Counter-Strike view models commonly use `view_glove.bmp`, `view_finger.bmp` and `view_skin.BMP`; custom models can use other names. Use separate material entries for the hand textures needed by your models. The client limit remains 16 distinct admitted textures per rendered entity, including other materials.

Call `ncl_gloves_init()` in `plugin_init` and `ncl_gloves_shutdown()` in `plugin_end`. Initialization preserves profiles registered during precache. The helper handles normal weapon deployment, spawning, removal from inventory, player disconnect and entity reuse. It uses ReAPI deployment hooks, so custom weapon code that bypasses normal deployment must call `ncl_gloves_refresh(player)` after updating the active weapon.

| Stock | Behavior |
|---|---|
| `ncl_gloves_set_player(player, profile)` | Set the player's default for weapons without an override. |
| `ncl_gloves_reset_player(player)` | Remove the player's default; a weapon override remains active. |
| `ncl_gloves_set_weapon(weapon, profile)` | Assign a profile to this weapon entity. It follows the weapon when transferred. |
| `ncl_gloves_reset_weapon(weapon)` | Remove this weapon's override and restore the current owner's default. |
| `ncl_gloves_refresh(player)` | Re-evaluate the current active weapon and apply the effective selection. |

Set, reset and refresh return `true` on success and `false` on invalid input or a failed immediate material bind. A failed setter or resetter preserves the previous assignment and effective bindings. A successful assignment to an inactive weapon is applied when deployed; a later refresh can still fail if the material service rejects a bind. These results do not confirm that the client downloaded files or rendered the material.

Weapon choices take priority regardless of assignment order. Inactive carried weapons do not change the visible gloves. Clearing a weapon choice restores the current owner's default; clearing both restores the model material. Each profile applies its bindings in the registered order. If several applicable materials target the same model texture, the last one in the profile takes precedence. Player defaults last for the connection and do not transfer to another player occupying the same slot. Weapon choices end when that weapon entity is freed or its serial changes.

One plugin must own glove selection and the corresponding material pairs and texture names. Do not independently assign the same hand textures through another material plugin, or clear the helper's bindings through `ncl_mat_clear`. Other texture bindings remain intact. The helper changes materials on existing meshes; it does not replace hand geometry. Weapon setters accept the standard Counter-Strike weapon classnames, including custom weapons built on those entities. Dropped shields and arbitrary renamed entity classes are rejected.

To use an external glove image, set `uBaseTexture` in the profile material. `uBaseUvMode: 0` preserves normal MDL UV layout; transparency follows the model flags and entity rendering mode. Profiles may also use `weapon_finish` and its wear, pattern and effects. Texture names apply to matching meshes under the rendered player's entity index, not exclusively to one model file.

## Run the example

Compile [nextclient_gloves_example.sma](../addons/amxmodx/scripting/nextclient_gloves_example.sma) with both this repository's API includes and your AMXX/ReAPI includes. Copy [gloves.mat](../amxx_test/materials/test_nextclient/gloves.mat) to `cstrike/materials/test_nextclient/gloves.mat`, install the compiled plugin and enable it in `plugins.ini`. The example tints the stock glove texture blue or red and needs no custom images. Its commands require the AMXX configuration access flag.

From a connected player's console, use `ncl_gloves_player 1` for a blue default and `ncl_gloves_weapon 2` for a red override on the active weapon. Switch weapons, transfer the overridden weapon to another player and run `ncl_gloves_weapon 0` to restore that player's default. `ncl_gloves_player 0` clears the player default. Check first-person spectators, respawn, reconnect, hand transparency and unrelated weapon materials in the game. Runtime observations remain separate from compilation and automated stock tests.

## Automated checks

The `pawn-gloves-example` CTest compiles the example with the real AMXX compiler and rejects compiler warnings. Set `NEXTCLIENTAPI_PAWN_COMPILER` and `NEXTCLIENTAPI_PAWN_INCLUDE_DIR` when configuring tests.

For standalone execution, also set `NEXTCLIENTAPI_PAWN_VM_DIR` to the `compiler/amxxpc` directory of an AMX Mod X source checkout. Python 3 and an x86 C++20 compiler are required. Build `glove-stocks-runner`, then run CTest filtered to `pawn-gloves`. The test executes the compiled production stocks with engine and material-native test doubles, covering precedence, transfer, serial/userid reuse, binding order for overlapping profiles, rollback after binding failure and cleanup without starting a server.
