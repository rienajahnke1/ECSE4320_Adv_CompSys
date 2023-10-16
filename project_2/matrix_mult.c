#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5000

void fillMatrix(float **matrix) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = (float)(rand() % 5);
        }
    }
}

void multiplyMatrices(float **A, float **B, float **result) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            result[i][j] = 0.0;
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
    float **matrixA = (float **)malloc(N * sizeof(float *));
    float **matrixB = (float **)malloc(N * sizeof(float *));
    float **resultMatrix = (float **)malloc(N * sizeof(float *));

    for (int i = 0; i < N; ++i) {
        matrixA[i] = (float *)malloc(N * sizeof(float));
        matrixB[i] = (float *)malloc(N * sizeof(float));
        resultMatrix[i] = (float *)malloc(N * sizeof(float));
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

    // Display the result
    printf("Result Matrix:\n");
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            printf("%f\t", resultMatrix[i][j]);
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
