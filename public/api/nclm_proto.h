#pragma once

#define clc_ncl_message						3			// clc_stringcmd
#define SVC_NCL_MESSAGE						57			// SVC_SENDCVARVALUE
#define NCLM_HEADER							0x616C636E 	// ncla

#include <stddef.h>

constexpr size_t RSA_KEY_LENGTH =			256;
constexpr size_t NCLM_VERIF_PAYLOAD_SIZE =	196;
constexpr size_t NCLM_VERIF_ENCRYPTED_PAYLOAD_SIZE = ((NCLM_VERIF_PAYLOAD_SIZE / RSA_KEY_LENGTH) + 1) * RSA_KEY_LENGTH;

enum NCLM_C2S {
	/*
		byte		Message header
		string		Prefered RSA public key version
	*/
	VERIFICATION_REQUEST = 0x01,

	/*
		byte		Message header
		string		Client version in SemVer notation 
		196 bytes	Decrypted message payload
	*/
	VERIFICATION_RESPONSE
};

enum NCLM_S2C {
	/*
		byte		Message header
		256 bytes	Encrypted message payload
	*/
	VERIFICATION_PAYLOAD
};