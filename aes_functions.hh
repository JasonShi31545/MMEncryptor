#ifndef AES_FUNCTIONS_HH
#define AES_FUNCTIONS_HH
#include "key_expansion.hh"
#include "byte_sub_table.hh"
#include "galois_field.hh"

using namespace std;
void sanitize_state(string &state) {
    if (state.size() % 4 != 0) {
        int n_counter = (state.size() / 4 + 1) * 4 - state.size();
        for (int i = 0; i < n_counter; i++) {
            state.push_back(' ');
        }
    }
}

bitset<32 * BYTE_SIZE> generate_key() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> distribution(0,1);

    bitset<32 * BYTE_SIZE> key; // because 256-bit key
    for (int i = 0; i < 32 * BYTE_SIZE; i++) {
        //        key[i] = distribution(generator);
        key[i] = distribution(rng);
    }
    assert(key.size() == 32 * BYTE_SIZE);
    return key;
}

/*

for a round
14 rounds for our 256 bit encryption
*/
/*
string encrypt(int round = 0) {
    switch (round) {

    }
}
*/
// bitset<60 * 4 * BYTE_SIZE> expanded_key_bytes; // 60 of 4 bytes; sizeof(expanded_key_bytes) == 240

// THE SIZE OF THE EXPANDED KEY BYTES IS 240 BYTES LONG, EACH ADD ROUND KEY TAKES (REMOVES) 16 BYTES, FOR AES, THERE IS 15 ROUNDS OF ENCRYPTION, WHICH IS EXACTLY (15 * 16 = 240).

string add_round_key(string state, int round, string exp_key) {
    // returns the round key for each round with specified round

    // DEBUG
    string temp = exp_key;

    assert(exp_key.size() == 240);
    assert(state.size() == 16);
//    assert(state.size() >= 16);
    assert(round >= 0 && round < 15);
    // 0 to 14, 15 values maximum. 15 * 16 = 240

    string exp_k_16;//(16);
    exp_k_16.resize(16);
    for (int i = 0; i < 16; i++) {
        exp_k_16[i] = exp_key[round*16 + i];
    }

    string result;//(16);
    result.resize(16);
    for (int i =0 ; i < 16;i ++) {
//        result[i] = (state[round*16 + i] ^ exp_k_16[i]);
        result[i] = (state[i] ^ exp_k_16[i]);
    }
    

    assert(exp_key == temp);

    return result;
}


string byte_sub(string state) {
    assert(state.size() == 16);
    string result;
    for (int i = 0; i < 4; i++) { // 4 SBOX substitutions
        string row_bytes = (string)state.substr(i*4, 4);
        assert(row_bytes.size() == 4);
        for (int j = 0; j < 4; j++) {
            // four bytes
            char byte = row_bytes[j];
            string hex = int_to_hex((int)byte);
            int index1 = hex_mapper[hex[0]];
            int index2 = hex_mapper[hex[1]];
//            cerr << int_to_hex(bs_sbox[index1][index2]) << endl;
            char hex_re = (char)((int)bs_sbox[index1][index2]);
            result.push_back(hex_re);
        }
    }
    return result;
}

string dbyte_sub(string ctstate) {
    assert(ctstate.size() == 16);
    string result;
    for (int i = 0; i < 4; i++) {
        string row_bytes = (string)ctstate.substr(i*4, 4);
        assert(row_bytes.size() == 4);
        for (int j = 0; j < 4; j++) {
            char byte = row_bytes[j];
            string hex = int_to_hex((int)byte);
            int index1 = hex_mapper[hex[0]];
            int index2 = hex_mapper[hex[1]];
            char hex_re = (char)((int)decrypt_bs_sbox[index1][index2]);
            result.push_back(hex_re);
        }
    }
    return result;
}


/*
// same as above, but with different type
vector<vector<char>> byte_sub(vector<vector<char>> state) {

}
*/

vector<char> shift_left(vector<char> str, int offset) {
    assert(str.size() == 4);
    vector<char> a;
    for (int i = 0; i < offset; i++) {
//        cerr << str[i] << endl;
        a.push_back(str[i]);
    }
    for (int i = 4-1; i > (offset-1); i--) {
//        cerr << "i: " << i << endl;
        a.insert(a.begin(), str[i]);
    }
    return a;
}

vector<char> shift_right(vector<char> str, int offset) {
    assert(str.size() == 4);
    vector<char> a;
    const int length = str.size();
    for (int i = length - offset; i < length; i++) {
        a.push_back(str[i]);
    }
    for (int i = 0; i < length - offset; i++) {
        a.push_back(str[i]);
    }
    return a;
}

