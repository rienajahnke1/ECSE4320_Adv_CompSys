## PROJECT FOUR: Implementaion of Dictionary Codec

In this project, I will implement dictionary codec by first encoding a raw column data file then creating a query of it. Dictionary encoding is used to compress data with relatively low cardinality and speed up search/scan operations. The dictionary encoding code will support multi-threading for faster read time and the encoded data column will use integer compression to further reduce the footprint on the SSD. The encoded query code will support the use of SIMD instructions to speed up the search/scan.