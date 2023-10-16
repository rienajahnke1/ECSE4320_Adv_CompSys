#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#define N 5000
#define thread_num 24

typedef int MatrixElement;  // Default to integer

MatrixElement matrixA[N][N];
MatrixElement matrixB[N][N];
MatrixElement resultMatrix[N][N];

struct ThreadData {
    int thread_id;
    int start_row;
    int end_row;
};

void *multiply(void *thread_arg) {
    struct ThreadData *data = (struct ThreadData *)thread_arg;
    int start_row = data->start_row;
    int end_row = data->end_row;

    for (int i = start_row; i < end_row; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                resultMatrix[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }

    pthread_exit(NULL);
}

double get_elapsed_time(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) + 1e-9 * (end.tv_nsec - start.tv_nsec);
}

int main(int argc, char *argv[]) {
    // Check if the command-line argument is provided and set the matrix element type
    if (argc > 1) {
        if (strcmp(argv[1], "FLOAT") == 0) {
            printf("Using 4-byte float for matrix elements\n");
            typedef float MatrixElement;
        } else if (strcmp(argv[1], "SHORT") == 0) {
            printf("Using 2-byte fixed point for matrix elements\n");
            typedef short MatrixElement;
        } else {
            printf("Unknown argument. Using default (integer) for matrix elements\n");
        }
    } else {
        printf("No argument provided. Using default (integer) for matrix elements\n");
    }

    // Initialize matrices with random values
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrixA[i][j] = rand() % 5;  // Initialize as float or fixed point based on the argument
            matrixB[i][j] = rand() % 5;  // Initialize as float or fixed point based on the argument
        }
    }

    // Start the timer
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_REALTIME, &start_time);

    // Create pthreads
    pthread_t threads[thread_num];
    struct ThreadData thread_data[thread_num];

    int rows_per_thread = N / thread_num;
    int start_row = 0;
    int end_row;

    for (int i = 0; i < thread_num; ++i) {
        end_row = start_row + rows_per_thread;

        thread_data[i].thread_id = i;
        thread_data[i].start_row = start_row;
        thread_data[i].end_row = end_row;

        pthread_create(&threads[i], NULL, multiply, (void *)&thread_data[i]);

        start_row = end_row;
    }

    for (int i = 0; i < thread_num; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Stop the timer
    clock_gettime(CLOCK_REALTIME, &end_time);
    double elapsed_time = get_elapsed_time(start_time, end_time);

    // Display the result
    printf("Result Matrix:\n");
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            printf("%d\t", resultMatrix[i][j]);
        }
        printf("\n");
    }

    // Display the elapsed time
    printf("Elapsed Time: %.4f seconds\n", elapsed_time);

    return 0;
}
