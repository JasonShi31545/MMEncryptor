//#include <bits/stdc++.h>
/*
#include "aes.hh"
#include "cryptopp_rsa.hh"
#include "otp.hh"
#include "sha256.hh"
#include "ripemd256.hh"
#include "master_slave_transactions.hh"
*/
//#include "_aux.hh"

#include "backend.hh"

/*
using namespace boost::multiprecision;
using namespace boost::random;
using namespace boost::math;

cpp_int fastExp4(cpp_int base, cpp_int exp, cpp_int mod) {
   cpp_int res = 1;
   while (exp > 0) {
      if (exp % 2 == 1)
         res= (res * base) % mod;
      exp = exp >> 1;
      base = (base * base) % mod;
   }
   return res;
}

int main(void) {

    clock_t cstart = clock();
    std::cout << fastExp4(12304, 13443, 342) << std::endl;
    clock_t cend = clock();
    printf("Time: %lf\n", (double)(cend - cstart));

    return 0;
}
*/

/*
void testb64(std::string data) {
    cout << endl;
    cout << "Raw data size: " << data.size() << endl;
    std::string base64data = B64::encode64(data);
    cout << "Base64 data size: " << base64data.size() << endl;
    cout << base64data << endl;
    std::string decoded64data = B64::decode64(base64data);
    cout << decoded64data << endl;
    cout << data << endl;
    cout << decoded64data.size() << endl;
    cout << data.size() << endl;
    cout << endl;
}
*/

int main(void) {


//   std::cerr << "p: " << _p << std::endl;
//   std::cerr << "q: " << q << std::endl;
//   std::cerr << "n: " << n << std::endl;
//   std::cerr << "phi: " << phi << std::endl;
//   std::cerr << "d: " << d << std::endl;
//   std::cerr << "e: " << e_ << std::endl;

//    e_ = 5;
//    n = 989;
//    d = 185;

    /*
    gen_rsa_k();

    std::cerr << std::endl << std::endl << std::endl;

    std::cerr << encrypt('C') << std::endl;
    std::cerr << encrypt('S') << std::endl;
    std::cerr << encrypt('5') << std::endl;
    std::cerr << encrypt('0') << std::endl;

    std::cerr << (char)decrypt(encrypt('C')) << std::endl;
    std::cerr << (char)decrypt(encrypt('S')) << std::endl;
    std::cerr << (char)decrypt(encrypt('5')) << std::endl;
    std::cerr << (char)decrypt(encrypt('0')) << std::endl;

    std::cerr << std::endl << std::endl << std::endl;

    std::cerr << encrypt_up('C') << std::endl;
    std::cerr << encrypt_up('S') << std::endl;
    std::cerr << encrypt_up('5') << std::endl;
    std::cerr << encrypt_up('0') << std::endl;

    std::cerr << decrypt_up(encrypt_up('C')) << std::endl;
    std::cerr << decrypt_up(encrypt_up('S')) << std::endl;
    std::cerr << decrypt_up(encrypt_up('5')) << std::endl;
    std::cerr << decrypt_up(encrypt_up('0')) << std::endl;

    std::cerr << std::endl << std::endl << std::endl;

    std::cerr << encrypt_op('C', 5, 989) << std::endl;
    std::cerr << encrypt_op('S', 5, 989) << std::endl;
    std::cerr << encrypt_op('5', 5, 989) << std::endl;
    std::cerr << encrypt_op('0', 5, 989) << std::endl;

    std::cerr << (char)decrypt_op_up(encrypt_op('C', 5, 989), 185, 989) << std::endl;
    std::cerr << (char)decrypt_op_up(encrypt_op('S', 5, 989), 185, 989) << std::endl;
    std::cerr << (char)decrypt_op_up(encrypt_op('5', 5, 989), 185, 989) << std::endl;
    std::cerr << (char)decrypt_op_up(encrypt_op('0', 5, 989), 185, 989) << std::endl;

    */

    /*

    gen_rsa_k();
    cerr << "Gen-ed!" << endl;

    init();
    string aesk = "ABCDEFGHIJKLMNOPQRSTUVWXYZABCDEF";
    assert(aesk.size() == 32);
    string expaesk = expand_key(str_to_bin(aesk));

//    bitset<32 * BYTE_SIZE> aesk = generate_key();
//    string saesk = bin_to_str(aesk);

//    string content = "AROUSE OUT FROM THE AZURE MAIN!";
    string content = "1234567890123456789009876543210987654321THISISLAST";
    assert(content.size() == 50);

    string otpk = "12345678901234567890123456789012";
    assert(otpk.size() == 32);

    string aes_encrypted = encrypt_full(process_state(content), expaesk);
    string aes_decrypted = decrypt_full(process_state(aes_encrypted), expaesk);

    cerr << aes_decrypted << endl;
    cerr << aes_decrypted.size() << endl;

    string expotpk = otp_key_expansion(otpk, aes_encrypted.size());

    string encrypted_final = encrypt_otp(aes_encrypted, expotpk);


    // Decrypt
    
    std::vector<cpp_int> ciaesk;
    for (int i = 0; i < aesk.size(); i++) {
        cerr << "A: " << (int)aesk[i] << endl;
        ciaesk.push_back((cpp_int)((int)aesk[i]));
    }
    std::vector<cpp_int> ciotpk;
    for (int i = 0; i < otpk.size(); i++) {
        cerr << "B: " << (int)otpk[i] << endl;
        ciotpk.push_back((cpp_int)((int)otpk[i]));
    }

#define svc std::vector<cpp_int>
    // we only have aesk, otpk, and encrypted_final
    svc enaesk = encrypt_full(ciaesk);
    svc deaesk = decrypt_full(enaesk);
    svc enotpk = encrypt_full(ciotpk);
    svc deotpk = decrypt_full(enotpk);

    string pdeaesk, pdeotpk;
    for (int i = 0; i < deaesk.size(); i++) {
        cerr << "A2: " << deaesk[i] << endl;
        pdeaesk.push_back((char)((int)deaesk[i]));
    }
    for (int i = 0; i < deotpk.size(); i++) {
        cerr << "B2: " << deotpk[i] << endl;
        pdeotpk.push_back((char)((int)deotpk[i]));
    }

    assert(pdeaesk == aesk);
    assert(pdeotpk == otpk);

    string expand_otp_key = otp_key_expansion(pdeotpk, encrypted_final.size());
    string stage1 = decrypt_otp(encrypted_final, expand_otp_key);
    string expanded_key = expand_key(str_to_bin(pdeaesk));
    string stage2 = decrypt_full(stage1, expanded_key);


    cerr << "content: " << content << endl;
    cerr << "stage2 : " << stage2 << endl;

    */


        // cout << int_to_bin((int)'A') << endl;

        /*
    std::string data1 = "AAAAAAAAAAAAAAAA";
    std::string data2 = "Arouseoutfromthe Azure main arouse arouse out from the azure main";
    std::string data3 = "asdf}{P{qerlqkjas,dmfnzQdrqeroiu234";
    std::string data4 = "Happy Birthday To sfASDfad|}{ Happy Birthday to asdfkaljsdf";
    std::string data5 = "TestTestTest";


    testb64(data1);
    testb64(data2);
    testb64(data3);
    testb64(data4);
    testb64(data5);
    */

    return 0;
}

