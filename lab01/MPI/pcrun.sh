#!/bin/bash
echo " "
mpicc PrimeCnt.c -o PrimeCnt
echo "Thread Number :1 "
mpirun -machinefile mf.txt -np 1 ./PrimeCnt 1000
mpirun -machinefile mf.txt -np 1 ./PrimeCnt 10000
mpirun -machinefile mf.txt -np 1 ./PrimeCnt 100000
mpirun -machinefile mf.txt -np 1 ./PrimeCnt 500000
echo " "
echo "Thread Number :2 "
mpirun -machinefile mf.txt -np 2 ./PrimeCnt 1000
mpirun -machinefile mf.txt -np 2 ./PrimeCnt 10000
mpirun -machinefile mf.txt -np 2 ./PrimeCnt 100000
mpirun -machinefile mf.txt -np 2 ./PrimeCnt 500000
echo " "
echo "Thread Number :4 "
mpirun -machinefile mf.txt -np 4 ./PrimeCnt 1000
mpirun -machinefile mf.txt -np 4 ./PrimeCnt 10000
mpirun -machinefile mf.txt -np 4 ./PrimeCnt 100000
mpirun -machinefile mf.txt -np 4 ./PrimeCnt 500000
echo " "
echo "Thread Number :8 "
mpirun -machinefile mf.txt -np 8 ./PrimeCnt 1000
mpirun -machinefile mf.txt -np 8 ./PrimeCnt 10000
mpirun -machinefile mf.txt -np 8 ./PrimeCnt 100000
mpirun -machinefile mf.txt -np 8 ./PrimeCnt 500000