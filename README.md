# MMEncryptor

## NOTE

**THIS PROJECT IS DEPRECATED. A NEW VERSION WILL BE WRITTEN AND RELEASE SOON ON GITHUB...**





Multimedia Encryptor is an encrypted communication program written completely from scratch (with some specific functions from Crypto++)

A command line client for RSA and AES message encryption. Reads and creates keys and use sophisticated cipher systems to ensure security

## Build dependencies

<!--
[//]: # (Depending on each version of Linux, the packages are named differently)
[//]: # (### Linux)
[//]: # (* libboost-random-dev (1.74.0.3 or above)
[//]: # (* libboost-thread-dev (1.74.0.3 or above)
[//]: # (* libssl-dev (1.1.1 or above)
[//]: # (* libgmp-dev (6.2.1 or above)
[//]: # (* libcrypto++-dev (8.4 or above)
-->

### Linux

Different distributions name and document their packages differently. 

Make sure every package is development enabled and statically-linkable. 

Make sure the boost library is installed with random and threading as additional dependencies. 

You will need the SSL (or OpenSSL) libraries, the GMP libraries, the Crypto++ libraries as dependencies. 

Its better to statically compile the Crypto++ library from source to prevent any problems with staitc links. (See More in: <a href="./CRYPTOPP.md">this document</a>)

# Instructions to Build

type ```make final``` in the source directory

# Other Information

The source code is licensed under the GNU Public License Version 3.
The license is carried with the source in in the `LICENSE` file.
Copyright (C) Jason Shi 2021-2022
