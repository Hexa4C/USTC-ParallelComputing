#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<time.h>

#define N 1000000
#define SIZE 100000

int main(){
	int a, b, l;
	int count = 0;
	int i;
	double headx, heady, tailx, taily, theta, dx, dy, p, pi;
	clock_t start, finish;
	double totaltime;
	a = 10;
	b = 10;
	l = 10;
	start = clock();
	for (i = 0; i < N; i ++) {
		headx = (double)(rand() % 1000) / 1000 + (int)(rand() % SIZE);
		heady = (double)(rand() % 1000) / 1000 + (int)(rand() % SIZE);
		theta = (double)(rand() % 360);
		dx = sin(theta * M_PI / 360);
		dy = cos(theta * M_PI / 360);
		tailx = headx + dx * l;
		taily = heady + (((int)rand() & 2) - 1) * dy * l;
		while (tailx < 0 || tailx > SIZE || taily < 0 || taily > SIZE ) {
			theta = (double)(rand() % 360);
			dx = sin(theta * M_PI / 360);
			dy = cos(theta * M_PI / 360);
			tailx = headx + dx * l;
			taily = heady + (((int)rand() & 2) - 1) * dy * l;
		}
		if ((int)(headx / a) == (int)(tailx / a) && (int)(heady / b) == (int)(taily / b)) {
			count++;
		}
	}
	finish = clock();
	totaltime = (double)(finish-start)/CLOCKS_PER_SEC;
	p = (double)(N - count) / N;
	//printf("p(l, a, b) = %lf\n", p);
	pi = (2 * l * (a + b) - l * l) / (a * b * p);
	printf("pi = %lf\n", pi);
	printf("time = %lfs\n", totaltime);
	return 0;
}