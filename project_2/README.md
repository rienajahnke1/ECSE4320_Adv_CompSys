# Course Project #2: Matrix-Matrix Multiplication

In this design project, I will use C moduals to carry out high speed matrix-matrix multiplication by explicitly utilizing multiple threads, x86 SIMD instructions (SSE) and techniques to minimize cache miss rate via restructuring data access patterns.





## Multi-threading

pthread_matrix_mult.c is the C file that incorperates multi-threading techniques to optimize run-time

Thread number set to 24 becuase my CPU has 24 threads and no hyper-threading

Command line arguments "FLOAT" and "SHORT" are used to run the file

Graph of Matrix Size vs Run Time (s) 


<img width="374" alt="image" src="https://github.com/rienajahnke1/ECSE4320_Adv_CompSys/assets/57211117/5f25c485-15ec-4560-89b5-6e3a64fa6c3b">


The time exponentially increases with size and the float runs slightly faster than the short.

## x86 SIMD Instructions (SSE)

SIMD_matrix_mult_float.c and SIMD_matrix_mult_short.c are the C files that incorperates SIMD instructions (SSE) to optimize run-time


SSE allows performing the same operation on multiple data elements simultaneously. For example, SSE can operate on four single-precision floating-point numbers (float) or eight 8-bit integers in parallel.

Graph of Matrix Size vs Run Time (s) 




## Cache Access Optimization

cache_miss_opt_float.c and cache_miss_opt_short.c are the C files that incorperate cache access optimization


Loop blocking is a technique used in algorithms to enhance cache optimization. It involves breaking the computation into smaller, contiguous blocks or tiles, which are then loaded into the cache. 

Graph of Matrix Size vs Run Time (s) 

