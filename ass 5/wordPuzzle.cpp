/*this cpp file defines the functions for wordPuzzle class. Has a basic constructor.
includes destructor because of the double pointer array. class is inherits AVL tree
 so a lot of functions will use those functions as well.
 purpose of this class is read in words and letters to make a word game where
 the defined functions will use avl functions so see how many solutions there are
 by using the dictionary.
 The dictionary is also sorted by an AVL tree as well. */

#include <iostream>
#include <fstream>
#include <string>
#include "avlTree.h"
#include "wordPuzzle.h"
#include "linkedQueue.h"

using namespace std;
//constructor
wordPuzzle::wordPuzzle(){
    order = 0;
    title = "";
    letters = NULL;
}
//destructor, deletes the double pointer array letters
wordPuzzle::~wordPuzzle(){
    for (int i = 0; i < order; i++)
        delete[] letters[i];
    delete letters;
    letters = NULL;
}
//read in letters, including title and order
bool wordPuzzle::readLetters(const string wordFile){
    string readInOrder;
    ifstream in;
    in.open(wordFile);
    if (!in)
        return false;
    //title read in order read in
    getline(in, title);
    in >> readInOrder;
    order = stoi(readInOrder);
    //initialize double pointer array for letters
    letters = new string* [order];
    for (int i = 0; i < order; i++)
        letters[i] = new string[order];
    //read into array
    for (int i = 0; i < order; i++)
        for (int j = 0; j < order; j++)
            in >> letters[i][j];
    return true;
}

//read words from file into tree
bool wordPuzzle::readDictionary(const string dicFile){
    string dictWord;
    ifstream in;
    in.open(dicFile);
    
    if (!in) return false;
    
    //loop for readin, stops at eof
    while(getline(in, dictWord))
        insert(dictWord);
    
    return true;
}

//basoc argument check
bool wordPuzzle::getArguments(int argc, char* argv[], string& dicFile , string& wordFile){
    if (argc == 1){
        cout << "Usage: ./findWords -d <dictFile> -w <wordFile>" << endl;
        return false;
    }
    
    if (argc != 5){
        cout << "Command line arguments are invalid. Please provide dictionary file and word file." << endl;
        return false;
    }
    
    
    // Check for dictionary file
    if (string(argv[1]) != "-d"){
        cout << "Command line arguments are invalid. Please provide a dictionary file." << endl;
        cout << "Usage: ./findWords -d <dictFile> -w <wordFile>" << endl;
        return false;
    } else dicFile = string(argv[2]);
    
    if (string(argv[3]) != "-w")
    {
        cout << "Command line arguments are invalid. Please provide a word file." << endl;
        cout << "Usage: ./findWords -d <dictFile> -w <wordFile>" << endl;
        return false;
    } else wordFile = string(argv[4]);
    
    return true;
}


//call private find word functin to restart recursively.
//do this for every cell
void wordPuzzle::findWords(){
    string isWord = "";
    
    for (int i = 0; i < order; i++)
        for (int j = 0; j < order; j++)
            findWords(i, j, isWord);
}

// Private findWords function
// Uses avlTree search to find a word
void wordPuzzle::findWords(int i, int j, string word){
    //check bounds
    if (i >= order or j >= order or i < 0 or j < 0)
        return;
    //word = letters, keep adding
    word += letters[i][j];
    
    if(search(word)){
        string iString = to_string(i);
        string jString = to_string(j);
        string tempStr = word;
        //insert into avl tree
        word += " from (" + iString + ", " + jString + ") \n";
        wordsFound.insert(word);

        // Recursively check each letter
        findWords(i+1, j, tempStr);
        findWords(i+1, j-1, tempStr);
        findWords(i+1, j+1, tempStr);
        findWords(i, j-1, tempStr);
        findWords(i, j+1, tempStr);
        findWords(i-1, j, tempStr);
        findWords(i-1, j-1, tempStr);
        findWords(i-1, j+1, tempStr);

        return;
    }
    if(!isPrefix(word))
        return;
    //recursive call time
    findWords(i+1, j, word);
    findWords(i+1, j-1, word);
    findWords(i+1, j+1, word);
    findWords(i, j-1, word);
    findWords(i, j+1, word);
    findWords(i-1, j, word);
    findWords(i-1, j-1, word);
    findWords(i-1, j+1, word);
}
//print title
void wordPuzzle::showTitle() const{
    cout << "Letter Set Title: " << title << endl;
}

//print node count
void wordPuzzle::showWordCount() const{
    cout << "Word Count: " << wordsFound.countNodes() << endl;
}

//print words using INORDER enum
void wordPuzzle::showWords() const{
    wordsFound.printTree(INORDER);
}

//print letters in format
//create cells that will hold cell info
//at end print the cells
void wordPuzzle::printLetters() const {
    string bar;
    string cells;
    //create bar with order length
    for (int i = 0; i < order; i++) {
        bar += "___";
        bar += " ";
    }
    cout << "  " << bar << endl;
    for (int i = 0; i < order; i++) {
        for (int j = 0; j < order; j++) {
            cells += " |  ";
        }
        cells += " |\n";
        for (int k = 0; k < order; k++) {
            cells += " | ";
            cells += letters[i][k];
        }
        cells += " |\n";
        cells += " ";
                for (int l = 0; l < order; l++) {
            cells += "|___";
        }
        cells += "|\n";
    }
    cout << cells << endl;
    
}
