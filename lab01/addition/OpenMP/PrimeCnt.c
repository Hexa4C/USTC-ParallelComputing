#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

#define chunck 10000

int main(int argc, char *argv[])
{
    int result = 0, i, j, number, *iters, iteration = 0, chuncknum = 0, brktag = 0;
    int np = atoi(argv[1]);
    double time = atof(argv[2]);
    double start, end, totaltime;
    int rank, size = np;
    iters = (int *) malloc (np * sizeof(int));
    for (i = 0; i < size; i ++) {
        iters[i] = 0;
    }
    omp_set_num_threads(np);
    start = omp_get_wtime();
    #pragma omp parallel for default(shared) private(rank, number, i, j) reduction(+:result)
    for (rank = 0; rank < size; rank ++) {
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
                    end = omp_get_wtime();
                    totaltime = (end - start);
                    if (totaltime >= time)
                    {
                        brktag = 1;
                        break;
                    }
                }
            }
            if (brktag) {
                iters[rank] = i + chuncknum * chunck / size;
                break;
            }
            chuncknum ++;
        }
    }
    for (i = 0; i < size; i ++) {
        iteration += iters[i];
    }
    printf("%d", iteration);
    return 0;
}