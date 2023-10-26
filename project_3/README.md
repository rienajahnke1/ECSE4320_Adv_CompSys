# PROJECT THREE

I am using FIO commands to run experiments against an Ubuntu 22.04.3 LTS OS, Intel Core i9-13900H processor ASUS Q540 laptop. These experiments will show how data access sizes, read/write ratio's and I/O que depth's affect bandwidth.

Here is an example command that shows the structure and parameters of the FIO commands


    sudo fio --filename=/dev/sdb --rwmixread=70  --bs=1M --ioengine=libaio --runtime=20 --numjobs=1 --time_based --      
    group_reporting --name=speed_job --iodepth=8 --size=1G --blocksize=4k


## PART ONE: data access size

modify --blocksize 4k-128k


## PART TWO: read vs write intensity ratio

modify --rw read, write, randrw, rwmixread=70


## PART THREE: I/O que depth

modify --iodepth 1 - 1024


