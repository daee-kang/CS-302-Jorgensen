//
//  WordPuzzle.h
//  ass 5
//
//  class definition for wordPuzzle;
//
#ifndef WordPuzzle_h
#define WordPuzzle_h

#include "avlTree.h"
using namespace std;

class wordPuzzle:public avlTree<string> {
private:
    string title;
    int order;
    string ** letters;
    avlTree<string> wordsFound;
    
    void findWords(int, int, string);
public:
    wordPuzzle();
    ~wordPuzzle();
    bool readLetters(const string);
    bool readDictionary(const string);
    bool getArguments(int, char *[], string &, string &);
    void findWords();
    void showTitle() const;
    void showWordCount() const;
    void printLetters() const;
    void showWords() const;
};

#endif /* WordPuzzle_h */
