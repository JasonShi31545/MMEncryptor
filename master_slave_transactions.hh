#ifndef MASTER_SLAVE_TRANSACTIONS
#define MASTER_SLAVE_TRANSACTIONS

#include "aux.hh"
#include "rsa.hh"

//using namespace std;

static std::string application_version_number(7, 'X');// = "v0.1 Alpha";

std::string gen_id_info(std::string id_name) {
    assert(application_version_number.size() == 7); // must be seven characters long
    assert(id_name.size() == 10);
    const std::string return_str =  "MMEV " + application_version_number + "HN: " + id_name + " ++END";
    assert(return_str.size() == 32);
    return return_str;
}

bool verify_id(std::string id_string, std::string expected_master_id_name) {
    if (id_string.find("MMEV ") == std::string::npos) {
        return false;
    }
    if (id_string.find("HN: ") == std::string::npos) {
        return false;
    }
    if (id_string.find(expected_master_id_name) == std::string::npos) {
        return false;
    }
    if (id_string.find(" ++END") == std::string::npos) {
        return false;
    }
    if (id_string != expected_master_id_name) {
        return false;
    }
    return true;
}

std::string transaction_message_master() {
    return "MME-M/S-GEN_RSA-NO_GEN_AES_+MASTER_RESERVED";
}

std::string transaction_message_slave() {
    return "MME-M/S-GEN_RSA-GEN_AES_+SLAVE_RESERVED";
}

static bool amIMaster;

void interpret_message(const std::string message) {
    if (message ==  "MME-M/S-GEN_RSA-NO_GEN_AES_+MASTER_RESERVED") {
        amIMaster = false;
    } else {
        amIMaster = true;
    }
    return;
}

std::string export_public_key() {
    std::string e__in_string = boost::lexical_cast<std::string>(e_);
    std::string n_in_string = boost::lexical_cast<std::string>(n);
    return e__in_string + "," + n_in_string;
}

std::string export_private_key() {
    std::string d_in_string = boost::lexical_cast<std::string>(d);
    std::string n_in_string = boost::lexical_cast<std::string>(n);
    return d_in_string + "," + n_in_string;
}

std::pair<cpp_int, cpp_int> interpret_sent_public_key(std::string str_pk) {
    cpp_int op_e;
    cpp_int op_n;
    bool ope_or_n = false;
    std::string sope = "";
    std::string sopn = "";
    for (int i = 0; i < (int)str_pk.size(); i++) {
        if (ope_or_n == false) {
            sope.push_back(str_pk[i]);
        } else {
            sopn.push_back(str_pk[i]);
        }
        if (str_pk[i] == ',') {
            ope_or_n = !ope_or_n; // toggle
        }
    }
    assert(ope_or_n == true);
    assert((int)sope.size() > 0 && (int)sopn.size() > 0);
    op_e = boost::lexical_cast<cpp_int>(sope);
    op_n = boost::lexical_cast<cpp_int>(sopn);
    return std::make_pair(op_e, op_n);
}

std::string export_encrypted_message(std::vector<cpp_int> ct) {
    std::string result = "";
    for (int i = 0; i < (int)ct.size(); i++) {
        result += (boost::lexical_cast<std::string>(ct[i]) + "\\");
    }
    return result;
}

std::vector<cpp_int> parse_received_message(std::string ct) {
    std::vector<cpp_int> result = {};
    std::string temp = "";
    for (int i = 0; i < (int)ct.size(); i++) {
        if (ct[i] == '\\') {
            if (temp.empty()) {
                continue;
            }
            try {
                result.push_back(boost::lexical_cast<cpp_int>(temp));
            } catch (...) {
                cerr << "Fucked!" << endl << endl;
                cerr << temp << "   " << "with size: " << temp.size() << endl << endl;
                result.push_back(str_to_cppint(temp));
            }
            temp = "";
        } else {
            temp.push_back(ct[i]);
        }
    }
    return result;
}



#endif // MASTER_SLAVE_TRANSACTIONS
