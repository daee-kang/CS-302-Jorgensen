//  CS 302
//  Dynamic Median Program

// ***********************************************************************
//  Includes...

#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <chrono>

#include "dynamicMedians.h"
#include "minHeap.h"
#include "maxHeap.h"

using namespace std;

// *******************************************************************

int main(int argc, char *argv[])
{
// ------------------------------
//  Declarations and headers.

	string	stars;
	stars.append(60,'*');
	string	bars;
	bars.append(50,'-');
	stringstream ss;

// ------------------------------
//  Command line args ok, display initial headers.

	cout << "CS 302 - Assignment #8" << endl;
	cout << "Dynamic Medians Program." << endl;
	cout << stars << endl;
	cout << endl;

// ------------------------------
//  Test set #0

    {
	dynamicMedians<unsigned short>	mySet0;
	unsigned short	myArr[] = {5, 15, 1, 3, 2, 8, 7, 9, 10, 6, 11, 4};
	unsigned short	size = sizeof(myArr)/sizeof(myArr[0]);

	if (!mySet0.setData(myArr, size))
		exit(1);

	cout << bars << endl << "Data Set 0" << endl << endl;
	mySet0.showData();
	mySet0.findMedians();
	mySet0.showMedians();
	cout << endl;
    }

// ------------------------------
//  Test set #1

	dynamicMedians<unsigned int>	mySet1;

	cout << bars << endl << "Data Set 1" << endl << endl;
	mySet1.generateData(10, 1000);
	mySet1.showData();
	mySet1.findMedians();
	mySet1.showMedians();
	cout << endl;

// ------------------------------
//  Test set #2

	dynamicMedians<unsigned long long>	mySet2;

	cout << bars << endl << "Data Set 2" << endl << endl;
	mySet2.generateData(1000000, 1000000);
	mySet2.findMedians();

	cout << "Selected Data:" << endl;
	cout << "--------------" << endl;
	for (int i=0; i<1000000; i+=100000)
		cout << mySet2.getDataItem(i) << " ";
	cout << endl << endl;

	cout << "Selected Medians:" << endl;
	cout << "-----------------" << endl;
	for (int i=0; i<1000000; i+=100000)
		cout << mySet2.getMediansItem(i) << " ";
	cout << endl;

	cout << endl;

// ------------------------------
//  Test min heapify function....

    const unsigned int	size1 = 50000000;
    const unsigned int	limit1 = 1000000;
	minHeap<int>	pqMin1(size1);
	minHeap<int>	pqMin2(size1);

	cout << bars << endl << "Min Heap Tests" << endl << endl;

	// start timer...
	auto t1 = chrono::high_resolution_clock::now();

	pqMin1.makeRandHeap1(size1, limit1);

	// show results with times
	auto t2 = chrono::high_resolution_clock::now();

	cout << "on-at-a-time inserts took: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
              << " milliseconds" << endl;

	// start timer...
	t1 = chrono::high_resolution_clock::now();

	pqMin2.makeRandHeap2(size1, limit1);

	// show results with times
	t2 = chrono::high_resolution_clock::now();

	cout << "heapify inserts took: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
              << " milliseconds" << endl;
	cout << endl;

	cout << endl << "Verification in process, standby..." << endl;
	for (unsigned int i=0; i < pqMin1.getCount(); i++) {
		if (pqMin1.deleteMin() != pqMin2.deleteMin())
			cout << "Error, invalid min heaps." << endl;
	}
	cout << endl;

// ------------------------------
//  Test max heapify function....

	const unsigned int	size2 = 50000000;
	const unsigned int	limit2 = 1000000;
	maxHeap<int>	pqMax3(size2);
	maxHeap<int>	pqMax4(size2);

	cout << bars << endl << "Max Heap Tests" << endl << endl;

	// start timer...
	t1 = chrono::high_resolution_clock::now();

	pqMax3.makeRandHeap1(size2, limit2);

	// show results with times
	t2 = chrono::high_resolution_clock::now();

	cout << "on-at-a-time inserts took: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
              << " milliseconds" << endl;

	// start timer...
	t1 = chrono::high_resolution_clock::now();

	pqMax4.makeRandHeap2(size2, limit2);

	// show results with times
	t2 = chrono::high_resolution_clock::now();

	cout << "heapify inserts took: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
              << " milliseconds" << endl;

	cout << endl << "Verification in process, standby..." << endl;
	for (unsigned int i=0; i < pqMax3.getCount(); i++) {
		if (pqMax3.deleteMax() != pqMax4.deleteMax())
			cout << "Error, invalid max heaps." << endl;
	}
	cout << endl;

// ------------------------------
//  Done, terminate program.

	cout << stars << endl << "Game Over, thank you for playing." << endl;
	return 0;
}

