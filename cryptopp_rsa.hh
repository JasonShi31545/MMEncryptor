#ifndef CRYPTOPP_RSA_HH
#define CRYPTOPP_RSA_HH

//#include <cryptopp/rsa.h>
//
#include "rsa.h"
#include "osrng.h"
#include "hex.h"
#include "files.h"
#include "cryptlib.h"
#include <iostream>

//using namespace std;
using namespace CryptoPP;

////////////////////////////////////////////////
// Generate keys
AutoSeededRandomPool rng;
InvertibleRSAFunction params;
//RSA::PrivateKey privateKey(params);
//RSA::PublicKey publicKey(params);
RSA::PrivateKey privateKey;
RSA::PublicKey publicKey;

void rsa_gen_key() {
    params.GenerateRandomWithKeySize(rng, 4096);
    privateKey = RSA::PrivateKey(params);
    publicKey = RSA::PublicKey(params);
}


//std::string plain = "RSA Encryption", cipher, recovered;

std::string encrypt_rsa(std::string plaintext, RSA::PublicKey pkey) {

    std::string cipher;
    RSAES_OAEP_SHA_Encryptor e(pkey);

    StringSource ss1(plaintext, true,
        new PK_EncryptorFilter(rng, e,
            new StringSink(cipher)
       ) // PK_EncryptorFilter
    ); // StringSource

    return cipher;
}

std::string decrypt_rsa(std::string ciphertext, RSA::PrivateKey pkey) {
    std::string plain;

    RSAES_OAEP_SHA_Decryptor d(pkey);

    StringSource ss2(ciphertext, true,
        new PK_DecryptorFilter(rng, d,
            new StringSink(plain)
       ) // PK_DecryptorFilter
    ); // StringSource

    return plain;
}

std::string cp_rsa_export_public_key() {
    std::string result = IntToString(params.GetPublicExponent(), 10) + ":::" + IntToString(params.GetModulus(), 10);
    return result;
}
std::string cp_rsa_export_private_key() {
    std::string result = IntToString(params.GetPrivateExponent(), 10) + ":::" + IntToString(params.GetModulus(), 10);
    return result;
}
#endif // CRYPTOPP_RSA_HH
