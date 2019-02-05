//
//  linkedQueue.hpp
//  ass 4
//
//  Created by Daee Kang on 9/19/18.
//  Copyright © 2018 Daee Kang. All rights reserved.
//

#ifndef linkedQueue_h
#define linkedQueue_h
#define SIZE 32000
#include <stdio.h>
#include <iostream>

using namespace std;

//node stuff
template <class myType>
struct queueNode
{
    myType dataSet[SIZE];
    int front, back;
    queueNode<myType> *link;
};
//class header stuff
template <class myType>
class linkedQueue {
private:
    queueNode<myType> *queueFront; // head
    queueNode<myType> *queueRear; // follows trailing node
    int count;
public:
    linkedQueue();
    ~linkedQueue();
    bool isEmptyQueue() const;
    void initializeQueue();
    void addItem(const myType& newItem);
    myType front() const;
    myType back() const;
    void deleteItem();
    int queueCount();
    void printQueue();
};

/* --------------------------------------------------------------------------
                        FUNCTIONS AND STUFF DOWN HERE
   -------------------------------------------------------------------------- */
template <class myType>
linkedQueue<myType>::linkedQueue(){
    queueFront = NULL;
    queueRear = NULL;
    count = 0;
}

template <class myType>
linkedQueue<myType>::~linkedQueue(){
    //TODO:
}

template <class myType>
bool linkedQueue<myType>::isEmptyQueue() const {
    return count == 0;
}

template <class myType>
void linkedQueue<myType>::initializeQueue(){
    if(queueFront == NULL){
        //if empty
        queueNode<myType> * newNode;
        newNode = new queueNode<myType>;
        newNode -> link = NULL;
        newNode -> front = newNode-> back = 0;
        queueFront = queueRear = newNode;
    } else {
        //if adding new stack
        queueNode<myType> * newNode;
        newNode = new queueNode<myType>;
        newNode -> link = NULL;
        newNode -> front = newNode-> back = 0;
        queueRear -> link = newNode;
        queueRear = newNode;
    }
}


template <class myType>
void linkedQueue<myType>::addItem(const myType& newItem){
    if(count == 0){
        initializeQueue();
        queueFront -> dataSet[0] = newItem;
        count++;
    } else if ((count % SIZE) == 0){//if stack reaches limit
        initializeQueue();
        queueRear -> dataSet[queueRear->back] = newItem;
        count++;
    } else {
        //regular push
        queueRear -> back++;
        queueRear -> dataSet[queueRear-> back] = newItem;
        count++;
    }
}

template <class myType>
myType linkedQueue<myType>::front() const {
    return queueFront->dataSet[queueFront->front];
}

template <class myType>
myType linkedQueue<myType>::back() const {
    return queueRear->dataSet[queueRear->back];
}

template <class myType>
void linkedQueue<myType>::deleteItem(){
    if(isEmptyQueue()) return;
    else {
        if(queueFront->front == queueFront->back){ //delete node
            queueNode<myType> * temp;
            
            temp = queueFront->link;
            delete queueFront;
            queueFront = temp;
            temp = NULL;
            count--;
            return;
        }
        count--;
        queueFront->front++;
        return;
    }
}

template <class myType>
int linkedQueue<myType>::queueCount(){
    return count;
}

template <class myType>
void linkedQueue<myType>::printQueue(){
    queueNode<myType> * traverseNode = queueFront;
    int counter = traverseNode-> front;
    
    while(traverseNode!=NULL){
        while(counter <= traverseNode->back){
            if(counter== SIZE) counter = 0;
            cout << traverseNode->dataSet[counter] << " ";
            counter++;
        }
        traverseNode = traverseNode->link;
    }
    
}
#endif /* linkedQueue_h */
