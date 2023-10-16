#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000
#define BLOCK_SIZE 32

void matrixMultiply(float **A, float **B, float **C) {
    for (int i = 0; i < N; i += BLOCK_SIZE) {
        for (int j = 0; j < N; j += BLOCK_SIZE) {
            for (int k = 0; k < N; k += BLOCK_SIZE) {
                // Perform block matrix multiplication
                for (int ii = i; ii < i + BLOCK_SIZE && ii < N; ii++) {
                    for (int jj = j; jj < j + BLOCK_SIZE && jj < N; jj++) {
                        float sum = 0.0f;

                        for (int kk = k; kk < k + BLOCK_SIZE && kk < N; kk++) {
                            sum += A[ii][kk] * B[kk][jj];
                        }

                        C[ii][jj] += sum;
                    }
                }
            }
        }
    }
}

// Function to initialize a matrix with random values
void initializeMatrix(float **matrix) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = (float)rand() / RAND_MAX;  // random float between 0 and 1
        }
    }
}

// Function to allocate memory for a matrix
float** allocateMatrix() {
    float** matrix = (float**)malloc(N * sizeof(float*));
    for (int i = 0; i < N; i++) {
        matrix[i] = (float*)malloc(N * sizeof(float));
    }
    return matrix;
}

double get_elapsed_time(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) + 1e-9 * (end.tv_nsec - start.tv_nsec);
}

// Function to free memory for a matrix
void freeMatrix(float** matrix) {
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    float** A = allocateMatrix();
    float** B = allocateMatrix();
    float** C = allocateMatrix();

    // Initialize matrices A and B with random values
    initializeMatrix(A);
    initializeMatrix(B);
    
    // Start the timer
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);

    // Perform matrix multiplication
    matrixMultiply(A, B, C);

    // Stop the timer
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double elapsed_time = get_elapsed_time(start_time, end_time);

    // Display the elapsed time
    printf("Elapsed Time: %.4f seconds\n", elapsed_time);

    // Print the result (C matrix)
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%f ", C[i][j]);
        }
        printf("\n");
    }
    
    // Free allocated memory
    freeMatrix(A);
    freeMatrix(B);
    freeMatrix(C);

    return 0;
}
