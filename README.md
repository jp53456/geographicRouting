# geographicRouting
This a program that takes in a conﬁguration ﬁle with nodes information to perform geographic routing. Each line in conﬁguration ﬁle will contain 3 values (node id, x coordinate of the node, y coordinate of the node) seperated with a space.

To compile: g++ -g -std=c++11 -o gf gf.cpp 

Example command to run the program: ./gf gf.conf 60 1 7 

(gf.conf ﬁle will be read in to populate node table, and the range in order to communicate is 60, source node is 1, destination node is 7)
