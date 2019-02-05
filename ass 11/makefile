
OBJS = main.o
CC = g++ -g -Wall -pedantic -std=c++11
DEPS1	= ganttUtils.h linkedQueue.h
all: main

main: main.o  $(DEPS1)
	$(CC) -Wall -o main $(OBJS)

main.o: main.cpp $(DEPS1)
	$(CC) -Wall -c main.cpp
