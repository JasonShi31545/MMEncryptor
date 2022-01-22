#!/bin/bash

if [ -f "./mme.out" ]
then
    ./mme.out -k;
    ./mme.out -c;
    ./mme.out -o;
    ./mme.out -p;
    ./mme.out -b;
    ./mme.out -m;
    ./mme.out -b;
    ./mme.out -a;
else
    make final;
    ./debug.sh
fi