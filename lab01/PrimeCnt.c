#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int size, rank, tag = 1;
    int result = 0, recvresult = 0, i, j, primetag, number;
    clock_t start, end;
    double totaltime;
    int N = atoi(argv[1]);
    start = clock();
    for (i = 1; i <= N; i++)
    {
        number = i;
        if (number == 1)
        {
            continue;
        }
        primetag = 1;
        for (j = 2; j < number / 2; j++)
        {
            if (number % j == 0)
            {
                primetag = 0;
            }
        }
        if (primetag)
        {
            result++;
        }
    }
    end = clock();
    totaltime = (end - start) / CLOCKS_PER_SEC;
    printf("The numberb of prime numbers between 0 and %d is %d\n", N, result);
    printf("the time cost is %lfs\n", totaltime);
    return 0;
}