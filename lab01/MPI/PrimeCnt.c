#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

//#define N 100

int main(int argc, char* argv[]) {
    int size, rank, tag = 1;
    int result = 0, recvresult = 0, i, j, number;
    double start, end;
    double totaltime;
    int N = atoi(argv[1]);
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0) {
        start = MPI_Wtime();
    }
    for (i = 0; i < N /size; i ++) {
        number = i + rank * N / size;
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
    }
    if (rank == 0) {
        for (i = 1; i < size; i++)
        {
            MPI_Recv(&recvresult, 1, MPI_INT, i, tag, MPI_COMM_WORLD, &status);
            result += recvresult;
        }
        end = MPI_Wtime();
        totaltime = (end - start);
        //printf("The number of prime numbers between 0 and %d is %d\n", N, result);
        //printf("the time cost is %lfs\n", totaltime);
        printf("%lf", totaltime);
    }
    else {
        MPI_Send(&result, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
    }
    MPI_Finalize();return 0;
}