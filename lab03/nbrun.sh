#!/bin/bash
mpicc NBodySim.c -o NBodySim -lm
echo -e "|64|\c"
mpirun -machinefile mf.txt -np 1 ./NBodySim 64 1000
echo -e "|\c"
mpirun -machinefile mf.txt -np 2 ./NBodySim 64 1000
echo -e "|\c"
mpirun -machinefile mf.txt -np 4 ./NBodySim 64 1000
echo -e "|\c"
#mpirun -machinefile mf.txt -np 8 ./NBodySim 64 1000
#echo -e "|\c"
echo ""
echo -e "|256|\c"
mpirun -machinefile mf.txt -np 1 ./NBodySim 256 1000
echo -e "|\c"
mpirun -machinefile mf.txt -np 2 ./NBodySim 256 1000
echo -e "|\c"
mpirun -machinefile mf.txt -np 4 ./NBodySim 256 1000
#echo -e "|\c"
#mpirun -machinefile mf.txt -np 8 ./NBodySim 256 1000
echo -e "|\c"
echo ""