#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define M 500
#define N 500
#define P 500
#define NUM_THREADS 4

int matrix1[M][N], matrix2[N][P], result[M][P];

struct thread_data {
    int thread_id;
    int start_row;
    int end_row;
};

void *multiply_matrices(void *arg) {
    struct thread_data *data = (struct thread_data *)arg;
    int start_row = data->start_row;
    int end_row = data->end_row;
    int i, j, k;

    for (i = start_row; i < end_row; i++) {
        for (j = 0; j < P; j++) {
            result[i][j] = 0;
            for (k = 0; k < N; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    pthread_exit(NULL);
}

int main() {
    int i, j;
    pthread_t threads[NUM_THREADS];
    struct thread_data thread_data_array[NUM_THREADS];
    clock_t start, end;
    double cpu_time_used;

    // Initialize matrices with random values
    srand(time(NULL));
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            matrix1[i][j] = rand() % 10;
        }
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < P; j++) {
            matrix2[i][j] = rand() % 10;
        }
    }

    // Multiply matrices using pthreads
    start = clock();
    int chunk_size = M / NUM_THREADS;
    for (i = 0; i < NUM_THREADS; i++) {
        thread_data_array[i].thread_id = i;
        thread_data_array[i].start_row = i * chunk_size;
        thread_data_array[i].end_row = (i == NUM_THREADS - 1) ? M : (i + 1) * chunk_size;
        pthread_create(&threads[i], NULL, multiply_matrices, (void *)&thread_data_array[i]);
    }
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    // Print resulting matrix
    printf("Resulting matrix:\n");
    for (i = 0; i < M; i++) {
        for (j = 0; j < P; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    printf("Time taken by pthreads: %lf seconds\n", cpu_time_used);

    return 0;
}
