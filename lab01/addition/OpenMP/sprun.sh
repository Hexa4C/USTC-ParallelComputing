#!/bin/bash
gcc -fopenmp SolvePi.c -o SolvePi
echo -e "|0.01|\c"
./SolvePi 1 0.01
echo -e "|\c"
 ./SolvePi 2 0.01
echo -e "|\c"
 ./SolvePi 4 0.01
echo -e "|\c"
 ./SolvePi 8 0.01
echo -e "|\c"
echo ""
echo -e "|0.1|\c"
./SolvePi 1 0.1
echo -e "|\c"
./SolvePi 2 0.1
echo -e "|\c"
./SolvePi 4 0.1
echo -e "|\c"
./SolvePi 8 0.1
echo -e "|\c"
echo ""
echo -e "|1|\c"
./SolvePi 1 1
echo -e "|\c"
./SolvePi 2 1
echo -e "|\c"
./SolvePi 4 1
echo -e "|\c"
./SolvePi 8 1
echo -e "|\c"
echo ""
echo -e "|10|\c"
./SolvePi 1 10
echo -e "|\c"
./SolvePi 2 10
echo -e "|\c"
./SolvePi 4 10
echo -e "|\c"
./SolvePi 8 10
echo -e "|\c"
echo ""