#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 5000
#define BLOCK_SIZE 64

void matrixMultiply(short **A, short **B, int **C) {
    for (int i = 0; i < N; i += BLOCK_SIZE) {
        for (int j = 0; j < N; j += BLOCK_SIZE) {
            for (int k = 0; k < N; k += BLOCK_SIZE) {
                // Perform block matrix multiplication
                for (int ii = i; ii < i + BLOCK_SIZE && ii < N; ii++) {
                    for (int jj = j; jj < j + BLOCK_SIZE && jj < N; jj++) {
                        int sum = 0;

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

// Function to initialize a matrix with random short integers
void initializeMatrix(short **matrix) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = rand() % 32768;  // random short integer
        }
    }
}

// Function to allocate memory for a matrix of short integers
short** allocateShortMatrix() {
    short** matrix = (short**)malloc(N * sizeof(short*));
    for (int i = 0; i < N; i++) {
        matrix[i] = (short*)malloc(N * sizeof(short));
    }
    return matrix;
}

// Function to allocate memory for a matrix of integers
int** allocateIntMatrix() {
    int** matrix = (int**)malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++) {
        matrix[i] = (int*)malloc(N * sizeof(int));
    }
    return matrix;
}

double get_elapsed_time(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) + 1e-9 * (end.tv_nsec - start.tv_nsec);
}

// Function to free memory for a matrix
void freeShortMatrix(short** matrix) {
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to free memory for a matrix of integers
void freeIntMatrix(int** matrix) {
    for (int i = 0; i < N; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    short** A = allocateShortMatrix();
    short** B = allocateShortMatrix();
    int** C = allocateIntMatrix();

    // Initialize matrices A and B with random short integers
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

    // Print a small portion of the result (C matrix)
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    // Free allocated memory
    freeShortMatrix(A);
    freeShortMatrix(B);
    freeIntMatrix(C);

    return 0;
}
