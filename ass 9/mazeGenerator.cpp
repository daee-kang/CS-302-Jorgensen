//
//  mazeGenerator.cpp
//  ass 9
//
//  Created by Daee Kang on 11/4/18.
//  Copyright © 2018 Daee Kang. All rights reserved.
//




#include "mazeGenerator.hpp"
#include "disjointSets.hpp"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

using namespace std;

mazeGenerator::mazeGenerator(){
    rows = 0;
    cols = 0;
    walls = NULL;
}
mazeGenerator::~mazeGenerator(){
    //TODO: delete double pointer array on size
}
void mazeGenerator::getSize(int& row, int& col) const{
    row = rows;
    col = cols;
}
bool mazeGenerator::setSize(int row, int col){
    if(col < MIN_COLS or col > MAX_COLS)
        return false;
    if(row < MIN_ROWS or row > MAX_ROWS)
        return false;
    
    cols = col;
    rows = row;
    
    int indexCount = col * row;
    //calculate total walls
    int totalWalls = 0;
    for(int i = 0; i < cols - 1; i++)
        totalWalls = totalWalls + ((rows - 1) * 2 + 1);
    totalWalls += rows - 1;
    
    //initiate double pointer array
    walls = new int * [2];
    walls[0] = new int [totalWalls];
    walls[1] = new int [totalWalls];

    //variables for for looping
    int count1 = indexCount - 1;
    int count2 = indexCount - cols;

    int count = 0;
    for(int i = 0; i < count1; i++){
        if((i + 1) % cols == 0)
            continue;
        walls[0][count] = i;
        walls[1][count] = i + 1;
        
        cout << i <<", " << i + 1 << " went in array pos " << count << endl;

        count++;
        
        
    }
    for(int i = 0; i < count2; i++){
        walls[0][count] = i;
        walls[1][count] = i + cols;
        cout << i <<", " << i + cols << " went in array pos " << count << endl;

        
        count++;
        

    }
    return true;
}
void mazeGenerator::generate(){
    //gotta copy this code again cos there is no variable for this lmao
    randomize();
    
    int totalWalls = 0;
    for(int i = 0; i < cols - 1; i++)
        totalWalls = totalWalls + ((rows - 1) * 2 + 1);
    totalWalls += rows - 1;
    
    disjointSets mazeSet = disjointSets(rows*cols);
    
    for(int i = 0; i < totalWalls; i++){
        int cell1, cell2;
        cell1 = walls[0][i];
        cell2 = walls[1][i];
        if(mazeSet.setFind(cell1) == mazeSet.setFind(cell2)){
            continue;
        } else {
        mazeSet.setUnion(cell1, cell2);
            walls[0][i] = -1;
            walls[1][i] = -1;
        }
    }
    }
void mazeGenerator::randomize(){
    //get count of walls because there is no variable
    //for it lmao
    int totalWalls = 0;
    for(int i = 0; i < cols - 1; i++)
        totalWalls = totalWalls + ((rows - 1) * 2 + 1);
    totalWalls += rows - 1;
    
    //loop time baby
    for(int i = totalWalls - 1; i > 0; i--){
        int switchIndex = rand() % i+1;
        int temp1, temp2;
        temp1 = walls[0][i];
        temp2 = walls[1][i];
        walls[0][i] = walls[0][switchIndex];
        walls[1][i] = walls[1][switchIndex];
        walls[0][switchIndex] = temp1;
        walls[1][switchIndex] = temp2;
    }
}
bool mazeGenerator::printMazeData(const string fName) const{
    ofstream out;
    out.open(fName);
    if(!out.is_open())
        return false;
    out << "ROWS " << rows << " COLS " << cols << endl;
    
    //again lol
    int totalWalls = 0;
    for(int i = 0; i < cols - 1; i++)
        totalWalls = totalWalls + ((rows - 1) * 2 + 1);
    totalWalls += rows - 1;
    
    for(int i = 0; i < totalWalls; i++){
        if(walls[0][i] == -1)
            continue;
        else {
            out << "WALL " << walls[0][i] << " " << walls[1][i] << endl;
        }
    }
    out.close();
    return true;
}
void mazeGenerator::printMazeText() const{
    
    //not finished
    
    
    
    int totalWalls = 0;
    for(int i = 0; i < cols - 1; i++)
        totalWalls = totalWalls + ((rows - 1) * 2 + 1);
    totalWalls += rows - 1;
    
    int count1 = cols*rows - rows;
    int count2 = cols*rows - cols;
    
    //initiate double pointer array
    bool isWall[2][totalWalls];
    
    for(int i = 0; i < totalWalls; i++){
        isWall[0][i] = false;
        isWall[1][i] = false;
    }
    
    //variables for for looping
    for(int i = 0; i < totalWalls; i++){
        int cell1 = walls[0][i];
        int cell2 = walls[1][i];
        
        if(cell1 == -1 or cell2 == -1)
            continue;
        
        cout << "fuck:" << walls[0][i] << ", " << walls[1][i] <<" ";

        if(cell1 == cell2 - 1){
            int count = 0;
            int divider = cell1;
            if(cell1 > cols){
                count = cell1 / cols;
            }
            isWall[0][cell1 - count] = true;
            isWall[1][cell1 - count] = true;
            cout << "went in array pos " << cell1 - count<< endl;
        }
        if(cell1 == cell2 - cols){
            isWall[0][cell1 + count1] = true;
            isWall[1][cell1 + count1] = true;
            cout << "went in array pos " << cell1 + count1<< endl;
        }
        
        
    }
    
    int horizontalCounter = 0;
    int verticalCounter = count1 ;
    
    //top row
    cout << "+  +";
    for(int i = 0; i < cols-1 ; i++)
        cout << "--+";
    cout << endl;

    for(int i = 0; i < rows; i++){
        cout << "|";
        //horizontal print
        for(int i = 0; i < cols - 1; i++){
            cout << "  ";
            if(isWall[0][horizontalCounter]){
                cout << "|";
            }
            else cout << " ";
            horizontalCounter++;
        }
        cout << "  |" << endl;
        if(verticalCounter == totalWalls)
            continue;
        //vertical print
        for(int i = 0; i < cols; i++){
            cout << "+";
            if(isWall[0][verticalCounter]){
                cout << "--";
            } else cout << "  ";
            verticalCounter++;
        }
        cout << "+" << endl;
    }
    
    for(int i = 0; i < cols-1 ; i++)
        cout << "+--";
    cout << "+  +" << endl;

    
}

bool mazeGenerator::getArguments(int argc, char * argv[], int & outRows, int & outCols, string & fName, bool & doPrint){
    if(argc == 7 or argc == 8){
        bool pFlag = false;
        if(argc == 8)
            pFlag = true;
        else pFlag = false;
            
        bool OFlag = false;
        bool cFlag = false;
        bool rFlag = false;
        int count = 1;
        doPrint = false;
        
        while(1){
            if(!OFlag and string(argv[count]) == "-o"){
                OFlag = true;
                fName = argv[count+1];
                count += 2;
                if(pFlag)
                    if(string(argv[count]) == "-p"){
                        count++;
                        doPrint = true;
                    }
            }
            else if(!cFlag and string(argv[count]) == "-c"){
                cFlag = true;
                outCols = stoi(argv[count+1]);
                count += 2;
            }
            else if(!rFlag and string(argv[count]) == "-r"){
                rFlag = true;
                outRows = stoi(argv[count+1]);
                count += 2;
            }
            else if(rFlag and cFlag and OFlag){
                break;
            } else return false;
        }
        return true;
    }
    return false;
}
