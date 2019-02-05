//  Main program for testing

#include <iostream>
#include <string>
#include <cstdlib>

#include "minHeap.h"
#include "maxHeap.h"

using namespace std;

int main(int argc, char *argv[])
{

// *****************************************************************
//  Headers...

	string	stars, bars, dashes;
	stars.append(65, '*');
	bars.append(65, '=');
	dashes.append(40,'-');
	const char* bold   = "\033[1m";
	const char* unbold   = "\033[0m";

	cout << stars << endl << bold << "CS 302 - Assignment #8" << endl;
	cout << "Priority Queue Tester" << unbold << endl;
	cout << endl;

// ------------------------------------------------------------------
//  MIN Heap - Initial testing, very small heap.
//	Always prints...

	minHeap<string>		myMinHeap0;
	string			currName;

	cout << endl << bars << endl << bold <<
		"Min Heap - Test Set #0" << unbold << endl;

	myMinHeap0.insert("google");
	myMinHeap0.insert("amazon");
	myMinHeap0.insert("newegg");
	myMinHeap0.insert("apple");
	myMinHeap0.insert("dell");
	myMinHeap0.insert("oracle");
	myMinHeap0.insert("cisco");
	myMinHeap0.insert("jupiter");
	myMinHeap0.insert("belkin");
	myMinHeap0.insert("ebay");

	cout << dashes << endl << "PQ Heap (level order):" << endl;
	myMinHeap0.printHeap();

	cout << dashes << endl << "PQ Heap Size: " << myMinHeap0.getCount() << endl;
	cout << "Priority Order:" << endl;
	while (!myMinHeap0.isEmpty()) {
		currName = myMinHeap0.deleteMin();
		cout << currName << endl;
	}


// ------------------------------------------------------------------
//  MIN heap - Some very basic testing.

	minHeap<char>	myMinHeap1;
	char		currChar;

	cout << endl << bars << endl << bold <<
		"Min Heap - Test Set #1" << unbold << endl;

	myMinHeap1.insert('w');
	myMinHeap1.insert('r');
	myMinHeap1.insert('g');
	myMinHeap1.insert('x');
	myMinHeap1.insert('y');
	myMinHeap1.insert('a');
	myMinHeap1.insert('z');
	myMinHeap1.insert('s');
	myMinHeap1.insert('n');
	myMinHeap1.insert('p');
	myMinHeap1.insert('d');
	myMinHeap1.insert('o');
	myMinHeap1.insert('c');
	myMinHeap1.insert('t');
	myMinHeap1.insert('j');
	myMinHeap1.insert('b');
	myMinHeap1.insert('e');
	myMinHeap1.insert('u');
	myMinHeap1.insert('l');
	myMinHeap1.insert('v');
	myMinHeap1.insert('f');
	myMinHeap1.insert('h');
	myMinHeap1.insert('k');
	myMinHeap1.insert('m');
	myMinHeap1.insert('i');
	myMinHeap1.insert('q');

	cout << dashes << endl << "PQ Heap (level order):" << endl;
	myMinHeap1.printHeap();

	cout << dashes << endl << "PQ Heap Size: " << myMinHeap1.getCount() << endl;
	cout << "Priority Order:" << endl;
	while (!myMinHeap1.isEmpty()) {
		currChar = myMinHeap1.deleteMin();
		cout << currChar << " ";
	}
	cout << endl;

// ------------------------------------------------------------------
//  MIN heap - Large testing...

   {
	minHeap<unsigned long long>	myMinHeap3(500000);
	bool			passed=true;
	unsigned long long	size=2000000;
	unsigned long long	j, k;

	cout << endl << bars << endl << bold <<
		"Min Heap - Test Set #2" << unbold << endl;

	for (unsigned long long i=size-1; i>=1; i--)
		myMinHeap3.insert(i);

	for (unsigned long long i=1; i<size; i++) {
		k = myMinHeap3.peek();
		j = myMinHeap3.deleteMin();
		if (j != k) {
			passed = false;
			cout << "Error, deleteMin() fail." << endl;
		}
		if (i != j) {
			passed = false;
			cout << "Error, deleteMin() fail." << endl;
		}
	}

	if (passed)
		cout << "Min Heap - Large test successful." << endl;
	else
		cout << "Min Heap - Large test fail." << endl;
   }


// ******************************************************************
//  MAX heap - Initial testing, very small heap.
//	Always prints...

	maxHeap<string>	myMaxHeap0;

	cout << endl << bars << endl << bold <<
		"Max Heap - Test Set #0" << unbold << endl;

	myMaxHeap0.insert("google");
	myMaxHeap0.insert("amazon");
	myMaxHeap0.insert("newegg");
	myMaxHeap0.insert("apple");
	myMaxHeap0.insert("dell");
	myMaxHeap0.insert("oracle");
	myMaxHeap0.insert("cisco");
	myMaxHeap0.insert("jupiter");
	myMaxHeap0.insert("belkin");
	myMaxHeap0.insert("ebay");

	cout << dashes << endl << "PQ Heap (level order):" << endl;
	myMaxHeap0.printHeap();

	cout << dashes << endl << "PQ Heap Size: " << myMaxHeap0.getCount() << endl;
	cout << "Priority Order:" << endl;
	while (!myMaxHeap0.isEmpty()) {
		currName = myMaxHeap0.deleteMax();
		cout << currName << endl;
	}

// ------------------------------------------------------------------
//  MAX heap - Some very basic testing.

	maxHeap<char>	myMaxHeap1;

	cout << endl << bars << endl << bold <<
		"Max Heap - Test Set #1" << unbold << endl;

	myMaxHeap1.insert('w');
	myMaxHeap1.insert('r');
	myMaxHeap1.insert('g');
	myMaxHeap1.insert('x');
	myMaxHeap1.insert('y');
	myMaxHeap1.insert('a');
	myMaxHeap1.insert('z');
	myMaxHeap1.insert('s');
	myMaxHeap1.insert('n');
	myMaxHeap1.insert('p');
	myMaxHeap1.insert('d');
	myMaxHeap1.insert('o');
	myMaxHeap1.insert('c');
	myMaxHeap1.insert('t');
	myMaxHeap1.insert('j');
	myMaxHeap1.insert('b');
	myMaxHeap1.insert('e');
	myMaxHeap1.insert('u');
	myMaxHeap1.insert('l');
	myMaxHeap1.insert('v');
	myMaxHeap1.insert('f');
	myMaxHeap1.insert('h');
	myMaxHeap1.insert('k');
	myMaxHeap1.insert('m');
	myMaxHeap1.insert('i');
	myMaxHeap1.insert('q');

	cout << dashes << endl << "PQ Heap (level order):" << endl;
	myMaxHeap1.printHeap();

	cout << dashes << endl << "PQ Heap Size: " << myMaxHeap1.getCount() << endl;
	cout << "Priority Order:" << endl;
	while (!myMaxHeap1.isEmpty()) {
		currChar = myMaxHeap1.deleteMax();
		cout << currChar << " ";
	}
	cout << endl;

// ------------------------------------------------------------------
//  MAX heap - Large testing...

   {
	maxHeap<unsigned long long>	myMaxHeap3(10000);
	bool			passed=true;
	unsigned long long	size=3000000;
	unsigned long long	j, k;

	cout << endl << bars << endl << bold <<
		"Max Heap - Test Set #2" << unbold << endl;

	for (unsigned long long i=1; i<size; i++)
		myMaxHeap3.insert(i);

	for (unsigned long long i=size-1; i>0; i--) {
		k = myMaxHeap3.peek();
		j = myMaxHeap3.deleteMax();
		if (j != k) {
			passed = false;
			cout << "Error, deleteMax() fail." << endl;
		}
		if (i != j) {
			passed = false;
			cout << "Error, deleteMax() fail." << endl;
		}
	}

	if (passed)
		cout << "Max Heap - Large test successful." << endl;
	else
		cout << "Max Heap - Large test fail." << endl;
   }

// *****************************************************************
//  Some misc. error testing.

	cout << endl << bars << endl << bold <<
		"Should show heap empty errors." << unbold << endl << endl;

	currChar = myMinHeap1.deleteMin();
	currChar = myMaxHeap1.deleteMax();

// *****************************************************************
//  All done.

	cout << endl << stars << endl <<
		"Game Over, thank you for playing." << endl;

	return 0;
}

