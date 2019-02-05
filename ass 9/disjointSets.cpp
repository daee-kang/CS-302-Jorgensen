//basic disjoin set class
#include "disjointSets.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

disjointSets::disjointSets(int size){
    if(size >= MIN_SIZE){
        setSize = size;
    } else setSize = 10;
    links = new int [setSize];
    for(int i = 0; i < setSize; i++)
        links[i] = -1;
    ranks = new int [setSize];
    for(int i = 0; i < setSize; i++)
        ranks[i] = 1;
}
disjointSets::~disjointSets(){
    delete [] links;
    delete [] ranks;
}
int disjointSets::entries() const{
    return setSize;
}
void disjointSets::printSets() const{
    cout << "index: ";
    for(int i = 0; i < setSize; i++)
        cout << setw(2) << i << " ";
    cout << endl;
    
    cout << "links: ";
    for(int i = 0; i < setSize; i++)
        cout << setw(2) << links[i] << " ";
    cout << endl;
    
    cout << "ranks: ";
    for(int i = 0; i < setSize; i++)
        cout << setw(2) << ranks[i] << " ";
    cout << endl;
}
int disjointSets::setUnion(int r1, int r2){
    //range check
    if(r1 < 0 or r1 > setSize or r2 < 0 or r2 > setSize)
        return -1;
    //parent and child variable
    int p = 0, c = 0;
    //find parent if not parent
    if(setFind(r1) != -1)
        r1 = setFind(r1);
    if(setFind(r2) != -1)
        r2 = setFind(r2);
    
    if(ranks[r1] <= ranks[r2]){
        p = r2;
        c = r1;
    } else {
        p = r1;
        c = r2;
    }
    links[c] = p;
    if(ranks[r1] == ranks[r2])
        ranks[p]++;
    return p;
}
int disjointSets::setFind(int search){
    //range check
    if(search > setSize or search < 0)
        return -1;
    
    if(links[search] < 0)
        return search;
    else return links[search] = setFind(links[search]);
}

