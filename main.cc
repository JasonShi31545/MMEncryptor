#include "backend.hh"

#include <errno.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

#include "main.hh"
/* The Front-end of my program */

/*
void parse_file(string &res, FILE *f_for_file, bool check_for_comma = true, bool b64decode = true) {
    // assert(res.empty() == true);
    // string tmpbuffer = "";
    
    // unsigned char char_input = 0;
    // while (true) {
    //     char_input = (unsigned char)fgetc(f_for_file);
    //     assert((int)char_input <= 255 && (int)char_input >= 0);
    //     if (char_input == (unsigned char)EOF) {
    //         break;
    //     }
    //     if (check_for_comma && char_input == (unsigned char)',') {
    //         break;
    //     }
    //     tmpbuffer.push_back((char)char_input);
    // }
    // if (b64decode) {
    //     res = B64::decode64(tmpbuffer);
    // } else {
    //     res = tmpbuffer;
    // }
    assert(res.empty() == true);
    string tmpbuffer = "";
    tmpbuffer = readAllFromFile(f_for_file);
    if (b64decode == true) {
        tmpbuffer = B64::decode64(tmpbuffer);
    }
    std::string result = "";
    if (check_for_comma) {
        int i = 0;
        while (i < tmpbuffer.size()) {
            if (tmpbuffer[i] != ',') {
                result.push_back(tmpbuffer[i]);
            } else {
                break;
            }
            i++;
        }
    } else { result = tmpbuffer; }
    res = result;
}
*/


// void parse_file_boss(string &res, FILE *fff /* f for file */) { // parse file based on string size
//     assert(res.empty() == true);
//     string tmpbuffer = "";
//     unsigned char char_input = 0;
//     unsigned long i = 0;
// //    const int size = (int)res.size();
//     fseek(fff, 0, SEEK_END);
//     unsigned long size = (unsigned long)ftell(fff);
//     fseek(fff, 0, SEEK_SET);
//     assert(size % 16 == 0); // assert that the size of the content in slave_vault.sto is divisible by 16
//     while (i < size) {
//         char_input = (unsigned char)fgetc(fff);
//         assert((int)char_input <= 255 && (int)char_input >= 0);
//         /*
//         if (char_input == (unsigned char)EOF) {
//             break;
//         }
//         */
//         tmpbuffer.push_back((char)char_input);
//         i++;
//     }
//     fseek(fff, 0, SEEK_SET);
//     res = B64::decode64(tmpbuffer);
// }


/*
WTF is this???
void exact_fputs(const string fcontent, FILE *f) {
    for (int i = 0; i < (int)fcontent.size(); i++) {
        fputc(content[i], f);
    }
}
*/

namespace PASSWORD_INPUT {
int getch() {
    int ch;
    struct termios t_old, t_new;

    tcgetattr(STDIN_FILENO, &t_old);
    t_new = t_old;
    t_new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t_new);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
    return ch;
}

string getpass(bool show_asterisk=true) {

    const char BACKSPACE=127;
    const char RETURN=10;

    string password;
    long long i = -1;
    while (true) {
        char a = getch();
        i++;
        if (i >= 1) {
            if (a == RETURN) {
                break;
            }
            if (a == BACKSPACE) {
                if (password.length() != 0) {
                    if (show_asterisk) {
                        cout << "\b \b";
                        password.resize(password.length() - 1);
                    }
                }
            } else {
                password += a;
                if (show_asterisk) {
                    cout << '*';
                }
            }
        }
    }
    return password;
}

string getpass2(bool show_asterisk=true) {

    const char BACKSPACE=127;
    const char RETURN=10;

    string password;
    while (true) {
        char a = getch();
        if (a == RETURN) {
            break;
        }
        if (a == BACKSPACE) {
            if (password.length() != 0) {
                if (show_asterisk) {
                    cout << "\b \b";
                    password.resize(password.length() - 1);
                }
            }
        } else {
            password += a;
            if (show_asterisk) {
                cout << '*';
            }
        }
    }
    return password;
}

};


//extern int errno;

