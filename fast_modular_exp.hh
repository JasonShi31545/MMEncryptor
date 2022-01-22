#ifndef FAST_MODULAR_EXP_HH
#define FAST_MODULAR_EXP_HH
#include "aux.hh"

using namespace boost::multiprecision;
using namespace boost::random;
using namespace boost::math;

cpp_int fmexp(cpp_int base, cpp_int exp, cpp_int mod) {
    assert(exp >= 0);
    cpp_int res = 1;
    while (exp > 0) {
       if (exp % 2 == 1)
          res= (res * base) % mod;
       exp = exp >> 1;
       base = (base * base) % mod;
    }
    return res;
}



/*
int po2(int base, int exp, int modulus) {
    // exp is a power of 2
    assert(exp % 2 == 0);
    int count = ceil(log(exp)/log(2));
    std::vector<int> dp;
    dp.resize(count+1);
    for (int i = 0; i <= count; i++) {
        if (i == 0) {
            dp[i] = base % modulus;
        } else {
            dp[i] = ((dp[i-1]) * (dp[i-1])) % modulus;
        }
        std::cerr << "i: " << i << "   dp[i]: " << dp[i] << std::endl;
        std::cerr << std::pow(2,i) << std::endl;
    }
    return dp[count];
}
*/
cpp_int cpb2(cpp_int exp) { // custom power base 2
    if (exp < 0) {
        return -404;
    }
    cpp_int r = 1;
    for (int i = 0; i < exp; i++) {
        r <<= 1;
    }
    return r;
}


static std::map<std::vector<cpp_int>, cpp_int> globl_fmexp_dp; // Global Fast Modular Exponentiation Dynamic Programming Memoization Look-up table.

static std::map<std::vector<cpp_int>, cpp_int> globl_fmexp_exp_dp;

// Key: vector<cpp_int> of 3 elements
// Value: (base**exp) % modulus

cpp_int fmexp_ori(cpp_int base, cpp_int exp, cpp_int modulus) {
    std::cerr << "FMEXP CALLED" << std::endl;
    const std::vector<cpp_int> current = {base, exp, modulus};
    if (globl_fmexp_dp.find(current) != globl_fmexp_dp.end()) {
        return globl_fmexp_dp[current];
    }
    const cpp_int original_exp = exp;
    std::map<cpp_int, cpp_int> bc; // the map key doesn't matter, because the indexes are cpp_int so the vector MAX_SIZE isn't limited // this is only for security and safety reason. Consider this map a vector for programming.
    cpp_int i = 0; // i is the digit placement
    while (exp != 0) {
        if (exp % 2 == 1) {
            bc[i] = i;
        } else { // exp % 2 == 0
            ; // nothing
        }
        i++;
        exp >>= 1;
    }
    /*
    for (auto ele: bc) {
        std::cerr << ele.second << std::endl;
    }
    */
    i-=1; // OFF BY 1 ERROR
    // we've got it
    cpp_int max_binary_exponent = cpb2(i);
    cpp_int k = 1; // current binary exponent
    std::map<cpp_int, cpp_int> dp;
    while (k <= max_binary_exponent) {
        const std::vector<cpp_int> this_time_info = {base, k, modulus};
        if (k == 1) {
            if (globl_fmexp_exp_dp.find(this_time_info) != globl_fmexp_exp_dp.end()) {
                dp[k] = globl_fmexp_exp_dp[this_time_info];
            } else {
                dp[k] = base % modulus;
                // globl
                globl_fmexp_exp_dp[this_time_info] = dp[k];
            }
        } else {
            assert(k%2==0);
            if (globl_fmexp_exp_dp.find(this_time_info) != globl_fmexp_exp_dp.end()) {
                dp[k] = globl_fmexp_exp_dp[this_time_info];
            } else {
                dp[k] = (dp[k/2] * dp[k/2]) % modulus;
                globl_fmexp_exp_dp[this_time_info] = dp[k];
            }
        }
        k <<= 1;
    }
    /*
    for (auto ele: dp) {
        std::cerr << ele.first << " : " << ele.second << std::endl;
    }
    */
    cpp_int product = 1;
    for (auto index : bc) {
        cpp_int id = index.second;
        product *= dp[cpb2(id)];
    }
    product = product % modulus;
    globl_fmexp_dp[current] = product;
    std::cerr << "FMEXP EXITING" << std::endl;
    return product;
}
#endif // FAST_MODULAR_EXP_HH
