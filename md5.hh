/*#ifndef MD5_HH
#define MD5_HH
#include "aux.hh"
#include <openssl/md5.h>


int main()
{
    unsigned char MD5result[16];
    std::string src = "aabbccddee";
    std::string md5 = ""; 
    std::string md5_16 = ""; 
    char temp[33] = {}; 
    MD5((const unsigned char*)src.c_str(), src.size(), MD5result);

    for(int i = 0; i < 16; ++i)
    {   
        snprintf(temp, 10, "%02x", MD5result[i]);
        md5 += temp;
        if(i >= 4 && i <= 11) 
            md5_16 += temp;
    }   
    printf("src:%s\nmd5 32位:%s\nmd5 16位:%s\n", src.c_str(), md5.c_str(), md5_16.c_str());                                                                                                                                                                           
    return 0;
}
//g++ -g -o openssl_md5 openssl_md5.cpp -I/usr/include/openssl -lssl -lcrypto -L/usr/lib64
#endif // MD5_HH
*/
