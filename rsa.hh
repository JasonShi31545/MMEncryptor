#ifndef RSA_HH
#define RSA_HH
#include "rsa_gen_keys.hh"
#include "fast_modular_exp.hh"
//using namespace std;


//    c = Pt ^ e mod n; // Encrypt
//    Pt = c ^ d mod n; // Decrypt

// REMEMBER TO PAD THE CHUNKS

using namespace boost::multiprecision;
using namespace boost::random;
using namespace boost::math;

// pad plaintext to create sophisticated RSA encrypted string against attacks
// Do not need multiplication optimization, too complicated and hard

std::string pad_inputs(std::string input) {
    assert(input.size() == 32);
    // 50 - 32 = 18
    const std::vector<int> indices = {0, 4, 26, 3, 7, 17, 13, 19, 8, 28, 25, 24, 29, 30, 20, 12, 16, 26};
    const std::vector<unsigned char> data = {0xab, 0x3a, 0xb4, 0x26, 0x11, 0x05, 0xf2, 0xf6, 0xfa, 0x10, 0xb4, 0xc1, 0xac, 0x89, 0x72, 0x6b, 0x7a, 0x33};
    assert(indices.size() == 18 && data.size() == 18);
    for (int i = 0; i < 18; i++) {
        input.insert(input.begin() + indices[i], data[i]);
    }
    assert(input.size() == 50);
    return input;
}

std::string depad_inputs(std::string input) {
    assert(input.size() == 50);
    const std::vector<int> indices = {26,16,12,20,30,29,24,25,28,8,19,13,17,7,3,26,4,0};
    assert(indices.size() == 18);
    for (int i = 0; i < 18; i++) {
        input.erase(input.begin() + indices[i]);
    }
    assert(input.size() == 32);
    return input;
}

cpp_int exp_custom(cpp_int base, cpp_int exponent) {
    assert(base > 0);
    assert(exponent > 0);
    cpp_int result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

cpp_int encrypt(cpp_int plaintext) {
//    cpp_int pt = (cpp_int)((int)plaintext);
    // public key (e, n)
    // e_ and n
//    cpp_int c = (exp_custom(pt, e_)) % n;
    cpp_int c = fmexp(plaintext, e_, n);
//    std::cerr << "E";
    return c;
}

cpp_int decrypt(cpp_int ciphertext) {
    // private key (d, n)
    // d and n
//    cpp_int m = (exp_custom(ciphertext, d)) % n;
    cpp_int m = fmexp(ciphertext, d, n);
//    std::cerr << "D";
    return m;
}

std::vector<cpp_int> encrypt_full(std::vector<cpp_int> pt) {
//    std::cerr << "Encrypt" << std::endl;
    std::vector<cpp_int> result(pt.size());
//    std::cerr << "Alloc result" << std::endl;
    for (int i = 0; i < (int)pt.size(); i++) {
        result[i] = encrypt(pt[i]);
//        std::cerr << "Allocated cpp_int" << std::endl;
    }
    return result;
}
std::vector<cpp_int> decrypt_full(std::vector<cpp_int> ct) {
//    std::cerr << "Decrypt" << std::endl;
    std::vector<cpp_int> decrypted;
    decrypted.resize(ct.size());
//    std::cerr << "Alloc result" << std::endl;
    for (int i = 0; i < (int)ct.size(); i++) {
        decrypted[i] = decrypt(ct[i]);
//        std::cerr << "Allocated char" << std::endl;
    }
    return decrypted;
}
// ID identification

cpp_int encrypt_up(unsigned char pt) {
    cpp_int pt_ = (cpp_int)((int)pt);
    cpp_int c = fmexp(pt_, d, n);
    return c;
}

unsigned char decrypt_up(cpp_int ct) {
    cpp_int m = fmexp(ct, e_, n);
    return (unsigned char)m;
}

std::vector<cpp_int> encrypt_using_private_key_full(std::string pt) { 
    std::vector<cpp_int> result(pt.size());
    for (int i = 0; i < (int)pt.size(); i++) {
        result[i] = encrypt_up(pt[i]);
    }
    return result;
}
std::string decrypt_using_public_key_full(std::vector<cpp_int> ct) { 
    std::string decrypted;
    decrypted.resize(ct.size());
    for (int i = 0; i < (int)ct.size(); i++) {
        decrypted[i] = decrypt_up(ct[i]);
    }
    return decrypted;
}


// implement encrypt with other people's public key
// implement decrypt with other people's public key
//
cpp_int encrypt_op(cpp_int plaintext, cpp_int op_e, cpp_int op_n) {
    cpp_int c = fmexp(plaintext, op_e, op_n);
    return c;
}

cpp_int decrypt_op_up(cpp_int ciphertext, cpp_int op_e, cpp_int op_n) {
    cpp_int m = fmexp(ciphertext, op_e, op_n);
    return m;
}

std::vector<cpp_int> encrypt_with_other_people_s_public_key_full(std::vector<cpp_int> pt, cpp_int op_e, cpp_int op_n) {
    // op_e, public key e from another person
    // op_n, public key n from another person
    std::vector<cpp_int> result(pt.size());
    for (int i = 0; i < (int)pt.size(); i++) {
        result[i] = encrypt_op(pt[i], op_e, op_n);
    }
    return result;
}
std::vector<cpp_int> decrypt_with_other_people_s_public_key_full(std::vector<cpp_int> ct, cpp_int op_e, cpp_int op_n) {
    std::vector<cpp_int> decrypted;
    decrypted.resize(ct.size());
//    std::cerr << "A1" << std::endl;
    for (int i = 0; i < (int)ct.size(); i++) {
//        std::cerr << "A2, i: " << i << std::endl;
        decrypted[i] = decrypt_op_up(ct[i], op_e, op_n);
    }
    return decrypted;
}

/*
// EXPORT FUNCTIONS

std::string export_public_key() {
    std::string result = (string)e_ + ":::" + (string)n;
}
std::string export_private_key() {
    std::string result = (string)d + ":::" + (string)n;
    return result;
}
*/

#endif // RSA_HH
