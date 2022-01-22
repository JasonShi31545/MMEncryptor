#ifndef KEY_EXPANSION_HH
#define KEY_EXPANSION_HH

#include "_aux.hh"

#define XOR ^

/*
 *
 * 0x7D --> SBOX[7][D] --> 0xFF
 * 0xFF --> INVERSE_SBOX[F][F} --> 0x7D
 *
 *
*/

using namespace std;
const vector<vector<int>> SBOX = {
{0x63 , 0x7C , 0x77 , 0x7B , 0xF2 , 0x6B , 0x6F , 0xC5 , 0x30 , 0x01 , 0x67 , 0x2B , 0xFE , 0xD7 , 0xAB , 0x76},
{0xCA , 0x82 , 0xC9 , 0x7D , 0xFA , 0x59 , 0x47 , 0xF0 , 0xAD , 0xD4 , 0xA2 , 0xAF , 0x9C , 0xA4 , 0x72 , 0xC0},
{0xB7 , 0xFD , 0x93 , 0x26 , 0x36 , 0x3F , 0xF7 , 0xCC , 0x34 , 0xA5 , 0xE5 , 0xF1 , 0x71 , 0xD8 , 0x31 , 0x15},
{0x04 , 0xC7 , 0x23 , 0xC3 , 0x18 , 0x96 , 0x05 , 0x9A , 0x07 , 0x12 , 0x80 , 0xE2 , 0xEB , 0x27 , 0xB2 , 0x75},
{0x09 , 0x83 , 0x2C , 0x1A , 0x1B , 0x6E , 0x5A , 0xA0 , 0x52 , 0x3B , 0xD6 , 0xB3 , 0x29 , 0xE3 , 0x2F , 0x84},
{0x53 , 0xD1 , 0x00 , 0xED , 0x20 , 0xFC , 0xB1 , 0x5B , 0x6A , 0xCB , 0xBE , 0x39 , 0x4A , 0x4C , 0x58 , 0xCF},
{0xD0 , 0xEF , 0xAA , 0xFB , 0x43 , 0x4D , 0x33 , 0x85 , 0x45 , 0xF9 , 0x02 , 0x7F , 0x50 , 0x3C , 0x9F , 0xA8},
{0x51 , 0xA3 , 0x40 , 0x8F , 0x92 , 0x9D , 0x38 , 0xF5 , 0xBC , 0xB6 , 0xDA , 0x21 , 0x10 , 0xFF , 0xF3 , 0xD2},
{0xCD , 0x0C , 0x13 , 0xEC , 0x5F , 0x97 , 0x44 , 0x17 , 0xC4 , 0xA7 , 0x7E , 0x3D , 0x64 , 0x5D , 0x19 , 0x73},
{0x60 , 0x81 , 0x4F , 0xDC , 0x22 , 0x2A , 0x90 , 0x88 , 0x46 , 0xEE , 0xB8 , 0x14 , 0xDE , 0x5E , 0x0B , 0xDB},
{0xE0 , 0x32 , 0x3A , 0x0A , 0x49 , 0x06 , 0x24 , 0x5C , 0xC2 , 0xD3 , 0xAC , 0x62 , 0x91 , 0x95 , 0xE4 , 0x79},
{0xE7 , 0xC8 , 0x37 , 0x6D , 0x8D , 0xD5 , 0x4E , 0xA9 , 0x6C , 0x56 , 0xF4 , 0xEA , 0x65 , 0x7A , 0xAE , 0x08},
{0xBA , 0x78 , 0x25 , 0x2E , 0x1C , 0xA6 , 0xB4 , 0xC6 , 0xE8 , 0xDD , 0x74 , 0x1F , 0x4B , 0xBD , 0x8B , 0x8A},
{0x70 , 0x3E , 0xB5 , 0x66 , 0x48 , 0x03 , 0xF6 , 0x0E , 0x61 , 0x35 , 0x57 , 0xB9 , 0x86 , 0xC1 , 0x1D , 0x9E},
{0xE1 , 0xF8 , 0x98 , 0x11 , 0x69 , 0xD9 , 0x8E , 0x94 , 0x9B , 0x1E , 0x87 , 0xE9 , 0xCE , 0x55 , 0x28 , 0xDF},
{0x8C , 0xA1 , 0x89 , 0x0D , 0xBF , 0xE6 , 0x42 , 0x68 , 0x41 , 0x99 , 0x2D , 0x0F , 0xB0 , 0x54 , 0xBB , 0x16}
};

