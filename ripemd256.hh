#ifndef RIPEMD256_HH
#define RIPEMD256_HH

#include "_aux.hh"

#include "cryptlib.h"
#include "sha.h"
#include "sha3.h"
#include "ripemd.h"
#include "hex.h"
#include "files.h"
//#include <cryptopp/sha.h> 
#include <iostream>

std::string ripemd_hash_it(std::string msg) {
    using namespace CryptoPP;
//    HexEncoder encoder(new FileSink(std::cout));
    std::string digest;
    RIPEMD256 hash;
    hash.Update((const CryptoPP::byte*)msg.data(), msg.size());
    digest.resize(hash.DigestSize());
    hash.Final((CryptoPP::byte*)&digest[0]);
//    std::cout << "Digest default encoder: "; StringSource(digest, true, new Redirector(encoder));
//    std::cout << std::endl;
    return digest;
}


#endif // RIPEMD256_HH
