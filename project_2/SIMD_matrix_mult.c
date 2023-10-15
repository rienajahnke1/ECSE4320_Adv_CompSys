#include <emmintrin.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define N 1000 //Matrix size

void matrix_multiply_sse(float *A, float *B, float *C, int n) {
	
    if ((uintptr_t)A % 16 != 0 || (uintptr_t)B % 16 != 0 || (uintptr_t)C % 16 != 0) {
        fprintf(stderr, "Error: Matrices are not properly aligned.\n");
        return;
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j += 4) {
            __m128 sum = _mm_setzero_ps();
            for (int k = 0; k < n; k++) {
                // Ensure proper memory alignment when loading
                __m128 a = _mm_loadu_ps(&A[i * n + k]);
                __m128 b = _mm_loadu_ps(&B[k * n + j]);
                sum = _mm_add_ps(sum, _mm_mul_ps(a, b));
            
            }
            // Ensure proper memory alignment when storing
            _mm_store_ps(&C[i * n + j], sum);       
        }
    }
}

double get_elapsed_time(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) + 1e-9 * (end.tv_nsec - start.tv_nsec);
}

int main() {
	// Start the timer
    struct timespec start_time, end_time;
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    
    // Ensure that both dimensions are multiples of 4
    int aligned_n = (N + 3) & ~3;

    // Allocate and initialize matrices A, B, and C
    float *A = (float *)_mm_malloc(aligned_n * aligned_n * sizeof(float), 16);
    float *B = (float *)_mm_malloc(aligned_n * aligned_n * sizeof(float), 16);
    float *C = (float *)_mm_malloc(aligned_n * aligned_n * sizeof(float), 16);

    if (A == NULL || B == NULL || C == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize matrices within a reasonable range
    for (int i = 0; i < aligned_n; i++) {
        for (int j = 0; j < aligned_n; j++) {
            A[i * aligned_n + j] = rand() % 5;  // Values between 0 and 5
            B[i * aligned_n + j] = rand() % 5;  
        }
    }
    
    // Perform matrix multiplication using SSE
    matrix_multiply_sse(A, B, C, aligned_n);

    // Print the result first five
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%f ", C[i * 5 + j]);
        }
        printf("\n");
    }
    
     // Stop the timer
    clock_gettime(CLOCK_MONOTONIC, &end_time);
    double elapsed_time = get_elapsed_time(start_time, end_time);
    
    // Display the elapsed time
    printf("Elapsed Time: %.4f seconds\n", elapsed_time);

    // Free allocated memory
    _mm_free(A);
    _mm_free(B);
    _mm_free(C);

    return 0;
}
