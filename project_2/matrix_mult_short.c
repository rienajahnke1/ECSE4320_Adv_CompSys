#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 2000

void fillMatrix(short **matrix) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = (short)(rand() % 5);
        }
    }
}

void multiplyMatrices(short **A, short **B, int **result) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            result[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

double get_elapsed_time(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) + 1e-9 * (end.tv_nsec - start.tv_nsec);
}

int main() {
    // Allocate memory for matrices
    short **matrixA = (short **)malloc(N * sizeof(short *));
    short **matrixB = (short **)malloc(N * sizeof(short *));
    int **resultMatrix = (int **)malloc(N * sizeof(int *));

    for (int i = 0; i < N; ++i) {
        matrixA[i] = (short *)malloc(N * sizeof(short));
        matrixB[i] = (short *)malloc(N * sizeof(short));
        resultMatrix[i] = (int *)malloc(N * sizeof(int));
    }

    // Fill matrices with random values
    fillMatrix(matrixA);
    fillMatrix(matrixB);

    // Start the timer
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_REALTIME, &start_time);

    // Perform multiplication
    multiplyMatrices(matrixA, matrixB, resultMatrix);

    // Stop the timer
    clock_gettime(CLOCK_REALTIME, &end_time);
    double elapsed_time = get_elapsed_time(start_time, end_time);

    // Display the result (you might want to comment this out for large matrices)
    printf("Result Matrix:\n");
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            printf("%d\t", resultMatrix[i][j]);
        }
        printf("\n");
    }

    // Display the elapsed time
    printf("Elapsed Time: %.4f seconds\n", elapsed_time);

    // Free allocated memory
    for (int i = 0; i < N; ++i) {
        free(matrixA[i]);
        free(matrixB[i]);
        free(resultMatrix[i]);
    }
    free(matrixA);
    free(matrixB);
    free(resultMatrix);

    return 0;
}
