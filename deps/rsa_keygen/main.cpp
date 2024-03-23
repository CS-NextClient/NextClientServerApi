#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <iostream>

void main() {
	BIO* bio_out;
	bio_out = BIO_new_file("rsa-key.pem", "w");

	EVP_PKEY* pkey = EVP_RSA_gen(2048);

	PEM_write_bio_PrivateKey(bio_out, pkey, NULL, NULL, 0, 0, NULL);
	BIO_printf(bio_out, "\n");
	PEM_write_bio_PUBKEY(bio_out, pkey);

	BIO_free(bio_out);

	std::cout << "RSA-2048 Public and private keys generated in file rsa-key.pem" << std::endl;
	system("pause");

	/*
	auto enc_ctx = EVP_PKEY_CTX_new(pkey, NULL);
	if (EVP_PKEY_encrypt_init(enc_ctx) <= 0)
		error_and_exit("Failed!", __LINE__);

	size_t outlen;
	unsigned char* out;
	unsigned char* in = (unsigned char*)"Secret message 123!";
	if (EVP_PKEY_encrypt(enc_ctx, NULL, &outlen, in, strlen((char*)in)) <= 0)
		error_and_exit("Failed!", __LINE__);

	out = (unsigned char*)OPENSSL_malloc(outlen);
	if (EVP_PKEY_encrypt(enc_ctx, out, &outlen, in, strlen((char*)in)) <= 0)
		error_and_exit("Failed!", __LINE__);

	// BIO_printf(bio_out, "Encrypted ciphertext (len: %d) is:\n", outlen);
	// BIO_dump(bio_out, (const char*)out, outlen);

	EVP_PKEY_CTX* dec_ctx = EVP_PKEY_CTX_new(pkey, NULL);
	if (EVP_PKEY_decrypt_init(dec_ctx) <= 0)
		error_and_exit("Failed!", __LINE__);

	unsigned char* dout;
	size_t doutlen;
	if (EVP_PKEY_decrypt(dec_ctx, NULL, &doutlen, out, outlen) <= 0)
		error_and_exit("Failed!", __LINE__);

	dout = (unsigned char*)OPENSSL_malloc(doutlen);
	if (EVP_PKEY_decrypt(dec_ctx, dout, &doutlen, out, outlen) <= 0)
		error_and_exit("Failed!", __LINE__);

	BIO_printf(bio_out, "Decrypted Plaintext is:\n");
	BIO_dump(bio_out, (const char*)dout, doutlen);

	BIO_printf(bio_out, "\nPEM Private key:\n");
	PEM_write_bio_PrivateKey(bio_out, pkey, NULL, NULL, 0, 0, NULL);

	BIO_printf(bio_out, "\nPEM Public key:\n");
	PEM_write_bio_PUBKEY(bio_out, pkey);
	*/
}