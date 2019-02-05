
OBJS	= main.o
OBJS1 = pqTest.o
CC	= g++ -g -Wall -pedantic -std=c++11
DEPS = maxHeap.h minHeap.h

all: main pqTest

main.o: main $(DEPS)
		$(CC) -c main.cpp

main: main.o
		$(CC) -o main $(OBJS)

pqTest.o: pqTest.cpp $(DEPS)
	$(CC) -c pqTest.cpp

pqTest: $(OBJS1)
	$(CC) -o pqTest $(OBJS1)

clean:
	rm main
	rm pqTest
	rm	$(OBJS)
	rm $(OBJS1)
