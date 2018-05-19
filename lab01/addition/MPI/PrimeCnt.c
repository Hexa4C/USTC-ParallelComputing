#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int size, rank, tag = 1;
    int result = 0, recvi = 0, i, j, number;
    double start, end;
    double totaltime;
    double time = atof(argv[1]);
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    start = MPI_Wtime();
    for (i = 0; ; i ++) {
        number = i * size + rank;
        if (number == 0 || number == 1) {
            continue;
        }
        for (j = 2; j < number / 2; j ++) {
            if (number % j == 0) {
                break;
            }
        }
        if (j >= number / 2) {
            result ++;
        }
        end = MPI_Wtime();
        totaltime = (end - start);
        if (totaltime >= time) {
            break;
        }
    }
    if (rank == 0) {
        for (j = 1; j < size; i++)
        {
            MPI_Recv(&recvi, 1, MPI_INT, j, tag, MPI_COMM_WORLD, &status);
            i += recvi;
        }
        printf("timecost: %lfs\n", time);
        printf("iterations: %d\n", i);
    }
    else {
        MPI_Send(&i, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
    }
    MPI_Finalize();return 0;
}