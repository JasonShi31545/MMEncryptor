#ifndef RSA_GEN_KEYS_HH
#define RSA_GEN_KEYS_HH

#include "_aux.hh"
#include "prime.hh"

//using namespace std;

using namespace boost::multiprecision;
using namespace boost::random;
using namespace boost::math;

cpp_int _p,q,n,phi,d,e_; // _p to avoid name collision, e_ to avoid name collision

void initialize_primes(cpp_int &a, cpp_int &b, const cpp_int k) {
    
    assert(k > 0);
    boost::random::independent_bits_engine<boost::random::random_device, 4096, cpp_int> gen;

    for (int i = 0; i < 2; i++) {
        while (1) {
            cpp_int r = gen();
            if (check_sieve(r)) {
                if (isPrime(r,k)) {
                    switch(i) {
                        case 0:
                            a = r;
                            break;
                        case 1:
                            b = r;
                            break;
                    }
                    break;
                }
            }
        }
    }

}
/*
void initialize_primes(cpp_int &a, cpp_int &b, const cpp_int k) {
    assert(k > 0);
    boost::random::independent_bits_engine<boost::random::random_device, 4096, cpp_int> genp;
    boost::random::independent_bits_engine<boost::random::random_device, 3072, cpp_int> genq;
    while (1) {
        cpp_int r = genp();
        if (check_sieve(r)) {
            if (isPrime(r,k)) {
                a = r;
                break;
            }
        }
    }
    while (1) {
        cpp_int r = genq();
        if (check_sieve(r)) {
            if (isPrime(r,k)) {
                b = r;
                break;
            }
        }
    }
}
*/

void initialize_e(cpp_int &__e, const cpp_int k) {
    
    assert(phi > 0);
    assert(n > 0);
    assert(k > 0);
    boost::random::independent_bits_engine<boost::random::random_device, 4148, cpp_int> gen_e;
    
    __e = 0;
    while (__e < _p || __e < q || (__e >= phi)) { // if any of these undesirable conditions are true, continue to find primes
        cpp_int r = gen_e();
        if (check_sieve(r)) {
            if(isPrime(r,k)) {
                __e = r;
            }
        }
    }
    assert(__e > _p && __e > q && __e < (phi));
}
/*
cpp_int get_d_() {
    // Extended Euclidean Algorithm

    std::vector<std::vector<cpp_int>> eea_table;
    eea_table = {{1,0,e_,0}, {0,1,phi,(e_/phi)}};

    int i = 2;

    const int x_id = 0;
    const int y_id = 1;
    const int d_id = 2;
    const int k_id = 3;

    while (true) {
        const cpp_int oldk = eea_table[i-1][k_id];
        cpp_int new_d = eea_table[i-2][d_id] - (eea_table[i-1][d_id] * oldk);
        cpp_int new_y = eea_table[i-2][y_id] - (eea_table[i-1][y_id] * oldk);
        cpp_int new_x = eea_table[i-2][x_id] - (eea_table[i-1][x_id] * oldk);
        cpp_int new_k = eea_table[i-1][d_id] / eea_table[i-2][d_id];
//        std::cerr << new_x << " " << new_y << " " << new_d << " " << new_k << std::endl;
        eea_table.push_back({new_x, new_y, new_d, new_k});
        if (new_k == eea_table[i-1][d_id]) {
            break;
        }
        i++;
    }


    return eea_table[i][x_id];
//    return 0;
}
*/

cpp_int get_d() {

    cpp_int a = e_;
    cpp_int b = phi;

    if (abs(a) == 1) {
        return a;
    } else if (abs(b) == 1) {
        return 0;
    }
    cpp_int old_remainder = a;
    cpp_int remainder = b;
    cpp_int old_coeff_a = 1;
    cpp_int coeff_a = 0;
    cpp_int old_coeff_b = 0;
    cpp_int coeff_b = 1;
    
    cpp_int temp;
    while (remainder != 0) {
        cpp_int quotient = old_remainder / remainder;
        temp = old_remainder;
        old_remainder = remainder;
        remainder = temp - quotient * remainder;
        temp = old_coeff_a;
        old_coeff_a = coeff_a;
        coeff_a = temp - quotient * coeff_a;
        temp = old_coeff_b;
        old_coeff_b = coeff_b;
        coeff_b = temp - quotient * coeff_b;
    }
    if (a < 0) {
        old_coeff_a = -old_coeff_a;
    }
    if (b < 0) {
        old_coeff_b = -old_coeff_b;
    }

    return old_coeff_a;
}

void gen_rsa_k() {
//    e_ = 65537;
    init_psl();
    cpp_int k = 6; // certainty of primality

    prime_generator();
    trim_prime_sieve_list();
    initialize_primes(_p, q, k);
    n = _p * q;
    phi = (_p - 1) * (q - 1);
    initialize_e(e_, k);
    assert(e_ < phi);
//    std::cerr << "Prime Gen is done" << std::endl;
    d = get_d();
    /*
    d = d % phi;
    if (d < 0) {
        d += phi;
    }
    */
    // Resolve negative d
    while (d < 0) {
        d += phi;
    }
    std::cout << "RSA key generation successful" << std::endl;
//    cpp_int _d = get_d_();
//    std::cerr << "COMPARE D: " << _d << std::endl;

}
#endif // RSA_GEN_KEYS_HH
