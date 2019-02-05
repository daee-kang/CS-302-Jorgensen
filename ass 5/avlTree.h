/* below is a class definition and function definitions using templates.
 the purpose of this class is to create a basic functioning avl tree that will
 be later used for the word puzzle class.
 
 the avl tree class uses nodes with a left and right
 and includes options to print in different options,
 to search for an item, and basic traversal. Also implements rotations to keep
 the tree balanced when inserting a node.
 
 also includes a prefix function that will look for the prefix of a number of letter and return
 true if found. big use for word puzzle.cpp
 
 */



#ifndef avlTree_h
#define avlTree_h

#include <iostream>
#include "linkedQueue.h"
using namespace std;

//node struct for tree (has left and right)
template <class myType>
struct nodeType {
    myType keyValue;
    int nodeHeight;
    nodeType<myType> *left;
    nodeType<myType> *right;
};
//enum for option to search
enum treeTraversalOptions { INORDER, PREORDER,
    POSTORDER, LEVELORDER, NONE };

//CLASS HEADER
template <class myType>
class avlTree{
public:
    avlTree();
    ~avlTree();
    void destroyTree();
    int countNodes() const;
    int height() const;
    bool search(myType) const;
    void printTree(treeTraversalOptions) const;
    void insert(myType);
    void deleteNode(myType);
    bool isPrefix(string) const;
private:
    void destroyTree(nodeType<myType> *);
    int countNodes(nodeType<myType> *) const;
    int height(nodeType<myType> *) const;
    nodeType<myType> * search(myType, nodeType<myType> *) const;
    void printTree(nodeType<myType> *, treeTraversalOptions) const;
    void printLevelOrder() const;
    nodeType<myType> * insert (myType, nodeType<myType> *);
    nodeType<myType> * rightRotate(nodeType<myType> *);
    nodeType<myType> * leftRotate(nodeType<myType> *);
    int getBalance(nodeType<myType> *) const;
    nodeType<myType> * deleteNode(myType, nodeType<myType> *);
    nodeType<myType> * minValueNode(nodeType<myType> *) const;
   //variables or just variable lol
    nodeType<myType> * root;
};

// BELOW ARE FUNCTIONS YEAH

/*
 PUBLIC FUNCTIONS
 */

//constructor, sets root to null
template <class myType>
avlTree<myType>::avlTree(){
    root = NULL;
}
//destructor by calling destroyTree
template <class myType>
avlTree<myType>::~avlTree(){
    destroyTree();
}
//calls the deleteTree functions then sets root equal to null.
template <class myType>
void avlTree<myType>::destroyTree(){
    destroyTree(root);
    root = NULL;
}
//if root = null, there are no nodes and returns 0.
//else it will call the recursive countNode function.
template <class myType>
int avlTree<myType>::countNodes() const{
    if(root == NULL) return 0;
    else return countNodes(root);
}
//returns height by calling private height function.
template <class myType>
int avlTree<myType>::height() const{
    return height(root);
}
//searches for value in tree, returns bool
//calls private search function
template <class myType>
bool avlTree<myType>::search(myType value) const{
    nodeType<myType> * node = search(value, root);
    if(node == NULL){
        return false;
    }
    else return true;
}
template <class myType>
void avlTree<myType>::printTree(treeTraversalOptions options) const{
    printTree(root, options);
}
template <class myType>
void avlTree<myType>::insert(myType value){
    root = insert(value, root);
}
template <class myType>
void avlTree<myType>::deleteNode(myType value){
    deleteNode(value, root);
}
template <class myType>
bool avlTree<myType>::isPrefix(string preStr) const {
    bool foundStr = false;
    nodeType<myType> * node = root;
    if(node == NULL)
        return false;
    while(!foundStr){
        string word = node->keyValue;
        word = word.substr(0, preStr.length());
        if(preStr == word){
            foundStr = true;
        } else if (preStr < word){
            if(node->left == NULL)
                return false;
            node = node->left;
        }
            else if (preStr > word){
            if(node->left == NULL)
                return false;
            node = node->right;
            }
    }
    
    // If string was found, return true
    if(foundStr)
        return true;
    
    else
        return false;
}


/*
 PRIVATE FUNCTIONs
 */

