# VANETs Polynomial Approach
-----------------------------------What does the algorithm do?------------------------------------------------

This algorithm makes it possible to elect the set of communication technologies in order to promote throughput. For this purpose, a scenario of two nodes is proposed. Each node has two communication technologies available: WIFI and LTE. The transfer of information is therefore done according to three choices: LTE, Wifi or both at the same time with the LAA. 

The algorithm works as follows:

0-> Initialization with 2 operators A and B exchanging UDP packets.

1-> sending UDP packets according to each communication technology 

2-> classification of data rates according to communication technology.

3->use of the apact algorithm to get an approximate solution:

  3a->local choice of the best communication technology for an operator

  3b->global choice of the best communication technology for all operators

4-> use of simplex to get an exact solution


-----------------------------------How to run the algorithm ?------------------------------------------------

Add at ns3 a polynomial approach in lbt simulation with lte and wifi

This program chooses a communication technology between 2 available: LTE and WIFI. 

The simulation consists of two static nodes, each of which can choose between LTE, WIFI and LAA (both at the same time).
They communicate with Udp protocol.

To operate, the installation is devised in 5 steps:

1-> installation of the basic structure: ns3-lbt http://code.nsnam.org/laa/ns-3-lbt/

2->modify scenario-helper by replacing it with the proposed one.

3-> add the other files: apact.cpp and the makefile

4-> add the scratch folder and the simplex folder

5->install the glpk with "sudo apt-get install glpk"


To execute the code, just enter "make" then"./apact"
