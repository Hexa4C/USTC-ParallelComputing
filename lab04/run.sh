#!/bin/bash
mpicc PSRS.c -o PSRS -lm
echo -e "|1000000|\c"
mpirun -machinefile mf.txt -np 1 ./PSRS 1000000
echo -e "|\c"
mpirun -machinefile mf.txt -np 2 ./PSRS 1000000
echo -e "|\c"
mpirun -machinefile mf.txt -np 4 ./PSRS 1000000
echo -e "|\c"
mpirun -machinefile mf.txt -np 8 ./PSRS 1000000
echo -e "|\c"
echo ""
echo -e "|2000000|\c"
mpirun -machinefile mf.txt -np 1 ./PSRS 2000000
echo -e "|\c"
mpirun -machinefile mf.txt -np 2 ./PSRS 2000000
echo -e "|\c"
mpirun -machinefile mf.txt -np 4 ./PSRS 2000000
echo -e "|\c"
mpirun -machinefile mf.txt -np 8 ./PSRS 2000000
echo -e "|\c"
echo ""
echo -e "|4000000|\c"
mpirun -machinefile mf.txt -np 1 ./PSRS 4000000
echo -e "|\c"
mpirun -machinefile mf.txt -np 2 ./PSRS 4000000
echo -e "|\c"
mpirun -machinefile mf.txt -np 4 ./PSRS 4000000
echo -e "|\c"
mpirun -machinefile mf.txt -np 8 ./PSRS 4000000
echo -e "|\c"
echo ""
echo -e "|8000000|\c"
mpirun -machinefile mf.txt -np 1 ./PSRS 8000000
echo -e "|\c"
mpirun -machinefile mf.txt -np 2 ./PSRS 8000000
echo -e "|\c"
mpirun -machinefile mf.txt -np 4 ./PSRS 8000000
echo -e "|\c"
mpirun -machinefile mf.txt -np 8 ./PSRS 8000000
echo -e "|\c"
echo ""