#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <openssl/pem.h>
#include "module_types.h"

struct VerificationPayload
{
    std::string preferred_RSA_key_version{};
    std::vector<uint8_t> payload{};
    std::vector<uint8_t> encrypted_payload{};
};

class Verifier
{
    std::string dirpath_public_keys_{};
    std::unordered_map<std::string, EVP_PKEY*> cached_pkeys_{};

public:
    explicit Verifier();
    ~Verifier();

    bool TryCreateVerificationPayload(ClientId client, const std::string& rsa_key_version, VerificationPayload& verification_payload_out);
    bool ValidateReceivedPayload(ClientId client, const std::vector<uint8_t>& received_payload, const VerificationPayload& verification_payload);

    int ReloadPublicKeys();

private:
    void FreeAllKeys();
};
