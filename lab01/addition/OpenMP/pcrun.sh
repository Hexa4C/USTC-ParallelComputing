#!/bin/bash
gcc -fopenmp PrimeCnt.c -o PrimeCnt
echo -e "|0.01|\c"
./PrimeCnt 1 0.01
echo -e "|\c"
 ./PrimeCnt 2 0.01
echo -e "|\c"
 ./PrimeCnt 4 0.01
echo -e "|\c"
 ./PrimeCnt 8 0.01
echo -e "|\c"
echo ""
echo -e "|0.1|\c"
./PrimeCnt 1 0.1
echo -e "|\c"
./PrimeCnt 2 0.1
echo -e "|\c"
./PrimeCnt 4 0.1
echo -e "|\c"
./PrimeCnt 8 0.1
echo -e "|\c"
echo ""
echo -e "|1|\c"
./PrimeCnt 1 1
echo -e "|\c"
./PrimeCnt 2 1
echo -e "|\c"
./PrimeCnt 4 1
echo -e "|\c"
./PrimeCnt 8 1
echo -e "|\c"
echo ""
echo -e "|10|\c"
./PrimeCnt 1 10
echo -e "|\c"
./PrimeCnt 2 10
echo -e "|\c"
./PrimeCnt 4 10
echo -e "|\c"
./PrimeCnt 8 10
echo -e "|\c"
echo ""