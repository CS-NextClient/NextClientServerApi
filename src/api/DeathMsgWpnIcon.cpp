#include "DeathMsgWpnIcon.h"
#include "utilfuncs.h"
#include <utility>

void DeathMsgWpnIcon::OnServerActivated(edict_t* pEdictList, int edictCount, int clientMax) {
	message_deathmsg_wpn_icon = utils::RegUserMsgSafe("DeathMsgWpn", -1);
}

void DeathMsgWpnIcon::SetIconForNextMessage(
	const std::string& sprite, int frame, 
	int rendermode, int r, int g, int b, int a, int recipient_id
) {
	if(recipient_id != 0)
		MESSAGE_BEGIN(MSG_ONE, message_deathmsg_wpn_icon, NULL, INDEXENT(recipient_id));
	else
		MESSAGE_BEGIN(MSG_ALL, message_deathmsg_wpn_icon);
	WRITE_STRING(sprite.c_str());
	WRITE_BYTE(frame);
	WRITE_BYTE(rendermode);
	WRITE_BYTE(r);
	WRITE_BYTE(g);
	WRITE_BYTE(b);
	WRITE_BYTE(a);
	MESSAGE_END();
}