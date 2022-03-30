#ifndef BASE64_HH
#define BASE64_HH

namespace B64 {

    const string b64charst = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"; // base64 character set
    std::string encode64(std::string inputBytes) { // return base64 string of the associated data
        std::string result_string = "";
        int groups = inputBytes.size() / 3;
        int left_overs = inputBytes.size() % 3;
        for (int i = 0; i < groups; i++) {
            std::string temp;
            char a = inputBytes[i * 3 + 0];
            char b = inputBytes[i * 3 + 1];
            char c = inputBytes[i * 3 + 2];
            std::string abin = int_to_bin((int)a);
            std::string bbin = int_to_bin((int)b);
            std::string cbin = int_to_bin((int)c);
            std::string concatenated = abin + bbin + cbin;
            assert(concatenated % 6 == 0);
            assert(concatenated % 8 == 0);
            std::vector<std::string> convertedBins(4);
            for (int i = 0; i < 4; i++) {
                std::string temp = "";
                int index = i * 6;
                for (int j = 0; j < 6; i++) {
                    temp.push_back(concatenated[index + j]);
                }
                assert(temp.size() == 6);
                convertedBins[i] = temp;
            }
            assert(convertedBins.size() == 4);
            for (int i = 0; i < convertedBins.size(); i++) {

            }
        }
    }

    std::string decode64(std::string inputString) { // return the associated data from the base64 string
    }





};

#endif // BASE64_HH
