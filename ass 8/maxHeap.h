/*

This file is for the maxHeap structure used in the main file and pfTest file.
The following template creates a priority heap using max values. 
It includes basic functions like deleteMax, isEmpty , insert ,
reheap up and down, and resize. 

Also includes 3 functions used for testing, makerandomheap 1
make random heap 2 and heapify. These are use to calculate 
the time difference in between inserting using the function or 
inserting into the array and then heapifying.

*/

#ifndef maxHeap_h
#define maxHeap_h

using namespace std;

//class declaration
template<class myType>
class maxHeap{
public:
    maxHeap(unsigned int = 1000);
    ~maxHeap();
    unsigned int getCount() const;
    void insert(const myType);
    myType deleteMax();
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
maxHeap<myType>::maxHeap(unsigned int size){
    if(size >= 1000)
        heapSize = size;
    else heapSize = 1000;
    count = 0;
    myHeap = new myType [heapSize];
}
//deconstructor
template<class myType>
maxHeap<myType>::~maxHeap(){
    delete [] myHeap;
}
//returns count
template<class myType>
unsigned int maxHeap<myType>::getCount() const{
    return count;
}
//inserts value and then reheaps up. also checks
//to see if the table needs to be resized.
template<class myType>
void maxHeap<myType>::insert(const myType insertData){
    if(++count == heapSize)
        resize();
    myHeap[count] = insertData;
    reheapUp(count);
}
//deletes the top of the heap if applicable 
 //and then reheaps down return the top value.
template<class myType>
myType maxHeap<myType>::deleteMax(){
    if(isEmpty()){
        cout << "Error, max heap empty." << endl;
        return {};
    }
    //holds return value of the top of heap
    myType returnValue = myHeap[1];
    //replace top of heat with bottom value
    myHeap[1] = myHeap[count];
    //"deletes" the last value
    count--;
    //reheap down from the top
    reheapDown(1);
    return returnValue;
}
//returns the top value
template<class myType>
myType maxHeap<myType>::peek(){
    if(isEmpty())
        return {};
    else return myHeap[1];
}
//returns if empty
template<class myType>
bool maxHeap<myType>::isEmpty() const{
    return (count == 0);
}
//prints heap
template<class myType>
void maxHeap<myType>::printHeap() const{
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
void maxHeap<myType>::makeRandHeap1(const unsigned int size, const unsigned int limit){
    srand(73);
    for(int i = 1; i < size; i++)
        insert(rand()%limit);
}
//makes random heap and organizes with heapify function.
template<class myType>
void maxHeap<myType>::makeRandHeap2(const unsigned int size , const unsigned int limit){
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
void maxHeap<myType>::reheapUp(unsigned int position){
    //baseCase
    if(position <= 1)
        return;
     //time to swap baby
    unsigned int parentNode = position/2;
    if(myHeap[position] > myHeap[parentNode]){
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
void maxHeap<myType>::reheapDown(unsigned int position){
    //get child left and right node
    unsigned int left = position * 2;
    unsigned int right = position * 2 + 1;
    //min pos is used to see which left or right is smaller
    myType temp;
    //checks boundaries
    unsigned int maxPos;
    //holds value for swapping
    if(left > count) return;
    if(right > count)
        maxPos = right;
    else {
        if(myHeap[left] >= myHeap[right])
            maxPos = left;
        else maxPos = right;
    }
    //swapt time baby
    if(myHeap[maxPos] > myHeap[position]){
        temp = myHeap[maxPos];
        myHeap[maxPos] = myHeap[position];
        myHeap[position] = temp;
        reheapDown(maxPos);
    }
}
template<class myType>
void maxHeap<myType>::heapify(){
    for (int i = count / 2; i >= 1; i--)
        reheapDown(i);
}
//makes new array double the size, copies it and replaces it.
template<class myType>
void maxHeap<myType>::resize(){
    heapSize = heapSize * 2;
    myType * newHeap = new myType [heapSize];
    for(int i = 0; i < count; i++)
        newHeap[i] = myHeap[i];
    delete [] myHeap;
    myHeap = newHeap;
    newHeap = NULL;
}
#endif /* maxHeap_h */
