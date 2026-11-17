#include <amxmodx>
#include <fakemeta>
#include <reapi>
#include <next_client_gloves>

native Check(bool:condition, const message[]);
native FixtureEnums(active_member, owner_member, classname_field);
native FixturePlayer(player, userid, weapon);
native FixtureDisconnect(player);
native FixtureWeapon(weapon, serial, owner);
native FixtureShield(entity);
native FixtureFailure(const material[]);
native bool:HasBinding(entity, const preset[], const material[]);
native BindingCount(entity);
native bool:BindingIsAt(entity, index, const preset[], const material[]);
native BindCalls();

stock CheckOrderedTransitions()
{
    new const preset[] = "materials/gloves.mat";
    new const forward_names[][] = {"hands_a", "hands_b"};
    new const override_names[][] = {"hands_b"};
    new const reverse_names[][] = {"hands_b", "hands_a"};
    new const mixed_names[][] = {"hands_b", "new_a", "hands_a", "new_b"};
    new forward_profile = ncl_gloves_register(preset, forward_names);
    new override_profile = ncl_gloves_register(preset, override_names);
    new reverse_profile = ncl_gloves_register(preset, reverse_names);
    new mixed_profile = ncl_gloves_register(preset, mixed_names);

    FixturePlayer(3, 30, 43);
    FixtureWeapon(43, 1, 3);
    ncl_mat_bind(3, preset, "unrelated_a");
    Check(ncl_gloves_set_player(3, forward_profile), "ordered player profile applies");
    ncl_mat_bind(3, preset, "unrelated_b");
    Check(BindingCount(3) == 4 && BindingIsAt(3, 1, preset, "hands_a") &&
        BindingIsAt(3, 2, preset, "hands_b"), "initial bindings follow profile order");
    Check(ncl_gloves_set_weapon(43, override_profile), "overlapping weapon profile applies");
    Check(BindingCount(3) == 3 && BindingIsAt(3, 1, preset, "hands_b"),
        "weapon override retains the existing pair");
    Check(ncl_gloves_reset_weapon(43), "overlapping weapon profile resets");
    Check(BindingCount(3) == 4 && BindingIsAt(3, 2, preset, "hands_a") &&
        BindingIsAt(3, 3, preset, "hands_b"), "weapon reset restores player binding order");
    Check(BindingIsAt(3, 0, preset, "unrelated_a") && BindingIsAt(3, 1, preset, "unrelated_b"),
        "weapon reset preserves unrelated bindings and their order");

    FixtureFailure("new_b");
    Check(!ncl_gloves_set_player(3, mixed_profile), "reordered profile reports a failed addition");
    Check(BindingCount(3) == 4 && BindingIsAt(3, 0, preset, "unrelated_a") &&
        BindingIsAt(3, 1, preset, "unrelated_b") && BindingIsAt(3, 2, preset, "hands_a") &&
        BindingIsAt(3, 3, preset, "hands_b"), "failed reorder keeps the complete previous binding order");
    FixtureFailure("");
    Check(ncl_gloves_refresh(3) && BindingCount(3) == 4, "failed reorder preserves the previous selection");

    Check(ncl_gloves_set_player(3, reverse_profile), "same pairs can be set in reverse order");
    Check(BindingCount(3) == 4 && BindingIsAt(3, 2, preset, "hands_b") &&
        BindingIsAt(3, 3, preset, "hands_a"), "reversed profile changes binding priority");
    Check(ncl_gloves_set_player(3, mixed_profile), "profile can interleave new and retained pairs");
    Check(BindingCount(3) == 6 && BindingIsAt(3, 0, preset, "unrelated_a") &&
        BindingIsAt(3, 1, preset, "unrelated_b") && BindingIsAt(3, 2, preset, "hands_b") &&
        BindingIsAt(3, 3, preset, "new_a") && BindingIsAt(3, 4, preset, "hands_a") &&
        BindingIsAt(3, 5, preset, "new_b"), "new and retained pairs follow the requested order");
}

