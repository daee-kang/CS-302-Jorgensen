//  Main program
//	reverse an audio file.

#include <iostream>
#include <fstream>
#include <string>
#include "linkedStack.h"
#include "linkedQueue.h"

using namespace std;

int main(int argc, char *argv[])
{
// *****************************************************************

	if (argc == 1) {
		cout << "Usage: ./reverse <inputFile> <outputFile>" << endl;
		return 0;
	}

	if (argc != 3) {
		cout << "Error, must provide input and output file names." << endl;
		return 0;
	}

	ifstream	inFile;
	ofstream	outFile;

	inFile.open(argv[1]);
	if (inFile.fail()) {
		cout << "Error, unable to open input file: " << argv[1] << endl;
		return 0;
	}

	outFile.open(argv[2]);
	if (inFile.fail()) {
		cout << "Error, unable to open output file: " << argv[2] << endl;
		return 0;
	}


// *****************************************************************
//  Headers...

	string bars = "--------------------------------------------------";

	cout << bars << endl << "CS 202 - Assignment #14" << endl;
	cout << "Audio Reversal Program" << endl << endl;


// *****************************************************************
//  Test basic queue operations.
//	Create some integer queues, add items, delete items,
//	display queues, etc...

	linkedQueue<double> dQueue;
	linkedStack<double> dStack;
	string		line;

	double	n1, n2;

	getline(inFile, line);
	outFile << line;

	getline(inFile, line);
	outFile << line;

	while (inFile >> n1 >> n2) {
		dQueue.addItem(n1);
		dStack.push(n2);
	}

	cout << "Count = " << dQueue.queueCount() << endl;

	while (!dQueue.isEmptyQueue()) {
		n1 = dQueue.front();
		dQueue.deleteItem();
		n2 = dStack.top();
		dStack.pop();
		outFile << "  " << n1 << "  " << n2 << endl;
	}


// *****************************************************************
//  All done.

	inFile.close();
	outFile.close();

	cout << bars << endl << "Reversal completed." << endl;

	return 0;
}


