#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

#define VMAX 20

int main(int argc, char* argv[]) {
    int size, rank, tag = 1, *v;
    long *d, distance;
    double p = 0.5, randnum;
    int i, j;
    int ncar = atoi(argv[1]);
    int cycles = atoi(argv[2]);
    d = (long *)malloc(ncar * sizeof(long));
    v = (int *) malloc (ncar * sizeof(int));
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    for (j = rank * ncar / size; j < rank * ncar / size + ncar / size; j ++) {
        d[j] = rand() % (VMAX / 2) + (VMAX / 2) * j;
        v[j] = 0;
    }
    if (size > 1) {
        for (j = 0; j < size; j ++) {
            MPI_Bcast(&d[j * ncar / size], ncar / size, MPI_LONG, j, MPI_COMM_WORLD);
            MPI_Bcast(&v[j * ncar / size], ncar / size, MPI_INT, j, MPI_COMM_WORLD);
        }
    }
    for (i = 0; i < cycles; i ++) {
        for (j = rank * ncar / size; j < rank * ncar / size + ncar / size; j ++) {
            if (j == ncar - 1 && v[j] < VMAX) {
                v[j] ++;
            }
            else if (j != ncar - 1) {
                if (v[j] < VMAX) {
                    v[j] ++;
                }
                distance = d[j + 1] - d[j];
                if (distance <= v[j]) {
                    v[j] = distance - 1;
                }
            }
            randnum = rand() / (double)RAND_MAX;
            if (randnum < p) {
                if (v[j] > 0) {
                    v[j]--;
                }
            }
            d[j] += v[j];
        }
        if (size > 1) {
            for (j = 0; j < size; j ++) {
                MPI_Bcast(&d[j * ncar / size], ncar / size, MPI_LONG, j, MPI_COMM_WORLD);
                MPI_Bcast(&v[j * ncar / size], ncar / size, MPI_INT, j, MPI_COMM_WORLD);
            }
        }
    }
    if (rank == 0) {
        for (i = 0; i < ncar; i ++) {
            if (i > 0 && d[i] - d[i - 1] > 1) {
                printf("\n");
            }
            printf("%ld ", d[i]);
        }
        printf("\n");
    }
    MPI_Finalize();
    return 0;
}