string shift_row(string state) {
    assert(state.size() == 16);
    vector<vector<char>> matrix(4, {0,0,0,0});
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[j][i] = state[i*4 + j];
        }
    }

    
    for (int i = 1; i <= 3; i++) {
        matrix[i] = shift_left(matrix[i], i);
    }

    // shift first row

    string result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.push_back(matrix[j][i]);
        }
    }
    return result;
    //return matrix;
}
string dshift_row(string ctstate) {
    assert(ctstate.size() == 16);
    vector<vector<char>> matrix(4, {0,0,0,0});
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[j][i] = ctstate[i*4 + j];
        }
    }

    
    for (int i = 1; i <= 3; i++) {
        matrix[i] = shift_right(matrix[i], i);
    }

    // shift first row

    string result;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            result.push_back(matrix[j][i]);
        }
    }
    return result;
    //return matrix;
}


char etable_lookup(int input) {
//    cerr << "E Table Lookup input: " << input << endl;
    string hex_val = int_to_hex(input);
    return etable[hex_mapper[hex_val[0]]][hex_mapper[hex_val[1]]];
}

unsigned char ltable_lookup(unsigned char input) {

    //unsigned int iinput = (unsigned int)input;
//    cerr << "L Table Lookup input: " << iinput << endl;
    string hex_val = int_to_hex((int)input);
//    cerr << "L Table Lookup input: " << hex_val << endl;
    
    /*
    if (hex_val[0] == '0' && hex_val[1] == '0') {
        cerr << "Invalid Input" << endl;
//        cerr << "llc: " << llc << endl;
        throw "Invalid Input";
    }
    */

    return (unsigned char)ltable[hex_mapper[hex_val[0]]][hex_mapper[hex_val[1]]];
}


unsigned char gmul(unsigned char a, unsigned char b) {
    if (a == 0x00 || b == 0x00) {
        return 0x00;
    }
    unsigned char op_a = ltable_lookup(a);
    unsigned char op_b = ltable_lookup(b);
    unsigned char sum;
    if ((unsigned int) op_a + (unsigned int) op_b > (unsigned int)0xff) {
        sum = (unsigned char)((unsigned int)op_a + (unsigned int)op_b) - 0xff;
    } else {
        sum = op_a + op_b;
    }
//    cerr << int_to_hex((int)op_a) << " " << int_to_hex((int)op_b )<< " " << int_to_hex((int)sum )<< endl;
    unsigned char result = etable_lookup(sum);
    return result;
}
string mix_column(string state) {

    vector<vector<char>> arr (4, {0,0,0,0});
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            arr[j][i] = state[i*4+j];
        }
    }
    vector<vector<char>> result (4, {0,0,0,0});

    const vector<vector<char>> mmatrix = {
        {2, 3, 1, 1},
        {1, 2, 3, 1},
        {1, 1, 2, 3},
        {3, 1, 1, 2}
    };

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // calculate for result[j][i]
            char r = 0;
            for (int k = 0; k < 4; k++) {
//                cerr << ((int)(unsigned char)mmatrix[j][k]) << " " << (int)((unsigned char)arr[k][i]) << endl << endl;
//                r ^= (mmatrix[j][k] * arr[k][i]);
                r ^= gmul(mmatrix[j][k], arr[k][i]);
            }
            result[j][i] = r;
//            cerr << "Coordinate " << "(" << j << ", " << i << ") " << "has element: " << int_to_hex((int)(unsigned char)result[j][i]) << endl;
        }
    }

    string _r;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            _r.push_back(result[j][i]);
        }
    }

    return _r;

}

string dmix_column(string ctstate) {

    vector<vector<char>> arr (4, {0,0,0,0});
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            arr[j][i] = ctstate[i*4+j];
        }
    }
    vector<vector<char>> result (4, {0,0,0,0});

    const vector<vector<char>> mmatrix = {
        {0x0E, 0x0B, 0x0D, 0x09},
        {0x09, 0x0E, 0x0B, 0x0D},
        {0x0D, 0x09, 0x0E, 0x0B},
        {0x0B, 0x0D, 0x09, 0x0E}
    };

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            // calculate for result[j][i]
            char r = 0;
            for (int k = 0; k < 4; k++) {
//                cerr << ((int)(unsigned char)mmatrix[j][k]) << " " << (int)((unsigned char)arr[k][i]) << endl << endl;
//                r ^= (mmatrix[j][k] * arr[k][i]);
                r ^= gmul(mmatrix[j][k], arr[k][i]);
            }
            result[j][i] = r;
//            cerr << "Coordinate " << "(" << j << ", " << i << ") " << "has element: " << int_to_hex((int)(unsigned char)result[j][i]) << endl;
        }
    }

    string _r;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            _r.push_back(result[j][i]);
        }
    }

    return _r;

}


//string initial_state = "";


