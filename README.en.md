# MMEncryptor

Multimedia Encryptor is an encrypted communication program written completely from scratch (with some specific functions from Crypto++)

A command line client for RSA and AES message encryption. Reads and creates keys and use sophisticated cipher systems to ensure security

## Build dependencies

### Linux
* libboost-random-dev (1.74.0.3 or above)
* libboost-thread-dev (1.74.0.3 or above)
* libssl-dev (1.1.1 or above)
* libgmp-dev (6.2.1 or above)
* libcrypto++-dev (8.4 or above) See [CRYPTOPP.md](./CRYPTOPP.md)

#### Windows Binary from Linux

For building binaries for Windows, along with the above mentioned Linux dependencies, you would also need:

* mingw compiler suite: mingw-w64

# Instructions to Build

type ```make final``` in the source directory


```mme.out``` or ```mme.exe``` should be compiled and linked in the source directory.
