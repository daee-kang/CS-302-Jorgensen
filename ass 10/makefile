
OBJS = paths.o graphAlgorithms.o
CC = g++ -g -Wall -pedantic -std=c++11
DEPS1	= graphAlgorithms.h
DEPS2	= graphAlgorithms.h minHeap.h linkedQueue.h
all: paths

paths: paths.o graphAlgorithms.o $(DEPS1)
	$(CC) -Wall -o paths $(OBJS)

paths.o: paths.cpp $(DEPS1)
	$(CC) -Wall -c paths.cpp

graphAlgorithms.o: graphAlgorithms.cpp $(DEPS2)
	$(CC) -Wall -c graphAlgorithms.cpp