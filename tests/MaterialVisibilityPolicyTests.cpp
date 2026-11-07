#include <cstdlib>
#include <iostream>

#include "services/ncl_entities/MaterialVisibilityPolicy.h"

namespace
{
    void Require(bool condition, const char* scenario)
    {
        if (!condition)
        {
            std::cerr << "FAILED: " << scenario << '\n';
            std::exit(EXIT_FAILURE);
        }
    }
} // namespace

int main()
{
    MaterialVisibilityPolicy policy;
    const MaterialEntityIdentity weapon{40, 7};
    const MaterialEntityIdentity player{1, 8};
    const MaterialEntityIdentity box{60, 9};
    const MaterialEntityIdentity host{2, 3};
    Require(!policy.Enable(weapon, player, false), "a binding is required");
    policy.BeginPack(player, host, true);
    Require(!policy.Check(player, host), "ordinary entities remain culled");
    policy.EndPack();
    Require(policy.Enable(weapon, player, true), "explicit opt-in");
    policy.BeginPack(player, host, false);
    Require(!policy.Check(player, host), "ordinary or unready recipients remain culled");
    policy.EndPack();
    policy.BeginPack(player, host, true);
    Require(policy.Check(player, host), "selected entity reaches a compatible recipient");
    Require(!policy.Check({1, 9}, host), "destination serial reuse is rejected");
    Require(!policy.Check(player, {2, 4}), "recipient serial reuse is rejected");
    Require(!policy.Check(box, host), "unrelated visibility queries remain culled");
    policy.BeginPack(box, host, true);
    Require(!policy.Check(player, host), "nested packing cannot borrow outer authorization");
    policy.EndPack();
    Require(policy.Check(player, host), "nested return restores its parent context");
    policy.EndPack();
    Require(!policy.Check(player, host), "no override outside entity packing");
    Require(policy.Update(weapon, box), "pickup or drop updates destination");
    policy.BeginPack(player, host, true);
    Require(!policy.Check(player, host), "previous owner loses authorization");
    policy.EndPack();
    policy.BeginPack(box, host, true);
    Require(policy.Check(box, host), "current owner gains authorization");
    policy.Disable(weapon.index);
    Require(!policy.Check(box, host), "disable revokes even an active context");
    policy.EndPack();
    Require(policy.Enable(weapon, player, true), "enable again");
    Require(!policy.Update({40, 8}, box), "source serial reuse clears authorization");
    policy.BeginPack(player, host, true);
    Require(!policy.Check(player, host), "stale source cannot preserve destination");
    policy.EndPack();
    policy.Enable(weapon, player, true);
    Require(!policy.Update(weapon, {player.index, player.serial + 1}), "owner serial reuse revokes authorization");
    policy.BeginPack({player.index, player.serial + 1}, host, true);
    Require(!policy.Check({player.index, player.serial + 1}, host), "a reused owner does not inherit the flag");
    policy.EndPack();
    policy.Enable(weapon, player, true);
    Require(!policy.Update(weapon, weapon, false), "an invalid owner chain revokes before fallback changes destination");
    Require(!policy.Update(weapon, {player.index, player.serial + 1}), "owner reuse cannot restore a revoked flag");
    policy.BeginPack({player.index, player.serial + 1}, host, true);
    Require(!policy.Check({player.index, player.serial + 1}, host), "owner reuse after a free interval remains culled");
    policy.EndPack();
    policy.Enable(weapon, player, true);
    policy.Clear();
    policy.BeginPack(player, host, true);
    Require(!policy.Check(player, host), "map change clears all state");
    policy.EndPack();
    std::cout << "Material visibility policy: all scenarios passed\n";
}
