//i couldn't do it :-(

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <string>
#include "assocArray.hpp"

using namespace std;

int main(int argc, char *argv[]){

    if(argc == 1){
        cout << "Usage:  (-i <inputFile> -o <outputFile>)." << endl;
        exit(0);
    }
    if(argc != 5){
        cout << "Invalid argument count. " << endl;
        exit(0);
    }
    if(string(argv[1]) != "-i" or string(argv[3]) != "-o"){
        cout << "Invalid argument" << endl;
        exit(0);
    }
    ifstream in;
    in.open(string(argv[2]));
    ofstream out;
    out.open(string(argv[4]));
    
    assocArray<double> movies;
    double sum = 0.0, avg= 0.0;
    unsigned int entries = 0;
    
    string name;
    string year;
    string rating;
    
    double dupRating;
    getline(in, name, '\t');
    while(in)
    {
        getline(in, rating, '\t');
        getline(in, year);
        
        name = name + "-" + year;
        
        cout << name << " " << rating << endl;

        getline(in, name, '\t');
        
    }
    in.close();}

    
    
    
    
    
    