int main(int argc, const char *argv[]) {

    int errnum;

    if (argc < 2) {
        std::cout << "Unknown Command; Consider using -h" << std::endl;
        return 1;
    }
    if ((string)argv[1] == "-h") {
        std::cout << "Help Menu MMEncryptor" << std::endl << std::endl;
        std::cout << "-h: Help menu" << std::endl;
        std::cout << "-c: Create New Communication as Master to create pub.sto, vault.sto, pass.sto, and comm.sto" << std::endl;
        std::cout << "-p: Continue to establish communication through external slave public key in file opub.key" << std::endl;
        std::cout << "-a: Digest AES key and info from mme_aesk.ekey (for slave purposes), with master's pub-key in master_pub.key" << std::endl;
        std::cout << "-k: Generate RSA key pairs (for slave purposes) slave_pub.sto, slave_vault.sto, slave_pass.sto" << std::endl;
        std::cout << "-o: Generate opub.key from slave_pub.sto" << std::endl;
        std::cout << "-m: Generate mme_aesk.ekey from comm.sto" << std::endl;
        std::cout << "-b: Generate master_pub.key from pub.sto" << std::endl;
        std::cout << "-x: Show generated keys in console (not recommended) output pub.sto" << std::endl;
        std::cout << "-e: Encrypt message provided by a file: [FILE]" << std::endl;
        std::cout << "-d: Decrypt message provided by a file: [FILE]" << std::endl;
        std::cout << "-i: Info about the current communication based on the directory" << std::endl;
        std::cout << std::endl << std::endl;
        cout << "Copyright (C) Jason Shi 2021-2022" << endl;
        cout << "Licensed under GNU GPL v3" << endl;
        cout << "Multimedia Encryptor" << endl << endl;
        return 0;
    }

    if (((string)argv[1]).size() < 2) {
        cout << "Unknown Command; Consider using -h" << endl;
        return 2;
    }

    int option = (int)argv[1][1];
    init();
    switch (option) {
        case ((int)'c'): {
            cout << "Creating New Communication as Master" << endl << endl;
            string mid_name;
            do {
                cout << "Enter your preferred username (must be 10 characters long): ";
                cin >> mid_name;
            } while (mid_name.size() != 10);

            cout << "Generating RSA keys" << endl;

            gen_rsa_k();

            const string master_id_info = gen_id_info(mid_name);
            amIMaster = true;

//            cerr << "Master ID: " << master_id_info << endl;

            bitset<32 * BYTE_SIZE> aes_key = generate_key();
            string str_aes_key = bin_to_str(aes_key);

//            cerr << "AES key: " << B64::encode64(str_aes_key) << endl;

            string padded_aes_key = pad_inputs(str_aes_key);
            string padded_id_info = pad_inputs(master_id_info);
            
            std::vector<cpp_int> rsa_encrypted_paesk = encrypt_using_private_key_full(padded_aes_key);
            std::vector<cpp_int> rsa_encrypted_idi = encrypt_using_private_key_full(padded_id_info);

            FILE *comm_sto_f;
            comm_sto_f = fopen("comm.sto", "w+");
            if (comm_sto_f == nullptr) {
                errnum = errno;
                perror("Failed to create files");
                fprintf(stderr, "Failed to create files: %s\n", strerror(errnum));
                return errnum;
            }

            string encrypted_info = export_encrypted_message(rsa_encrypted_paesk) + ";;;" + export_encrypted_message(rsa_encrypted_idi);

            fputs(B64::encode64(encrypted_info).c_str(),comm_sto_f);

            FILE *pub_sto_f;
            FILE *vault_sto_f;
            FILE *pass_sto_f;
            pub_sto_f = fopen("pub.sto", "w+");
            vault_sto_f = fopen("vault.sto", "w+");
            pass_sto_f = fopen("pass.sto", "w+");
            if (pub_sto_f == nullptr || vault_sto_f == nullptr || pass_sto_f == nullptr) {
                errnum = errno;
                perror("Failed to create files");
                fprintf(stderr, "Failed to create files: %s\n", strerror(errnum));
                return errnum;
            }

            // Password
            string input1;
            string input2;
            while (true) {
                while (input1.size() < 8) {
                    cout << "Setup a password: ";
                    input1 = PASSWORD_INPUT::getpass();
                    cout << endl;
                    cout << "Confirm password: ";
                    input2 = PASSWORD_INPUT::getpass2();
                    cout << endl;
                    if (input1 != input2) {
                        errnum = errno;
                        fprintf(stderr, "Password Confirmation failed\n");
                        fprintf(stderr, "Try again\n");
                    } else {
                        goto SUCCESS_PW;
                    }
                }
            }

SUCCESS_PW:

            // Success for inputting password
            string password = input1;
            string secure_pw_hashed = sha_hash_it(ripemd_hash_it(password));
            fputs(B64::encode64(secure_pw_hashed).c_str(), pass_sto_f);

            string secret = export_private_key() + ";;;" + str_aes_key;

            string secret_aes_key = sha_hash_it(sha3_hash_it(password));
            bitset<32 * BYTE_SIZE> secret_aes_key_bin = str_to_bin(secret_aes_key);
            string expanded_secret_aes_key = expand_key(secret_aes_key_bin);

            string encrypted_secret_content = encrypt_full(process_state(secret), expanded_secret_aes_key);

            string secret_otp_key = sha_hash_it(password);
            string expanded_secret_otp_key = otp_key_expansion(secret_otp_key, encrypted_secret_content.size());
            string encrypted_vault_content = encrypt_otp(encrypted_secret_content, expanded_secret_otp_key);

            fputs(B64::encode64(encrypted_vault_content).c_str(), vault_sto_f);

            fputs(export_public_key().c_str(), pub_sto_f);

            // Close files
            fclose(comm_sto_f);
            fclose(pub_sto_f);
            fclose(vault_sto_f);
            fclose(pass_sto_f);

            break;
        }
        case ((int)'p'): {
            
            // This 'p' operation is exclusively for masters
            // Remember, there is no e, d, p, q, n in memory, thus master's keys has to be interpreted from the files
            
            // Ask for password

            string input1;
            while (input1.size() < 8) {
                cout << "Enter your vault password: ";
                input1 = PASSWORD_INPUT::getpass2();
                cout << endl;
                cout << endl;
            }
            string hashed = sha_hash_it(ripemd_hash_it(input1));

            // read from pass.sto

            FILE *pass_file = fopen("pass.sto", "r");
            if (pass_file == nullptr) {
                cerr << "Error: Password file does not exist!" << endl;
                return 5;
            }
            string supposed_hash;
            // parse_file(supposed_hash, pass_file, false);
            supposed_hash = B64::decode64(readAllFromFile(pass_file));
            if (supposed_hash == hashed) {
                cerr << "Verification Successful!" << endl;
            } else {
                cerr << "Verification Failed!" << endl;
                return 6;
            }
            fclose(pass_file);


            // Verification passed

            FILE *opub_f; // This is the slave public key, not the master's
            opub_f = fopen("opub.key", "r");
            if (opub_f == nullptr) {
                errnum = errno;
                perror("Failed to open file");
                fprintf(stderr, "My disappointment is immeasurable, and my day is ruined");
                return errnum;
            }

            string e_in_str, n_in_str;

            pair<string, string> public_key_pair = splitAtComma(readAllFromFile(opub_f));
            // parse_file(e_in_str, opub_f);
            e_in_str = public_key_pair.first;
            // parse_file(n_in_str, opub_f);
            n_in_str = public_key_pair.second;
            
            
//            e_in_str = clean_up_string(e_in_str);
//            n_in_str = clean_up_string(n_in_str);

            cpp_int public_key_e = boost::lexical_cast<cpp_int>(e_in_str);
            cpp_int public_key_n = boost::lexical_cast<cpp_int>(n_in_str);

            FILE *comm_sto_f = fopen("comm.sto", "rw+");
            if (comm_sto_f == nullptr) {
                errnum = errno;
                perror("Failed to open file");
                fprintf(stderr, "My disappointment is immeasurable, and my day is ruined");
                return errnum;
            }
            string comm_file_content;

            // parse_file(comm_file_content, comm_sto_f, false);
            comm_file_content = B64::decode64(readAllFromFile(comm_sto_f));
//            comm_file_content = clean_up_string(comm_file_content);
            
            string encrypted_aes_key, encrypted_infos;
            int split_index = -1;
            for (int i = 0; i < (int)(comm_file_content.size() - 3); i++) {
                if (comm_file_content.substr(i, 3) == ";;;") {
                    split_index = i+1+1+1;
                    break;
                } else {
                    encrypted_aes_key.push_back((unsigned char)comm_file_content[i]);
                }
            }
            for (int i = split_index; i < (int)(comm_file_content.size()); i++) {
                encrypted_infos.push_back((unsigned char)comm_file_content[i]);
            }

            std::vector<cpp_int> processed_encrypted_aes_k = parse_received_message(encrypted_aes_key);
            std::vector<cpp_int> processed_encrypted_infos = parse_received_message(encrypted_infos);

            std::vector<cpp_int> final_encrypted_aes_key = encrypt_with_other_people_s_public_key_full(processed_encrypted_aes_k,public_key_e,public_key_n);
            std::vector<cpp_int> final_encrypted_infos = encrypt_with_other_people_s_public_key_full(processed_encrypted_infos,public_key_e,public_key_n);

            string feak_str = export_encrypted_message(final_encrypted_aes_key);
            string fei_str = export_encrypted_message(final_encrypted_infos);

            string sum = feak_str + ";;;" + fei_str;

//            sum = clean_up_string(sum); // clean up all those \0s

            fclose(fopen("comm.sto", "w")); // clears the content of the existing comm.sto
            fputs(B64::encode64(sum).c_str(), comm_sto_f);
            fclose(comm_sto_f);

            break;
        }
        case ((int)'a'): {
            // Start having fun!
            string input1;
            while (input1.size() < 8) {
                cout << "Enter your vault password: ";
                input1 = PASSWORD_INPUT::getpass2();
                cout << endl;
                cout << endl;
            }
            string hashed = sha_hash_it(ripemd_hash_it(input1));
            
            FILE *pass_file = fopen("slave_pass.sto", "r");
            if (pass_file == nullptr) {
                cerr << "Error: Password file does not exist!" << endl;
                return 5;
            }
            
            string supposed_hashed_passwd;
            // parse_file(supposed_hashed_passwd, pass_file, false);
            supposed_hashed_passwd = B64::decode64(readAllFromFile(pass_file));
            
            if (supposed_hashed_passwd == hashed) {
                cerr << "Verification Successful!" << endl;
            } else {
                cerr << "Verification Failed!" << endl;
                return 6;
            }

            // Finished with user verification

            string expected_master_name;
            cout << "Enter expected master username: ";
            cin >> expected_master_name;

            // Finished asking for expected master username input

            // Start business...
            
            // Read files
            FILE *ekey = fopen("mme_aesk.ekey", "r");
            FILE *master_pubkey = fopen("master_pub.key", "r");
            if (ekey == nullptr || master_pubkey == nullptr) {
                errnum = errno;
                cerr << "The required files do not exist!" << endl;
                return errnum;
            }

            // Interpret master public key from master_pub.key
            string master_e, master_n;
            // parse_file(master_e, master_pubkey);
            pair<string, string> master_public_key_pair = splitAtComma(readAllFromFile(master_pubkey));
            master_e = master_public_key_pair.first;
            // parse_file(master_n, master_pubkey);
            master_n = master_public_key_pair.second;
            
            // master_e = clean_up_string(master_e);
            // master_n = clean_up_string(master_n);

            cpp_int master_key_e = boost::lexical_cast<cpp_int>(master_e);
            cpp_int master_key_n = boost::lexical_cast<cpp_int>(master_n);

            // Parse the received communication message mme_aesk.ekey
            string pure_content;
            // parse_file(pure_content, ekey, false);
            pure_content = B64::decode64(readAllFromFile(ekey));
            // pure_content = clean_up_string(pure_content);

            std::vector<cpp_int> encrypted_aes_key, encrypted_id_info;
            string aesContent, idInfoContent;
            int split_index = -1;
            for (int i = 0; i < (int)pure_content.size() - 3; i++) {
                if (pure_content.substr(i, 3) == ";;;") {
                    split_index = i;
                    break;
                } else {
                    aesContent.push_back(pure_content[i]);
                }
            }
            for (int i = split_index+3; i < (int)pure_content.size(); i++) {
                idInfoContent.push_back(pure_content[i]);
            }


//            cerr << "Pure content size: " << pure_content.size() << endl;
//            cerr << "AES content size: " << aesContent.size() << endl;
//            cerr << "ID INFO content size: " << idInfoContent.size() << endl;

            
//            cerr << "1" << endl;
            encrypted_aes_key = parse_received_message(aesContent);
//            cerr << "2" << endl;
            encrypted_id_info = parse_received_message(idInfoContent);

//            cerr << "ENCRYPTED AES KEY size: " << encrypted_aes_key.size() << endl;
//            cerr << "ENCRYPTED ID INFO size: " << encrypted_id_info.size() << endl;

            // Parse operation is completed

            // Read slave_vault.sto to get the private keys

            FILE *sv = fopen("slave_vault.sto", "r");
            string encrypted_vault_content;
            // parse_file(encrypted_vault_content, sv, false);
            //            parse_file_boss(encrypted_vault_content, sv);
            encrypted_vault_content = B64::decode64(readAllFromFile(sv));

//            cerr << "encrypted vault content size: " << encrypted_vault_content.size() << endl;
            
//            cerr << "Uno" << endl;
            // plaintext password is input1

            string aes_key = sha_hash_it(sha3_hash_it(input1));
            bitset<32 * BYTE_SIZE> akbin = str_to_bin(aes_key);
            string exp_ak = expand_key(akbin); // expanded aes key

//            cerr << "Dos" << endl;
            
            string otp_key = sha_hash_it(input1);
            string expanded_otpk = otp_key_expansion(otp_key, encrypted_vault_content.size()); // expanded otp key

//            cerr << "Tres" << endl;
            
            string stage1 = decrypt_otp(encrypted_vault_content, expanded_otpk);

//            cerr << "Tres y medio" << endl;

//            cerr << "Stage 1 size: " << stage1.size() << endl;

            string stage2 = unprocess_state(decrypt_full(stage1, exp_ak));
//            cerr << "cuadro" << endl;
//
            string private_keys = "";
            for (int i = 0; i < (int)stage2.size() - 3; i++) {
                if (stage2.substr(i, 3) == ";;;") {
                    break;
                } else {
                    private_keys.push_back(stage2[i]);
                }
            }

            assert(private_keys.size() == stage2.size() - 3);

//            cerr << "cinco" << endl;

            string kd, kn;
            int break_id = -404;
            for (int i = 0; i < (int)private_keys.size(); i++) {
                if (private_keys[i] == ',') {
                    break_id = i+1;
                    break;
                } else {
                    kd.push_back(private_keys[i]);
                }
            }
            for (int i = break_id; i < (int)private_keys.size(); i++) {
                kn.push_back(private_keys[i]);
            }


//    	    cerr << "Pure KD: " << kd << endl;
//            cerr << "Pure KN: " << kn << endl;

//            cerr << "seis" << endl;

//            kd = clean_up_string(kd);
//            kn = clean_up_string(kn);

//            cerr << "KD: " << kd << endl;
//            cerr << "KN: " << kn << endl;

//            cerr << "siete" << endl;

            cpp_int slave_d = boost::lexical_cast<cpp_int>(kd);
            cpp_int slave_n = boost::lexical_cast<cpp_int>(kn);

//            cerr << "ocho" << endl;

            d = slave_d;
            n = slave_n;

//            cerr << d << "-------------" << n << endl << endl;

            std::vector<cpp_int> decrypt_stage1_ak = decrypt_full(encrypted_aes_key);
            std::vector<cpp_int> decrypt_stage1_ii = decrypt_full(encrypted_id_info);

//            cerr << "Size of decrypt_stage1_ak: " << decrypt_stage1_ak.size() << endl;
//            cerr << "Size of decrypt_stage1_ii: " << decrypt_stage1_ii.size() << endl;

            // Unsign

            
            std::vector<cpp_int> unsigned_stage2_ak = decrypt_with_other_people_s_public_key_full(decrypt_stage1_ak, master_key_e, master_key_n);
            std::vector<cpp_int> unsigned_stage2_ii = decrypt_with_other_people_s_public_key_full(decrypt_stage1_ii, master_key_e, master_key_n);

//            cerr << "Size of unsigned_stage2_ak: " << unsigned_stage2_ak.size() << endl;
//            cerr << "Size of unsigned_stage2_ii: " << unsigned_stage2_ii.size() << endl;

            string aes_key_final = "";
            string master_info_final = "";

//            cerr << "nueve" << endl;

            for (int i = 0; i < (int)unsigned_stage2_ak.size(); i++) {
//                assert(unsigned_stage2_ak[i] >= 0 && unsigned_stage2_ak[i] < 256);
                aes_key_final.push_back((unsigned char)unsigned_stage2_ak[i]);
            }
//            cerr << "Uno" << endl;
            for (int i = 0; i < (int)unsigned_stage2_ii.size(); i++) {
//                assert(unsigned_stage2_ii[i] >= 0 && unsigned_stage2_ii[i] < 256);
                master_info_final.push_back((unsigned char)unsigned_stage2_ii[i]);
            }

//            cerr << "AES Key Final: " << aes_key_final << endl;
//            cerr << "Master Info Final: " << master_info_final << endl;

//            cerr << "Dos" << endl;

//            cerr << aes_key_final.size() << endl;
//            cerr << master_info_final.size() << endl;

//            cerr << "Tres" << endl;

            aes_key_final = depad_inputs(aes_key_final);
            master_info_final = depad_inputs(master_info_final);

//            cerr << "cuadro" << endl;

            assert(aes_key_final.size() == 32);
            assert(master_info_final.size() == 32);

//            cerr << "cinco" << endl;

            FILE *important_key_f = fopen("AES_KEY_important.key", "w+");
            fputs(B64::encode64(aes_key_final).c_str(), important_key_f);

//            cerr << "diez" << endl;

            // Verify master info
            //
            cout << "Master Info: " << master_info_final << endl;

            string check_master_str = "MMEV XXXXXXXHN: " + expected_master_name + " ++END";
            cout << ((check_master_str == master_info_final) ? "MASTER VERIFIED" : "MASTER INFO INCONSISTENT") << endl;


            fclose(important_key_f);
            fclose(sv);
            fclose(pass_file);
            fclose(ekey);
            fclose(master_pubkey);
            break;
        }
        case ((int)'k'): {
            cout << "Creating New RSA keys as Slave" << endl << endl;

            gen_rsa_k();

            FILE *vault_sto_f = fopen("slave_vault.sto", "w+");
            FILE *pass_sto_f = fopen("slave_pass.sto", "w+");
            FILE *pub_sto_f = fopen("slave_pub.sto", "w+");
            if (vault_sto_f == nullptr || pass_sto_f == nullptr || pub_sto_f == nullptr) {
                errnum = errno;
                perror("Failed to create files");
                fprintf(stderr, "Failed to create files: %s\n", strerror(errnum));
                return errnum;
            }
            // Password Setup
            
            string input1;
            string input2;
            while (input1.size() < 8) {
                cout << "Setup a password: ";
                input1 = PASSWORD_INPUT::getpass2();
                cout << endl;
                cout << "Confirm password: ";
                input2 = PASSWORD_INPUT::getpass2();
                cout << endl;
                if (input1 != input2) {
                    errnum = errno;
                    fprintf(stderr, "Password Confirmation failed\n");
                    fprintf(stderr, "Try again\n");
                    return -5;
                }
            }

            // Success for inputting password
            string password = input1;
            string secure_pw_hashed = sha_hash_it(ripemd_hash_it(password));
            fputs(B64::encode64(secure_pw_hashed).c_str(), pass_sto_f);

            string secret = export_private_key() + ";;;";

//            cerr << "secret size: " << secret.size() << endl;

            string secret_aes_key = sha_hash_it(sha3_hash_it(password));
            bitset<32 * BYTE_SIZE> secret_aes_key_bin = str_to_bin(secret_aes_key);
            string expanded_secret_aes_key = expand_key(secret_aes_key_bin);

            string encrypted_secret_content = encrypt_full(process_state(secret), expanded_secret_aes_key);

//            cerr << "encrypted secret content size: " << encrypted_secret_content.size() << endl;

            string secret_otp_key = sha_hash_it(password);
            string expanded_secret_otp_key = otp_key_expansion(secret_otp_key, encrypted_secret_content.size());
            string encrypted_vault_content = encrypt_otp(encrypted_secret_content, expanded_secret_otp_key);

//            cerr << "encrypted vault content: " << encrypted_vault_content.size() << endl;

            assert(encrypted_vault_content.size() % 16 == 0);
//            assert(strlen(encrypted_vault_content.c_str()) % 16 == 0);

            fputs(B64::encode64(encrypted_vault_content).c_str(), vault_sto_f);
//            exact_fputs(encrypted_vault_content, vault_sto_f);

            fputs(export_public_key().c_str(), pub_sto_f);
            
            // close files
            fclose(pub_sto_f);
            fclose(vault_sto_f);
            fclose(pass_sto_f);

            break;
        }
        case ((int)'e'): {
            // assume that either AES_KEY_important.key or vault.sto is present
            FILE *akifile = fopen("AES_KEY_important.key", "r");
            FILE *vaultfile = fopen("vault.sto", "r");
            if (vaultfile == NULL || vaultfile == nullptr) {
                // slave
                // AES_KEY_important.key has the encryption key
                if (akifile == NULL || akifile == nullptr) {
                    cerr << "No file found" << endl;
                    return -5;
                }
                FILE *targetFile = fopen(argv[2], "r");
                if (targetFile == nullptr || targetFile == NULL) {
                    cerr << "No file passed as argument" << endl;
                    return -6;
                }

                string aes_key = B64::decode64(readAllFromFile(akifile));
                bitset<32 * BYTE_SIZE> aes_key_bin = str_to_bin(aes_key);
                string expanded_key = expand_key(aes_key_bin);
                string fileContent = readAllFromFile(targetFile);
                fileContent = encrypt_full(process_state(fileContent), expanded_key);

                string filename(argv[2]);
                filename += ".mmee";

                FILE *resultFile = fopen(filename.c_str(), "w");
                fputs(B64::encode64(fileContent).c_str(), resultFile);

                fclose(resultFile);
                fclose(targetFile);
                fclose(akifile);
            } else {
                // master
                // vault.sto has the encryption key
                if (vaultfile == NULL || vaultfile == nullptr) {
                    cerr << "No file found" << endl;
                    return -5;
                }

                FILE *targetFile = fopen(argv[2], "r");
                if (targetFile == nullptr || targetFile == NULL) {
                    cerr << "No file passed as argument" << endl;
                    return -6;
                }


                // ask for password
                string vaultContent = B64::decode64(readAllFromFile(vaultfile));

                string input1;
                while (input1.size() < 8) {
                    cout << "Enter your vault password: ";
                    input1 = PASSWORD_INPUT::getpass2();
                    cout << endl;
                }
                string hashed = sha_hash_it(ripemd_hash_it(input1));

                // read from pass.sto

                FILE *pass_file = fopen("pass.sto", "r");
                if (pass_file == nullptr) {
                    cerr << "Error: Password file does not exist!" << endl;
                    return 5;
                }
                string supposed_hash;
                // parse_file(supposed_hash, pass_file, false);
                supposed_hash = B64::decode64(readAllFromFile(pass_file));
                if (supposed_hash == hashed) {
                    cerr << "Verification Successful!" << endl;
                } else {
                    cerr << "Verification Failed!" << endl;
                    return 6;
                }
                fclose(pass_file);




                string aes_key = sha_hash_it(sha3_hash_it(input1));
                bitset<32 * BYTE_SIZE> aes_key_bin = str_to_bin(aes_key);
                string expanded_aes_key = expand_key(aes_key_bin);
                string otp_key = sha_hash_it(input1);
                string expanded_otp_key = otp_key_expansion(otp_key, vaultContent.size());
                string decryptedFile = decrypt_otp(vaultContent, expanded_otp_key);
                string more_decrypted_file = unprocess_state(decrypt_full(process_state(decryptedFile), expanded_aes_key));
                // find ;;;
                int breaker_index = -1;
                for (int i = 0; i < (int)more_decrypted_file.size() - 3; i++) {
                    if (more_decrypted_file.substr(i, 3) == ";;;") {
                        breaker_index = i + 3;
                        break;
                    }
                }
                if (breaker_index == -1) {
                    cerr << "Things are fucked" << endl;
                    return -20;
                }
                string the_real_aes_key = "";
                for (int i = breaker_index; i < (int)more_decrypted_file.size(); i++) { the_real_aes_key.push_back(more_decrypted_file[i]); }


                bitset<32 * BYTE_SIZE> traesk = str_to_bin(the_real_aes_key);
                string trexpanded_key = expand_key(traesk);
                string fileContent = readAllFromFile(targetFile);
                fileContent = encrypt_full(process_state(fileContent), trexpanded_key);

                string filename(argv[2]);
                filename += ".mmee";

                FILE *resultFile = fopen(filename.c_str(), "w");

                fputs(B64::encode64(fileContent).c_str(), resultFile);

                fclose(resultFile);
                fclose(targetFile);
                fclose(vaultfile);
            }
            break;
        }
        case ((int)'d'): {
            // assume that either AES_KEY_important.key or vault.sto is present
            
            FILE *akifile = fopen("AES_KEY_important.key", "r");
            FILE *vaultfile = fopen("vault.sto", "r");
            if (vaultfile == NULL || vaultfile == nullptr) {
                 if (akifile == NULL || akifile == nullptr) {
                    cerr << "No file found" << endl;
                    return -5;
                }
                FILE *targetFile = fopen(argv[2], "r");
                if (targetFile == nullptr || targetFile == NULL) {
                    cerr << "No file passed as argument" << endl;
                    return -6;
                }

                string aes_key = B64::decode64(readAllFromFile(akifile));
                bitset<32 * BYTE_SIZE> aes_key_bin = str_to_bin(aes_key);
                string expanded_key = expand_key(aes_key_bin);
                string fileContent = B64::decode64(readAllFromFile(targetFile));
                fileContent = unprocess_state(decrypt_full(process_state(fileContent), expanded_key));

                string filename(argv[2]);
                filename += ".mmed";

                FILE *resultFile = fopen(filename.c_str(), "w");
                fputs(fileContent.c_str(), resultFile);
                fclose(resultFile);
                fclose(targetFile);
                fclose(akifile);
                
            } else {

                if (vaultfile == NULL || vaultfile == nullptr) {
                    cerr << "No file found" << endl;
                    return -5;
                }

                FILE *targetFile = fopen(argv[2], "r");
                if (targetFile == nullptr || targetFile == NULL) {
                    cerr << "No file passed as argument" << endl;
                    return -6;
                }


                // ask for password
                string vaultContent = B64::decode64(readAllFromFile(vaultfile));

                string input1;
                while (input1.size() < 8) {
                    cout << "Enter your vault password: ";
                    input1 = PASSWORD_INPUT::getpass2();
                    cout << endl;
                }
                string hashed = sha_hash_it(ripemd_hash_it(input1));

                // read from pass.sto

                FILE *pass_file = fopen("pass.sto", "r");
                if (pass_file == nullptr) {
                    cerr << "Error: Password file does not exist!" << endl;
                    return 5;
                }
                string supposed_hash;
                // parse_file(supposed_hash, pass_file, false);
                supposed_hash = B64::decode64(readAllFromFile(pass_file));
                if (supposed_hash == hashed) {
                    cerr << "Verification Successful!" << endl;
                } else {
                    cerr << "Verification Failed!" << endl;
                    return 6;
                }
                fclose(pass_file);




                string aes_key = sha_hash_it(sha3_hash_it(input1));
                bitset<32 * BYTE_SIZE> aes_key_bin = str_to_bin(aes_key);
                string expanded_aes_key = expand_key(aes_key_bin);
                string otp_key = sha_hash_it(input1);
                string expanded_otp_key = otp_key_expansion(otp_key, vaultContent.size());
                string decryptedFile = decrypt_otp(vaultContent, expanded_otp_key);
                string more_decrypted_file = unprocess_state(decrypt_full(process_state(decryptedFile), expanded_aes_key));
                // find ;;;
                int breaker_index = -1;
                for (int i = 0; i < (int)more_decrypted_file.size() - 3; i++) {
                    if (more_decrypted_file.substr(i, 3) == ";;;") {
                        breaker_index = i + 3;
                        break;
                    }
                }
                if (breaker_index == -1) {
                    cerr << "Things are fucked" << endl;
                    return -20;
                }
                string the_real_aes_key = "";
                for (int i = breaker_index; i < (int)more_decrypted_file.size(); i++) { the_real_aes_key.push_back(more_decrypted_file[i]); }


                bitset<32 * BYTE_SIZE> traesk = str_to_bin(the_real_aes_key);
                string trexpanded_key = expand_key(traesk);
                string fileContent = B64::decode64(readAllFromFile(targetFile));
                fileContent = unprocess_state(decrypt_full(process_state(fileContent), trexpanded_key));

                string filename(argv[2]);
                filename += ".mmed";

                FILE *resultFile = fopen(filename.c_str(), "w");
                fputs(fileContent.c_str(), resultFile);
                fclose(resultFile);
                fclose(targetFile);
                fclose(vaultfile);
            }

            break;
        }
        case ((int)'x'): {
            FILE *slave_pubf = fopen("slave_pub.sto", "r");
            FILE *master_pubf = fopen("pub.sto", "r");
            if (slave_pubf == NULL) {
                string inside = readAllFromFile(master_pubf);
                cout << inside << endl;
                fclose(master_pubf);
            } else {
                if (slave_pubf == NULL) {
                    cerr << "No available files and information" << endl;
                    return -5;
                }
                string inside = readAllFromFile(slave_pubf);
                cout << inside << endl;
                fclose(slave_pubf);
            }
            break;
        }
        case ((int)'i'): {
            if (fopen("vault.sto", "r") != NULL) {
                cout << "Master operations" << endl;
                return 0;
            } else if (fopen("AES_KEY_important.key", "r") != NULL) {
                cout << "Completed Transaction Slave Operation" << endl;
                return 0;
            } else {
                cout << "No completed exchange operations" << endl;
                return 0;
            }
            break;
        }
        case ((int)'o'): {
            // from slave_pub.sto, create opub.key
            FILE *slave_pub_key_f = fopen("slave_pub.sto", "r");
            FILE *opub_key_f = fopen("opub.key", "w");
            if (slave_pub_key_f == nullptr || opub_key_f == nullptr) {
                errnum = errno;
                cerr << "File failed to open" << endl;
                return errnum;
            }

            fclose(fopen("opub.key", "w")); // clears content
            char ch;
            ch = fgetc(slave_pub_key_f);
            while(ch != EOF)
            {
                fputc(ch, opub_key_f);
                ch = fgetc(slave_pub_key_f);
            }
            fclose(slave_pub_key_f);
            fclose(opub_key_f);
            break;
        }
        case ((int)'b'): {
            FILE *master_pub_key_F = fopen("pub.sto", "r");
            FILE *master_pub_share_f = fopen("master_pub.key", "w");
            if (master_pub_key_F == nullptr || master_pub_share_f == nullptr) {
                errnum = errno;
                cerr << "File failed to open" << endl;
                return errnum;
            }
            fclose(fopen("master_pub.key", "w"));
            char ch;
            ch = fgetc(master_pub_key_F);
            while (ch != EOF) {
                fputc(ch, master_pub_share_f);
                ch = fgetc(master_pub_key_F);
            }
            fclose(master_pub_key_F);
            fclose(master_pub_share_f);
            break;
        }
        case ((int)'m'): {
            // from comm.sto, create mme_aesk.ekey
            FILE *comm_pub_key_f = fopen("comm.sto", "r");
            FILE *mme_key_f = fopen("mme_aesk.ekey", "w");
            if (comm_pub_key_f == nullptr || mme_key_f == nullptr) {
                errnum = errno;
                cerr << "File failed to open" << endl;
                return errnum;
            }

            fclose(fopen("mme_aesk.ekey", "w")); // clears content
            char ch;
            ch = fgetc(comm_pub_key_f);
            while(ch != EOF)
            {
                fputc(ch, mme_key_f);
                ch = fgetc(comm_pub_key_f);
            }
            fclose(comm_pub_key_f);
            fclose(mme_key_f);
            break;
        }
        default: {
            cout << "Unknown Command; Consider using -h" << endl;
            return 3;
        }
    }


    return 0;
}
