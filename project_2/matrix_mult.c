#include <stdio.h>

#define ROW_A 3
#define COL_A 2
#define ROW_B 2
#define COL_B 4

void multiplyMatrices(int A[ROW_A][COL_A], int B[ROW_B][COL_B], int result[ROW_A][COL_B]) {
    int i, j, k;

    // Initialize the result matrix to 0
    for (i = 0; i < ROW_A; ++i) {
        for (j = 0; j < COL_B; ++j) {
            result[i][j] = 0;
        }
    }

    // Perform matrix multiplication
    for (i = 0; i < ROW_A; ++i) {
        for (j = 0; j < COL_B; ++j) {
            for (k = 0; k < COL_A; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void printMatrix(int matrix[ROW_A][COL_B]) {
    int i, j;
    for (i = 0; i < ROW_A; ++i) {
        for (j = 0; j < COL_B; ++j) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int matrixA[ROW_A][COL_A] = {{1, 2},
                                 {3, 4},
                                 {5, 6}};

    int matrixB[ROW_B][COL_B] = {{7, 8, 9, 10},
                                 {11, 12, 13, 14}};

    int resultMatrix[ROW_A][COL_B];

    // Perform multiplication
    multiplyMatrices(matrixA, matrixB, resultMatrix);

    // Display the result
    printf("Result Matrix:\n");
    printMatrix(resultMatrix);

    return 0;
}