const vector<vector<int>> INVERSE_SBOX = {
{0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB},
{0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB},
{0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E},
{0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25},
{0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92},
{0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84},
{0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06},
{0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B},
{0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73},
{0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E},
{0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B},
{0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4},
{0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F},
{0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF},
{0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61},
{0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D}
};

// sizeof(SBOX | INVERSE_SBOX) should be 16*16*4 bytes


//string key_string = string("1110101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010011111");

bitset<32 * BYTE_SIZE> keya;
bitset<60 * 4 * BYTE_SIZE> expanded_key_bytes; // 60 of 4 bytes; sizeof(expanded_key_bytes) == 240

bitset<4 * BYTE_SIZE> K(bitset<32 * BYTE_SIZE> key, int offset) {
    bitset<4 * BYTE_SIZE> result;
    string _result;
    for (int i = offset*BYTE_SIZE; i < (offset*BYTE_SIZE)+(4*BYTE_SIZE); i++) {
        // key[i] means the bit inside the 4 byte range, total 32 bits
        _result.push_back('0' + key[i]);
    }
    // cerr << _result << endl;
    result = bitset<4 * BYTE_SIZE> (_result);
    return result;
}

/*
bitset<4> ROT(bitset<4> four_bits) {
    bitset<4> result = four_bits;
    int element = result[0];
    for (int i = 0; i < (int)four_bits.size() - 1; i++) {
        result[i] = result[i+1];
    }
    result[result.size() - 1] = element;
    return result;
}
*/

bitset<4 * BYTE_SIZE> ROT(bitset<4 * BYTE_SIZE> four_bytes) {
    assert(four_bytes.size() == 4 * BYTE_SIZE);
    bitset<BYTE_SIZE> first_byte;
    for (int i = 0; i < 8; i++) {
        first_byte[i] = four_bytes[i];
    }
    bitset<4 * BYTE_SIZE> result;
    for (int i = 8; i < (int)four_bytes.size(); i++) {
        result[i-8] = four_bytes[i];
    }
    for (int i = 24; i < (int)result.size(); i++) {
        result[i] = first_byte[i-24];
    }
    return result;
}



/*
bitset<2 * BYTE_SIZE> subpartition_substitution(string hex_val) {
    assert(hex_val.size() == 2);
    char first_char, second_char;
    first_char = hex_val[0];
    second_char = hex_val[1];
    int index1 = hex_mapper[first_char];
    int index2 = hex_mapper[second_char];
    int byte = SBOX[index1][index2];
    // convert int (of 2 bytes) to binary and convert to bitset
    string binary = int_to_bin(byte, 8);
    return bitset<2 * BYTE_SIZE>(binary);
}
*/


