# PROJECT FOUR: Implementaion of Dictionary Codec

## Introduction
In this project, I will implement dictionary codec by first encoding a raw column data file then creating a query of it. Dictionary encoding is used to compress data with relatively low cardinality and speed up search/scan operations. The dictionary encoding code will support multi-threading for faster read time and the encoded data column will use integer compression to further reduce the footprint on the SSD. The encoded query code will support the use of SIMD instructions to speed up the search/scan.


## Encoding
To encode the data, I first played around with diffrent multi-threading techniques in python to see which process is the most efficent. The tests ran below was against a 241.6MB file. I could not use the 1GB file to benchmark becuase some teqniuqes could not handle the size of the file and return a "Killed" error. All failed files are in folder "failed_encoding".

<img width="500" alt="image" src="https://github.com/rienajahnke1/ECSE4320_Adv_CompSys/assets/57211117/7724c2ae-1f79-4fa5-bcaa-a4016ffa5524">

**Dask**:

Dask is a parallel computing library that enables parallel and distributed computing. It primarily relies on task parallelism rather than data parallelism. This means it breaks down computations into smaller tasks that can then be excuted independently. Dask was unfortunatily the slowest performer and took 40.373 seconds to run the 241MB file. It also had a "Killed" error when the 1GB file was used. This could be from human error, were I did not implement the function in the best way, or because of background computing Dask is running that could slow down excution. Dask also relies on the Python Global Interpreter Lock (GIL) which can limit CPU-bound tasks.

**Multiprocessing**

The Multiprocessing modual in python works by making each process run in its own python interpreter and has its own memory space, allowing parallel execution of tasks on different CPU cores. I chose to work with this modual because unlike Dask and threading, it is not bound by the GIL, enabling tru parallelism for CPU bound tasks. This means you can take advantage of the multiple cores in your computer. The downside of multiprocessing is that task parallelism can be more complex and not as efficient, which can slow down computing large datasets. It took 40.081 seconds for multiprocessing to execute the 241MB file, which is very close to Dask, and the second slowest option.

**Threading**
