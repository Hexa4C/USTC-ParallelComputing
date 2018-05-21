#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define chunck 10000

int main(int argc, char* argv[]) {
    int size, rank, tag = 1;
    int result = 0, recvi = 0, i, j, number, chuncknum = 0, brktag = 0;
    double start, end;
    double totaltime;
    double time = atof(argv[1]);
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    start = MPI_Wtime();
    while(1) {
        for (i = 0; i < chunck / size; i ++) {
            number = i + rank * chunck / size + chunck * chuncknum;
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
            if (i % 100 == 0)
            {
                end = MPI_Wtime();
                totaltime = (end - start);
                if (totaltime >= time)
                {
                    brktag = 1;
                    break;
                }
            }
        }
        if (brktag) {
            i = i + chuncknum * chunck / size;
            break;
        }
        chuncknum ++;
    }
    if (rank == 0) {
        for (j = 1; j < size; j++)
        {
            MPI_Recv(&recvi, 1, MPI_INT, j, tag, MPI_COMM_WORLD, &status);
            i += recvi;
        }
        printf("%d", i);
    }
    else {
        MPI_Send(&i, 1, MPI_INT, 0, tag, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}