/*the following program takes in two input values. With these input values used as boundaries for
 thread count and input count, it will check all the numbers inbetween the input count to check
 if they are harshard numbers using threads depending on the inputted thread count. If the number is
 a harsard number, it will add it to an array and once done processing, it will output the
 number of harshard numbers plus the time it took to execute. */

#include <string>
#include <iostream>
#include <thread>
#include <cstdlib>
#include <mutex>
#include <chrono>
#include <vector>


using namespace std;

//global variables
static long long inputThread, inputLimit;
static const unsigned long long MIN_THREAD_COUNT = 1;
static const unsigned long long MAX_THREAD_COUNT = 64;
static const unsigned long long MIN_LIMIT = 10;
static const unsigned long long MAX_LIMIT = 10000000000;
static const unsigned long long HARSHAD_STEP = 10000;
//count increment (increments in Harshard_STep)
unsigned long long numCount = 0;
//vector for holding the harshard numbers.
vector<unsigned long long> harshadCount;
//global mutex
mutex Mutex;

//function protos
bool commandLine(int, char * []);
void hashidCount();
void isHashid(unsigned long long);
unsigned long long getNextNum();
void pushBack(unsigned long long);


int main(int argc, char *argv[]){
    //check command line arguments and set values for inputs
    if(!commandLine(argc, argv))
        exit(0);
    
    //output header
    cout << "CS 302 Assignment 7" << endl;
    cout << "Daee Kang - 1004" << endl << endl;
    cout << "Hardware count: " <<  thread::hardware_concurrency() << endl;
    cout << "User Thread Count: " << inputThread << endl;
    cout << "Numbers Limit: " << inputLimit << endl << endl;
    
    //timer start
    auto t1 = chrono::high_resolution_clock::now();
    
    //create array of threads based on input
    thread *threadArray = new thread[inputThread];
    //thread runs function and inputs into array
    
    for(int i = 0; i < inputThread; i++)
        threadArray[i] = thread(hashidCount);
    //join threads
    for(int i = 0; i < inputThread; i++)
        threadArray[i].join();
    
    delete [] threadArray;
    
    //timer end
    auto t2 = chrono::high_resolution_clock::now();
    
    cout << "Results: " << endl;
    cout << "Count of Harshard numbers between 1 and " << inputLimit << " is " << harshadCount.size() << "." << endl << endl;
    cout << "Program took: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << " milliseconds" << endl;
}
//Checks the command line arguments. If it does not work, it will output an error message and then return false
//thus exiting the program. Otherwise it will set the values correctly to their places used later in the program.
bool commandLine(int argc, char * argv[]){
    if(argc == 1){
        cout << "Usage: ./harshadNums -t <threadCount> -l <limitValue>" << endl;
        return false;
    }
    if(argc != 5){
        cout << "Error, wrong argument count. " << endl;
        return false;
    }
    if(string(argv[1]) != "-t"){
        cout << "Error, invalid argument." << endl;
        return false;
    }
    if(string(argv[3]) != "-l"){
        cout << "Error, invalud argument." << endl;
        return false;
    }
    if(stoll(string(argv[2])) < MIN_THREAD_COUNT or stoll(string(argv[2])) > MAX_THREAD_COUNT){
        cout << "Error, invalid thread count" << endl;
        return false;
    }
    if(stoll(string(argv[4])) < MIN_LIMIT or stoll(string(argv[4])) > MAX_LIMIT){
        cout << "Error, invalid limit count" << endl;
        return false;
    }
    inputThread = stoll(string(argv[2]));
    inputLimit = stoll(string(argv[4]));
    return true;
}
//thread function, gets the next hardshard step and inputs into isHashid to operate on 10,000 numbers.
//when it reaches the inputLimit, it will do nothing and return.
void hashidCount(){
    unsigned long long check = 0;
    while((check = getNextNum()) - HARSHAD_STEP <= inputLimit)
        isHashid(numCount);
    return;
}
//checks to see if the inputed number is a hardsharaefafd number. Since it is increased by 10,000, the function
//starts from that minus 10,000 working up to the inputted number. If it reaches the limit, function will return.
void isHashid(unsigned long long num){
    for(unsigned long long i = num - 10000; i < num; i++){
        
        unsigned long long sum = 0, temp = 0;
        
        if(i == 0)
            continue;
        if(i > inputLimit)
            return;
        for (temp = i; temp > 0; temp /= 10)
            sum += temp % 10;
        if((i % sum) == 0)

            pushBack(i);
    }
}
//increments number by 10,000
unsigned long long getNextNum(){
    lock_guard<mutex> guard(Mutex);
    numCount += HARSHAD_STEP;
    return numCount;
}
//pushes the inputted number into the vertex.
void pushBack(unsigned long long num){
    lock_guard<mutex> guard(Mutex);
    harshadCount.push_back(num);
}




