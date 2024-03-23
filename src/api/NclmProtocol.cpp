#include "NclmProtocol.h"
#include "SizeBufWriter.h"
#include "api/nclm_proto.h"
#include "rehlds_api_provider.h"
#include "asserts.h"
#include <stddef.h>
#include <string>
#include <map>

class NclmSizeBufWriter : public SizeBufWriter {
public:
	NclmSizeBufWriter(sizebuf_t* output_buf, size_t maxsize)
		: SizeBufWriter(output_buf, maxsize) {
		WriteByte(SVC_NCL_MESSAGE);
		WriteLong(NCLM_HEADER);
	}

	std::map<uint8_t, uint8_t> escaping_symbols_ = {
		{ 0x0, '0' },
		{ 0xFF, 'm' },
		{ '^', '^' }
	};

	void Send() override {
		auto slice = GetTempBufCurSizeSlice();

		for (auto it = slice.begin(); it != slice.end(); it++) {
			auto symbol = *it;
			if (escaping_symbols_.count(symbol)) {
				*it = '^';
				it = slice.insert(it + 1, escaping_symbols_[symbol]);
			}
		}
		slice.push_back(NULL);

		ReplaceTempBufWithSlice(slice);
		SizeBufWriter::Send();
	}
};

NclmProtocol::NclmProtocol(EventManager* event_manager)
	: event_manager_(event_manager) { }

void NclmProtocol::OnHandleNCLMessage(int client, NCLM_C2S opcode) {
	switch (opcode) {
	case VERIFICATION_REQUEST:
		OnVerificationRequest(client);
		break;

	case VERIFICATION_RESPONSE:
		OnVerificationResponse(client);
		break;
	}
}

void NclmProtocol::OnVerificationRequest(int client) {
	std::string rsaKeyVersion = MSG_ReadString();

	NAPI_LOG_ASSERT(!MSG_IsBadRead(), "%s: badread on %s", __FUNCTION__, MF_GetPlayerName(client));

	event_manager_->OnNclmVerificationRequest(client, rsaKeyVersion);
}

void NclmProtocol::OnVerificationResponse(int client) {
	std::vector<uint8_t> payload;

	payload.assign(NCLM_VERIF_PAYLOAD_SIZE, 0x00);
	std::string clientVersion = MSG_ReadString();
	auto written = MSG_ReadBuf(payload.size(), payload.data());

	auto name = MF_GetPlayerName(client);
	auto netMessage = g_RehldsFuncs->GetNetMessage();
    int readcount = *g_RehldsFuncs->GetMsgReadCount();
	NAPI_LOG_ASSERT(!MSG_IsBadRead(), "%s: badread on %s (%d/%d/%d)", 
		__FUNCTION__, name, readcount, readcount + NCLM_VERIF_PAYLOAD_SIZE, netMessage->cursize);

	event_manager_->OnNclmVerificationResponse(client, clientVersion, payload);
}

sizebuf_t* NclmProtocol::GetClientReliableChannel(int client) {
	auto cl = g_RehldsApi->GetServerStatic()->GetClient(client - 1);
	return cl->GetNetChan()->GetMessageBuf();
}

sizebuf_t* NclmProtocol::GetClientUnrealibleChannel(int client) {
	auto cl = g_RehldsApi->GetServerStatic()->GetClient(client - 1);
	return cl->GetDatagram();
}

void NclmProtocol::SendVerificationPayload(int client, std::vector<uint8_t> payload) {
	NclmSizeBufWriter message(GetClientReliableChannel(client), 0x140);

	message.WriteByte(NCLM_S2C::VERIFICATION_PAYLOAD)
		->WriteBuf(payload)
		->Send();
}