//
//  dynamicMedians.h
//  ass 8
//
//  Created by Daee Kang on 10/25/18.
//  Copyright © 2018 Daee Kang. All rights reserved.
//

#ifndef dynamicMedians_h
#define dynamicMedians_h

#include "maxHeap.h"
#include "minHeap.h"
using namespace std;
template<class myType>
class dynamicMedians{
public:
    dynamicMedians();
    ~dynamicMedians();
    bool setData(myType [], const int);
    bool generateData(const int, const int);
    void showData() const;
    void showMedians() const;
    myType getDataItem(const unsigned int) const;
    myType getMediansItem(const unsigned int) const;
    void findMedians();
private:
    static const unsigned int MIN_LENGTH = 5;
    int arrLength;
    myType * myData;
    myType * mediansArr;
};

//FUNCTIONS


//constructor
template<class myType>
dynamicMedians<myType>::dynamicMedians(){
    arrLength = 0;
    myData = NULL;
    mediansArr = NULL;
}
//destructor
template<class myType>
dynamicMedians<myType>::~dynamicMedians(){
    
    delete [] myData;
    delete [] mediansArr;
    
}
//allocates and fills array with input array. does not work if size is too small
template<class myType>
bool dynamicMedians<myType>::setData(myType inputArray[], const int size){
    //checks if the length of array is below the minimum
    if(size < MIN_LENGTH){
        cout << "Error, invalid size." << endl;
        return false;
    }
    //else run function
    //allocate array to size and fill data with inputArray
    myData = new myType [size];
    for(int i = 0; i < size; i++)
        myData[i] = inputArray[i];
   //set arrLength
    arrLength = size;
    return true;
}
//generates randomData%limit to array if size is big enough.
//used for test???
//tests either use this function or setData not both to allocate array
template<class myType>
bool dynamicMedians<myType>::generateData(const int size, const int limit){
    //checks if the length of array is below the minimum
    if(size < MIN_LENGTH){
        cout << "Error, invalid size." << endl;
        return false;
    }
    //else run function
    //allocates array by random numbers
    myData = new myType [size];
    for(int i = 0; i < size; i++)
        myData[i] = rand()%limit;
    arrLength = size;
    return true;
}
template<class myType>
void dynamicMedians<myType>::showData() const{
    cout << "Data:" << endl;
    cout << "-----" << endl;
    for(int i = 0; i < arrLength; i++){
        cout << myData[i] << " ";
    }
    cout << endl << endl;
}
template<class myType>
void dynamicMedians<myType>::showMedians() const{
    cout << "Dynamic Medians:" << endl;
    cout << "----------------" << endl;
    for(int i = 0; i < arrLength; i++){
        cout << mediansArr[i] << " ";
    }
    cout << endl << endl;
}
template<class myType>
myType dynamicMedians<myType>::getDataItem(const unsigned int index) const{
    return myData[index];
}
template<class myType>
myType dynamicMedians<myType>::getMediansItem(const unsigned int index) const{
    return mediansArr[index];
}
template<class myType>
void dynamicMedians<myType>::findMedians(){
    mediansArr = new myType[arrLength];
    myType currMedian = 1;
    minHeap<myType> MinHeap(0);
    maxHeap<myType> MaxHeap(0);
    int count = 0;
    while(count < arrLength){
        myType value = myData[count];
        if(MinHeap.getCount() == MaxHeap.getCount()){
            if(value < currMedian){
                MaxHeap.insert(value);
                currMedian = MaxHeap.peek();
            } else {
                MinHeap.insert(value);
                currMedian = MinHeap.peek();
            }
        }
        else if(MaxHeap.getCount() > MinHeap.getCount()){
            if(value < currMedian){
                MinHeap.insert(MaxHeap.deleteMax());
                MaxHeap.insert(value);
            } else {
                MinHeap.insert(value);
            }
            currMedian = (MaxHeap.peek() + MinHeap.peek())/2;
        }
        else if(MinHeap.getCount() > MaxHeap.getCount()){
            if(value < currMedian)
                MaxHeap.insert(value);
            else {
                myType data = MinHeap.deleteMin();
                MaxHeap.insert(data);
                MinHeap.insert(value);
            }
            currMedian = (MaxHeap.peek() + MinHeap.peek())/2;
        }
        mediansArr[count] = currMedian;
        count++;
        
    }
}



#endif /* dynamicMedians_h */
