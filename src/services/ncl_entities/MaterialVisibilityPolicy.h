#pragma once

#include <unordered_map>
#include <vector>

struct MaterialEntityIdentity
{
    int index{};
    int serial{};

    bool operator==(const MaterialEntityIdentity& other) const
    {
        return index == other.index && serial == other.serial;
    }
};

class MaterialVisibilityPolicy
{
private:
    struct Selection
    {
        MaterialEntityIdentity source;
        MaterialEntityIdentity destination;
    };

    struct Packing
    {
        MaterialEntityIdentity entity;
        MaterialEntityIdentity host;
        bool compatible{};
    };

    std::unordered_map<int, Selection> selections_;
    std::vector<Packing> packing_;

public:
    bool Enable(MaterialEntityIdentity source, MaterialEntityIdentity destination, bool bound)
    {
        if (!bound)
        {
            return false;
        }

        selections_[source.index] = {source, destination};
        return true;
    }

    void Disable(int source_index)
    {
        selections_.erase(source_index);
    }

    bool is_empty() const
    {
        return selections_.empty();
    }

    bool ContainsSource(int source_index) const
    {
        return selections_.find(source_index) != selections_.end();
    }

    bool Update(MaterialEntityIdentity source, MaterialEntityIdentity destination, bool destination_valid = true)
    {
        auto found = selections_.find(source.index);
        if (found == selections_.end())
        {
            return false;
        }

        if (!destination_valid || !(found->second.source == source))
        {
            selections_.erase(found);
            return false;
        }

        if (found->second.destination.index == destination.index && found->second.destination.serial != destination.serial)
        {
            selections_.erase(found);
            return false;
        }

        found->second.destination = destination;
        return true;
    }

    void BeginPack(MaterialEntityIdentity entity, MaterialEntityIdentity host, bool compatible)
    {
        packing_.push_back({entity, host, compatible});
    }

    void EndPack()
    {
        if (!packing_.empty())
        {
            packing_.pop_back();
        }
    }

    MaterialEntityIdentity get_host() const
    {
        return packing_.empty() ? MaterialEntityIdentity{} : packing_.back().host;
    }

    bool Check(MaterialEntityIdentity entity, MaterialEntityIdentity host) const
    {
        if (packing_.empty())
        {
            return false;
        }

        const Packing& current = packing_.back();
        if (!current.compatible || !(current.entity == entity) || !(current.host == host))
        {
            return false;
        }

        for (const auto& item : selections_)
        {
            if (item.second.destination == entity)
            {
                return true;
            }
        }

        return false;
    }

    void Clear()
    {
        selections_.clear();
        packing_.clear();
    }
};
