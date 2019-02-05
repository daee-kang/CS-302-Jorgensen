//
//  mazeGenerator.hpp
//  ass 9
//
//  Created by Daee Kang on 11/4/18.
//  Copyright © 2018 Daee Kang. All rights reserved.
//

#ifndef mazeGenerator_hpp
#define mazeGenerator_hpp

#include <stdio.h>
#include <iostream>
using namespace std;

class mazeGenerator{
public:
    mazeGenerator();
    ~mazeGenerator();
    void getSize(int&, int&) const;
    bool setSize(int, int);
    void generate();
    bool printMazeData(const string) const;
    void printMazeText() const;
    bool getArguments(int, char *[], int&, int&, string&, bool&);
    void randomize();
private:
    int rows;
    int cols;
    int ** walls;
    static constexpr int MIN_ROWS = 5;
    static constexpr int MIN_COLS = 5;
    static constexpr int MAX_ROWS = 100000;
    static constexpr int MAX_COLS = 100000;
};




#endif /* mazeGenerator_hpp */
