#include <algorithm>
#include <cctype>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include <amx.h>

namespace
{
    struct CellArray
    {
        int width{};
        std::vector<std::vector<cell>> rows;
    };

    struct Entity
    {
        int user{};
        int serial = 1;
        int active{};
        int owner{};
        bool weapon{};
        bool connected{};
        bool shield{};
    };

    using Binding = std::pair<std::string, std::string>;

    std::map<int, CellArray> g_Arrays;
    std::map<int, Entity> g_Entities;
    std::map<int, std::vector<Binding>> g_Bindings;
    std::string g_FailMaterial;
    std::string g_Error;
    int g_NextArray{};
    int g_Checks{};
    int g_ActiveMember{};
    int g_OwnerMember{};
    int g_ClassnameField{};
    int g_BindCalls{};

    cell* Address(AMX* amx, cell address)
    {
        cell* result = nullptr;
        if (amx_GetAddr(amx, address, &result) != AMX_ERR_NONE)
        {
            throw std::runtime_error("invalid Pawn address");
        }
        return result;
    }

    std::string String(AMX* amx, cell address)
    {
        cell* data = Address(amx, address);
        int length = 0;
        amx_StrLen(data, &length);
        std::vector<char> text(length + 1);
        amx_GetString(text.data(), data, 0, text.size());
        return text.data();
    }

    cell WriteString(AMX* amx, cell address, int length, const std::string& value)
    {
        const size_t count = std::min(value.size(), static_cast<size_t>(length));
        amx_SetString(Address(amx, address), value.c_str(), 0, 0, count + 1);
        return static_cast<cell>(count);
    }

    cell Dispatch(AMX* amx, const std::string& name, const cell* p)
    {
        if (name == "Check")
        {
            ++g_Checks;
            if (!p[1])
            {
                throw std::runtime_error(String(amx, p[2]));
            }
            return 1;
        }
        if (name == "FixtureEnums")
        {
            g_ActiveMember = p[1];
            g_OwnerMember = p[2];
            g_ClassnameField = p[3];
            return 1;
        }
        if (name == "FixturePlayer")
        {
            Entity& player = g_Entities[p[1]];
            player.user = p[2];
            player.active = p[3];
            player.connected = p[2] != 0;
            return 1;
        }
        if (name == "FixtureDisconnect")
        {
            g_Entities[p[1]].connected = false;
            return 1;
        }
        if (name == "FixtureWeapon")
        {
            g_Entities[p[1]] = Entity{0, p[2], 0, p[3], true};
            return 1;
        }
        if (name == "FixtureShield")
        {
            g_Entities[p[1]] = Entity{};
            g_Entities[p[1]].shield = true;
            return 1;
        }
        if (name == "FixtureFailure")
        {
            g_FailMaterial = String(amx, p[1]);
            return 1;
        }
        if (name == "HasBinding")
        {
            const auto& bindings = g_Bindings[p[1]];
            const Binding binding{String(amx, p[2]), String(amx, p[3])};
            return std::find(bindings.begin(), bindings.end(), binding) != bindings.end();
        }
        if (name == "BindingCount")
        {
            return static_cast<cell>(g_Bindings[p[1]].size());
        }
        if (name == "BindingIsAt")
        {
            const auto& bindings = g_Bindings[p[1]];
            const Binding binding{String(amx, p[3]), String(amx, p[4])};
            const size_t index = static_cast<size_t>(p[2]);

            return index < bindings.size() && bindings[index] == binding;
        }
        if (name == "BindCalls")
        {
            return g_BindCalls;
        }
        if (name == "ncl_mat_clear")
        {
            throw std::runtime_error("gloves must not clear unrelated materials");
        }
        if (name == "ncl_mat_bind")
        {
            ++g_BindCalls;
            const Binding binding{String(amx, p[2]), String(amx, p[3])};
            if (binding.second == g_FailMaterial)
            {
                return 0;
            }

            auto& bindings = g_Bindings[p[1]];
            if (std::find(bindings.begin(), bindings.end(), binding) == bindings.end())
            {
                bindings.push_back(binding);
            }

            return 1;
        }
        if (name == "ncl_mat_unbind")
        {
            const Binding binding{String(amx, p[2]), String(amx, p[3])};
            return std::erase(g_Bindings[p[1]], binding) != 0;
        }
        if (name == "get_maxplayers")
        {
            return 32;
        }
        if (name == "global_get")
        {
            return 512;
        }
        if (name == "get_user_userid")
        {
            return g_Entities[p[1]].user;
        }
        if (name == "is_user_connected" || name == "is_user_alive")
        {
            return g_Entities[p[1]].connected;
        }
        if (name == "pev_serial")
        {
            return g_Entities[p[1]].serial;
        }
        if (name == "pev_valid")
        {
            return g_Entities.contains(p[1]) ? 2 : 0;
        }
        if (name == "get_member" || name == "get_member_s")
        {
            if (g_Entities[p[1]].shield)
            {
                throw std::runtime_error("CWShield is not a CBasePlayerItem");
            }
            if (p[2] == g_ActiveMember)
            {
                return g_Entities[p[1]].active;
            }
            if (p[2] == g_OwnerMember)
            {
                return g_Entities[p[1]].owner;
            }
            throw std::runtime_error("unexpected ReAPI member");
        }
        if (name == "pev")
        {
            if (p[2] != g_ClassnameField)
            {
                throw std::runtime_error("unexpected entity field");
            }
            return WriteString(
                amx, p[3], p[4], g_Entities[p[1]].shield ? "weapon_shield" : (g_Entities[p[1]].weapon ? "weapon_ak47" : "player")
            );
        }
        if (name == "get_weaponid")
        {
            const std::string classname = String(amx, p[1]);
            return classname == "weapon_ak47" ? 28 : (classname == "weapon_shield" ? 99 : 0);
        }
        if (name == "RegisterHookChain" || name == "EnableHookChain" || name == "DisableHookChain" || name == "register_forward" ||
            name == "unregister_forward" || name == "GetHookChainReturn")
        {
            return 1;
        }
        if (name == "strlen")
        {
            return static_cast<cell>(String(amx, p[1]).size());
        }
        if (name == "copy")
        {
            return WriteString(amx, p[1], p[2], String(amx, p[3]));
        }
        if (name == "equal" || name == "equali")
        {
            std::string left = String(amx, p[1]);
            std::string right = String(amx, p[2]);
            if (p[3] > 0)
            {
                left.resize(std::min(left.size(), size_t(p[3])));
                right.resize(std::min(right.size(), size_t(p[3])));
            }
            if (name == "equali")
            {
                for (char& c : left)
                {
                    c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
                }
                for (char& c : right)
                {
                    c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
                }
            }
            return left == right;
        }
        if (name == "ArrayCreate")
        {
            g_Arrays[++g_NextArray] = CellArray{p[1], {}};
            return g_NextArray;
        }
        if (name == "ArrayDestroy")
        {
            cell* handle = Address(amx, p[1]);
            g_Arrays.erase(*handle);
            *handle = 0;
            return 1;
        }
        CellArray& array = g_Arrays.at(p[1]);
        if (name == "ArraySize")
        {
            return static_cast<cell>(array.rows.size());
        }
        if (name == "ArrayResize")
        {
            array.rows.resize(p[2], std::vector<cell>(array.width));
            return 1;
        }
        if (name == "ArrayGetArray")
        {
            const int count = p[4] < 0 ? array.width : p[4];
            std::copy_n(array.rows.at(p[2]).data(), count, Address(amx, p[3]));
            return count;
        }
        if (name == "ArraySetArray" || name == "ArrayPushArray")
        {
            const bool push = name == "ArrayPushArray";
            const int index = push ? static_cast<int>(array.rows.size()) : p[2];
            if (push)
            {
                array.rows.emplace_back(array.width);
            }
            const int count = p[push ? 3 : 4] < 0 ? array.width : p[push ? 3 : 4];
            std::copy_n(Address(amx, p[push ? 2 : 3]), count, array.rows.at(index).data());
            return index;
        }
        if (name == "ArrayPushString")
        {
            array.rows.emplace_back(array.width);
            const std::string value = String(amx, p[2]);
            amx_SetString(array.rows.back().data(), value.c_str(), 0, 0, array.width);
            return static_cast<cell>(array.rows.size() - 1);
        }
        if (name == "ArrayGetString")
        {
            std::vector<char> value(array.width);
            amx_GetString(value.data(), array.rows.at(p[2]).data(), 0, value.size());
            return WriteString(amx, p[3], p[4], value.data());
        }
        throw std::runtime_error("unhandled native " + name);
    }

