#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SIZE 500

int main() {
    int i, j, k;
    int matrix1[SIZE][SIZE], matrix2[SIZE][SIZE], result[SIZE][SIZE];

    // Initialize matrices with random values
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            matrix1[i][j] = rand() % 10;
            matrix2[i][j] = rand() % 10;
        }
    }

    // Matrix multiplication with OpenMP
    double start_time = omp_get_wtime();
    #pragma omp parallel for private(i,j,k) shared(matrix1,matrix2,result)
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            result[i][j] = 0;
            for (k = 0; k < SIZE; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    double end_time = omp_get_wtime();

    // Print resulting matrix
    printf("Resulting matrix:\n");
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    printf("Elapsed time: %f seconds\n", end_time - start_time);

    return 0;
}
