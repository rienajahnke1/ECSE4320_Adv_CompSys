# PROJECT THREE

I am using FIO commands to run experiments against an Ubuntu 22.04.3 LTS OS, Intel Core i9-13900H processor ASUS Q540 laptop. These experiments will show how data access sizes, read/write ratio's and I/O que depth's affect bandwidth.

Here is an example command that shows the structure and parameters of the FIO commands


    sudo fio --filename=/dev/sdb --rwmixread=70  --bs=128k --ioengine=libaio --runtime=20 --numjobs=1 --time_based --      
    group_reporting --name=speed_job --iodepth=8 --size=128m

## PART ONE: data access size

To change the data access size, I modified the --bs/--blocksize parameter from 4k-128k

<img width="460" alt="image" src="https://github.com/rienajahnke1/ECSE4320_Adv_CompSys/assets/57211117/433baf6f-7542-47c9-977a-035e4f3aeb7f">


As shown in the graph above, as you increase blocksize, you increase bandwidth. This is expected because data is being written in larger chuncks, and bandwidth is how many bits are being transmitted in one second. But at somewhere inbetween 48k and 69k, the bandwidth starts to plateau. My prediction is that when the block size gets too big, it causes page changes to happen more frequently, which increases total row access latency. When total row access latency increases, it can limit the bandwidth becuase more time is spent accessing and updating data rows.

## PART TWO: read/write intensity ratio

To change the read/write intensity ration, I modified the --rw paramenter to randread, randwrite, rwmixread=50, rwmixread=70

<img width="470" alt="image" src="https://github.com/rienajahnke1/ECSE4320_Adv_CompSys/assets/57211117/f5ca7363-9f93-466c-83d9-e226014d2b87">


The graph shows that read function is significantly faster than write. This is because you have to earase data before you write data, a step not needed for read functions. When combining read and write, the 70:30 r:w ratio was slightly faster than the 50:50, which makes sense because there are more slower read functions. It also shows that when combing both functions, it is not a combined time of both but a disproportionate amount slower. I predict this is the case because either the reads affect the time disproportionally than the writes, or mixing both functions require extra processing requirments in FIO.
## PART THREE: I/O que depth

To change the I/O depth, I modified the --iodepth paraemter from 1 - 1024

<img width="505" alt="image" src="https://github.com/rienajahnke1/ECSE4320_Adv_CompSys/assets/57211117/336ff0d3-08aa-4ec1-b3c9-80575d0cbcdc">

