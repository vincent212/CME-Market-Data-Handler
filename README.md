# CME-Market-Data-Handler
A minimalist CME MDP 3.0 C++ market data feed handler implementing all required features
needed to certify on CME AutoCert. It is tested/certified on futures but with minor modifications will work for
spreads, options, BTEC, and EBS.

Copyright 2022 Vincent Maciejewski, Quant Enterprises & M2 Tech
Contact:
v@m2te.ch
mayeski@gmail.com
https://www.linkedin.com/in/vmayeski/
http://m2te.ch/

A bit more information on the handler is found on my blog:
http://maye.ski/

In particular please see:
http://maye.ski/index.php/2022/08/10/open-source-cme-market-data-handler/
http://maye.ski/index.php/2022/09/10/using-transaction-time-in-cme-gap-recovery/

Latency from moment a packet is received to moment application callback is invoked is under 1 micro.
