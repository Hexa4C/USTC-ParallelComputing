#!/bin/bash
echo " "
mpicc SolvePi.c -o SolvePi
echo "Thread Number :1 "
mpirun -machinefile mf.txt -np 1 ./SolvePi 1000
mpirun -machinefile mf.txt -np 1 ./SolvePi 10000
mpirun -machinefile mf.txt -np 1 ./SolvePi 50000
mpirun -machinefile mf.txt -np 1 ./SolvePi 100000
echo " "
echo "Thread Number :2 "
mpirun -machinefile mf.txt -np 2 ./SolvePi 1000
mpirun -machinefile mf.txt -np 2 ./SolvePi 10000
mpirun -machinefile mf.txt -np 2 ./SolvePi 50000
mpirun -machinefile mf.txt -np 2 ./SolvePi 100000
echo " "
echo "Thread Number :4 "
mpirun -machinefile mf.txt -np 4 ./SolvePi 1000
mpirun -machinefile mf.txt -np 4 ./SolvePi 10000
mpirun -machinefile mf.txt -np 4 ./SolvePi 50000
mpirun -machinefile mf.txt -np 4 ./SolvePi 100000
echo " "
echo "Thread Number :8 "
mpirun -machinefile mf.txt -np 8 ./SolvePi 1000
mpirun -machinefile mf.txt -np 8 ./SolvePi 10000
mpirun -machinefile mf.txt -np 8 ./SolvePi 50000
mpirun -machinefile mf.txt -np 8 ./SolvePi 100000