#ifndef AUX_HH
#define AUX_HH

#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <sstream>
#include <cassert>
#include <cmath>
#include <map>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cerrno>
#include <error.h>
#include <random>
#include <algorithm>

#include <boost/random/random_device.hpp>
#include <boost/math/special_functions/powm1.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/discrete_distribution.hpp>
#include <boost/random.hpp>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/gmp.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/multiprecision/number.hpp>
#include <boost/lexical_cast.hpp>

//using namespace std;

// AUXILIARY FUNCTIONS

const int BYTE_SIZE = 8;
std::map<char, int> hex_mapper;/* = {
    '0': 0,
    '1': 1,
    '2': 2,
    '3': 3,
    '4': 4,
    '5': 5,
    '6': 6,
    '7': 7,
    '8': 8,
    '9': 9,
    'A': 10,
    'B': 11,
    'C': 12,
    'D': 13,
    'E': 14,
    'F': 15
};
*/


int bin_to_int(std::string bins) {
    int result = 0;
    for (int i = 0; i < (int)bins.size(); i++) {
        int index = (bins.size() - 1) - i;
        int bit = bins[index] - '0';
        if (bit == 1) {
            result += pow(2, i);
        }
    }
    return result;
}

std::string int_to_hex(int input) {
//    cerr << "The input: " << input << endl;
//    assert(input < 128 && input > -127);
    std::stringstream stream;
    stream << std::hex << input;
    std::string result(stream.str());

    // add padding zero if necessary to the hexadecimal value
    if (result.size() < 2) {
        int count = 2 - result.size();
        for (int x = 0; x < count; x++) {
            result.insert(result.begin(), '0');
        }
    }
    // done padding

//    cerr << "Int to hex size: " << result.size() << endl;
    if (result.size() == 8) {
        result = result.substr(6,result.size());
//        cerr << "result.size() == " << result.size() << endl;
    }
    assert(result.size() == 2);
    return result;
}

std::string int_to_bin(int _input, const int targeted_size = 8) {
    std::string result;
    int input = _input;

    if (input < 0) {
        const int and_operand = 0b00000000000000000000000001111111; // because sizeof(int) == 4 Bytes, which is 32 bits
        input = (input & and_operand) + (int)pow(2,7);
    }

    while (input > 0) {
        int _digit = input % 2;
        input /= 2;
        char digit = _digit + '0';
        result.insert(result.begin(), digit);
    }

    // add padding zeros based on targeted_size (default: 1 byte)
    
    if ((int)result.size() < targeted_size) {
        int count = targeted_size - result.size();
        for (int i = 0; i < count; i++) {
            result.insert(result.begin(), '0');
        }
    }
    // done adding

    return result;
}
int hex_to_int(std::string hex_val) {
    assert(hex_val.size() == 2);
    int result = 0;
    for (int i = 1; i >= 0; i--) {
        result += pow(16, i) * hex_mapper[hex_val[1-i]];
    }
    return result;
}

std::string bin_to_str(std::bitset<4 * BYTE_SIZE> bin_of_four_bytes) {
    std::string string_form;
//    std::string_form.resize(4 * BYTE_SIZE);
    assert(bin_of_four_bytes.size() == 4 * BYTE_SIZE);
    for (int i = 0; i < (int) bin_of_four_bytes.size(); i++) {
        bool element = bin_of_four_bytes[i];
        string_form.push_back(element ? '1' : '0');
    }
    assert(string_form.size() == 4 * BYTE_SIZE);
    return string_form;
}

std::string bin_to_chars(std::bitset<16 * BYTE_SIZE> bin_of_sixteen_bytes) {
    std::string string_form;
    string_form.resize(16);
    assert(bin_of_sixteen_bytes.size() == 16 * BYTE_SIZE);
    for (int i = 0; i < 16; i++) {
        char character = 0;
        for (int j = 0; j < BYTE_SIZE; j++) {
            //cerr << ((bin_of_sixteen_bytes[i*BYTE_SIZE + j]) ? '1' : '0');
            //cerr << bin_of_sixteen_bytes[i*BYTE_SIZE + j] * (int)pow(2, (BYTE_SIZE) - j) << " ";
            character += bin_of_sixteen_bytes[i*BYTE_SIZE + j] * (int)pow(2, (BYTE_SIZE-1) - j);
        }
        //cerr << character << "::";
        string_form[i] = character;
    }
    assert(string_form.size() == 16);
    return string_form;
}

