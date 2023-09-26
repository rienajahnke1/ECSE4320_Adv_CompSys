#!/bin/bash
echo "*************Next four sets repeat instructions*********************"
perf stat -e cpu-clock,L1-dcache-load-misses python3 ./mult_func.py 100000
perf stat -e cpu-clock,L1-dcache-load-misses python3 ./mult_func.py 200000
perf stat -e cpu-clock,L1-dcache-load-misses python3 ./mult_func.py 300000
perf stat -e cpu-clock,L1-dcache-load-misses python3 ./mult_func.py 600000
echo "*************next three sets don't repeat instructions***************"
perf stat -e cpu-clock,L1-dcache-load-misses python3 ./mult_func.py 600000
perf stat -e cpu-clock,L1-dcache-load-misses python3 ./mult_func.py 600000
perf stat -e cpu-clock,L1-dcache-load-misses python3 ./mult_func.py 600000
