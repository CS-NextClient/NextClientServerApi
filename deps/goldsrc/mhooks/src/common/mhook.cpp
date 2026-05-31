/*
 *  Copyright (C) 2020 the_hunter
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include "../cleanup.h"
#include <mhooks/common/mhook.h>

namespace mhooks
{
    MHook::MHook(const cssdk::HookChainPriority priority, const bool enable)
        : destroy_at_detach_(false), priority_(priority), enabled_(enable)
    {
        DestroyAtDetach(true);
    }

    MHook::~MHook()
    {
        MHook::Disable();
        Notify(this, MHookNotice::Destroy);
        detail::RemoveFromDestroyList(this);
    }

    void MHook::Enable()
    {
        if (!enabled_) {
            enabled_ = true;
            Notify(this, MHookNotice::Enable);
        }
    }

    void MHook::Disable()
    {
        if (enabled_) {
            enabled_ = false;
            Notify(this, MHookNotice::Disable);
        }
    }

    void MHook::Toggle(const bool enable) noexcept
    {
        if (enable) {
            Enable();
        }
        else {
            Disable();
        }
    }

    void MHook::DestroyAtDetach(const bool destroy) const
    {
        if (destroy_at_detach_ != destroy) {
            destroy_at_detach_ = destroy;

            if (destroy_at_detach_) {
                detail::AddToDestroyList(this);
            }
            else {
                detail::RemoveFromDestroyList(this);
            }
        }
    }
}
