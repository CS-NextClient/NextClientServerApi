#include "Verifier.h"

#include <cctype>

#include <easylogging++.h>
#include <openssl/crypto.h>
#include <openssl/pem.h>
#include <openssl/rand.h>
#include <openssl/rsa.h>
#include <openssl/sha.h>

#include <amxx/api.h>

#include "NclmProtocol.h"
#include "utils/scope_exit.h"

#undef read

namespace
{
    bool IsHwidHex(const std::string& hwid)
    {
        if (hwid.size() != NCLM_HWID_SIZE)
        {
            return false;
        }

        for (const char c : hwid)
        {
            if (!((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f')))
            {
                return false;
            }
        }
        return true;
    }
} // namespace

Verifier::Verifier()
{
    dirpath_public_keys_ = amxx::BuildPathName("%s/nextclient_api/pkeys/", amxx::GetLocalInfo("amxx_datadir", "addons/amxmodx/data"));

    ReloadPublicKeys();
}

Verifier::~Verifier()
{
    FreeAllKeys();
}

bool Verifier::TryCreateVerificationPayload(
    ClientId client,
    const std::string& rsa_key_version,
    VerificationPayload& verification_payload_out
)
{
    const char* client_name = amxx::GetPlayerName(client);

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

    auto ctx_guard = utils::MakeScopeExit([ctx] { EVP_PKEY_CTX_free(ctx); });

    int res = EVP_PKEY_encrypt_init(ctx);
    if (res <= 0)
    {
        LOG(ERROR) << "Cannot initialize encrypt context (code " << res << ") on " << client_name;
        return false;
    }

    res = RAND_bytes(verification_payload_out.payload.data(), verification_payload_out.payload.size());
    if (res <= 0)
    {
        LOG(ERROR) << "Cannot generate random bytes (code " << res << ") on " << client_name;
        return false;
    }

    size_t out_len;
    res = EVP_PKEY_encrypt(ctx, nullptr, &out_len, verification_payload_out.payload.data(), verification_payload_out.payload.size());
    if (res <= 0)
    {
        LOG(ERROR) << "Cannot perform encrypt operation (code " << res << ") on " << client_name;
        return false;
    }

    if (out_len != NCLM_VERIF_ENCRYPTED_PAYLOAD_SIZE)
    {
        LOG(DEBUG) << "'" << rsa_key_version << "' key length does not match (" << out_len << ", but need "
                   << NCLM_VERIF_ENCRYPTED_PAYLOAD_SIZE << ") on " << client_name;
        return false;
    }

    res = EVP_PKEY_encrypt(
        ctx,
        verification_payload_out.encrypted_payload.data(),
        &out_len,
        verification_payload_out.payload.data(),
        verification_payload_out.payload.size()
    );
    if (res <= 0)
    {
        LOG(ERROR) << "Cannot perform encrypt operation 2 (code " << res << ")" << " on " << client_name;
        return false;
    }

    return true;
}

bool Verifier::ValidateReceivedPayload(
    ClientId client,
    const std::vector<uint8_t>& received_payload,
    const VerificationPayload& verification_payload
)
{
    const char* name = amxx::GetPlayerName(client);

    if (received_payload.size() != verification_payload.payload.size() ||
        CRYPTO_memcmp(received_payload.data(), verification_payload.payload.data(), received_payload.size()) != 0)
    {
        LOG(ERROR) << "Decrypted payload body mismatch (" << verification_payload.preferred_RSA_key_version << ") on " << name;
        return false;
    }

    return true;
}

bool Verifier::TryRecoverHwid(
    ClientId client,
    const std::string& rsa_key_version,
    const std::vector<uint8_t>& signature,
    const std::vector<uint8_t>& nonce,
    std::string& hwid_out
)
{
    const char* name = amxx::GetPlayerName(client);

    auto it = cached_pkeys_.find(rsa_key_version);
    if (it == cached_pkeys_.end())
    {
        LOG(ERROR) << "Unknown HWID key version (" << rsa_key_version << ") on " << name;
        return false;
    }

    if (signature.size() != NCLM_HWID_SIGNATURE_SIZE || nonce.empty())
    {
        LOG(WARNING) << "Bad HWID signature/nonce size on " << name;
        return false;
    }

    EVP_PKEY_CTX* ctx = EVP_PKEY_CTX_new(it->second, nullptr);
    if (ctx == nullptr)
    {
        LOG(ERROR) << "Cannot create HWID verify context on " << name;
        return false;
    }

    auto ctx_guard = utils::MakeScopeExit([ctx] { EVP_PKEY_CTX_free(ctx); });

    if (EVP_PKEY_verify_recover_init(ctx) <= 0)
    {
        LOG(ERROR) << "Cannot init HWID verify_recover on " << name;
        return false;
    }

    if (EVP_PKEY_CTX_set_rsa_padding(ctx, RSA_PKCS1_PADDING) <= 0)
    {
        LOG(ERROR) << "Cannot set HWID rsa padding on " << name;
        return false;
    }

    uint8_t recovered[NCLM_HWID_SIGNATURE_SIZE];
    size_t recovered_len = sizeof(recovered);
    if (EVP_PKEY_verify_recover(ctx, recovered, &recovered_len, signature.data(), signature.size()) <= 0)
    {
        LOG(WARNING) << "HWID signature recovery failed on " << name;
        return false;
    }

    if (recovered_len != NCLM_HWID_SIGNED_MESSAGE_SIZE)
    {
        LOG(WARNING) << "HWID recovered length mismatch (" << recovered_len << ") on " << name;
        return false;
    }

    // Verify the nonce binding: recovered[NCLM_HWID_SIZE..] == SHA-256(nonce).
    uint8_t nonce_digest[SHA256_DIGEST_LENGTH];
    SHA256(nonce.data(), nonce.size(), nonce_digest);

    if (CRYPTO_memcmp(recovered + NCLM_HWID_SIZE, nonce_digest, NCLM_HWID_NONCE_BINDING_SIZE) != 0)
    {
        LOG(WARNING) << "HWID nonce binding mismatch on " << name;
        return false;
    }

    std::string hwid(reinterpret_cast<const char*>(recovered), NCLM_HWID_SIZE);
    for (char& c : hwid)
    {
        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
    }

    if (!IsHwidHex(hwid))
    {
        LOG(WARNING) << "Recovered HWID value is not valid hex on " << name;
        return false;
    }

    hwid_out = std::move(hwid);
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
