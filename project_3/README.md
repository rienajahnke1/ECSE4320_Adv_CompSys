# PROJECT THREE

I am using FIO commands to run experiments against an Ubuntu 22.04.3 LTS OS, Intel Core i9-13900H processor ASUS Q540 laptop. These experiments will show how data access sizes, read/write ratio's and I/O que depth's affect bandwidth.

Here is an example command that shows the structure and parameters of the FIO commands


    sudo fio --filename=/dev/sdb --rwmixread=70  --bs=128k --ioengine=libaio --runtime=20 --numjobs=1 --time_based --      
    group_reporting --name=speed_job --iodepth=8 --size=128m

## PART ONE: data access size

To change the data access size, I modified the --blocksize parameter from 4k-128k

<img width="460" alt="image" src="https://github.com/rienajahnke1/ECSE4320_Adv_CompSys/assets/57211117/433baf6f-7542-47c9-977a-035e4f3aeb7f">

## PART TWO: read/write intensity ratio

To change the read/write intensity ration, I modified the --rw paramenter to randread, randwrite, rwmixread=50, rwmixread=70

<img width="470" alt="image" src="https://github.com/rienajahnke1/ECSE4320_Adv_CompSys/assets/57211117/f5ca7363-9f93-466c-83d9-e226014d2b87">

## PART THREE: I/O que depth

To change the I/O depth, I modified the --iodepth paraemter from 1 - 1024

<img width="505" alt="image" src="https://github.com/rienajahnke1/ECSE4320_Adv_CompSys/assets/57211117/336ff0d3-08aa-4ec1-b3c9-80575d0cbcdc">

