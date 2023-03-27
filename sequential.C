#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define M 500
#define N 500
#define P 500

int matrix1[M][N];
int matrix2[N][P];
int result[M][P];

int main() {
    int i, j, k;
    clock_t start, end;
    double elapsed_time;

    // Initialize random seed
    srand(time(NULL));

    // Fill matrix1 and matrix2 with random values
    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j++) {
            matrix1[i][j] = rand() % 100;
        }
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < P; j++) {
            matrix2[i][j] = rand() % 100;
        }
    }

    // Perform matrix multiplication
    start = clock();
    for (i = 0; i < M; i++) {
        for (j = 0; j < P; j++) {
            result[i][j] = 0;
            for (k = 0; k < N; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    end = clock();

    // Print resulting matrix
    printf("Resulting matrix:\n");
    for (i = 0; i < M; i++) {
        for (j = 0; j < P; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    // Calculate and print elapsed time
    elapsed_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Elapsed time: %lf seconds\n", elapsed_time);

    return 0;
}
