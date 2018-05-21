#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int size, rank, tag = 1;
    int i, j, recvi;
    double time = atof(argv[1]);
    double x, y, pi, recvpi, sum;
    double start, end;
    double totaltime;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    start = MPI_Wtime();
    i = 0;
    sum = 0;
    while(1){
        i++;
        x = rand() / (double)(RAND_MAX);
        y = rand() / (double)(RAND_MAX);
        if (x * x + y * y < 1) {
            sum ++;
        }
        if (i % 100 == 0)
        {
            end = MPI_Wtime();
            totaltime = (end - start);
            if (totaltime >= time)
            {
                break;
            }
        }
    }
    if (rank == 0)
    {
        for (j = 1; j < size; j++)
        {
            MPI_Recv(&recvi, 1, MPI_INT, j, tag, MPI_COMM_WORLD, &status);
            i += recvi;
        }
        printf("%d", i);
    }
    else
    {
        MPI_Send(&i, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}