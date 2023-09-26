::target L1 Cache ->
mlc --loaded_latency -c0 -e -r -b192 -d300000
::target L2 Cache ->
mlc --loaded_latency -c0 -e -r -b23437 -d300000
::target L3 Cache ->
mlc --loaded_latency -c0 -e -r -b62500 -d300000
::target RAM ->
mlc --loaded_latency -c0 -e -r -b100000 -d300000
::target RAM ->
mlc --loaded_latency -c0 -e -r -b250000 -d300000
::target RAM ->
mlc --loaded_latency -c0 -e -r -b500000 -d300000