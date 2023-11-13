#include <stdio.h>
#include <string.h>
#include <immintrin.h>

/*
int count_and_find_indices(const int* encoded_data, int search_key, int* indices, int dataSize, int search_key_len) {
    int matches = 0;

    // Ensure proper alignment for AVX2
    __m256i key_chunk = _mm256_set1_epi32(search_key);

    // Iterate over the encoded data with SIMD integer comparison
    for (int i = 0; i <= dataSize - search_key_len; ++i) {
        // Ensure proper alignment for AVX2
        __m256i data_chunk = _mm256_load_si256((__m256i*)(encoded_data + i));

        // Compare the chunks
        __m256i compare_result = _mm256_cmpeq_epi32(data_chunk, key_chunk);

        // Check if all elements are equal
        if (_mm256_testz_si256(compare_result, compare_result)) {
            indices[matches] = i;
            matches++;
        }
    }

    return matches;
}
*/

int find_indices(const char* encoded_data, const char* compressed_key, int* indices, int dataSize) {
    int matches = 0;

    // Iterate over the encoded data
    for (int i = 0; i < dataSize; ++i) {
        // Check if the compressed key matches the current position in the encoded data
        if (memcmp(encoded_data + i, compressed_key, strlen(compressed_key)) == 0) {
            indices[matches] = i;
            matches++;
        }
    }

    return matches;
}