bitset<4 * BYTE_SIZE> SUB(bitset<4 * BYTE_SIZE> input) {

    string string_bins = bin_to_str(input);

//    cerr << "BITSET TO STIRNG SUCCESSFUL" << endl;

    assert(string_bins.size() == 32); // 32 as in 4 * BYTE_SIZE
    int integer_bytes[4];
    for (int i = 0; i < 4; i++) {
        const string substring = (string)string_bins.substr(i*BYTE_SIZE, BYTE_SIZE);
//        cerr << "Substring of binary to be converted to integer: " << substring << endl;
        integer_bytes[i] = bin_to_int(substring);
    }

//    cerr << "INTEGER CONVERSION SUCCESSFUL" << endl;

    string hex_values[4];
    for (int i = 0; i < 4; i++) {
        hex_values[i] = int_to_hex(integer_bytes[i]);

//        cerr << "HEX VALUE SPECIFIC:   " << hex_values[i] << endl;
        assert(hex_values[i].size() == 2);
    }


//    cerr << "HEX CONVERSION SUCCESSFUL" << endl;

    // SBOX
    for (int i = 0; i < 4; i++) {
//        hex_values[i] = SBOX[hex_values[i][0]][hex_values[i][1]];
        assert(hex_values[i].size() == 2);
//        cerr << endl;
//        cerr << "Hex value: " << hex_values[i] << endl;
//        int index1 = hex_mapper[hex_values[i][0]];
//        int index2 = hex_mapper[hex_values[i][1]];
//        cerr << "Index 1: " << index1 << endl;
//        cerr << "Index 2: " << index2 << endl;
        hex_values[i] = int_to_hex(SBOX[hex_mapper[hex_values[i][0]]][hex_mapper[hex_values[i][1]]]);
//        cerr << "SBOX Converted: " << hex_values[i] << endl;
//        cerr << endl;


        assert(hex_values[i].size() == 2);
    }

//    cerr << "HEX SBOX SUBSTITUTION SUCCESSFUL" << endl;

    string binary_values[4];
    for (int i = 0; i < 4; i++) {
        binary_values[i] = int_to_bin(hex_to_int(hex_values[i]));
        assert(binary_values[i].size() == BYTE_SIZE);
    }
    
//    cerr << "HEX TO BIN SUCCESSFUL" << endl;

    // convert to bitset
    bitset<BYTE_SIZE> converted_bitsets[4];
    for (int i = 0; i < 4; i++) {
        converted_bitsets[i] = bitset<BYTE_SIZE> (reverse_string_r(binary_values[i]));
    }
    
//    cerr << "BIN TO BITSET SUCCESSFUL" << endl;


    // combine 4 bitsets with length of BYTE_SIZE to 1 bitset with a length of (4 * BYTE_SIZE)
    
    bitset<4 * BYTE_SIZE> final_result;
    for (int i = 0; i < 4; i++) {
        bitset<BYTE_SIZE> element = converted_bitsets[i];
        assert(element.size() == BYTE_SIZE);
        for (int j  = 0; j < (int)element.size(); j++) {
            final_result[i*BYTE_SIZE + j] = element[j];
        }
    }

//    cerr << "BITSET COMBINATION SUCCESSFUL" << endl;

    return final_result;
}

/*
bitset<4 * BYTE_SIZE> SUB_DECRYPT() {
    
}
*/


//vector<bitset<4 * BYTE_SIZE>> expanded_key_bytes(60); // a collection of each round of 4-byte expanded keys, 60 of them of total 240-bytes; // sizeof(this_object) should be 240.


bitset<4 * BYTE_SIZE> EK(bitset<32 * BYTE_SIZE> key, int offset) {
    bitset<4 * BYTE_SIZE> result;
    string _result;
    for (int i = offset*BYTE_SIZE; i < (offset*BYTE_SIZE) + (4 * BYTE_SIZE); i++) {
        _result.push_back('0' + expanded_key_bytes[i]);
    }
    result = bitset<4 * BYTE_SIZE> (_result);
    return result;
}
/*
 * THIS IS INCORRECT
bitset<4 * BYTE_SIZE> EK(bitset<32 * BYTE_SIZE> key, int offset) {
    bitset<4 * BYTE_SIZE> result;
    string _result;
    for (int i = offset*BYTE_SIZE; i < (offset*BYTE_SIZE) + (4 * BYTE_SIZE); i++) {
        _result.push_back('0' + key[i]);
    }
    result = bitset<4 * BYTE_SIZE> (_result);
    return result;
}
*/

int _RCON(int val) {
    switch (val) {
    case 0:
        return 0x01000000;
        break;
    case 1:
        return 0x02000000;
        break;
    case 2:
        return 0x04000000;
        break;
    case 3:
        return 0x08000000;
        break;
    case 4:
        return 0x10000000;
        break;
    case 5:
        return 0x20000000;
        break;
    case 6:
        return 0x40000000;
        break;
    case 7:
        return 0x80000000;
        break;
    case 8:
        return 0x1B000000;
        break;
    case 9:
        return 0x36000000;
        break;
    case 10:
        return 0x6C000000;
        break;
    case 11:
        return 0xD8000000;
        break;
    case 12:
        return 0xAB000000;
        break;
    case 13:
        return 0x4D000000;
        break;
    case 14:
        return 0x9A000000;
        break;
    default:
        throw "Rcon invalid input";
        break;
    }
}

