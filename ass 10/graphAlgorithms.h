#pragma once
#ifndef graphAlgorithms_h
#define graphAlgorithms_h

#include <iostream>
using namespace std;

class graphAlgorithms{
private:
	//variables
	int vertexCount;
	string title;
	int ** graphMatrix;
	int * dist;
	int * prev;
	int * topoNodes; 
	int topoCount;
	//functions
	void showPath(const int) const;
	void destroyGraph();
public:
	graphAlgorithms(int = 5);
	~graphAlgorithms();
	void newGraph(int);
	void addEdge(int, int, int);
	bool readGraph(const string);
	int getVertexCount() const;
	void printMatrix() const;
	void topoSort();
	void dijkstraSP(int);
	void printPath(const int, const int) const;
	string getGraphTitle() const;
	void setGraphTitle(const string);
	void printDistances(const int) const;
	bool getArgs(int, char *[], bool &, string &, int &, int &, bool &);
};

#endif // !graphAlgorithms_h
