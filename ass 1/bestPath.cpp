#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "bestPath.h"

using namespace std;

bestPath::bestPath(){
    matrixOrder = 0;
    matrix = NULL;
    
}
bestPath::~bestPath(){
    if(matrix != NULL){
        for(int i = 0; i < matrixOrder; i++){
            delete matrix[i];
        }
        delete[] matrix;
    }
}

void bestPath::displayMatrix(){
    for (int i = 0; i < matrixOrder; i++){   // row
        for (int j = 0; j < matrixOrder; j++){ //column
            cout << setw(5) << right << matrix[i][j];
        }
    cout << endl;
    }
}

bool bestPath::createMatrix(const int inputOrder){
    matrixOrder = inputOrder;
    if(matrixOrder<MIN_ORDER || matrixOrder > MAX_ORDER){
        return false;
    }
    
    //create board with double pointer
    matrix = new int*[matrixOrder];
    for (int i = 0; i < matrixOrder; i++) {
        matrix[i] = new int[matrixOrder];
    }
    
    //populate board with random ints
    for (int i = 0; i < matrixOrder; i++){   // row
        for (int j = 0; j < matrixOrder; j++){ //column
            matrix[i][j] = rand()%LIMIT+1;
        }
    }
    
    return true;
}

int bestPath::bestPthDY(){

//    int matrixCopy[matrixOrder][matrixOrder];
//    for (int i = 0; i < matrixOrder; i++){
//        int temp = matrix[0][i];
//
//        matrixCopy[0][i] = temp;
//    }
    
    int ** matrixCopy;
    matrixCopy = new int*[matrixOrder];
    for (int i = 0; i < matrixOrder; i++) {
        matrixCopy[i] = new int[matrixOrder];
        matrixCopy[0][i] = matrix[0][i];
    }
    
    for(int i = 1; i < matrixOrder; i++){
        for(int j = 0; j < matrixOrder-1; j++){
            if((j-1) < 0){
                matrixCopy[i][j] = matrixCopy[i-1][j+1] + matrix[i][j];
            } else if ((j+1 ) == matrixOrder){
                matrixCopy[i][j] = matrixCopy[i-1][j-1] + matrix[i][j];
            } else {
                matrixCopy[i][j] = max((matrixCopy[i-1][j-1] + matrix[i][j]), (matrixCopy[i-1][j+1] + matrix[i][j]));
            }
        }
    }

    int finalValue = 0;
    for(int i = 0; i < matrixOrder; i++){
        if(matrixCopy[matrixOrder-1][i] > finalValue){
            finalValue = matrixCopy[matrixOrder - 1][i];
        }
    }
    return finalValue;
}

int bestPath::bestPthREC(){
    int maxValue = 0;
    int r = 0;
    for(int c = 0; c < matrixOrder; c++){
        int temp = bestPthREC1(r, c);
        if(temp > maxValue) maxValue = temp;
    }
    return maxValue;
}

int bestPath::bestPthREC1(int r, int c){
    if(c < 0 || c >= matrixOrder){
        return 0;
    } else if (r == matrixOrder-1){
        return matrix[r][c];
    } else {
        return max(matrix[r][c] + bestPthREC1(r+1, c-1),
            matrix[r][c] + bestPthREC1(r+1, c+1));
    }
}
