//daee kang ass 7 sec 1004
//i don't know what's going on with my code
//incomplete i am sorry
//but i gotta turn something in;

#ifndef assocArray_hpp
#define assocArray_hpp
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

/********************<CLASS DECLARATION>*************************/

template <class myType>
class assocArray{
private:
    unsigned int hashSize;
    unsigned int reSizeCount;
    unsigned int collisionCount;
    unsigned int entries;
    unsigned int currIteratorIndex;
    
    string * hashKeys;
    myType * hashValues;
    
    static constexpr double loadFactor = 0.65;
    static constexpr unsigned int initialHashSize = 1013;
    static constexpr unsigned int hashSizesCount = 13;
    static constexpr unsigned int hashSizes[13] =
    {9973, 30011, 60013, 120017, 240089, 480043,
        960017, 1920013, 3840037, 7680103, 15360161,
        30720299, 61440629};
public:
    assocArray();
    ~assocArray();
    myType& operator[] (const string);
    string begin();
    string end();
    string next();
    bool exists(const string) const;
    bool erase(const string);
    void printHash() const;
    void showStats() const;
    unsigned int hash(const string) const;
    void rehash();
};



//gotta include this in for some reason
template <class myType>
constexpr unsigned int assocArray<myType>::hashSizes[];


/********************<FUNCTION DEFINITION>*************************/

/*
 class default constructor, sets initial hash sizes to the given and all else
 values to 0.
 */
template <class myType>
assocArray<myType>::assocArray(){
    reSizeCount = 0;
    collisionCount = 0;
    entries = 0;
    currIteratorIndex = 0;
    //initialize dynamic arrays to the initial hash size
    hashSize = initialHashSize;
    hashKeys = new string [hashSize];
    for(unsigned int i = 0; i < hashSize; i++)
        hashKeys[i] = "";
    hashValues = new myType [hashSize];
}
/*
 deconstructor for dynamically created arrays ( keys and values )
 */
template <class myType>
assocArray<myType>::~assocArray(){
    delete [] hashKeys;
    delete [] hashValues;
}
template <class myType>
myType& assocArray<myType>::operator[](const string key){
    
    if(!exists(key)){
        //insert it in
        //check load factor
        if(double(entries)/double(hashSize) > loadFactor)
            rehash();
        
        unsigned int index = hash(key);
        unsigned int i = 0;
        while(hashKeys[index] != ""){
            i++;
            collisionCount++;
            index = (index + i * i) % hashSize;
        }
        entries++;
        hashKeys[index] = key;
        return hashValues[(index + (i*i))%hashSize];
    } else {
        //time 2 search baby
        //know for a fact value exists.
        unsigned int index = hash(key);
        unsigned int i = 0;
        while(hashKeys[index] != key){
            i++;
            index = (index + i * i) % hashSize;
        }
        return hashValues[(index + (i*i))%hashSize];
    }
}
//find the beginning of the hashTable and set currIteratorIndex to that location
template <class myType>
string assocArray<myType>::begin(){
    currIteratorIndex = 0;
    bool found = false;
    while(!found){
        currIteratorIndex++;
        if(currIteratorIndex >= hashSize)
            return "";
        if(hashKeys[currIteratorIndex] != "*")
            if(hashKeys[currIteratorIndex] != "")
                found = true;
    }

    if(found) return hashKeys[currIteratorIndex];
    else return "";
}
//find end, don't know what this function is for lol
template <class myType>
string assocArray<myType>::end(){
    return "";
}
//find next value on hashtable and set to curriteratorindex
template <class myType>
string assocArray<myType>::next(){
    for (int i = currIteratorIndex + 1; i < hashSize; i++){
        if(hashKeys[i] != "")
            if(hashKeys[i] != "*"){
                currIteratorIndex = i;
                return hashKeys[i];
            }
        if(i >= hashSize){
            return "";
        }
        
    }
    return "";
}
//finds if the item exists in the hashkeys array
template <class myType>
bool assocArray<myType>::exists(const string key) const{
    unsigned int index = hash(key);
    if(hashKeys[index] == "")
        return false;
    else if(hashKeys[index] != key){
        unsigned int i = 0;
        while(hashKeys[index] != key){
            if(hashKeys[index] == "")
                return false;
            i++;
            index = (index + i*i) % hashSize;
        }
        return true; // found
    }
    return true;
}
template <class myType>
bool assocArray<myType>::erase(const string key){
    if(!exists(key))
        return false;
    unsigned int index = hash(key);
    unsigned int i = 0;
    while(hashKeys[index] != key){
        i++;
        index = (index + i*i) % hashSize;
    }
    //found
    entries--;
    hashKeys[index] = "*";
    return true;
}
template <class myType>
void assocArray<myType>::printHash() const{
    
}
template <class myType>
void assocArray<myType>::showStats() const{
    cout << "Hash Stats" << endl;
    cout << " " << "Current Entries Count: " << entries << endl;
    cout << " " << "Current Hash Size: " << hashSize << endl;
    cout << " " << "Hash Resize Operations: " << reSizeCount << endl;
    cout << " " << "Hash Collisions: " << collisionCount << endl;
}
//hash function (SDBM standard)
template <class myType>
unsigned int assocArray<myType>::hash(const string key) const{
    //SDBM
    unsigned int hashVal = 0;
    
    for(unsigned int i = 0; i < key.length(); i++)
        hashVal = key[i] + (hashVal << 6) + (hashVal << 16) - hashVal;
    return hashVal % hashSize;
    //TODO: ASCI STUFF
}
template <class myType>
void assocArray<myType>::rehash(){
    unsigned int oldSize = hashSize;
    hashSize = hashSizes[reSizeCount];

    string * newKeys;
    newKeys= new string [hashSize];
    myType * newValues;
    newValues = new myType [hashSize];
    
    for(int i = 0; i < hashSize; i++){
        newKeys[i] = "";
        newValues[i] = NULL;
    }
    
    for (int i = 0; i < oldSize; i++){
        unsigned int index = hash(hashKeys[i]);
        unsigned int k = 0;
        while(hashKeys[index] != ""){
            k++;
            collisionCount++;
            index = (index + k*k) % hashSize;
        }
        newKeys[index] = hashKeys[i];
        newValues[index] = hashValues[i];
    }

    delete [] hashKeys;
    delete [] hashValues;
    hashKeys = newKeys;
    hashValues = newValues;
    
    // Rehash was successful
    // Update the number of times the hash table has been resized
    reSizeCount++;
    
    
}
#endif /* assocArray_hpp */

