#!/bin/bash
mpicc trafficSimAll0.c -o trafficSimAll0
echo -e "|100000 / 2000|\c"
mpirun -machinefile mf.txt -np 1 ./trafficSimAll0 100000 2000 status11.csv
echo -e "|\c"
mpirun -machinefile mf.txt -np 2 ./trafficSimAll0 100000 2000 status12.csv
echo -e "|\c"
mpirun -machinefile mf.txt -np 4 ./trafficSimAll0 100000 2000 status14.csv
echo -e "|\c"
mpirun -machinefile mf.txt -np 8 ./trafficSimAll0 100000 2000 status18.csv
echo -e "|\c"
echo ""
echo -e "|500000 / 500|\c"
mpirun -machinefile mf.txt -np 1 ./trafficSimAll0 500000 500 status21.csv
echo -e "|\c"
mpirun -machinefile mf.txt -np 2 ./trafficSimAll0 500000 500 status22.csv
echo -e "|\c"
mpirun -machinefile mf.txt -np 4 ./trafficSimAll0 500000 500 status24.csv
echo -e "|\c"
mpirun -machinefile mf.txt -np 8 ./trafficSimAll0 500000 500 status28.csv
echo -e "|\c"
echo ""
echo -e "|1000000 / 300|\c"
mpirun -machinefile mf.txt -np 1 ./trafficSimAll0 1000000 300 status31.csv
echo -e "|\c"
mpirun -machinefile mf.txt -np 2 ./trafficSimAll0 1000000 300 status32.csv
echo -e "|\c"
mpirun -machinefile mf.txt -np 4 ./trafficSimAll0 1000000 300 status34.csv
echo -e "|\c"
mpirun -machinefile mf.txt -np 8 ./trafficSimAll0 1000000 300 status38.csv
echo -e "|\c"
echo ""