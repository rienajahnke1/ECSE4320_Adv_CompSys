#!/bin/bash
echo "*************testing dTLB load misses*********************"
perf stat -e cpu-clock,dTLB-loads-misses python3 ./mult_func.py 10000000
perf stat -e cpu-clock,dTLB-loads-misses python3 ./mult_func.py 10000000
perf stat -e cpu-clock,dTLB-loads-misses python3 ./mult_func.py 10000000
perf stat -e cpu-clock,dTLB-loads-misses python3 ./mult_func.py 10000000
