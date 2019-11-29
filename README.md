# VANETsPolynomialApproach
Add at ns3 a polynomial approach in lbt simulation with lte and wifi


This program chooses a communication technology between 2 available: LTE and WIFI. 

The simulation consists of two static nodes, each of which can choose between LTE, WIFI and LAA (both at the same time).
They communicate with Udp protocol.

To operate, the installation is devised in 4 steps:
1-> installation of the basic structure: ns3-lbt http://code.nsnam.org/laa/ns-3-lbt/
2->modify scenario-helper by replacing it with the proposed one.
3-> add the other files: apact.cpp and the makefile
4-> add the scratch folder

To execute the code, just enter "make" then"./apact"
