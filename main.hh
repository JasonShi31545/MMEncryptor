#ifndef MAIN_HH
#define MAIN_HH

/*
string clean_up_string(string input) {
    string result = "";
    for (int i = 0; i < (int)input.size(); i++) {
        if (input[i] != '\0') {
            result.push_back(input[i]);
        }
    }
    if (result.empty()) {
        cerr << "\"result\" is empty" << endl;
        return "";
    }
    return result;
}
*/



std::vector<char> readAllFromFile(const char *filepath) {
    // check exists
    std::cerr << "Filepath: " << filepath << std::endl;
    FILE *f = fopen(filepath, "r");
    if (f == NULL) return (std::vector<char>){};
    fclose(f);

    std::filesystem::path p(filepath);
    std::vector<char> res;
    std::ifstream ifs(std::filesystem::absolute(p), std::ios::binary);
    assert(ifs);

    res = std::vector<char>(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
    // // std::for_each(res.begin(), res.end(), [](char c) { std::cout << c; });
    // // std::cin.get();

    return res;
}

std::string readFileToString(std::vector<char> f) {
    std::string str(f.begin(), f.end());
    return str;
}

std::pair<std::string, std::string> splitAtComma(string input) {
    string a = "", b = "";
    bool toggleComma = false;
    int commaCount = 0;
    int i = -1;
    for (i = 0; i < (int)input.size(); i++) {
        if (input[i] == ',') {
            commaCount++;
            if (commaCount > 1) { // we have a problem
                cerr << "More than 1 comma in the string" << endl;
                throw "More than 1 comma in the string";
            }
            toggleComma = true;
            continue;
        }
        if (toggleComma == true) {
            b.push_back(input[i]);
        } else {
            a.push_back(input[i]);
        }
    }
    if (i == -1) {
        cerr << "No comma found" << endl;
        return std::make_pair("", "");
    }
    return make_pair(a,b);
}


#endif // MAIN_HH
