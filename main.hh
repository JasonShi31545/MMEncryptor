#ifndef MAIN_HH
#define MAIN_HH


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

std::string readAllFromFile(FILE *fff) {
    std::string result = "";
    char ch;
    if (fff == NULL || fff == nullptr) {
        throw "File cannot be opened";
    }

    ch = fgetc(fff);
    while (ch != EOF) {
        result.push_back(ch);
        ch = fgetc(fff);
    }
    // fclose(fff);

    return result;
    
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