    int AMXAPI Callback(AMX* amx, cell index, cell* result, cell* parameters)
    {
        char name[128]{};
        amx_GetNative(amx, index, name);
        try
        {
            *result = Dispatch(amx, name, parameters);
            return AMX_ERR_NONE;
        }
        catch (const std::exception& error)
        {
            g_Error = std::string(name) + ": " + error.what();
            return AMX_ERR_NATIVE;
        }
    }
} // namespace

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        return 2;
    }
    std::ifstream stream(argv[1], std::ios::binary);
    std::vector<unsigned char> image((std::istreambuf_iterator<char>(stream)), {});
    if (image.size() < sizeof(AMX_HEADER))
    {
        return 2;
    }
    AMX_HEADER header{};
    std::memcpy(&header, image.data(), sizeof(header));
    image.resize(std::max(image.size(), static_cast<size_t>(header.stp)));
    AMX amx{};
    int error = amx_Init(&amx, image.data());
    if (error == AMX_ERR_NONE)
    {
        amx_SetCallback(&amx, Callback);
        amx.flags |= AMX_FLAG_NTVREG;
        int index = 0;
        error = amx_FindPublic(&amx, "RunTests", &index);
        cell result = 0;
        if (error == AMX_ERR_NONE)
        {
            error = amx_Exec(&amx, &result, index);
        }
    }
    amx_Cleanup(&amx);
    if (error != AMX_ERR_NONE)
    {
        std::cerr << "FAIL after " << g_Checks << " checks (AMX " << error << "): " << g_Error << '\n';
        return 1;
    }
    std::cout << "PASS: " << g_Checks << " stock behavior checks\n";
    return 0;
}
