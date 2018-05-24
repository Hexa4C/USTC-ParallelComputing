#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

#define VMAX 10

int main(int argc, char* argv[]) {
    int size, rank, tag = 1, *v, *cell, distance, *d, *origin_d;
    double p = 0.5, randnum;
    int i, j;
    int ncar = atoi(argv[1]);
    int cycles = atoi(argv[2]);
    char* path = argv[3];
    FILE *fp;
    fp = fopen(path, "w");
    int roadlen = 2 * VMAX * cycles;
    double start, end;
    double totaltime;
    cell = (int *) malloc (roadlen * sizeof(int));
    d = (int *)malloc(ncar * sizeof(int));
    origin_d = (int *)malloc(ncar * sizeof(int));
    v = (int *) malloc (ncar * sizeof(int));
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (rank == 0) {
        start = MPI_Wtime();
    }
    for (i = rank * ncar / size; i < rank * ncar / size + ncar / size; i ++) {
        d[i] = 0;
        origin_d[i] = 0;
        v[i] = 0;
    }
    for (i = rank * roadlen / size; i < rank * roadlen / size + roadlen / size; i ++) {
        cell[i] = 0;
    }
    if (size > 1) {
        for (i = 0; i < size; i ++) {
            MPI_Bcast(&d[i * ncar / size], ncar / size, MPI_INT, i, MPI_COMM_WORLD);
            MPI_Bcast(&v[i * ncar / size], ncar / size, MPI_INT, i, MPI_COMM_WORLD);
            MPI_Bcast(&cell[i * roadlen / size], roadlen / size, MPI_INT, i, MPI_COMM_WORLD);
        }
    }
    cell[0] = ncar;
    srand(rank);
    for (i = 0; i < cycles; i ++) {
        for (j = rank * ncar / size; j < rank * ncar / size + ncar / size; j ++) {
            if (v[j] < VMAX) {
                v[j] ++;
            }
            distance = 1;
            while (distance <= VMAX) {
                if (cell[d[j] + distance] > 0) {
                    break;
                }
                distance ++;
            }
            if (distance <= v[j]) {
                v[j] = distance - 1;
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
                MPI_Bcast(&d[j * ncar / size], ncar / size, MPI_INT, j, MPI_COMM_WORLD);
                MPI_Bcast(&v[j * ncar / size], ncar / size, MPI_INT, j, MPI_COMM_WORLD);
            }
        }
        for (j = 0; j < ncar; j ++) {
            cell[origin_d[j]] --;
            cell[d[j]] ++;
            origin_d[j] = d[j];
        }
    }
    if (rank == 0) {
        end = MPI_Wtime();
        for (i = 0; i < roadlen; i ++) {
            fprintf(fp, "%d,%d\n", i, cell[i]);
        }
        totaltime = end - start;
        printf("%lf", totaltime);
    }
    MPI_Finalize();
    return 0;
}