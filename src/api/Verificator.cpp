#include "Verificator.h"
#include "asserts.h"

Verificator::Verificator(NclmProtocol* protocol, EventManager* event_manager) 
    : protocol_(protocol), event_manager_(event_manager)
{
    dirpath_public_keys_ = MF_BuildPathname("%s/nextclient_api/pkeys/", MF_GetLocalInfo("amxx_datadir", "addons/amxmodx/data"));
}

void Verificator::OnServerActivated(edict_t* pEdictList, int edictCount, int clientMax)
{
    for (int i = 0; i <= clientMax; i++)
        player_data_[i] = PlayerData();

    ParsePublicKeys();
}

void Verificator::OnClientDropConnection(int client, bool crash, const char* reason)
{
    if (player_data_.count(client) == 0)
        return;

    player_data_[client].payload.clear();
}

void Verificator::OnNclmVerificationRequest(int client, std::string rsaKeyVersion) {
    if (player_data_.count(client) == 0)
        return;

    auto name = MF_GetPlayerName(client);
    NAPI_LOG_ASSERT(map_cached_pkeys_.count(rsaKeyVersion) > 0, 
        "%s requesting verification with invalid key version (%s)", name, rsaKeyVersion.c_str());

    auto playerData = &player_data_[client];
    auto payload = &playerData->payload;
    if (!payload->empty())
        return;

    payload->assign(NCLM_VERIF_PAYLOAD_SIZE, 0x00);
    playerData->prefered_RSA_key_version = rsaKeyVersion;

    int res;
    auto ctx = EVP_PKEY_CTX_new(map_cached_pkeys_[rsaKeyVersion], NULL);
    res = EVP_PKEY_encrypt_init(ctx);
    NAPI_LOG_ASSERT(res > 0, "Cannot initialize encrypt context (code %d) on %s", res, name);

    size_t outLen;
    auto out = &playerData->encrypted_payload;
    out->assign(NCLM_VERIF_ENCRYPTED_PAYLOAD_SIZE, 0x00);

    RAND_bytes(payload->data(), payload->size());

    res = EVP_PKEY_encrypt(ctx, NULL, &outLen, payload->data(), payload->size());
    NAPI_LOG_ASSERT(res > 0, "Cannot perform encrypt operation (code %d) on %s", res, name);
    NAPI_LOG_ASSERT(outLen == NCLM_VERIF_ENCRYPTED_PAYLOAD_SIZE, "'%s' key length does not match (%d, but need %d) on %s",
                    rsaKeyVersion.c_str(), outLen, NCLM_VERIF_ENCRYPTED_PAYLOAD_SIZE, name);

    res = EVP_PKEY_encrypt(ctx, out->data(), &outLen, payload->data(), payload->size());
    NAPI_LOG_ASSERT(res > 0, "Cannot perform encrypt operation 2 (code %d) on %s", res, name);
}

void Verificator::OnSendServerInfo(int client) {
    if(player_data_.count(client) == 0)
        return;

    auto payload = &player_data_[client].encrypted_payload;
    if(!payload->empty()) {
        protocol_->SendVerificationPayload(client, *payload);
        payload->clear();
    }
}

void Verificator::OnNclmVerificationResponse(int client, std::string clientVersion, std::vector<uint8_t> payload) {
    if (player_data_.count(client) == 0)
        return;

    auto playerData = &player_data_[client];
    if (playerData->payload.empty())
        return;

    auto name = MF_GetPlayerName(client);
    auto rsaKeyVersion = playerData->prefered_RSA_key_version;

    NAPI_LOG_ASSERT(payload == playerData->payload, "%s: Decrypted payload body mismatch (%s) on %s",
                    __FUNCTION__, rsaKeyVersion.c_str(), name);

    event_manager_->OnClientVerificated(client, clientVersion, rsaKeyVersion);
}

int Verificator::ParsePublicKeys()
{
    using std::ifstream;

    map_cached_pkeys_.clear();

    ifstream fileActive(dirpath_public_keys_ + "active.txt");
    if (!fileActive.is_open())
        return 0;

    std::string line;
    char buffer[1024];

    while (std::getline(fileActive, line))
    {
        ifstream fileRSAKey(dirpath_public_keys_ + line + ".pem");
        if (!fileRSAKey.is_open())
            continue;

        long long readed = 0;
        BIO* bio = BIO_new(BIO_s_mem());

        while (fileRSAKey.good())
        {
            readed = fileRSAKey.rdbuf()->sgetn(buffer, 1024);
            BIO_write(bio, buffer, readed);

            if (readed != 1024)
                fileRSAKey.setstate(ifstream::eofbit | ifstream::failbit);
            else
                fileRSAKey.setstate(ifstream::goodbit);
        }
        map_cached_pkeys_[line] = PEM_read_bio_PUBKEY(bio, NULL, NULL, NULL);
    }

    return map_cached_pkeys_.size();
}
