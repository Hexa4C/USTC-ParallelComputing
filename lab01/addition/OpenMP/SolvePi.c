#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i, *iters, iteration = 0;
    int sum, x, y, pi;
    int np = atoi(argv[1]);
    double time = atof(argv[2]);
    double start, end, totaltime;
    int rank, size = np;
    iters = (int *)malloc(np * sizeof(int));
    omp_set_num_threads(np);
    start = omp_get_wtime();
    #pragma omp parallel for default(shared) private(rank, end, totaltime, i) reduction(+:sum)
    for (rank = 0; rank < size; rank ++) {
        i = 0;
        while(1) {
            i ++;
            x = rand() / (double)(RAND_MAX);
            y = rand() / (double)(RAND_MAX);
            if (x * x + y * y < 1) {
                sum ++;
            }
            if (i % 100 == 0)
            {
                end = omp_get_wtime();
                totaltime = (end - start);
                if (totaltime >= time)
                {
                    break;
                }
            }
        }
        iters[rank] = i;
    }
    for (i = 0; i < size; i ++) {
        iteration += iters[i];
    }
    printf("%d", iteration);
    return 0;
}