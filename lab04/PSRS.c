#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

int comp(const void *p, const void *q) {
    return (*(int *)p - *(int *)q);
}

int main(int argc, char* argv[]){
    int size, rank, tag = 1;
    int N = atoi(argv[1]);
    int i, j;
    int *a, *sample, *pivot, *psize, *pstart;
    int *chunk_start, *chunk_length, data_idx;
    int *recv_start, *recv_length, *recv_buffer;
    int *indice, wtag = 0, min, min_idx, *sorted_part, idx, *result;
    int *send_len, local_len, *send_start;
    double start, end;
    a = (int *)malloc(N * sizeof(int));
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    psize = (int *)malloc(size * sizeof(int));
    pstart = (int *)malloc(size * sizeof(int));
    pstart[0] = 0;
    for (i = 0; i < size - 1; i ++) {//分片，决定每个片的大小和开始位置
        psize[i] = N / size;
        pstart[i + 1] = pstart[i] + psize[i];
    }
    psize[size - 1] = N - (size - 1) * (N / size);
    if (rank == 0) {//生成随机数
        for (i = 0; i < N; i ++) {
            a[i] = rand() % 100;
        }
        /*for (i = 0; i < N; i ++) {
            printf("%d  ", a[i]);
        }
        printf("\n");*/
    }
    else {
        for (i = 0; i < N; i ++) {
            a[i] = 0;
        }
    }

    if (rank == 0) {//发送分片
        start = MPI_Wtime();
        for (i = 1; i < size; i ++) {
            MPI_Send(&a[pstart[i]], psize[i], MPI_INT, i, tag, MPI_COMM_WORLD);
        }
    }
    else {
        MPI_Recv(&a[pstart[rank]], psize[rank], MPI_INT, 0, tag, MPI_COMM_WORLD, &status);
    }
    tag++;
    qsort(&a[pstart[rank]], psize[rank], sizeof(int), comp); //局部排序

    if (rank == 0) {
        sample = (int *)malloc(size * size * sizeof(int));
    }
    else {
        sample = (int *)malloc(size * sizeof(int));
    }
    for (i = 0; i < size; i ++) {//正则采样
        sample[i] = a[pstart[rank] + i * psize[rank] / size];
    }

    pivot = (int *)malloc((size - 1) * sizeof(int));
    if (rank == 0) {
        for (i = 1; i < size; i ++) {//接收采样结果
            MPI_Recv(&sample[size * i], size, MPI_INT, i, tag, MPI_COMM_WORLD, &status);
        }
        qsort(sample, size * size, sizeof(int), comp);//采样排序
        for (i = 1; i < size; i ++) {//选择主元
            pivot[i - 1] = sample[i * size];
        }
    }
    else {//将采样结果发送给root
        MPI_Send(sample, size, MPI_INT, 0, tag, MPI_COMM_WORLD);
    }
    tag ++;
    MPI_Bcast(pivot, size - 1, MPI_INT, 0, MPI_COMM_WORLD);//广播主元

    chunk_start = (int *)malloc(size * sizeof(int));
    chunk_length = (int *)malloc(size * sizeof(int));
    data_idx = pstart[rank];
    for (i = 0; i < size - 1; i ++) {//主元划分，计算划分块的起始索引和长度
        chunk_start[i] = data_idx;
        chunk_length[i] = 0;
        while(((rank < size && data_idx < pstart[rank + 1]) || data_idx < N) && (a[data_idx] <= pivot[i])) {
            chunk_length[i] ++;
            data_idx ++;
        }
    }
    chunk_start[size - 1] = data_idx;
    if (rank < size - 1) {
        chunk_length[size - 1] = pstart[rank + 1] - data_idx;
    }
    else {
        chunk_length[size - 1] = N - data_idx;
    }

    recv_start = (int *) malloc(size * sizeof(int));
    recv_length = (int *) malloc (size * sizeof(int));
    recv_buffer = (int *)malloc(N * sizeof(int));
    memset(recv_buffer, 0, N);
    for (i = 0; i < size; i ++) {//全局交换
        MPI_Gather(&chunk_length[i], 1, MPI_INT, recv_length, 1, MPI_INT, i, MPI_COMM_WORLD);
        if (rank == i) {
            recv_start[0] = 0;
            for (j = 0; j < size; j ++) {
                recv_start[j] = recv_start[j - 1] + recv_length[j - 1];
            }
        }
        MPI_Gatherv(&a[chunk_start[i]], chunk_length[i], MPI_INT, recv_buffer, recv_length, recv_start, MPI_INT, i, MPI_COMM_WORLD);
    }

    indice = (int *) malloc(size * sizeof(int));
    sorted_part = (int*)malloc(N * sizeof(int));
    for (i = 0; i < size; i ++) {
        indice[i] = recv_start[i];
    }
    idx = 0;
    while(! wtag) {//归并排序
        for (i = 0; i < size; i ++) {
            if (indice[i] < recv_start[i] + recv_length[i]) {
                min = recv_buffer[indice[i]];
                min_idx = i;
                break;
            }
        }
        for (i = 0; i < size; i ++) {
            if (indice[i] < recv_start[i] + recv_length[i] && recv_buffer[indice[i]] < min) {
                min = recv_buffer[indice[i]];
                min_idx = i;
            }
        }
        sorted_part[idx] = min;
        indice[min_idx] ++;
        wtag = 1;
        for (i = 0; i < size; i ++) {
            if (indice[i] < recv_start[i] + recv_length[i]) {
                wtag = 0;
                break;
            }
        }
        idx ++;
    }

    if (rank == 0) {
        send_len = (int *)malloc(size * sizeof(int));
        send_start = (int *) malloc(size * sizeof(int));
        local_len = recv_start[size - 1] + recv_length[size - 1];
        result = (int *)malloc(N * sizeof(int));
    }
    local_len = recv_start[size - 1] + recv_length[size - 1];
    MPI_Gather(&local_len, 1, MPI_INT, send_len, 1, MPI_INT, 0, MPI_COMM_WORLD);//将归并后的片的长度信息告诉root
    if (rank == 0) {
        send_start[0] = 0;
        for (i = 1; i < size; i ++) {
            send_start[i] = send_start[i - 1] + send_len[i - 1];
        }
    }

    MPI_Gatherv(sorted_part, local_len, MPI_INT, result, send_len, send_start, MPI_INT, 0, MPI_COMM_WORLD);//收集归并结果
    if (rank == 0) {
        end = MPI_Wtime();
        /*for (i = 0; i < N; i ++) {
            printf("%d  ", result[i]);
        }
        printf("\n");*/
        printf("%lf", end - start);
    }
    if (rank == 0) {
        free(send_len);
        free(send_start);
        free(result);
    }
    free(a);
    free(sample);
    free(pivot);
    free(chunk_start);
    free(chunk_length);
    free(recv_buffer);
    free(recv_length);
    free(recv_start);
    free(indice);
    free(sorted_part);
    MPI_Finalize();
    return 0;
}