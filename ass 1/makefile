# Make file for assignment #1.

OBJS	= main.o bestPath.o
CC	= g++ -g -Wall -pedantic -std=c++11

all: main

main: main.o bestPath.o bestPath.h
	$(CC) -o main $(OBJS)

main.o: main.cpp bestPath.h
	$(CC) -c main.cpp

bestPath.o: bestPath.cpp bestPath.h
	$(CC) -c bestPath.cpp

# -----
# clean by removing object files.

clean:
	rm	$(OBJS)

