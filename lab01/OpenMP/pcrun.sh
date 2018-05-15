#!/bin/bash
echo " "
gcc -fopenmp PrimeCnt.c -o PrimeCnt
echo "Thread Number :1 "
./PrimeCnt 1 1000
./PrimeCnt 1 10000
./PrimeCnt 1 100000
./PrimeCnt 1 500000
echo " "
echo "Thread Number :2 "
./PrimeCnt 2 1000
./PrimeCnt 2 10000
./PrimeCnt 2 100000
./PrimeCnt 2 500000
echo " "
echo "Thread Number :4 "
./PrimeCnt 4 1000
./PrimeCnt 4 10000
./PrimeCnt 4 100000
./PrimeCnt 4 500000
echo " "
echo "Thread Number :8 "
./PrimeCnt 8 1000
./PrimeCnt 8 10000
./PrimeCnt 8 100000
./PrimeCnt 8 500000