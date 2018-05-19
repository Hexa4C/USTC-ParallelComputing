#!/bin/bash
echo " "
mpicc PrimeCnt.c -o PrimeCnt
echo "Thread Number :1 "
mpirun -machinefile mf.txt -np 1 ./PrimeCnt 0.01
mpirun -machinefile mf.txt -np 1 ./PrimeCnt 0.1
mpirun -machinefile mf.txt -np 1 ./PrimeCnt 1
mpirun -machinefile mf.txt -np 1 ./PrimeCnt 10
echo " "
echo "Thread Number :2 "
mpirun -machinefile mf.txt -np 2 ./PrimeCnt 0.01
mpirun -machinefile mf.txt -np 2 ./PrimeCnt 0.1
mpirun -machinefile mf.txt -np 2 ./PrimeCnt 1
mpirun -machinefile mf.txt -np 2 ./PrimeCnt 10
echo " "
echo "Thread Number :4 "
mpirun -machinefile mf.txt -np 4 ./PrimeCnt 0.01
mpirun -machinefile mf.txt -np 4 ./PrimeCnt 0.1
mpirun -machinefile mf.txt -np 4 ./PrimeCnt 1
mpirun -machinefile mf.txt -np 4 ./PrimeCnt 10
echo " "
echo "Thread Number :8 "
mpirun -machinefile mf.txt -np 8 ./PrimeCnt 0.01
mpirun -machinefile mf.txt -np 8 ./PrimeCnt 0.1
mpirun -machinefile mf.txt -np 8 ./PrimeCnt 1
mpirun -machinefile mf.txt -np 8 ./PrimeCnt 10