void init() {
    hex_mapper.insert(std::make_pair('0', 0));
    hex_mapper.insert(std::make_pair('1', 1));
    hex_mapper.insert(std::make_pair('2', 2));
    hex_mapper.insert(std::make_pair('3', 3));
    hex_mapper.insert(std::make_pair('4', 4));
    hex_mapper.insert(std::make_pair('5', 5));
    hex_mapper.insert(std::make_pair('6', 6));
    hex_mapper.insert(std::make_pair('7', 7));
    hex_mapper.insert(std::make_pair('8', 8));
    hex_mapper.insert(std::make_pair('9', 9));
    hex_mapper.insert(std::make_pair('A', 10));
    hex_mapper.insert(std::make_pair('B', 11));
    hex_mapper.insert(std::make_pair('C', 12));
    hex_mapper.insert(std::make_pair('D', 13));
    hex_mapper.insert(std::make_pair('E', 14));
    hex_mapper.insert(std::make_pair('F', 15));
    hex_mapper.insert(std::make_pair('a', 10));
    hex_mapper.insert(std::make_pair('b', 11));
    hex_mapper.insert(std::make_pair('c', 12));
    hex_mapper.insert(std::make_pair('d', 13));
    hex_mapper.insert(std::make_pair('e', 14));
    hex_mapper.insert(std::make_pair('f', 15));
}
void reverse_string(std::string &str) {
    std::string temp = str;
    for (int i = str.size() - 1; i >= 0; i--) {
        temp[(str.size() - 1) - i] = str[i];
    }
    str = temp;
}

std::string reverse_string_r(std::string str) {
    std::string temp = str;
    for (int i = str.size() - 1; i >= 0; i--) {
        temp[(str.size() - 1) - i] = str[i];
    }
    return temp;
}


std::string final_key_conversion(std::bitset<60 * 4 * BYTE_SIZE> ek) { // ek stands for expanded_key
    std::string result = "";
    //    int sdtlsdfjasdf = 0;
    for (int i = 0; i < 60 * 4; i++) {
        char byte = 0;
        for (int j = 0; j < BYTE_SIZE; j++) {
            byte += ek[i*BYTE_SIZE + j] * pow(2, (BYTE_SIZE-(j+1)));

            //            sdtlsdfjasdf++;
            //            cerr << "BYTE FOR CONVERSION: " << (int)byte << endl;
        }
        result.push_back(byte);
    }
    //    cerr << "Result size: " << result.size() << endl;
    assert(result.size() == 240);
    //    cerr << sdtlsdfjasdf << endl;
    return result;
}
std::string bin_to_str(std::bitset<32 * BYTE_SIZE> bits) {
    std::string result = "";
    for (int i = 31; i >= 0; i--) {
        unsigned char byte = 0;
        for (int j = BYTE_SIZE-1; j >= 0; j--) {
            bool bit = bits[i*BYTE_SIZE + j];
            int exponent = j;
            byte += (int)bit * std::pow(2, exponent);
        }
        result.push_back(byte);
    }
    return result;
}

std::bitset<32 * BYTE_SIZE> str_to_bin(std::string istr) {
    std::string rbin = "";
    assert(istr.size() == 32);
    for (int i = 0; i < (int)istr.size(); i++) {
        unsigned char byte = istr[i];
        std::string bins = int_to_bin((int)byte);
        rbin += bins;
    }
    return std::bitset<32 * BYTE_SIZE>(rbin);
}

boost::multiprecision::cpp_int str_to_cppint(std::string istr) {
    boost::multiprecision::cpp_int result = 0;
    for (int i = istr.size() - 1; i >= 0; i--) {
        assert(istr[i] >= '0' && istr[i] <= '9');
        boost::multiprecision::cpp_int buffer = (istr[i] - '0');
        int place = istr.size() - (i+1);
        for (int j = 0; j < place; j++) {
            buffer *= 10;
        }
        result += buffer;
    }
    return result;
}


#endif // AUX_HH
