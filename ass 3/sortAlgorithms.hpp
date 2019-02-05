/*
 header file for sortAlgorithms class
 
 functions quicksort, insertionSort, partition, and median of 3
 are used in public classes privately.
 
 followed structure given by pdf
 
 Just wondering, what else should I comment for header files
 */
#ifndef sortAlgorithms_hpp
#define sortAlgorithms_hpp

#include <stdio.h>

#endif /* sortAlgorithms_hpp */
class sortAlgorithms{
private:
    int length;
    short *myArray;
    static const int RANGE = 1000;
    void quickSort(int, int);
    void insertionSort(int, int);
    int partition(int, int);
    int medianOf3(int, int);
public:
    sortAlgorithms();
    ~sortAlgorithms();
    void generateData(int);
    int getLength();
    int getItem(int);
    void printData();
    void countSort();
    void bubbleSort();
    void insertionSort();
    void quickSort();
    
};
