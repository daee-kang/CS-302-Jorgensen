# Make file for stack and queue assignment

OBJS	= reverse.o
OBJS1	= testDataStructures.o
CC	= g++
DEPS	= linkedStack.h linkedQueue.h

all: testDataStructures reverse

testDataStructures: $(OBJS1)
	$(CC) -Wall -g -o testDataStructures $(OBJS1)

testDataStructures.o:	testDataStructures.cpp $(DEPS)
	$(CC) -Wall -g -c testDataStructures.cpp

reverse.o: reverse.cpp $(DEPS)
	$(CC) -Wall -g -c reverse.cpp

reverse: reverse.o
	$(CC) -Wall -g -o reverse $(OBJS)

# -----
# clean by removing object files.

clean:
	rm	$(OBJS)

