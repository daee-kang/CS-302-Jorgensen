//
//  linkedStack.hpp
//  ass 4
//
//  Created by Daee Kang on 9/19/18.
//  Copyright © 2018 Daee Kang. All rights reserved.
//

#ifndef linkedStack_h
#define linkedStack_h
#define SIZE 32000

#include <stdio.h>
#include <iostream>

using namespace std;

//node stuff
template <class myType>
struct nodeType {
    myType dataSet[SIZE];
    //use datasetSize to create a new linked list when the current is full
    int top;
    //set to zero with new list
    nodeType<myType> *link;
    //linker
};

//header class stuff
template <class myType>
class linkedStack {
private:
    nodeType<myType> *stackTop;
    int count;
public:
    linkedStack();
    ~linkedStack();
    bool isEmptyStack() const;
    void initializeStack();
    int stackCount();
    void push(const myType& newItem);
    myType top() const;
    void pop();
};

/* --------------------------------------------------------------------------
                        FUNCTIONS AND STUFF DOWN HERE
   -------------------------------------------------------------------------- */
//constructor -- initializes data
template <class myType>
linkedStack<myType>::linkedStack(){
    stackTop = NULL;
    count = 0;
}
//deconstructor -- yea
template <class myType>
linkedStack<myType>::~linkedStack(){
    while(stackTop != NULL){
        nodeType<myType> * temp = stackTop -> link;
        delete stackTop;
        stackTop = temp;
    }
    delete stackTop;
}
//returns if the stack is empty or nah
template <class myType>
bool linkedStack<myType>::isEmptyStack() const{
    return count == 0; //returns false or true
}
//initalizes to a new empty stack
template <class myType>
void linkedStack<myType>::initializeStack(){
    if(stackTop == NULL){
        //if empty
        nodeType<myType> * newNode;
        newNode = new nodeType<myType>;
        newNode -> link = NULL;
        newNode -> top = 0;
        stackTop = newNode;
    } else {
        //if adding new stack
        nodeType<myType> * newNode;
        newNode = new nodeType<myType>;
        newNode -> link = stackTop;
        newNode -> top = 0;
        stackTop = newNode;
    }
}
//returns the stack count
template <class myType>
int linkedStack<myType>::stackCount(){
    return count;
}
//pushes new myType item into the stack
template <class myType>
void linkedStack<myType>::push(const myType& newItem){
    if(count == 0){
        initializeStack();
        stackTop -> dataSet[0] = newItem;
        count++;
    } else if ((count % SIZE) == 0){//if stack reaches limit
        initializeStack();
        stackTop -> dataSet[stackTop->top] = newItem;
        count++;
    } else {
        //regular push
        stackTop -> top++;
        stackTop -> dataSet[stackTop -> top] = newItem;
        count++;
    }
}
//returns the top of the stack
template <class myType>
myType linkedStack<myType>::top() const{
    return (stackTop->dataSet[stackTop->top]);
    //the top node has current array, return top of the array
}
//pops the top of the stack
template <class myType>
void linkedStack<myType>::pop(){
    if(isEmptyStack()) return;
    else {
        if(stackTop->top == 0){ //delete node
            nodeType<myType> * temp;
            
            temp = stackTop->link;
            delete stackTop;
            stackTop = temp;
            temp = NULL;
            count--;
            return;
        }
        count--;
        stackTop->top--;
        return;
    }
    
}

#endif /* linkedStack_h */
