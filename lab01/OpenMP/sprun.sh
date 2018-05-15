#!/bin/bash
echo " "
gcc -fopenmp SolvePi.c -o SolvePi
echo "Thread Number :1 "
./SolvePi 1 1000
./SolvePi 1 10000
./SolvePi 1 50000
./SolvePi 1 100000
echo " "
echo "Thread Number :2 "
./SolvePi 2 1000
./SolvePi 2 10000
./SolvePi 2 50000
./SolvePi 2 100000
echo " "
echo "Thread Number :4 "
./SolvePi 4 1000
./SolvePi 4 10000
./SolvePi 4 50000
./SolvePi 4 100000
echo " "
echo "Thread Number :8 "
./SolvePi 8 1000
./SolvePi 8 10000
./SolvePi 8 50000
./SolvePi 8 100000