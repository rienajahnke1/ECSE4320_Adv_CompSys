import os
import timeit

MEMORY_DEVICE = "/proc/memory"
DATA_SIZE = 10000 * 1024  # xKB

def write_to_memory():
    data = bytearray(DATA_SIZE)

    with open(MEMORY_DEVICE, "wb") as f:
        f.write(data)

def read_from_memory():
    with open(MEMORY_DEVICE, "rb") as f:
        data = f.read()
    return data

write_time = timeit.timeit(write_to_memory, number=1)
print(f"Write time: {write_time:.6f} seconds")

read_time = timeit.timeit(read_from_memory, number=1)
print(f"Read time: {read_time:.6f} seconds")
