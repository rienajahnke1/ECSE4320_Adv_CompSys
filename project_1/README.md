I am running this experiment against a AMD Ryzen 5 PRO 4650U which has 192KB in L1 cache, 3MB in L2 cache and 8MB in L3 cache.


***PART ONE***


The read/write latency of cache and main memory when the queue length is zero


To solve this problem, I will run a set of experiments through .batch scripts using the Intel Memory Latency Checker (MLC) tool.


The command --loaded_latency prints the loaded memory latency of the platform. Argument -c0 sends the data to core 0, insuring single core use. -e keeps the pre-fetcher settings. -r makes sure the values are random. -b lets you choose the size of the buffer in Kib. -d lets you choose the load injection delay.

<img width="613" alt="image" src="https://github.com/rienajahnke1/ECSE4320_Adv_CompSys/assets/57211117/f7cc5768-89d1-4af4-ba09-2179ca9cb87c">

***PART TWO***


The maximum bandwidth of the main memory under different data access granularity and different read vs write intensity ratios


To solve this problem, I will run a set of experiments through .batch scripts using the Intel Memory Latency Checker (MLC) tool.


The command --max_bandwidth prints the maximum memory bandwidth for various read-write ratios. The argument -l sets the stride size in bytes. MLC does not have a way to change access granularities


The bandwidth decreased as the read-write ratio increased (more writes). That shows us that writes are slower than reads. This is because you have to erase data before you write data, a step not needed for read functions. There can also be read caching, where freqently accessed data is stored up front thus a faster access time, where write caching is a more complex/longer process.


The larger the stride size, the lower the bandwidth because increased stride size means data is read or written in larger chunks. This can cause data page changes to happen more frequently, which increases total row access latency. When total row access latency increases, it can limit the bandwidth becuase more time is spent accessing and updating data rows.


***PART THREE***


The trade-off between read/write latency and throughput of the main memory to demonstrate what the queuing theory predicts


Queing theory predicts that there is a direct relationship between queue depth and server utilization. 


    Length of queue = (server utilization)^2 /(1 - server utilization)
    Server utilization = arrival rate x average time to service a task


To solve this problem, I will run a set of experiments through .batch scripts using the Intel Memory Latency Checker (MLC) tool.


The command --loaded_latency prints the loaded memory latency of the platform. Argument -c0 sends the data to core 0, insuring single core use. -e keeps the pre-fetcher settings. -r makes sure the values are random.


MLC has not way to directly measure throughput vs latency, so I will be using the bandwidth given by the --loaded_latency command and keep in mind that the real throughput will be slightly less.
