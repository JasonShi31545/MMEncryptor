#ifndef PRIME_HH
#define PRIME_HH

#include "_aux.hh"

using namespace boost::multiprecision;
//using namespace std;
using namespace boost::random;
using namespace boost::math;

int _n;
std::string content; std::vector<int> prime_sieve_list;

void init_psl() {
    _n = 4;
    content = "";

    int i = 0;
    while (i < pow(10, _n)) {
        prime_sieve_list.push_back(i);
        i++;
    }

}
void prime_generator() { 
    for (auto ele : prime_sieve_list) {
        if (ele == 0 || ele == 1) {
            continue;
        }
        int j = 2;
        while ((ele * j) < (int)prime_sieve_list.size()) {
            int k = ele * j;
            prime_sieve_list[k] = 0;
            j++;
        }
    }
    for (int i = 0; i < (int)prime_sieve_list.size(); i++) {
        if (prime_sieve_list[i] == 1) {
            prime_sieve_list.erase(prime_sieve_list.begin() + i);
            break;
        }
    }
}

cpp_int power(cpp_int x, cpp_int y, cpp_int p) {
    cpp_int res = 1;
    x = x % p;
    while (y > 0) {
        if (y & 1) {
//            res = (res * x) % p;
            res = ((res % p) * (x % p)) % p;
        }
        y = y >> 1; // y = y / 2
//        x = (x * x) % p;
        x = ((x % p)*(x % p)) % p;
    }
    return res;
}

 
bool millerTest(cpp_int d, cpp_int n) {

//    independent_bits_engine<mt19937, 3333, cpp_int> gen;

    cpp_int a; // random
    boost::random::random_device dev;
    boost::random::mt19937 mt(dev());
//    mt19937 mt;
//    std::cerr << "n: " << n << std::endl;
    boost::random::uniform_int_distribution<cpp_int> ui(1, n - 4);
    a = 2 + ui(mt);
//    a = 2 + (cpp_int)ui(dev);
//    std::cerr << "a: " << a << " which is 2+r(1...n-4)" << std::endl;
    assert((a - 2) <= n-4 && (a-2) >= 1);
    cpp_int x = power(a, d, n);
    if (x == 1 || x == n - 1) {
        return true;
    }
    while (d != n - 1) {
//        x = (x * x) % n;
        x = ((x % n) * (x % n)) % n;
        d *= 2;
        if (x == 1) {
            return false;
        }
        if (x == n - 1) {
            return true;
        }
    }
    return false;
}


bool isPrime(cpp_int n, cpp_int k) {
    if (n <= 1 || n == 4) {
        return false;
    }
    if (n <= 3) {
        return true;
    }

    cpp_int d = n - 1;
    while (d % 2 == 0) {
        d /= 2;
    }
    for (cpp_int i = 0; i < k; i++) {
        if (millerTest(d, n) == false) {
            return false;
        }
    }
    return true;
}


bool check_sieve(cpp_int n) {
    if (n == 0) {
        return false;
    }
    bool ok = true;
    for (int i = 0; i < (int)prime_sieve_list.size(); i++) {
        if (prime_sieve_list[i] == 0) {
            continue;
        }
        if (n % prime_sieve_list[i] == 0) {
            ok = false;
            break;
        }
    }
    return ok;
}

void trim_prime_sieve_list() {
    int i = 0;
    while (i < (int)prime_sieve_list.size()) {
        if (prime_sieve_list[i] == 0) {
            prime_sieve_list.erase(prime_sieve_list.begin() + i);
        } else {
            i++;
        }
    }
}

/*
int main(void) {

    init_psl();
    cpp_int k = 4;
    cpp_int number_it = 1;

    prime_generator();
    trim_prime_sieve_list();


//    random_device dev;
//    mt19937 mt(dev());
//    mt19937 mt;


//    uniform_int_distribution<cpp_int> ui((cpp_int)powm1(10,500)+1, (cpp_int)powm1(10,1000)+1);

    //independent_bits_engine<mt19937, 3333, cpp_int> gen;
    independent_bits_engine<mt19937, 1222, cpp_int> gen;
    while (1) {


        // 1661
        // 3333

        cpp_int r = gen();
//        cpp_int r = (cpp_int)ui(mt);

//        std::cerr << r << std::endl;
        if (check_sieve(r)) {
            if (isPrime(r,k)) {
                std::cout << r << std::endl;
            }
        }
//        std::cout << "#" << " ";
    }

    return 0;
}
*/
#endif // PRIME_HH
