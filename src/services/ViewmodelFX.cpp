#include "ViewmodelFX.h"

#include <easylogging++.h>

#include <core/type_conversion.h>
#include <metamod/engine.h>

#include "utils/msg_ex.h"

using namespace core;
using namespace metamod;
using namespace msg_ex;

ViewmodelFX::ViewmodelFX(ServerEventsManager& server_events_manager) :
    server_events_manager_(server_events_manager)
{
    server_events_manager_.on_server_activated().connect(&ViewmodelFX::ServerActivatedHandler, this);
}

void ViewmodelFX::WriteRenderMode(int rendermode)
{
    if (!is_message_building_)
    {
        LOG(ERROR) << "Writing RenderMode with no started message";
        return;
    }

    if (rendermode == -1)
    {
        StateReset(VFX::VMFX_RENDERMODE);
    }
    else
    {
        vfx_state_.rendermode = rendermode;
        StateSet(VFX::VMFX_RENDERMODE);
    }
}

void ViewmodelFX::WriteRenderAmt(int renderamt)
{
    if (!is_message_building_)
    {
        LOG(ERROR) << "Writing RenderAmt with no started message";
        return;
    }

    if (renderamt == -1)
    {
        StateReset(VFX::VMFX_RENDERAMT);
    }
    else
    {
        vfx_state_.renderamt = renderamt;
        StateSet(VFX::VMFX_RENDERAMT);
    }
}

void ViewmodelFX::WriteRenderColor(int r, int g, int b)
{
    if (!is_message_building_)
    {
        LOG(ERROR) << "Writing RenderColor with no started message";
        return;
    }

    if (r == -1)
    {
        StateReset(VFX::VMFX_RENDERCOLOR);
    }
    else
    {
        cssdk::Color24* color = &vfx_state_.rendercolor;
        color->red = r;
        color->green = g;
        color->blue = b;
        StateSet(VFX::VMFX_RENDERCOLOR);
    }
}

void ViewmodelFX::WriteRenderFX(int renderfx)
{
    if (!is_message_building_)
    {
        LOG(ERROR) << "Writing RenderFX with no started message";
        return;
    }

    if (renderfx == -1)
    {
        StateReset(VFX::VMFX_RENDERFX);
    }
    else
    {
        vfx_state_.renderfx = renderfx;
        StateSet(VFX::VMFX_RENDERFX);
    }
}

void ViewmodelFX::WriteSkin(int skin)
{
    if (!is_message_building_)
    {
        LOG(ERROR) << "Writing Skin with no started message";
        return;
    }

    if (skin == -1)
    {
        StateReset(VFX::VMFX_SKIN);
    }
    else
    {
        vfx_state_.skin = skin;
        StateSet(VFX::VMFX_SKIN);
    }
}

void ViewmodelFX::WriteBody(int body)
{
    if (!is_message_building_)
    {
        LOG(ERROR) << "Writing Body with no started message";
        return;
    }

    if (body == -1)
    {
        StateReset(VFX::VMFX_BODY);
    }
    else
    {
        vfx_state_.body = body;
        StateSet(VFX::VMFX_BODY);
    }
}

void ViewmodelFX::StateSet(VFX state)
{
    bit_state_set_ |= (1 << (int)state);
}

void ViewmodelFX::StateReset(VFX state)
{
    bit_state_reset_ |= (1 << (int)state);
}

bool ViewmodelFX::StateIsSet(VFX state) const
{
    return (bit_state_set_ & (1 << (int)state));
}

void ViewmodelFX::Begin(ClientId client)
{
    if (is_message_building_)
    {
        LOG(ERROR) << "Repeating of message beginning";
        return;
    }

    memset(&vfx_state_, 0, sizeof(VFXState));

    client_id_ = client;
    bit_state_set_ = 0;
    bit_state_reset_ = 0;
    is_message_building_ = true;
}

void ViewmodelFX::End()
{
    if (!is_message_building_)
    {
        LOG(ERROR) << "Ending with no started message";
        return;
    }

    MessageBegin(cssdk::MessageType::One, message_viewmodelFX_, nullptr, type_conversion::EdictByIndex(client_id_));

    if (bit_state_reset_)
    {
        bit_state_set_ |= (1 << 6);
    }

    WriteByte(bit_state_set_);

    if (bit_state_reset_)
    {
        WriteByte(bit_state_reset_);
    }

    if (StateIsSet(VFX::VMFX_RENDERMODE) || StateIsSet(VFX::VMFX_RENDERFX))
    {
        WriteByte(vfx_state_.rendermode | (vfx_state_.renderfx << 3));
    }

    if (StateIsSet(VFX::VMFX_RENDERAMT))
    {
        WriteByte(vfx_state_.renderamt);
    }

    if (StateIsSet(VFX::VMFX_RENDERCOLOR))
    {
        cssdk::Color24* color = &vfx_state_.rendercolor;

        WriteByte(color->red);
        WriteByte(color->green);
        WriteByte(color->blue);
    }

    if (StateIsSet(VFX::VMFX_SKIN))
    {
        WriteByte(vfx_state_.skin);
    }

    if (StateIsSet(VFX::VMFX_BODY))
    {
        WriteInt(vfx_state_.body);
    }

    engine::MessageEnd();

    is_message_building_ = false;
}

void ViewmodelFX::ServerActivatedHandler(ServerActivatedEvent event)
{
    message_viewmodelFX_ = RegUserMsgSafe("ViewModelFx", -1);
}
