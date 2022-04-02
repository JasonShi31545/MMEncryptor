#ifndef AES_HH
#define AES_HH

#include "aes_functions.hh"
using namespace std;

string process_state(const string _state) {
    string state = _state;
    if (state.size() % 16 != 0) {
        int n_of_spaces_to_add = ((state.size() / 16 + 1) * 16) - state.size();
        assert(n_of_spaces_to_add > 0);
        for (int i = 0; i < n_of_spaces_to_add; i++) {
            state.push_back(' ');
        }
    }
    return state;
}

string unprocess_state(const string _state) {
    string state = _state;
//    assert(state.size() % 16 == 0);
    int i = state.size() - 1;
    while (state[i] == ' ') {
        state.erase(state.begin() + i);
        i--;
    }
    return state;
}

string encrypt(const string state, string ek) {
    assert(state.size() == 16);
    string ct;
    string sixteen_bytes = state;
    ct.resize(state.size());

//    cerr << "Start encrypt" << endl;

    // initial round of xor

    sixteen_bytes = add_round_key(sixteen_bytes, 0, ek);
//    cerr << "Init successful" << endl;

    for (int round = 1; round <= 14; round++) { // fourteen rounds
//        cerr << "Round: " << round << endl;
        assert(sixteen_bytes.size() == 16);
        switch (round) {
//                sixteen_bytes = add_round_key(sixteen_bytes, round, ek);
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
                sixteen_bytes = add_round_key(mix_column(shift_row(byte_sub(sixteen_bytes))), round, ek);
//                cerr << round << "th" << " round le-successful" << endl;
                break;
            case 14:
                sixteen_bytes = add_round_key(byte_sub(shift_row(sixteen_bytes)), round, ek);
//                cerr << "Last round successful" << endl;
                break;
            default:
//                cerr << "FUCKED UP ROUND ERROR" << endl;
                throw "FUCKED UP";
                break;
        }
    }
    ct = sixteen_bytes;
    return ct;
}

string decrypt(const string ctstate, string ek) {
    assert(ctstate.size() == 16);
    string pt;
    string sixteen_bytes = ctstate;
    pt.resize(ctstate.size());

//    cerr << "Start decrypt" << endl;


// sixteen_bytes = add_round_key(sixteen_bytes, round, ek);

   sixteen_bytes = dshift_row(dbyte_sub(add_round_key(sixteen_bytes, 14, ek)));

    for (int round = 1; round <= 14; round++) { // fourteen rounds
//        cerr << "Round: " << round << endl;
        assert(sixteen_bytes.size() == 16);
        switch (round) {
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9:
            case 10:
            case 11:
            case 12:
            case 13:
//                sixteen_bytes = dmix_column(add_round_key(dbyte_sub(dshift_row(sixteen_bytes)), round, ek));

                sixteen_bytes = dbyte_sub(dshift_row(dmix_column(add_round_key(sixteen_bytes, 14-round, ek))));
//                cerr << round << "th" << " round le-successful" << endl;
                break;
            case 14:
//                sixteen_bytes = add_round_key(dbyte_sub(dshift_row(sixteen_bytes)), round, ek);
                sixteen_bytes = add_round_key(sixteen_bytes, 14-round, ek);
//                cerr << "Last round successful" << endl;
                break;
            default:
//                cerr << "FUCKED UP ROUND ERROR (Decrypt)" << endl;
                throw "FUCKED UP";
                break;
        }
    }
    pt = sixteen_bytes;
    return pt;
}

vector<string> split_pt(const string plaintext) {
    vector<string> buffer;
    assert(plaintext.size() % 16 == 0);
    for (int i = 0; i < (int)plaintext.size()/16; i++) {
        buffer.push_back(plaintext.substr(16*i, 16));
    }

    //debug
    for (string str: buffer) {
        assert(str.size() == 16);
    }
//    cerr << "Split completed" << endl;

    return buffer;
}

string encrypt_full(const string plaintext, string ek) {
    vector<string> pt = split_pt(plaintext);
    vector<string> encrypted;

    // pt[x].size() == 16
//    cerr << "PT SIZE: ";
//    cerr << pt.size() << endl;
    
    for (string s: pt) {
//        cerr << "sixteen bytes!" << endl;
        encrypted.push_back(encrypt(s, ek));
    }
    string f = "";
    for (string s: encrypted) {
        f += s;
    }
    return f;
}

string decrypt_full(const string ciphertext, string ek) {
    vector<string> ct = split_pt(ciphertext);
    vector<string> decrypted;

//    cerr << "CT: SIZE: ";
//    cerr << ct.size() << endl;

    for (string s: ct) {
//        cerr << "sixteen bytes (decrypt)!" << endl;
        decrypted.push_back(decrypt(s, ek));
    }
    string f = "";
    for (string s: decrypted) {
        f += s;
    }
    return f;
}


#endif // AES_HH
