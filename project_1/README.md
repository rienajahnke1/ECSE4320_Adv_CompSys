For parts one, two and three, I am running this experiment against a Windows OS, AMD Ryzen 5 PRO 4650U which has 192KB in L1 cache, 3MB in L2 cache and 8MB in L3 cache.

Parts four and five are ran against Ubuntu 22.04.3 LTS OS, Intel Core i9-13900H processor ASUS Q540 laptop.

## PART ONE


The read/write latency of cache and main memory when the queue length is zero


To solve this problem, I will run a set of experiments through .batch scripts using the Intel Memory Latency Checker (MLC) tool.


The command --loaded_latency prints the loaded memory latency of the platform. Argument -c0 sends the data to core 0, insuring single core use. -e keeps the pre-fetcher settings. -r makes sure the values are random. -b lets you choose the size of the buffer in Kib. -d lets you choose the load injection delay.

<img width="613" alt="image" src="https://github.com/rienajahnke1/ECSE4320_Adv_CompSys/assets/57211117/f7cc5768-89d1-4af4-ba09-2179ca9cb87c">

## PART TWO


The maximum bandwidth of the main memory under different data access granularity and different read vs write intensity ratios


To solve this problem, I will run a set of experiments through .batch scripts using the Intel Memory Latency Checker (MLC) tool.


The command --max_bandwidth prints the maximum memory bandwidth for various read-write ratios. The argument -l sets the stride size in bytes. MLC does not have a way to change access granularities

<img width="732" alt="image" src="https://github.com/rienajahnke1/ECSE4320_Adv_CompSys/assets/57211117/de9770a2-b382-46ea-abdd-5ebce383c083">


The bandwidth decreased as the read-write ratio increased (more writes). That shows us that writes are slower than reads. This is because you have to erase data before you write data, a step not needed for read functions. There can also be read caching, where freqently accessed data is stored up front thus a faster access time, where write caching is a more complex/longer process.


The larger the stride size, the lower the bandwidth because increased stride size means data is read or written in larger chunks. This can cause data page changes to happen more frequently, which increases total row access latency. When total row access latency increases, it can limit the bandwidth becuase more time is spent accessing and updating data rows.


## PART THREE


The trade-off between read/write latency and throughput of the main memory to demonstrate what the queuing theory predicts


Queing theory predicts that there is a direct relationship between queue depth and server utilization. 


    Length of queue = (server utilization)^2 /(1 - server utilization)
    Server utilization = arrival rate x average time to service a task


To solve this problem, I will run a set of experiments through .batch scripts using the Intel Memory Latency Checker (MLC) tool.


The command --loaded_latency prints the loaded memory latency of the platform. Argument -c0 sends the data to core 0, insuring single core use. -e keeps the pre-fetcher settings. -r makes sure the values are random.


MLC has not way to directly measure throughput vs latency, so I will be using the bandwidth given by the --loaded_latency command and keep in mind that the real throughput will be slightly less.

<img width="581" alt="image" src="https://github.com/rienajahnke1/ECSE4320_Adv_CompSys/assets/57211117/db1c70bc-ee39-4329-9314-53f77d1d2b7c">


## PART FOUR


The impact of cache miss ratio on the software speed preformance


To solve this problem, I will run a set of experiments through bash (.sh) scripts using linux perf commands.


What each command line argument means ->
    stat                          Run a command and gather performance counter statistics
    -e, --event <event>           Event selector. use 'perf list' to list available events
    cpu-clock                     Software event which captures cpu clock time
    L1-dcache-load-misses         Hardware cache event that captures how many dcache load misses happened on L1
    python3 ./mult_func.py        Runs the python script that we are measuring against
    X00000                        If 100000, runs a function to do an inputed amount of multiplication 6 times, 200000 3                                         times, 300000 2 times, 600000 1 time. (explination of why below)


    


