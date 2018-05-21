#!/bin/bash
mpicc PrimeCnt.c -o PrimeCnt
echo -e "|0.01|\c"
mpirun -machinefile mf.txt -np 1 ./PrimeCnt 0.01
echo -e "|\c"
mpirun -machinefile mf.txt -np 2 ./PrimeCnt 0.01
echo -e "|\c"
mpirun -machinefile mf.txt -np 4 ./PrimeCnt 0.01
echo -e "|\c"
mpirun -machinefile mf.txt -np 8 ./PrimeCnt 0.01
echo -e "|\c"
echo ""
echo -e "|0.1|\c"
mpirun -machinefile mf.txt -np 1 ./PrimeCnt 0.1
echo -e "|\c"
mpirun -machinefile mf.txt -np 2 ./PrimeCnt 0.1
echo -e "|\c"
mpirun -machinefile mf.txt -np 4 ./PrimeCnt 0.1
echo -e "|\c"
mpirun -machinefile mf.txt -np 8 ./PrimeCnt 0.1
echo -e "|\c"
echo ""
echo -e "|1|\c"
mpirun -machinefile mf.txt -np 1 ./PrimeCnt 1
echo -e "|\c"
mpirun -machinefile mf.txt -np 2 ./PrimeCnt 1
echo -e "|\c"
mpirun -machinefile mf.txt -np 4 ./PrimeCnt 1
echo -e "|\c"
mpirun -machinefile mf.txt -np 8 ./PrimeCnt 1
echo -e "|\c"
echo ""
echo -e "|10|\c"
mpirun -machinefile mf.txt -np 1 ./PrimeCnt 10
echo -e "|\c"
mpirun -machinefile mf.txt -np 2 ./PrimeCnt 10
echo -e "|\c"
mpirun -machinefile mf.txt -np 4 ./PrimeCnt 10
echo -e "|\c"
mpirun -machinefile mf.txt -np 8 ./PrimeCnt 10
echo -e "|\c"
echo ""