bitset<4 * BYTE_SIZE> RCON(int val) {
    return bitset<4 * BYTE_SIZE> (reverse_string_r(int_to_bin(_RCON(val), 4 * BYTE_SIZE)));
}


bitset<4 * BYTE_SIZE> _expand_key(bitset<32 * BYTE_SIZE> key, int round);

string expand_key(bitset<32 * BYTE_SIZE> the_key) {
    // initialize key expansion array (expanded_key_bytes) to be equal to the first bytes of the key
    // initialization process START

    assert(the_key.size() == 32 * BYTE_SIZE);

    for (int i = 0 ; i < (int)the_key.size(); i ++) {
        expanded_key_bytes[i] = the_key[i];
    }


//    cerr << "Fine 1" << endl;
    /*
     * The first bytes of the expanded key are always equal to the key. If the key is 16 bytes long the first 16 bytes of the
expanded key will be the same as the original key. If the key size is 32 bytes then the first 32 bytes of the expanded key
will be the same as the original key.
    */

    // initialization process END

    for (int i = 0; i < 60; i++) { // rounds
        //        expanded_key_bytes[i] = expand_key(the_key, i);
        bitset<4 * BYTE_SIZE> expanded = _expand_key(the_key, i);
        assert(expanded.size() == 4 * BYTE_SIZE);
        for (int j = 0; j < (int)expanded.size(); j++) {
            expanded_key_bytes[4 * BYTE_SIZE * i + j] = expanded[j];
        }
    }


    //cerr << "Fine 2" << endl;

    // Convert it to string because I swear I will not do fucking bitsets no more
    
    return final_key_conversion(expanded_key_bytes);


    // return 0;
}

