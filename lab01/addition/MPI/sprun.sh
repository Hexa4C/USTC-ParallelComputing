#!/bin/bash
mpicc SolvePi.c -o SolvePi
echo -e "|0.01|\c"
mpirun -machinefile mf.txt -np 1 ./SolvePi 0.01
echo -e -e "|\c"
mpirun -machinefile mf.txt -np 2 ./SolvePi 0.01
echo -e -e "|\c"
mpirun -machinefile mf.txt -np 4 ./SolvePi 0.01
echo -e -e "|\c"
mpirun -machinefile mf.txt -np 8 ./SolvePi 0.01
echo -e -e "|\c"
echo ""
echo -e "|0.1|\c"
mpirun -machinefile mf.txt -np 1 ./SolvePi 0.1
echo -e "|\c"
mpirun -machinefile mf.txt -np 2 ./SolvePi 0.1
echo -e "|\c"
mpirun -machinefile mf.txt -np 4 ./SolvePi 0.1
echo -e "|\c"
mpirun -machinefile mf.txt -np 8 ./SolvePi 0.1
echo -e "|\c"
echo ""
echo -e "|1|\c"
mpirun -machinefile mf.txt -np 1 ./SolvePi 1
echo -e "|\c"
mpirun -machinefile mf.txt -np 2 ./SolvePi 1
echo -e "|\c"
mpirun -machinefile mf.txt -np 4 ./SolvePi 1
echo -e "|\c"
mpirun -machinefile mf.txt -np 8 ./SolvePi 1
echo -e "|\c"
echo ""
echo -e "|10|\c"
mpirun -machinefile mf.txt -np 1 ./SolvePi 10
echo -e "|\c"
mpirun -machinefile mf.txt -np 2 ./SolvePi 10
echo -e "|\c"
mpirun -machinefile mf.txt -np 4 ./SolvePi 10
echo -e "|\c"
mpirun -machinefile mf.txt -np 8 ./SolvePi 10
echo -e "|\c"
echo ""