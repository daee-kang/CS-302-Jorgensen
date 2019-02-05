OBJS	= assocTest.o
OBJS1 = movieRatings.o
CC	= g++ -g -Wall -pedantic -std=c++11
DEPS = assocArray.hpp

all: assocTest movieRatings

# assocTest Compilaion
assocTest.o: assocTest.cpp $(DEPS)
		$(CC) -c assocTest.cpp

assocTest: assocTest.o
		$(CC) -o assocTest $(OBJS)

# movieRatings Compilation
movieRatings.o: movieRatings.cpp $(DEPS)
	$(CC) -c movieRatings.cpp

movieRatings: $(OBJS1)
	$(CC) -o movieRatings $(OBJS1)

# Remove old object files
clean:
	rm assocTest
	rm movieRatings
	rm	$(OBJS)
	rm $(OBJS1)
