# search_functions.pyx
# This is the Cython file

# cython: language_level=3

import cython
from libc.string cimport memcmp
from libc.stdlib cimport malloc, free
from cython.parallel cimport parallel
cimport numpy as np
from cpython.array cimport array, clone

# Function to find a string in the dictionary
cpdef int find_in_dictionary(str search_string, list dictionary):
    for i, value in enumerate(dictionary):
        if search_string == value:
            return i
    return -1  # Not found

# Function to count occurrences and find indices using SIMD
cpdef count_and_find_indices(bytes encoded_data, str search_key, int[:] indices, int[:] occurrences):
    cdef int dataSize = len(encoded_data)
    cdef int search_key_len = len(search_key)
    cdef int matches = 0

    with nogil, parallel():
        for i in range(dataSize - search_key_len + 1):
            if memcmp(&encoded_data[i], search_key, search_key_len) == 0:
                indices[matches] = i
                matches += 1

    occurrences[0] = matches
