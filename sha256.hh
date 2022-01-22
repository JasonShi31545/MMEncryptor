#ifndef SHA256_HH
#define SHA256_HH

#include "_aux.hh"

#include "cryptlib.h"
#include "sha.h"
#include "sha3.h"
#include "ripemd.h"
#include "hex.h"
#include "files.h"
#include <cryptopp/sha.h> 
#include <iostream>

std::string sha_hash_it(std::string msg) {
    using namespace CryptoPP;
//    HexEncoder encoder(new FileSink(std::cout));
    std::string digest;
    SHA256 hash;
    hash.Update((const CryptoPP::byte*)msg.data(), msg.size());
    digest.resize(hash.DigestSize());
    hash.Final((CryptoPP::byte*)&digest[0]);
//    std::cout << "Digest default encoder: "; StringSource(digest, true, new Redirector(encoder));
//    std::cout << std::endl;
    return digest;
}
 
std::string sha3_hash_it(std::string msg) {
    using namespace CryptoPP;
//    HexEncoder encoder(new FileSink(std::cout));
    std::string digest;
    SHA3_256 hash;
    hash.Update((const CryptoPP::byte*)msg.data(), msg.size());
    digest.resize(hash.DigestSize());
    hash.Final((CryptoPP::byte*)&digest[0]);
//    std::cout << "Digest default encoder: "; StringSource(digest, true, new Redirector(encoder));
//    std::cout << std::endl;
    return digest;
}

//using namespace std;

/*
#include <openssl/sha.h>

std::string sha256(const std::string str)
{
	char buf[2];
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    std::string NewString = "";
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        sprintf(buf,"%02x",hash[i]);
        NewString = NewString + buf;
    }
	return NewString;
}
*/

/*int main() {
	std::string x = "hello world";
	cout << sha256(x) << endl;
    return 0;
}
*/

#endif // SHA256_HH