//destroys by going down the tree, at every node, it will check left
//and right to see if it can go further. base case is if its null so
//when it hits null it will return nothing, and then delete the
//node.
template <class myType>
void avlTree<myType>::destroyTree(nodeType<myType> * node){
    if(node != NULL){
        destroyTree(node -> left);
        destroyTree(node -> right);
        delete node;
    } else return; //node == NULL
}
//private count node functions used by public count node function.
template <class myType>
int avlTree<myType>::countNodes(nodeType<myType> * node) const{
    //recursively every node will have a count of 1
    int count = 1;
    //as the function returns, it will return the count of 1,
    //adding to the main recursive call count value.
    if(node -> left != NULL)
        count += countNodes(node -> left);
    if(node -> right != NULL)
        count += countNodes(node -> right);
    //returns total count
    return count;
}
template <class myType>
int avlTree<myType>::height(nodeType<myType> *node) const{
    if(node == NULL)
        return 0;
    else{
        int left = height(node -> left);
        int right = height(node -> right);
        return (max(left + 1, right + 1));
    }
}
//recursive function, will search through every node by calling itself
//changing only the node.
//returns true if found.
template <class myType>
nodeType<myType> * avlTree<myType>::search(myType value, nodeType<myType> * node) const{
    if(node == NULL)
        return NULL;
    if(node->keyValue == value)
        return node;
    else {
        if(value > node->keyValue)
            node = search(value, node->right);
        else if(value < node->keyValue)
            node = search(value, node->left);
    }
    return node;
}
template <class myType>
void avlTree<myType>::printTree(nodeType<myType> * node, treeTraversalOptions options) const{
    if(options == INORDER){
        if(node != NULL){
            printTree(node -> left, options);
            cout << node ->keyValue;
            printTree(node -> right, options);
        }
    } else if (options == PREORDER){
        if(node != NULL){
            cout << node -> keyValue;
            printTree(node -> left, options);
            printTree(node -> right, options);
        }
    } else if (options == POSTORDER){
        if(node != NULL){
            printTree(node -> left, options);
            printTree(node -> right, options);
            cout << node -> keyValue;
        }
    } else if (options == LEVELORDER) printLevelOrder();
    else if(options == NONE){
        return;
    }
}
//prints by level order using algorithm given to us in pdf
template <class myType>
void avlTree<myType>::printLevelOrder() const{
    if(root == NULL) return;
    //queue object
    linkedQueue<nodeType<myType> *> queue;
    
    queue.addItem(root);
    while(queue.isEmptyQueue() == false){
        //dequeue node and assign to node
        nodeType<myType> * node = queue.front();
        //print data
        cout << node -> keyValue << " ";
        queue.deleteItem();
        //enqueue children
        if(node->left != NULL)
            queue.addItem(node->left);
        if(node->right != NULL)
            queue.addItem(node->right);
    }
}

template <class myType>
nodeType<myType> * avlTree<myType>::insert(myType value, nodeType<myType> * node){
    //if root = null, create a new node with given and value and return
    if(node == NULL){
        node = new nodeType<myType>;
        node -> nodeHeight = 1;
        node->keyValue = value;
        node->right = node->left = NULL;
        return node;
    } else if (value < node->keyValue)
        node->left = insert(value, node->left);
    else if(value > node->keyValue)
        node->right = insert(value, node->right);
    
    //set node height
    node -> nodeHeight = 1 + max(height(node->left), height (node->right));
    //get balance factpr
    int balanceFactor = getBalance(node);

    //check for possible cases for unbalanced
    if(balanceFactor > 1 and value < node->left->keyValue)
        return rightRotate(node);
    if(balanceFactor < -1 and value > node->right->keyValue)
        return leftRotate(node);
    if(balanceFactor > 1 and value > node->left->keyValue){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if(balanceFactor < -1 and value < node->right->keyValue){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    //return node (possibly unchanged)
    return node;
}
template <class myType>
nodeType<myType> * avlTree<myType>::rightRotate(nodeType<myType> * node){
    nodeType<myType> * temp1 = node->left;
    nodeType<myType> * temp2 = temp1->right;
    
    temp1->right = node;
    node->left = temp2;
    
    node->nodeHeight = max(height(node->left), height(node->right)) + 1;
    temp1->nodeHeight = max(height(temp1->left), height(temp1->right)) + 1;
    
    return temp1;
}
template <class myType>
nodeType<myType> * avlTree<myType>::leftRotate(nodeType<myType> *node){
    nodeType<myType> * temp1 = node->right;
    nodeType<myType> * temp2 = temp1->left;
    
    temp1->left = node;
    node->right = temp2;
    
    node->nodeHeight = max(height(node->left), height(node->right)) + 1;
    temp1->nodeHeight = max(height(temp1->left), height(temp1->right)) + 1;
    
    return temp1;
}
template <class myType>
int avlTree<myType>::getBalance(nodeType<myType> * node) const{
    return (height(node->left) - height(node->right));
}
template <class myType>
nodeType<myType> * avlTree<myType>::deleteNode(myType value, nodeType<myType> * node){
    if(node == NULL) return node;
    //call recursive functions until it finds the node that equals the value
    if(value < node->keyValue)
        node->left = deleteNode(value, node->left);
    else if(value > node->keyValue)
        node->right = deleteNode(value, node->right);
    //found, now delete the node
    else{
        //nodes with less then two parents
        nodeType<myType> * temp;
        if(node->left == NULL){
            temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == NULL){
            temp = node->left;
            delete node;
            return temp;
        }
        //two parent nodes
        //using min value node
        temp = minValueNode(node->right);
        node->keyValue = temp->keyValue;
        node->right = deleteNode(temp->keyValue, node->right);
    } return node;
}
template <class myType>
nodeType<myType> * avlTree<myType>::minValueNode(nodeType<myType> * node) const{
    while(node -> left != NULL)
        node = node -> left;
    return node;
}
#endif /* avlTree_h */
