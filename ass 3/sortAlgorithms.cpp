/*

daee kang ass 3


The following code is the code for functions defined in the header file, for the functions
in the class of sortAlgorithms. Below functions include constructors, destructors, and basic fetches for 
length and items. 

More importantly they define the sorts that are implemented - bubble sort, counting sort, quick sort, and
insertion sort. Important to note that insertion sort uses a recursive method calling a private function. 
Quick sort also does this but also has another two functions called partition and median of 3 which do exactly
that. 



*/


#include "sortAlgorithms.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

sortAlgorithms::sortAlgorithms(){
//default constructor
    length = 0;
    myArray = NULL;
}
sortAlgorithms::~sortAlgorithms(){
//deconstructor
    delete[] myArray;
}
void sortAlgorithms::generateData(int len){
/* populate array with random numbers based on length and set length
 accordingly */
    length = len;
    myArray = new short [len];
    for(int i = 0; i < length; i++)
        myArray[i] = rand() % RANGE;
}
int sortAlgorithms::getLength(){
//return length lol ez
    return length;
}
int sortAlgorithms::getItem(int request){
//returns value at array, if not valid returns 0
    if(request > 0 and request <= length){
        return myArray[request];
    } else return 0;
}
void sortAlgorithms::printData(){
//prints out array in rows of 12, container of 4 + space
    int counter = 0;
    for(int i = 0; i < length; i++){
        cout << setw(4) << myArray[i] << " ";
        counter++;
        if(counter == 12){
            cout << endl;
            counter = 0;
        }
    }
}
void sortAlgorithms::countSort(){
//
//    int *TempArr;
//    short max = myArray[0];
//
//    // searches for the max in the list
//    for(int i = 0; i < length ; i++)
//    {
//        if(max < myArray[i])
//            max = myArray[i];
//    }
//
//    TempArr = new int[max+1];
//
//    //zeros out the new array created
//    for(int i = 0; i< max; i++)
//        TempArr[i] = 0;
//
//    int temp;
//    // counts the number of instances the value appears in the
//    //array and increments by one in the new array
//    for(int x = 0; x < length;x++)
//    {
//        temp = static_cast<int>(myArray[x]);//forces the value
//        // to become a int instead of a short
//        TempArr[temp]++;
//    }
//
//    int count = 0;//will be used to count until it reaches
//    //the length
//    int j = 1;// used to count how many occurences it appeared
//    // in the TempArr
//
//    for(int i = 0 ; i <= max ; i++)
//    {
//        j = 1;
//        if(TempArr[i] > 0)
//        {
//            while(j <= TempArr[i])
//            {
//                myArray[count] = i;
//                j++;
//                count++;
//            }
//        }
//    }
//    delete [] TempArr;
//
//    return;
    int * countArray;
    countArray = new int [RANGE];

    //initialize array with 0
    for(int i = 0; i < RANGE; i++)
        countArray[i] = 0;

    for(int i = 0; i < length + 1; i++)
        countArray[myArray[i]]++;

    for(int i = 1; i < RANGE; i++){
        countArray[i] += countArray[i - 1];
    }

    int count = 0, j = 1;
    for(int i = 0; i < RANGE; i++){
        j = 1;
        if(countArray[i] > 0){
            while(j <= myArray[i]){
                myArray[count] = i;
                j++;
                count++;
            }
        }
    }

    delete [] countArray;
}
void sortAlgorithms::bubbleSort(){
    /*runs through list length times iterating through the list every time. If the value ahead of j is greater, it swapps and sets swapped to true. at the end of the loop, if it hasn't swapped, the sort is finished and will break, otherwise keep looping and swapping */
    bool swapped = false;
    for(int i = 0; i < length - 1; i++){
        swapped = false;
        for(int j = 0; j < length - 1; j++){
            if(myArray[j] > myArray[j+1]){
                //swap
                int temp = myArray[j+1];
                myArray[j+1] = myArray[j];
                myArray[j] = temp;
                swapped = true;
            }
        }
        if(!swapped) break;
    }
}
void sortAlgorithms::insertionSort(){
    //calling the start of insertion sort with index 0 to length
    int a = 0;
    insertionSort(a, length-1);
}
void sortAlgorithms::quickSort(){
    //calling quicksort recursively with index 0 to length
    quickSort(0, length - 1);
}
void sortAlgorithms::quickSort(int start, int end){
    //base case is assuming that start > endl
    if(start < end){
        int partitionPoint = partition(start, end);
        //call recursive function on first half and then second half
        quickSort(start, partitionPoint - 1);
        quickSort(partitionPoint + 1, end);
    }
}
void sortAlgorithms::insertionSort(int a, int n){
//not sure why there has to be two perameters since first will always be 0
    //base case
    if(n>1){

    //recursive call, n -1
        
    insertionSort(a, n);
    
    //gets last array position and goes down the indices swapping if needed
    int last = myArray[n];
    int j = n-1;
    
    //swap time baby
    while(j > 0 and myArray[j] > last){
        myArray[j+1] = myArray[j];
        j--;
    }

    //places the value at j index
    myArray[j+1] = last;
    }
}
int sortAlgorithms::partition(int start, int end){
	//find pivot from median of 3 function.
    int pivot = medianOf3(start, end);

    //define i and j to move through partition.
    int i = start - 1;

    for(int j = start; j <= end - 1; j++){
        if(myArray[j] <= pivot){
            i++;
            //swap
            int temp = myArray[i];
            myArray[i] = myArray[j];
            myArray[j] = temp;
        }
    }
    //swap 
    int temp = myArray[end];
    myArray[end] = myArray[i+1];
    myArray[i+1] = temp;
    return i + 1;
    
}
int sortAlgorithms::medianOf3(int start, int end){
    //if there are more than 2 numbers, run this algorithm
    if(end - start>= 3){
        //create array to store low, high, and mid value in unspecified order
        int medValues[3];
        medValues[0] = myArray[start];
        medValues[1] = myArray[end];
        
        //odd or even
        if((end+start)%2 == 1){
            medValues[2] = myArray[(start+end)/2];
        } else medValues[2] = myArray[(start+end+1)/2];
        
        //find highest
        int high = 0;
        for(int i = 0; i < 2; i++){
            if(high < medValues[i]) high = medValues[i];
        }
        //find lowest
        int low = 0;
        for(int i = 0; i < 2; i++){
            if(low > medValues[i]) low = medValues[i];
        }
        //find mid value based on lowest and highest values and return mid value
        int mid = 0;
        for(int i = 0; i < 2; i++){
            if(medValues[i] != low or medValues[i]!= high) mid = medValues[i];
        }
        return mid;
    } else return myArray[end];
}

