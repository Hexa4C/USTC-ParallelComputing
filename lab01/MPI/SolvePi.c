#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int size, rank, tag = 1;
    int i, j;
    int N = atoi(argv[1]);
    double *local, *tmp, pi, w, recvpi;
    double start, end;
    double totaltime;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0)
    {
        start = MPI_Wtime();
    }
    w = 1.0 / N;
    local = (double *)malloc(N / size * sizeof(double));
    tmp = (double *)malloc(N / size * sizeof(double));
    pi = 0;
    for (i = 0; i < N / size; i ++) {
        local[i] = (i * size + rank + 0.5) * w;
        tmp[i] = 4.0 / (1.0 + local[i] * local[i]);
        pi += tmp[i];
    }
    pi = pi * w;
    if (rank == 0) {
        for (i = 1; i < size; i++)
        {
            MPI_Recv(&recvpi, 1, MPI_DOUBLE, i, tag, MPI_COMM_WORLD, &status);
            pi += recvpi;
        }
        end = MPI_Wtime();
        totaltime = (end - start);
        printf("The value of pi is %.12lf\n", pi);
        printf("the time cost is %lfs\n", totaltime);
    }
    else {
        MPI_Send(&pi, 1, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}