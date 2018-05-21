#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

//#define N 100

int main(int argc, char *argv[])
{
    int result = 0, i, j, number, rank, size;
    int np = atoi(argv[1]);
    int N = atoi(argv[2]);
    double start, end;
    omp_set_num_threads(np);
    size = np;
    start = omp_get_wtime();
    #pragma omp parallel for default(shared) private(rank, number, i, j) reduction(+:result)
    for (rank = 0; rank < size; rank ++) {
        for (i = 0; i < N / size; i++) {
            number = i + rank * N / size;
            if (number == 0 || number == 1) {
                continue;
            }
            for (j = 2; j < number / 2; j++) {
                if (number % j == 0) {
                    break;
                }
            }
            if (j >= number / 2) {
                result ++;
            }
        }
    }
    end = omp_get_wtime();
    //printf("The number of prime numbers between 0 and %d is %d\n", N, result);
    //printf("the time cost is %lfs\n", end - start);
    printf("%lf", end - start);
    return 0;
}