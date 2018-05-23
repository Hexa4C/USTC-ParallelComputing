#!/bin/bash
mpicc trafficSimAll0.c -o trafficSimAll0
echo -e "|100000 / 2000|\c"
mpirun -machinefile mf.txt -np 1 ./trafficSimAll0 100000 2000
echo -e "|\c"
mpirun -machinefile mf.txt -np 2 ./trafficSimAll0 100000 2000
echo -e "|\c"
mpirun -machinefile mf.txt -np 4 ./trafficSimAll0 100000 2000
echo -e "|\c"
mpirun -machinefile mf.txt -np 8 ./trafficSimAll0 100000 2000
echo -e "|\c"
echo ""
echo -e "|500000 / 500|\c"
mpirun -machinefile mf.txt -np 1 ./trafficSimAll0 500000 500
echo -e "|\c"
mpirun -machinefile mf.txt -np 2 ./trafficSimAll0 500000 500
echo -e "|\c"
mpirun -machinefile mf.txt -np 4 ./trafficSimAll0 500000 500
echo -e "|\c"
mpirun -machinefile mf.txt -np 8 ./trafficSimAll0 500000 500
echo -e "|\c"
echo ""
echo -e "|1000000 / 300|\c"
mpirun -machinefile mf.txt -np 1 ./trafficSimAll0 1000000 300
echo -e "|\c"
mpirun -machinefile mf.txt -np 2 ./trafficSimAll0 1000000 300
echo -e "|\c"
mpirun -machinefile mf.txt -np 4 ./trafficSimAll0 1000000 300
echo -e "|\c"
mpirun -machinefile mf.txt -np 8 ./trafficSimAll0 1000000 300
echo -e "|\c"
echo ""