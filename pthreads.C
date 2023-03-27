#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define M 4 
#define N 3
#define P 3
#define NUM_THREADS 2

int mat1[M][N] = {{5, 6, 7}, {8, 9, 1}, {2, 3, 4}, {6, 5, 4}};
int mat2[N][P] = {{4, 5, 6}, {9, 8, 7}, {1, 2, 3}};
int result[M][P];

pthread_barrier_t barrier;

typedef struct {
    int thread_id;
} thread_args;

void *multiply(void *arg) {
    thread_args *args = (thread_args*)arg;
    int thread_id = args->thread_id;
    int start_row = thread_id * (M / NUM_THREADS);
    int end_row = (thread_id + 1) * (M / NUM_THREADS);

    for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < P; j++) {
            for (int k = 0; k < N; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }

    pthread_barrier_wait(&barrier);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    thread_args args[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    struct timespec start_time, end_time;
    double elapsed_time;

    pthread_barrier_init(&barrier, NULL, NUM_THREADS);

    // Create threads to calculate matrix multiplication
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        args[i].thread_id = i;
        pthread_create(&threads[i], NULL, multiply, (void*)&args[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    clock_gettime(CLOCK_MONOTONIC, &end_time);

    // Calculate and print elapsed time
    elapsed_time = (end_time.tv_sec - start_time.tv_sec) +
                   (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
    printf("Elapsed time: %f seconds\n", elapsed_time);

    // Print resulting matrix
    printf("Resulting matrix:\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < P; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    pthread_barrier_destroy(&barrier);
    return 0;
}
