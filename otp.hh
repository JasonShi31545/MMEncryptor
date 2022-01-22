#ifndef OTP_HH
#define OTP_HH

#include "_aux.hh"
//#include <bits/stdc++.h>
//using namespace std;

std::string global_otp_key;

void gen_key(int length) {
    std::string key;
    for (int i = 0; i < length; i++) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(1, 50);
        int random_key = dis(gen);
        key.push_back(random_key);
    }
    global_otp_key = key;
}

std::vector<unsigned char> parse_sha256_from_str(std::string input) {
    std::vector<unsigned char> parsed;
    assert(input.size() == 64);
    for (int i = 0; i < 64; i+=2) {
        std::string _byte = input.substr(i,2);
        int result = hex_to_int(_byte);
        assert(result < 256);
        parsed.push_back((unsigned char)result);
    }
    return parsed;
}

std::string otp_key_expansion(std::string shaOutput, int chrCountOfEncryptedMessage) {
//    std::vector<char> bytes_from_it = parse_sha256_from_std::string(sha64chrOutput);
    const int number_of_bytes = (int)shaOutput.size();
    assert(number_of_bytes == 32);
    const int times = chrCountOfEncryptedMessage / number_of_bytes;
    const int remainder = chrCountOfEncryptedMessage % number_of_bytes;
    std::vector<std::vector<unsigned char>> grid;
    assert(times > 0 && remainder >= 0);
    if (remainder != 0) {
        grid.resize(times + 1);
    } else {
        grid.resize(times);
    }
    for (int i = 0; i < (int)grid.size(); i++) {
        grid[i].resize(32);
    }
    for (int i = 0; i < times; i++) {
        for (int j = 0; j < 32; j++) {
            grid[i][j] = shaOutput[j];
        }
    }
    if (remainder != 0) {
        for (int i = 0; i < remainder; i++) {
            grid[(times + 1)-1][i] = shaOutput[i];
        }
    }
    std::string final_result;
    for (int i = 0; i < 32; i++) {
        // grid[i][j]
        if (i < remainder) {
            for (int j = 0; j < times+1; j++) {
                final_result.push_back(grid[j][i]);
            }
        } else {
            for (int j = 0; j < times; j++) {
                final_result.push_back(grid[j][i]);
            }
        }
    }
    assert(final_result.size() == (long unsigned int)chrCountOfEncryptedMessage);
    return final_result;
}

std::string encrypt_otp(std::string plaintext, std::string key) {
    std::string ciphertext = plaintext;
    for (int i = 0; i < (int)plaintext.size(); i++) {
        ciphertext[i] ^= key[i];
    }
    assert(ciphertext.size() == plaintext.size());
    return ciphertext;
}

std::string decrypt_otp(std::string ciphertext, std::string key) {
    std::string plaintext = ciphertext;
    for (int i = 0; i < (int)ciphertext.size(); i++) {
        plaintext[i] ^= key[i];
    }
    assert(plaintext.size() == ciphertext.size());
    return plaintext;
}

/*
int main(void) {
    
    std::string input;
    cout << "Input the std::string: ";
    cin >> input;
    gen_key(input.size());
    cout << "String: " << input << endl;
    std::string encrypted = encrypt(input);
    cout << "Encrypted: " << encrypted << endl;
    cout << endl;
    cout << "Decrypted: " << decrypt(encrypted, global_key) << endl;
    
    return 0;
}
*/

#endif // OTP_HH
