#include "Verifier.h"
#include <easylogging++.h>
#include <openssl/pem.h>
#include <openssl/rand.h>
#include "NclmProtocol.h"

#undef read

Verifier::Verifier()
{
    dirpath_public_keys_ =
        MF_BuildPathname("%s/nextclient_api/pkeys/", MF_GetLocalInfo("amxx_datadir", "addons/amxmodx/data"));

    ReloadPublicKeys();
}

Verifier::~Verifier()
{
    FreeAllKeys();
}

bool Verifier::TryCreateVerificationPayload(ClientId client, const std::string& rsa_key_version, VerificationPayload& verification_payload_out)
{
    const char* client_name = MF_GetPlayerName(client);

    auto it = cached_pkeys_.find(rsa_key_version);
    if (it == cached_pkeys_.end())
    {
        LOG(ERROR) << client_name << " requesting verification with invalid key version (" << rsa_key_version << ")";
        return false;
    }

    verification_payload_out.payload.assign(NCLM_VERIF_PAYLOAD_SIZE, 0);
    verification_payload_out.encrypted_payload.assign(NCLM_VERIF_ENCRYPTED_PAYLOAD_SIZE, 0);
    verification_payload_out.preferred_RSA_key_version = rsa_key_version;

    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new(it->second, nullptr);
    if (ctx == nullptr)
    {
        LOG(ERROR) << "Cannot create encrypt context on " << client_name;
        return false;
    }

    int res = EVP_PKEY_encrypt_init(ctx);
    if (res <= 0)
    {
        LOG(ERROR) << "Cannot initialize encrypt context (code " << res << ") on " << client_name;
        EVP_PKEY_CTX_free(ctx);
        return false;
    }

    res = RAND_bytes(verification_payload_out.payload.data(), verification_payload_out.payload.size());
    if (res <= 0)
    {
        LOG(ERROR) << "Cannot generate random bytes (code " << res << ") on " << client_name;
        EVP_PKEY_CTX_free(ctx);
        return false;
    }

    size_t out_len;
    res = EVP_PKEY_encrypt(ctx, nullptr, &out_len, verification_payload_out.payload.data(), verification_payload_out.payload.size());
    if (res <= 0)
    {
        LOG(ERROR) << "Cannot perform encrypt operation (code " << res << ") on " << client_name;
        EVP_PKEY_CTX_free(ctx);
        return false;
    }

    if (out_len != NCLM_VERIF_ENCRYPTED_PAYLOAD_SIZE)
    {
        LOG(DEBUG) << "'" << rsa_key_version << "' key length does not match (" << out_len << ", but need " << NCLM_VERIF_ENCRYPTED_PAYLOAD_SIZE << ") on " << client_name;
        EVP_PKEY_CTX_free(ctx);
        return false;
    }

    res = EVP_PKEY_encrypt(ctx, verification_payload_out.encrypted_payload.data(), &out_len, verification_payload_out.payload.data(), verification_payload_out.payload.size());
    if (res <= 0)
    {
        LOG(ERROR) << "Cannot perform encrypt operation 2 (code " << res << ")" << " on " << client_name;
        EVP_PKEY_CTX_free(ctx);
        return false;
    }

    EVP_PKEY_CTX_free(ctx);
    return true;
}

bool Verifier::ValidateReceivedPayload(ClientId client, const std::vector<uint8_t>& received_payload, const VerificationPayload& verification_payload)
{
    const char* name = MF_GetPlayerName(client);

    if (received_payload != verification_payload.payload)
    {
        LOG(ERROR) << "Decrypted payload body mismatch (" << verification_payload.preferred_RSA_key_version << ") on " << name;
        return false;
    }

    return true;
}

int Verifier::ReloadPublicKeys()
{
    FreeAllKeys();

    std::ifstream active_list_file(dirpath_public_keys_ + "active.txt");
    if (!active_list_file.is_open())
    {
        return 0;
    }

    std::string line;
    char buffer[1024];

    while (std::getline(active_list_file, line))
    {
        std::ifstream rsa_key_file(dirpath_public_keys_ + line + ".pem");
        if (!rsa_key_file.is_open())
        {
            continue;
        }

        long long read = 0;
        BIO* bio = BIO_new(BIO_s_mem());
        if (bio == nullptr)
        {
            LOG(ERROR) << "Cannot create BIO for key " << line;
            continue;
        }

        while (rsa_key_file.good())
        {
            read = rsa_key_file.rdbuf()->sgetn(buffer, 1024);
            BIO_write(bio, buffer, (int)read);

            if (read != 1024)
            {
                rsa_key_file.setstate(std::ifstream::eofbit | std::ifstream::failbit);
            }
            else
            {
                rsa_key_file.setstate(std::ifstream::goodbit);
            }
        }

        EVP_PKEY* pkey = PEM_read_bio_PUBKEY(bio, nullptr, nullptr, nullptr);
        BIO_free(bio);

        if (pkey == nullptr)
        {
            LOG(ERROR) << "Cannot read public key from " << line << ".pem";
            continue;
        }

        cached_pkeys_[line] = pkey;
    }

    return (int)cached_pkeys_.size();
}

void Verifier::FreeAllKeys()
{
    for (auto& pair : cached_pkeys_)
    {
        if (pair.second != nullptr)
        {
            EVP_PKEY_free(pair.second);
        }
    }
    cached_pkeys_.clear();
}
