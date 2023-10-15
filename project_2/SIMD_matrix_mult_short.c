#include <emmintrin.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define N 4000 //Matrix size

void matrix_multiply_sse_short(short *A, short *B, short *C, int n) {
	
    if ((uintptr_t)A % 16 != 0 || (uintptr_t)B % 16 != 0 || (uintptr_t)C % 16 != 0) {
        fprintf(stderr, "Error: Matrices are not properly aligned.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j += 8) { //8 short elements per SSE register
            __m128i sum = _mm_setzero_si128();
            for (int k = 0; k < n; k++) {
                // Ensure proper memory alignment when loading
                __m128i a = _mm_loadu_si128((__m128i*)&A[i * n + k]);
                __m128i b = _mm_loadu_si128((__m128i*)&B[k * n + j]);
                sum = _mm_add_epi16(sum, _mm_mullo_epi16(a, b));
            }
            // Ensure proper memory alignment when storing
            _mm_storeu_si128((__m128i*)&C[i * n + j], sum);
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

    // Ensure that both dimensions are multiples of 8
    int aligned_n = (N + 7) & ~7; //8 short elements per SSE register

    // Allocate and initialize matrices A, B, and C
    short *A = (short *)_mm_malloc(aligned_n * aligned_n * sizeof(short), 16);
    short *B = (short *)_mm_malloc(aligned_n * aligned_n * sizeof(short), 16);
    short *C = (short *)_mm_malloc(aligned_n * aligned_n * sizeof(short), 16);

    if (A == NULL || B == NULL || C == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Initialize matrices within a reasonable range
    for (int i = 0; i < aligned_n * aligned_n; i++) {
        A[i] = rand() % 5;
        B[i] = rand() % 5;
    }

    // Perform matrix multiplication using SSE
    matrix_multiply_sse_short(A, B, C, aligned_n);

    // Print the result
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%d ", C[i * 5 + j]);
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
