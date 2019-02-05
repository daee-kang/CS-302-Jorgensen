//  Main program for testing

#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

#include "graphAlgorithms.h"

using namespace std;



// ************************************************************************
//  Main program for testing graph algorithms object.

int main(int argc, char *argv[])
{

	// ------------------------------------------------------------------
	//  Declare variables and display some cute headers...

	string		stars, bars, dashes;
	string		fName;
	const char	*bold = "\033[1m";
	const char	*unbold = "\033[0m";
	bool		doTesting = false;
	bool		showMatrix = false;
	string		graphFile = "";
	int		startNode, destNode;
	graphAlgorithms	myGraph;

	dashes.append(40, '-');
	stars.append(65, '*');
	bars.append(65, '=');

	// ------------------------------------------------------------------
	//  Check/get arguments

	if (!myGraph.getArgs(argc, argv, doTesting, graphFile,
		startNode, destNode, showMatrix)) {
		exit(1);
	}

	// ------------------------------------------------------------------
	//  Basic error testing...

	if (doTesting) {
		cout << bars << endl;
		cout << "Error testing: " << endl << endl;

		graphAlgorithms	badGraph1(-1);
		graphAlgorithms	badGraph2(3);
		graphAlgorithms	badGraph3(10);
		graphAlgorithms	tmpGraph4;

		badGraph3.newGraph(-2);
		badGraph3.newGraph(2);
		badGraph3.newGraph(20);
		badGraph3.addEdge(11, -11, 100);
		badGraph3.addEdge(51, 11, 100);
		badGraph3.addEdge(-11, 11, 100);
		badGraph3.addEdge(3, 3, 10);
		badGraph3.addEdge(5, 7, 100);			// ok
		badGraph3.setGraphTitle("Unused Example");

		if (badGraph3.getGraphTitle() != "Unused Example")
			cout << "main: title functions do not work." << endl;

		if (tmpGraph4.getVertexCount() != 5)
			cout << "main, constructor did not set"
			<< "vertex count correctly." << endl;

		tmpGraph4.newGraph(1000);
		if (tmpGraph4.getVertexCount() != 1000)
			cout << "main, newGraph() and/or getVertexCount()"
			<< "functions did not work correctly." << endl;

		cout << endl;
		badGraph2.topoSort();

		cout << endl;
		badGraph2.printMatrix();

		cout << endl;
		badGraph2.dijkstraSP(0);

		cout << endl;
		badGraph3.dijkstraSP(40);
	}

	// ------------------------------------------------------------------
	//  Graph Algorithms -> Dijkstra and Topo sort
	//	read graph file
	//	if print option selected, print
	//	topo sort (which prints results)
	//	find shortest path (which prints results)

	if (!doTesting) {

		cout << stars << endl << bold << "CS 302 - Assignment #10" << endl;
		cout << endl;
		cout << bars << endl;
		cout << bold << "Graph Algorithms" << unbold << endl << endl;

		if (myGraph.readGraph(graphFile)) {
			if (showMatrix)
				myGraph.printMatrix();
			myGraph.topoSort();
			myGraph.dijkstraSP(startNode);
			cout << dashes << endl;
			myGraph.printPath(startNode, destNode);
		}
		else {
			cout << "main: Error reading " << graphFile << "." << endl;
		}

		cout << endl;
	}

	// ------------------------------------------------------------------
	//  All done.

	cout << endl << stars << endl <<
		"Game Over, thank you for playing." << endl;

	return 0;
}