bitset<4 * BYTE_SIZE> _expand_key(bitset<32 * BYTE_SIZE> key, int round) {
    switch (round) {
        case 0: {
            return K(key, 0);
            break;
        }
        case 1: {
            return K(key, 4);
        }
        case 2: {
            return K(key, 8);
        }
        case 3: {
            return K(key, 12);
        }
        case 4: {
            return K(key, 16);
        }
        case 5: {
            return K(key, 20);
        }
        case 6: {
            return K(key, 24);
        }
        case 7: {
            return K(key, 28);
        }
        case 8: {
            return SUB(ROT(EK(key,(8-1)*4))) ^ RCON((8/4)-1) ^ EK(key,(8-4)*4);
        }
        case 9: {
            return EK(key,(9-1)*4) XOR EK(key,(9-4)*4);
        }
        case 10: {
            return EK(key,(10-1)*4) XOR EK(key,(10-4)*4);
        }
        case 11: {
            return EK(key,(11-1)*4) XOR EK(key,(11-4)*4);
        }
        case 12: {
            return SUB(EK(key,(12-1)*4)) XOR EK(key,(12-4)*4);
        }
        case 13: {
            return EK(key,(13-1)*4) XOR EK(key,(13-4)*4);
        }
        case 14: {
            return EK(key,(14-1)*4) XOR EK(key,(14-4)*4);
        }
        case 15: {
            return EK(key,(15-1)*4) XOR EK(key,(15-4)*4);
        }
        case 16: {
            return SUB(ROT(EK(key,(16-1)*4))) XOR RCON((16/4)-1) XOR EK(key,(16-4)*4);
        }
        case 17: {
            return EK(key,(17-1)*4) XOR EK(key,(17-4)*4);
        }
        case 18: {
            return EK(key,(18-1)*4) XOR EK(key,(18-4)*4);
        }
        case 19: {
            return EK(key,(19-1)*4) XOR EK(key,(19-4)*4);
        }
        case 20: {
            return SUB(EK(key,(20-1)*4)) XOR EK(key,(20-4)*4);
        }
        case 21: {
            return EK(key,(21-1)*4) XOR EK(key,(21-4)*4);
        }
        case 22: {
            return EK(key,(22-1)*4) XOR EK(key,(22-4)*4);
        }
        case 23: {
            return EK(key,(23-1)*4) XOR EK(key,(23-4)*4);
        }
        case 24: {
            return SUB(ROT(EK(key,(24-1)*4))) XOR RCON((24/4)-1) XOR EK(key,(24-4)*4);
        }
        case 25: {
           return EK(key,(25-1)*4) XOR EK(key,(25-4)*4);
        }
        case 26: {
            return EK(key,(26-1)*4) XOR EK(key,(26-4)*4);
        }
        case 27: {
            return EK(key,(27-1)*4) XOR EK(key,(27-4)*4);
        }
        case 28: {
            return SUB(EK(key,(28-1)*4)) XOR EK(key,(28-4)*4);
        }
        case 29: {
            return EK(key,(29-1)*4) XOR EK(key,(29-4)*4);
        }
        case 30: {
            return EK(key,(30-1)*4) XOR EK(key,(30-4)*4);
        }
        case 31: {
            return EK(key,(31-1)*4) XOR EK(key,(31-4)*4);
        }
        case 32: {
            return SUB(ROT(EK(key,(32-1)*4))) XOR RCON((32/4)-1) XOR EK(key,(32-4)*4);
        }
        case 33: {
            return EK(key,(33-1)*4) XOR EK(key,(33-4)*4);
        }
        case 34: {
            return EK(key,(34-1)*4) XOR EK(key,(34-4)*4);
        }
        case 35: {
            return EK(key,(35-1)*4) XOR EK(key,(35-4)*4);
        }
        case 36: {
            return SUB(EK(key,(36-1)*4)) XOR EK(key,(36-4)*4);
        }
        case 37: {
            return EK(key,(37-1)*4) XOR EK(key,(37-4)*4);
        }
        case 38: {
            return EK(key,(38-1)*4) XOR EK(key,(38-4)*4);
        }
        case 39: {
            return EK(key,(39-1)*4) XOR EK(key,(39-4)*4);
        }
        case 40: {
            return SUB(ROT(EK(key,(40-1)*4))) XOR RCON((40/4)-1) XOR EK(key,(40-4)*4);
        }
        case 41: {
            return EK(key,(41-1)*4) XOR EK(key,(41-4)*4);
        }
        case 42: {
            return EK(key,(42-1)*4) XOR EK(key,(42-4)*4);
        }
        case 43: {
            return EK(key,(43-1)*4) XOR EK(key,(43-4)*4);
        }
        case 44: {
            return SUB(EK(key,(44-1)*4)) XOR EK(key,(44-4)*4);
        }
        case 45: {
            return EK(key,(45-1)*4) XOR EK(key,(45-4)*4);
        }
        case 46: {
            return EK(key,(46-1)*4) XOR EK(key,(46-4)*4);
        }
        case 47: {
            return EK(key,(47-1)*4) XOR EK(key,(47-4)*4);
        }
        case 48: {
            return SUB(ROT(EK(key,(48-1)*4))) XOR RCON((48/4)-1) XOR EK(key,(48-4)*4);
        }
        case 49: {
            return EK(key,(49-1)*4) XOR EK(key,(49-4)*4);
        }
        case 50: {
            return EK(key,(50-1)*4) XOR EK(key,(50-4)*4);
        }
        case 51: {
            return EK(key,(51-1)*4) XOR EK(key,(51-4)*4);
        }
        case 52: {
            return SUB(EK(key,(52-1)*4)) XOR EK(key,(52-4)*4);
        }
        case 53: {
            return EK(key,(53-1)*4) XOR EK(key,(53-4)*4);
        }
        case 54: {
            return EK(key,(54-1)*4) XOR EK(key,(54-4)*4);
        }
        case 55: {
            return EK(key,(55-1)*4) XOR EK(key,(55-4)*4);
        }
        case 56: {
            return SUB(ROT(EK(key,(56-1)*4))) XOR RCON((56/4)-1) XOR EK(key,(56-4)*4);
        }
        case 57: {
            return EK(key,(57-1)*4) XOR EK(key,(57-4)*4);
        }
        case 58: {
            return EK(key,(58-1)*4) XOR EK(key,(58-4)*4);
        }
        case 59: {
            return EK(key,(59-1)*4) XOR EK(key,(59-4)*4);
        }
        default: {
            throw "Error: Keysize should be in a range of [0,60)";
            return bitset<4 * BYTE_SIZE> ();
        }
    }
}
#endif // KEY_EXPANSION_HH
