#include <stdio.h>
#include <time.h>

#define M 4 
#define N 3
#define P 3

int matrix1[M][N] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {3, 4, 5}};
int matrix2[N][P] = {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}};
int result[M][P];

int main() {
    int i, j, k;
    clock_t start, end;
    double elapsed_time;

    // Matrix multiplication
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
    elapsed_time = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Print resulting matrix
    printf("Resulting matrix:\n");
    for (i = 0; i < M; i++) {
        for (j = 0; j < P; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    printf("Elapsed time: %f seconds\n", elapsed_time);

    return 0;
}
