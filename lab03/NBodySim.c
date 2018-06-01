#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define G 6.67e-11
#define delta_t 1e-3

int N;

void compute_force (double *x, double *y, int bid, double *fx, double *fy) {
    int i, x0 = x[bid], y0 = y[bid];
    double r, sumx = 0, sumy = 0, cosine, sine;
    for (i = 0; i < N; i ++) {
        if (i == bid) {
            continue;
        }
        r = sqrtl((x[i] - x0) * (x[i] - x0) + (y[i] - y0) * (y[i] - y0));
        cosine = (x[i] - x0) / r;
        sine = (y[i] - y0) / r;
        if ( r < 2) {
            r = 2;
        }
        sumx += G * cosine / (r * r);
        sumy += G * sine / (r * r);
    }
    fx[bid] = sumx;
    fy[bid] = sumy;
}

void compute_velocities (double *vx, double *vy, double *fx, double *fy, int bid) {
    vx[bid] += fx[bid] * delta_t;
    vy[bid] += fy[bid] * delta_t;
}

void compute_positions (double *x, double *y, double *vx, double *vy, int bid) {
    x[bid] += vx[bid] * delta_t;
    y[bid] += vy[bid] * delta_t;
}

int main(int argc, char* argv[]) {
    int size, rank, tag = 1;
    int len;
    int i, j;
    double *x, *y, *fx, *fy, *vx, *vy;
    double start, end;
    int steps = atoi(argv[2]);
    N = atoi(argv[1]);
    len = sqrt(N);
    x = (double *)malloc(N * sizeof(double));
    y = (double *)malloc(N * sizeof(double));
    fx = (double *)malloc(N * sizeof(double));
    fy = (double *)malloc(N * sizeof(double));
    vx = (double *)malloc(N * sizeof(double));
    vy = (double *)malloc(N * sizeof(double));
    for (i = 0; i < N; i ++) {
        vx[i] = 0;
        vy[i] = 0;
        x[i] = i % len;
        y[i] = i / len;
    }
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    if (0 == rank) {
        start = MPI_Wtime();
    }
    for (i = 0; i < steps; i ++) {
        for (j = N / size * rank; j < N / size; j ++) {
            compute_force(x, y, j, fx, fy);
            compute_velocities(vx, vy, fx, fy, j);
            compute_positions(x, y, vx, vy, j);
        }
        if (size > 1) {
            for (j = 0; j < size; j ++) {
                MPI_Bcast(&x[N / size * j], N / size, MPI_DOUBLE, j, MPI_COMM_WORLD);
                MPI_Bcast(&y[N / size * j], N / size, MPI_DOUBLE, j, MPI_COMM_WORLD);
                MPI_Bcast(&vx[N / size * j], N / size, MPI_DOUBLE, j, MPI_COMM_WORLD);
                MPI_Bcast(&vy[N / size * j], N / size, MPI_DOUBLE, j, MPI_COMM_WORLD);
                MPI_Bcast(&fx[N / size * j], N / size, MPI_DOUBLE, j, MPI_COMM_WORLD);
                MPI_Bcast(&fy[N / size * j], N / size, MPI_DOUBLE, j, MPI_COMM_WORLD);
            }
        }
    }
    if (0 == rank) {
        end = MPI_Wtime();
        printf("%lf", end - start);
    }
    MPI_Finalize();
    return 0;
}