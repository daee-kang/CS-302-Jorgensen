/*

This file is for the minHeap structure used in the main file and pfTest file.
The following template creates a priority heap using min values. 
It includes basic functions like deleteMin, isEmpty , insert ,
reheap up and down, and resize. 

Also includes 3 functions used for testing, makerandomheap 1
make random heap 2 and heapify. These are use to calculate 
the time difference in between inserting using the function or 
inserting into the array and then heapifying.

*/

#ifndef minHeap_h
#define minHeap_h

using namespace std;

//class declaration
template<class myType>
class minHeap{
public:
    minHeap(unsigned int = 1000);
    ~minHeap();
    unsigned int getCount() const;
    void insert(const myType);
    myType deleteMin();
    myType peek();
    bool isEmpty() const;
    void printHeap() const;
    void makeRandHeap1(const unsigned int, const unsigned int);
    void makeRandHeap2(const unsigned int, const unsigned int);
private:
    void reheapUp(unsigned int);
    void reheapDown(unsigned int);
    void heapify();
    void resize();
    //variables
    unsigned int count;
    unsigned int heapSize;
    myType * myHeap;
};

//--------FUNCTIONS--------//

//constructor, if size is below 1000, it will 
//set it to 1000, else set it to size. 
template<class myType>
minHeap<myType>::minHeap(unsigned int size){
    if(size >= 1000)
        heapSize = size;
    else heapSize = 1000;
    count = 0;
    myHeap = new myType [heapSize];
}
//deconstructor
template<class myType>
minHeap<myType>::~minHeap(){
    delete [] myHeap;
}
//returns count
template<class myType>
unsigned int minHeap<myType>::getCount() const{
    return count;
}
//inserts value and then reheaps up. also checks
//to see if the table needs to be resized.
template<class myType>
void minHeap<myType>::insert(const myType insertData){
    if(++count == heapSize)
        resize();
    myHeap[count] = insertData;
    reheapUp(count);
}
//deletes the top of the heap if applicable 
 //and then reheaps down return the top value.
template<class myType>
myType minHeap<myType>::deleteMin(){
    if(isEmpty()){
        cout << "Error, min heap empty." << endl;
        return {};
    }
    //holds return value of the top of heap
    myType returnValue = myHeap[1];
    //replace top of heat with bottom value
    myHeap[1] = myHeap[count];
    //"deletes" the last value
    count--;
    //reheap down from the top
    int index = 1;
    reheapDown(index);
    return returnValue;
}
//returns the top value.
template<class myType>
myType minHeap<myType>::peek(){
    if(isEmpty())
        return {};
    else return myHeap[1];
}
//returns if empty
template<class myType>
bool minHeap<myType>::isEmpty() const{
    return (count == 0);

}
//prints heap
template<class myType>
void minHeap<myType>::printHeap() const{
    int j = 1;
    int k = 0;
    //j is a container for the levels of the heap
    //if k reaches the level, it starts over again
    //but j is multiplied by 2. 

    //basically just prints in 1, 2, 4, 8 ... etc lol
    for(int i = 1; i <= count; i++){
        cout << myHeap[i] << endl;
        k++;
        if(k == j){
            cout << endl;
            j = j * 2;
            k = 0;
        }
    }
    cout << endl;
}
//makes random heap and inserts with the function
template<class myType>
void minHeap<myType>::makeRandHeap1(const unsigned int size, const unsigned int limit){
    srand(73);
    for(int i = 1; i < size; i++)
        insert(rand()%limit);
}
//makes random heap and organizes with heapify function.
template<class myType>
void minHeap<myType>::makeRandHeap2(const unsigned int size, const unsigned int limit){
    srand(73);
    for(int i = 1; i < size; i++){
        myHeap[i] = rand()%limit;
        count++;
    }
    heapify();
}
//starts from the position(around bottom level) and works up
//swapping if needed.
template<class myType>
void minHeap<myType>::reheapUp(unsigned int position){
    //baseCase
    if(position <= 1)
        return;

    //time to swap baby
    unsigned int parentNode = position/2;
    if(myHeap[position] < myHeap[parentNode]){
        myType temp = myHeap[position];
        myHeap[position] = myHeap[parentNode];
        myHeap[parentNode] = temp;
    }
    //recursive call
    reheapUp(parentNode);
}
//reheaps down from the top of the value. for heapify, 
//its used at every parent node
template<class myType>
void minHeap<myType>::reheapDown(unsigned int position){
    //get child left and right node
    unsigned int left = position * 2;
    unsigned int right = position * 2 + 1;
    //min pos is used to see which left or right is smaller
    unsigned int minPos;
    //holds value for swapping
    myType temp;
    //checks boundaries
    if(left > count) return;
    if(right > count)
        minPos = left;
    else {
        if(myHeap[left] <= myHeap[right])
            minPos = left;
        else minPos = right;
    }
    //time to swap baby
    if(myHeap[minPos] < myHeap[position]){
        temp = myHeap[minPos];
        myHeap[minPos] = myHeap[position];
        myHeap[position] = temp;
        reheapDown(minPos);
    }
}
template<class myType>
void minHeap<myType>::heapify(){
    for (int i = count / 2; i >= 1; i--)
        reheapDown(i);

}
//makes new array double the size, copies it and replaces it.
template<class myType>
void minHeap<myType>::resize(){
    heapSize = heapSize * 2;
    myType * newHeap = new myType [heapSize];
    for(int i = 0; i < count; i++)
        newHeap[i] = myHeap[i];
    delete [] myHeap;
    myHeap = newHeap;
    newHeap = NULL;
}
#endif /* minHeap_h */
