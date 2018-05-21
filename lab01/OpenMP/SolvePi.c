#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i;
    double local, tmp, pi, w;
    int np = atoi(argv[1]);
    int N = atoi(argv[2]);
    double start, end;
    omp_set_num_threads(np);
    w = 1.0 / N;
    pi = 0;
    start = omp_get_wtime();
    #pragma omp parallel for default(shared) private(i, local, tmp) reduction(+ : pi)
    for (i = 0; i < N; i++)
    {
        local = (i + 0.5) * w;
        tmp = 4.0 / (1.0 + local * local);
        pi += tmp;
    }
    end = omp_get_wtime();
    pi = pi * w;
    //printf("The value of pi is %.12lf\n", pi);
    //printf("the time cost is %lfs\n", end - start);
    printf("%lf", end - start);
    return 0;
}