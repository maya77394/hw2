#include <stdio.h>
#include <omp.h>

#define M 4 
#define N 3
#define P 3

int matrix1[M][N] = {{5, 6, 7}, {8, 9, 1}, {2, 3, 4}, {6, 5, 4}};
int matrix2[N][P] = {{4, 5, 6}, {9, 8, 7}, {1, 2, 3}};
int result[M][P];

int main() {
    int i, j, k;
    double start_time, end_time, elapsed_time;

    // Matrix multiplication with OpenMP
    start_time = omp_get_wtime();
    #pragma omp parallel for private(i,j,k) shared(matrix1,matrix2,result)
    for (i = 0; i < M; i++) {
        for (j = 0; j < P; j++) {
            result[i][j] = 0;
            for (k = 0; k < N; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
    end_time = omp_get_wtime();

    elapsed_time = end_time - start_time;
    printf("time: %f seconds\n", elapsed_time);
    // Print resulting matrix
    printf("Resulting matrix:\n");
    for (i = 0; i < M; i++) {
        for (j = 0; j < P; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    


    return 0;
}
