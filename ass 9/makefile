CC = g++ -g -Wall -pedantic -std=c++11

all: maze

maze: maze.o mazeGenerator.o mazeGenerator.hpp 
	$(CC)  -o  records maze.o mazeGenerator.o disjointSets.o

maze.o: maze.cpp mazeGenerator.hpp disjointSets.hpp
	$(CC)  -c maze.cpp

mazeGenerator.o: mazeGenerator.cpp mazeGenerator.hpp disjointSets.hpp
	$(CC)  -c mazeGenerator.cpp

disjointSets.o: disjointSets.cpp disjointSets.hpp
	$(CC)  -c disjointSets.cpp


clean: 
	rm *o records