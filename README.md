### C++ application using socket API

#### Overview

C++ application developed on CERN CentOS Linux distribution, is only compatible with Linux OS.

One thread accepts a connection from an MCU (socket API used).
Another thread receives data from an MCU and analyses their integrity. Errors are logged into a text file - "errors.txt".

It is intended to be used during the test of an Ethernet link.

The code of this project can be reused within a FESA class QPS_ETH.