public RunTests()
{
    FixtureEnums(_:m_pActiveItem, _:m_pPlayer, _:pev_classname);
    FixturePlayer(1, 10, 40);
    FixtureWeapon(40, 1, 1);
    new const materials[][] = {"hands"};
    new profile = ncl_gloves_register("materials/gloves.mat", materials);
    ncl_gloves_init();
    Check(ncl_gloves_set_player(1, profile), "player default applies");
    Check(HasBinding(1, "materials/gloves.mat", "hands"), "default is bound to rendered player");
    new const red_names[][] = {"red_hands", "red_fingers"};
    new const shared_names[][] = {"hands", "red_fingers"};
    new const bad_names[][] = {"temporary", "fail"};
    new const duplicates[][] = {"hands", "HANDS"};
    new red = ncl_gloves_register("materials/gloves.mat", red_names);
    new shared = ncl_gloves_register("materials/gloves.mat", shared_names);
    new failing = ncl_gloves_register("materials/gloves.mat", bad_names);
    Check(red > 0 && shared > 0 && failing > 0, "profiles can be registered after initialization");
    Check(!ncl_gloves_register("materials/gloves.mat", duplicates), "case-insensitive duplicate names are rejected");
    Check(!ncl_gloves_register("", materials), "empty preset rejected");
    Check(!ncl_gloves_register("materials/gloves.mat", materials, 0), "empty profile rejected");
    Check(!ncl_gloves_set_player(0, profile), "world is not a player");
    Check(!ncl_gloves_set_player(1, 999), "invalid profile leaves choice unchanged");
    Check(!ncl_gloves_set_weapon(1, profile), "player is not a weapon");
    Check(!ncl_gloves_set_weapon(900, profile), "out-of-range weapon rejected");
    Check(!ncl_gloves_set_weapon(41, profile), "missing weapon rejected");
    FixtureShield(42);
    Check(!ncl_gloves_set_weapon(42, profile), "dropped shield is rejected without reading weapon members");
    Check(!ncl_gloves_reset_weapon(42), "shield reset is rejected without mutating state");
    ncl_mat_bind(1, "materials/other.mat", "unrelated");
    new calls = BindCalls();
    Check(ncl_gloves_set_player(1, profile), "repeated selection succeeds");
    Check(BindCalls() == calls, "unchanged profile does not send redundant bindings");
    Check(ncl_gloves_set_weapon(40, red), "active weapon override applies");
    Check(HasBinding(1, "materials/gloves.mat", "red_hands"), "weapon profile wins");
    Check(!HasBinding(1, "materials/gloves.mat", "hands"), "player default is temporarily removed");
    Check(HasBinding(1, "materials/other.mat", "unrelated"), "weapon override preserves unrelated materials");
    Check(ncl_gloves_set_player(1, shared), "default can change under an override");
    Check(!HasBinding(1, "materials/gloves.mat", "hands"), "changing default does not hide weapon override");
    Check(ncl_gloves_reset_weapon(40), "weapon reset succeeds");
    Check(HasBinding(1, "materials/gloves.mat", "hands") && HasBinding(1, "materials/gloves.mat", "red_fingers"), "reset restores current player default and shared pair");
    Check(!HasBinding(1, "materials/gloves.mat", "red_hands"), "only obsolete pairs removed");
    Check(ncl_gloves_set_player(1, profile), "shared profile can return to simple profile");
    Check(HasBinding(1, "materials/gloves.mat", "hands") && !HasBinding(1, "materials/gloves.mat", "red_fingers"), "overlap kept and extra pair removed");

    FixtureWeapon(41, 1, 1);
    Check(ncl_gloves_set_weapon(41, red), "inactive weapon accepts its own choice");
    Check(HasBinding(1, "materials/gloves.mat", "hands"), "inactive weapon cannot override active one");
    FixturePlayer(1, 10, 41);
    _NclGlovesDeploy(41);
    Check(HasBinding(1, "materials/gloves.mat", "red_hands"), "deploy applies inactive weapon choice");
    FixturePlayer(1, 10, 40);
    _NclGlovesDeploy(40);
    Check(HasBinding(1, "materials/gloves.mat", "hands"), "switch back restores default");
    FixturePlayer(2, 20, 41);
    FixtureWeapon(41, 1, 2);
    Check(ncl_gloves_set_player(2, shared), "new owner can have a different default");
    _NclGlovesDeploy(41);
    Check(HasBinding(2, "materials/gloves.mat", "red_hands"), "weapon assignment follows transfer");
    Check(ncl_gloves_reset_weapon(41), "new owner can clear weapon override");
    Check(HasBinding(2, "materials/gloves.mat", "hands") && HasBinding(2, "materials/gloves.mat", "red_fingers"), "transfer reset uses new owner's default");

    FixtureFailure("fail");
    Check(!ncl_gloves_set_player(1, failing), "partial player bind failure is reported");
    Check(HasBinding(1, "materials/gloves.mat", "hands") && !HasBinding(1, "materials/gloves.mat", "temporary"), "failed player change preserves old pairs and rolls back additions");
    FixtureFailure("");
    _NclGlovesSpawn(1);
    Check(HasBinding(1, "materials/gloves.mat", "hands") && !HasBinding(1, "materials/gloves.mat", "fail"), "failed player request cannot apply on a later spawn");
    FixtureFailure("fail");
    Check(!ncl_gloves_set_weapon(40, failing), "partial weapon bind failure is reported");
    FixtureFailure("");
    _NclGlovesDeploy(40);
    Check(HasBinding(1, "materials/gloves.mat", "hands") && !HasBinding(1, "materials/gloves.mat", "fail"), "failed weapon request cannot apply on a later deploy");
    Check(ncl_gloves_set_weapon(40, red), "prepare reset failure");
    FixtureFailure("hands");
    Check(!ncl_gloves_reset_weapon(40), "failed fallback rejects reset");
    Check(HasBinding(1, "materials/gloves.mat", "red_hands"), "failed fallback keeps previous effective profile");
    FixtureFailure("");
    _NclGlovesDeploy(40);
    Check(HasBinding(1, "materials/gloves.mat", "red_hands"), "failed reset keeps requested weapon choice");
    Check(ncl_gloves_reset_player(1), "player reset under override succeeds");
    Check(HasBinding(1, "materials/gloves.mat", "red_hands"), "player reset preserves weapon override");
    Check(ncl_gloves_reset_weapon(40), "weapon reset with no default succeeds");
    Check(!HasBinding(1, "materials/gloves.mat", "red_hands"), "no assignments restores original model material");

    Check(ncl_gloves_set_player(1, profile) && ncl_gloves_set_weapon(40, red), "prepare entity reuse");
    FixtureWeapon(40, 2, 1);
    _NclGlovesDeploy(40);
    Check(HasBinding(1, "materials/gloves.mat", "hands"), "serial change rejects stale weapon choice without a free callback");
    Check(ncl_gloves_set_weapon(40, red), "new entity can receive its own override");
    _NclGlovesFree(40);
    _NclGlovesDeploy(40);
    Check(HasBinding(1, "materials/gloves.mat", "hands"), "pre-free clearing precedes nested deployment");
    Check(ncl_gloves_set_weapon(40, red), "prepare weapon removal");
    FixturePlayer(1, 10, 0);
    _NclGlovesRemove(1);
    Check(HasBinding(1, "materials/gloves.mat", "hands"), "removal uses current active item after the GameDLL clears it");
    FixtureDisconnect(1);
    _NclGlovesDisconnect(1);
    Check(!HasBinding(1, "materials/gloves.mat", "hands"), "disconnect removes own bindings");
    Check(HasBinding(1, "materials/other.mat", "unrelated"), "disconnect does not clear unrelated material state");
    FixturePlayer(1, 11, 41);
    FixtureWeapon(41, 3, 1);
    _NclGlovesSpawn(1);
    Check(!HasBinding(1, "materials/gloves.mat", "hands"), "new connection cannot inherit player default");
    Check(ncl_gloves_set_player(1, profile), "new connection accepts a default");
    FixturePlayer(1, 12, 41);
    _NclGlovesSpawn(1);
    Check(!HasBinding(1, "materials/gloves.mat", "hands"), "userid change rejects stale player state even without disconnect callback");
    CheckOrderedTransitions();
    ncl_gloves_shutdown();
    Check(!HasBinding(2, "materials/gloves.mat", "hands"), "shutdown removes only active glove profiles");
    Check(BindingCount(3) == 2 && BindingIsAt(3, 0, "materials/gloves.mat", "unrelated_a") &&
        BindingIsAt(3, 1, "materials/gloves.mat", "unrelated_b"), "shutdown preserves unrelated bindings after reordering");
    Check(!ncl_gloves_set_player(2, profile), "shutdown invalidates profile handles");
    new restarted = ncl_gloves_register("materials/gloves.mat", materials);
    Check(ncl_gloves_init() && ncl_gloves_set_player(2, restarted), "shutdown and reinitialization are supported");
    ncl_gloves_shutdown();
}