/*
int main(void) {
    init();

//    string test_state = "Hello World!1234Hello World!1234Hello World!1234Hello World!1234Hello World!1234Hello World!1234Hello World!1234Hello World!1234Hello World!1234Hello World!1234Hello World!1234Hello World!1234Hello World!1234Hello World!1234Hello World!1234Hello World!1234";
//    assert(test_state.size() % 16 == 0);
    bitset<32 * BYTE_SIZE> generated_key = generate_key();
    string expanded_key = expand_key(generated_key);
//    expand_key(generate_key());
//    expand_key(bitset<32 * BYTE_SIZE> (("0100100001001000010010000100100001001000010010000100100001001000010010000100100001001000010010000100100001001000010010000100100001001000010010000100100001001000010010000100100001001000010010000100100001001000010010000100100001001000010010000100100001001000")));
    assert(expanded_key_bytes.size() == 240*BYTE_SIZE);


    cerr << endl;
    cerr << "------------------- Completed Key Expansion --------------------" << endl;
    cerr << endl;


//    char tbyte = ('H' * 2) ^ ('O' * 3) ^ ('L' * 1) ^ ('2' * 1);
//    cerr << int_to_hex((int)tbyte) << endl;
    

    string test;

    test.push_back((char)0xD4);
    test.push_back((char)0xBF);
    test.push_back((char)0x5D);
    test.push_back((char)0x30);

    test.push_back((char)0xD4);
    test.push_back((char)0xBF);
    test.push_back((char)0x5D);
    test.push_back((char)0x30);


    test.push_back((char)0xD4);
    test.push_back((char)0xBF);
    test.push_back((char)0x5D);
    test.push_back((char)0x30);


    test.push_back((char)0xD4);
    test.push_back((char)0xBF);
    test.push_back((char)0x5D);
    test.push_back((char)0x30);


    cerr << test.size() << endl;

    string aha = mix_column(test);
    assert(aha.size() == 16);
    
    for (int i = 0; i < (int)aha.size(); i++) {
        cerr << (int)aha[i] << endl;
        cerr << int_to_bin((int)aha[i]) << endl;
        cerr << int_to_hex((int)aha[i]) << endl;
    }

    cerr << "Everything went fine" << endl;
    vector<vector<char>> result = mix_column_mm(_state_matrix);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cerr << (int)result[i][j] << " ";
        }
        cerr << endl;
    }
    cerr << endl;




//     cerr << "START FUCKING..." << endl;

//     for (int i = 0; i < (int)expanded_key_bytes.size(); i++) {
//         cout << ((expanded_key_bytes[i]) ? '1' : '0');
//     }
//     cout << endl;


//     // key

//     cerr << "START TESTING" << endl << endl;
//     cerr << "START TESTING" << endl << endl;
//     cerr << "START TESTING" << endl << endl;
//     cerr << "START TESTING" << endl << endl;
//     cerr << "START TESTING" << endl << endl;
//     cerr << "START TESTING" << endl << endl;
//     cerr << "START TESTING" << endl << endl;
//     cerr << "START TESTING" << endl << endl;


//     for (int i = 0; i < (int)expanded_key_bytes.size(); i++) {
//         if (i == 16 * BYTE_SIZE) {
//             break;
//         }
//         cout << ((expanded_key_bytes[i]) ? '1' : '0');
//         if ((i+1) % 8 == 0) {
//             cout << endl;
//         }
//     }
//     cout << "Continue? ";
//     int x;
//     cin >> x;
//     if (x != 1) {
//         return -1;
//     }
//     cout << endl << endl;
//     vector<char> r = add_round_key(test_state, 0);
// //    assert(r.size() == 16);
//     for (int i = 0; i < (int)r.size(); i++) {
//         cout << (unsigned int)r[i] << endl;
//     }

//
//cerr << int_to_hex(byte_sub(test_state)) << endl;

    //bitset<16 * BYTE_SIZE> da_string;
    //string a = "Hello World!1234";
    //cout << (int)a[0] << endl;
    //for (int i = 0; i < (int)a.size(); i++) {
        //string bin = int_to_bin(a[i]);
        //cout << bin << endl;
        //bitset<BYTE_SIZE> character = bitset<BYTE_SIZE> (reverse_string_r(bin));
        //assert(character.size() == BYTE_SIZE);
        //for (int j = 0; j < BYTE_SIZE; j++) {
            //da_string[i*BYTE_SIZE + j] = character[j];
        //}
    //}
    //for (int i = 0; i < da_string.size(); i++) {
        //cerr << ((da_string[i]) ? '1' : '0');
    //}
    //cerr << endl << endl;
    //string b = bin_to_chars(da_string);
    //cout << b << endl;

    return 0;
}
*/

#endif // AES_FUNCTIONS_HH
