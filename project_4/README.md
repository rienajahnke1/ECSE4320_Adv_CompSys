# PROJECT FOUR: Implementaion of Dictionary Codec

## Introduction
In this project, I will implement dictionary codec by first encoding a raw column data file then creating a query of it. Dictionary encoding is used to compress data with relatively low cardinality and speed up search/scan operations. The dictionary encoding code will support multi-threading for faster read time and the encoded data column will use integer compression to further reduce the footprint on the SSD. The encoded query code will support the use of SIMD instructions to speed up the search/scan.


## Encoding
To encode the data, I first played around with diffrent multi-threading techniques in python to see which process is the most efficent. The tests ran below was against a 241.6MB file. I could not use the 1GB file to benchmark becuase some teqniuqes could not handle the size of the file and return a "Killed" error. All failed files are in folder "failed_encoding".

<img width="500" alt="image" src="https://github.com/rienajahnke1/ECSE4320_Adv_CompSys/assets/57211117/3abe97dc-5724-45ff-a608-bbd0e2ea1e38">


**<ins>Dask</ins>**

Dask is a parallel computing library that enables parallel and distributed computing. It primarily relies on task parallelism rather than data parallelism. This means it breaks down computations into smaller tasks that can then be excuted independently. Dask was unfortunatily the slowest performer and took 40.373 seconds to run the 241MB file. It also had a "Killed" error when the 1GB file was used. This could be from human error, were I did not implement the function in the best way, or because of background computing Dask is running that could slow down excution. Dask also relies on the Python Global Interpreter Lock (GIL) which can limit CPU-bound tasks.

**<ins>Multiprocessing</ins>**

The dask.multiprocessing modual in python works by making each process run in its own python interpreter and has its own memory space, allowing parallel execution of tasks on different CPU cores. I chose to work with this modual because unlike Dask threading, it is not bound by the GIL, enabling tru parallelism for CPU bound tasks. This means you can take advantage of the multiple cores in your computer. The downside of multiprocessing is that task parallelism can be more complex and not as efficient, which can slow down computing large datasets. It took 40.081 seconds for multiprocessing to execute the 241MB file, which is very close to Dask, and the second slowest option.

**<ins>Threading</ins>**

The Threading modual in python is used to create and manage threads. It allows for concurrent execution of tasks, making it useful for I/O bound operations. The issue with using the basic threading modual is that in CPython, the default implementation of Python, there is a Global Interpreter Lock (GIL) that allows only one thread excutes Python bytecode at a time. This means it is not suitible for achieveing true parallelism in CPU bound tasks. With that said, it is a straight forward modual with no extra processing happening in the background, which is why I think it did better than Dask with 28.549 seconds to execute the 241MB file. Though it was faster, it still failed when the 1GB file was attempted.

**<ins>Processpool</ins>**

After the failed attempts, I looked into the concurrent.futures module for asynchronous execution of functions. The ProcessPoolExecutor withen concurrent.futures utilizes a pool of working processes for parallel execution. Because each process runs on its own interpreter, it allows for parallelism without the GIL. The downside to this is overhead may arrise when creating and managing seperate processes. All in all, it was significantly better than the Dask modual and the second best at 17.533 seconds when running the 241MB file. Though it was faster, it still failed when the 1GB file was attempted.

**<ins>Threadpool</ins>**

The concurrent.futures modual seemed to be the right path so I tried ThreadPoolExecutor, another implementation of the executor interface. Instead of the ProcessPool, ThreadPool creates a pool of worker threads to execute tasks concurrently, but is now subjected to the GIL. I used the "map" method to execute the encoding function over the values. Threadpool was the only technique that could handle the 1GB file and executed the 241MB file the fastest at 2.534 seconds. 



  **Conclusion:** 
I chose to use the Pandas Dataframe for the dictionary because of its ease of use, vectorized operations and integration with numpy (might use in query part). This made it easier to combine the encoded results onto a single dataframe and save the dictionary on a csv file and the encoded data on a feather file. A feather file is a binary columnar data storage format file type which was the best choice for storing the large integer encoded dataset. This is because each column is stored together and has memory mapped I/O, allowing fast access to data and higher performance. The integer compression modual I used was varint - a method of encoding integers using a variable number of bytes. It uses fewer bytes to represent smaller numbers and is often used in data serialization where compactness is important. That is why I chose varint and becuase of it's ease of use.

## Query

To Query the encoded data file against the dictionary, I first take in the desired string to search, check if it exisits in the dictionary, use the same encoding teqnique as above (varint), then use the encoded value to find all the indecies 
