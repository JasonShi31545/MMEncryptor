#ifndef BACKEND_HH
#define BACKEND_HH

#include "rsa.hh"
#include "aes.hh"
#include "sha256.hh"
#include "ripemd256.hh"
#include "otp.hh"
#include "master_slave_transactions.hh"
#include "base64.hh"


/*
void initNewCommunication() {
    init();
    gen_rsa_k();
}
*/

/*
void master_operation(std::string master_id_name) {
    std::bitset<32 * BYTE_SIZE> aes_key = generate_key();
    std::string id_info = gen_id_info(master_id_name);
    std::string padded_aes_key = pad_inputs(bin_to_str(aes_key));
    std::string padded_id_info = pad_inputs(id_info);
    std::vector<cpp_int> rsa_encrypted_paesk = encrypt_using_private_key_full(padded_aes_key);
    std::vector<cpp_int> rsa_encrypted_idi = encrypt_using_private_key_full(padded_id_info);

}

void slave_operation() {
}

*/
#endif // BACKEND_HH
