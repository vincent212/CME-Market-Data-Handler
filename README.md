# CME-Market-Data-Handler
A minimalist CME MDP3.0 C++ market data feed handler (and pcap file reader) implementing all required features
needed to certify on CME AutoCert. It is tested/certified on futures but with minor modifications will work for
spreads, options, BTEC, and EBS.

The code read MDP3 data from pcap files as well when compiled with USE_PCAP flag.

Copyright 2022 Vincent Maciejewski, Quant Enterprises & M2 Tech
Contact:
v@m2te.ch
mayeski@gmail.com
https://www.linkedin.com/in/vmayeski/
http://m2te.ch/

Latency from moment a packet is received to moment application callback is invoked is under 1 micro.

Please note the code has been tested on Centos and will not work on Windows.
