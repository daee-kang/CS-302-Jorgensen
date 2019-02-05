//
//  disjointSets.hpp
//  ass 9
//
//  Created by Daee Kang on 11/4/18.
//  Copyright © 2018 Daee Kang. All rights reserved.
//

#ifndef disjointSets_hpp
#define disjointSets_hpp

#include <stdio.h>

class disjointSets{
public:
    disjointSets(int = 10);
    ~disjointSets();
    int entries() const;
    void printSets() const;
    int setUnion(int, int);
    int setFind(int);
private:
    int setSize;
    int * links;
    int * ranks;
    static constexpr int MIN_SIZE = 10;
};








#endif /* disjointSets_hpp */
