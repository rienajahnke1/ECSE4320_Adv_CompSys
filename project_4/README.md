# PROJECT FOUR: Implementaion of Dictionary Codec

## Introduction
In this project, I will implement dictionary codec by first encoding a raw column data file then creating a query of it. Dictionary encoding is used to compress data with relatively low cardinality and speed up search/scan operations. The dictionary encoding code will support multi-threading for faster read time and the encoded data column will use integer compression to further reduce the footprint on the SSD. The encoded query code will support the use of SIMD instructions to speed up the search/scan.


## Encoding
To encode the data, I first played around with diffrent multi-threading techniques in python to see which process is the most efficent, and could handle the large dataset.

<img width="500" alt="image" src="https://github.com/rienajahnke1/ECSE4320_Adv_CompSys/assets/57211117/7724c2ae-1f79-4fa5-bcaa-a4016ffa5524">

