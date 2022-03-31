#ifndef BASE64_HH
#define BASE64_HH

namespace B64 {


    int b64BinToIndex(std::string binaryStr) {
        assert(binaryStr.size() == 6);
        int power = 5; // since the most power is 6, the biggest should be 5, or else it would be an off-by-one error
        int result = 0;
        for (int i = 0; i < (int)binaryStr.size(); i++) {
            result += (binaryStr[i] - '0') * (1 << power);
            power--;
        }
        return result;
    }
    
    const std::string b64charst = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"; // base64 character set
    std::map<char, std::string> anticharst = {
        {'A', "000000"},
        {'B', "000001"},
        {'C', "000010"},
        {'D', "000011"},
        {'E', "000100"},
        {'F', "000101"},
        {'G', "000110"},
        {'H', "000111"},
        {'I', "001000"},
        {'J', "001001"},
        {'K', "001010"},
        {'L', "001011"},
        {'M', "001100"},
        {'N', "001101"},
        {'O', "001110"},
        {'P', "001111"},
        {'Q', "010000"},
        {'R', "010001"},
        {'S', "010010"},
        {'T', "010011"},
        {'U', "010100"},
        {'V', "010101"},
        {'W', "010110"},
        {'X', "010111"},
        {'Y', "011000"},
        {'Z', "011001"},
        {'a', "011010"},
        {'b', "011011"},
        {'c', "011100"},
        {'d', "011101"},
        {'e', "011110"},
        {'f', "011111"},
        {'g', "100000"},
        {'h', "100001"},
        {'i', "100010"},
        {'j', "100011"},
        {'k', "100100"},
        {'l', "100101"},
        {'m', "100110"},
        {'n', "100111"},
        {'o', "101000"},
        {'p', "101001"},
        {'q', "101010"},
        {'r', "101011"},
        {'s', "101100"},
        {'t', "101101"},
        {'u', "101110"},
        {'v', "101111"},
        {'w', "110000"},
        {'x', "110001"},
        {'y', "110010"},
        {'z', "110011"},
        {'0', "110100"},
        {'1', "110101"},
        {'2', "110110"},
        {'3', "110111"},
        {'4', "111000"},
        {'5', "111001"},
        {'6', "111010"},
        {'7', "111011"},
        {'8', "111100"},
        {'9', "111101"},
        {'+', "111110"},
        {'/', "111111"}
    };
    
    std::string encode64(std::string inputBytes) {
        std::string result = "";
        int equalsigns = 0;
        std::string binaries = "";
        for (int i = 0; i < (int)inputBytes.size(); i++) {
            binaries += int_to_bin((int)inputBytes[i]);
        }
        assert(binaries.size() % 8 == 0);
        assert((binaries.size() % 6) % 2 == 0);
        if (binaries.size() % 6 != 0) {
            equalsigns = (6 - (binaries.size() % 6))/2;
            const int additionalZeros = (6 - (binaries.size() % 6));
            for (int i = 0; i < (int)additionalZeros; i++) { binaries.push_back('0'); };
        }
        assert(binaries.size() % 6 == 0);
        for (int i = 0; i < (int)binaries.size() / 6; i++) {
            std::string tmp = "";
            for (int j = 0; j < 6; j++) {
                tmp.push_back(binaries[i * 6 + j]);
            }
            // process tmp
            result.push_back(b64charst[b64BinToIndex(tmp)]);
        }
        for (int i = 0; i < equalsigns; i++) { result += "="; };
        return result;
    }

    std::string decode64(std::string inputString) { // return the associated data from the base64 string
        int equalsigns = 0;
        int k = inputString.size() - 1;
        while (inputString[k] == '=') {
            equalsigns++;
            k--;
        }
        std::string result = "";
        inputString = inputString.substr(0, inputString.size() - equalsigns);

        std::string binaries = "";
        for (int i = 0; i < (int)inputString.size(); i++) {
            binaries += anticharst[inputString[i]];
        }
        for (int i = 0; i < equalsigns; i++) {
            binaries = binaries.substr(0,binaries.size() - 2); // remove 2 trailing zeros
        }
        assert(binaries.size() % 8 == 0);

        for (int i = 0; i < (int)binaries.size() / 8; i++) {
            int prechar = bin_to_int(binaries.substr(i*8, 8));
            assert(prechar >= 0 && prechar <= 255);
            result.push_back((char)prechar);
        }
        return result;
    }
};

#endif // BASE64_HH
