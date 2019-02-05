
#include "ganttUtils.h"
#include "linkedQueue.h"


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <iomanip>


using namespace std;

ganttUtils::ganttUtils(){
    
}
ganttUtils::~ganttUtils(){
    delete [] array;
    delete [] inDegreeArray;
    delete [] outDegreeArray;
    delete [] topoNodes;
    delete [] crPath;
    delete [] slackTimes;
    delete [] distances;
}
void ganttUtils::destroyGraph(){
    
}
bool ganttUtils::getArguments(int argc, char * argv[], string & tasksFile, bool & printFlag){
    
    if(argc > 4 or argc == 2){
        //TODO: fill in this errors
        cout << "invalid arguments" << endl;
        return false;
    }
    if(argc == 1){
        cout << "usage message" << endl;
        return false;
    }
    if(string(argv[1]) != "-f"){
        cout << "-f error replace this" << endl;
        return false;
    } else
        tasksFile = string(argv[2]);
    if(argc == 3)
        return true;
    else if (argc == 4){
        if(string(argv[3]) == "-p")
            printFlag = true;
        else {
            cout << "-p error replace this" << endl;
            return false;
        }
    }
    return true;
}
bool ganttUtils::readGraph(const string inputFile){
    ifstream in;
    in.open(inputFile);
    if(!in.is_open()){
        return false;
    }
    
    int inFrom, inTo, inWeight;
    getline(in, title);
    string temp;
    getline(in, temp);
    temp = temp.substr(12, temp.length() - 1);
    milestoneCount = stoi(temp);
    getline(in, temp);
    temp = temp.substr(8, temp.length() - 1);
    sourceNode = stoi(temp);
    destroyGraph();
    
    array = new adjList[milestoneCount];
    for (int i = 0; i < milestoneCount; i++)
        array[i].head = NULL;
    
    while (in >> inFrom >> inTo >> inWeight){
        //add edge where infrom is source and into is dest
        graphNode * insertNode = newNode(inTo, inWeight);
        if(array[inFrom].head == NULL){
            taskCount++;
            array[inFrom].head = insertNode;
            insertNode = NULL;
        } else {
            insertNode->link = array[inFrom].head;
            array[inFrom].head = insertNode;
            taskCount++;
//            graphNode * tail = array[inFrom].head;
//            while(tail->link != NULL)
//                tail = tail->link;
//            tail->link = insertNode;
//            tail = NULL;
//            taskCount++;
        }
    }
    
//    //debug print graph
//    for(int i = 0; i < milestoneCount; i++){
//        graphNode * crawl = array[i].head;
//        cout << "Adjacency list of vertex" << i << endl << "head";
//        while(crawl){
//            cout << "->" << crawl->to << " - w:" << crawl->weight;
//            crawl = crawl->link;
//        }
//        cout << endl;
//    }
    return true;
}
graphNode * ganttUtils::newNode(int inTo, int inWeight){
    graphNode * insertNode;
    insertNode = new graphNode;
    insertNode->to = inTo;
    insertNode->weight = inWeight;
    insertNode->link = NULL;
    return insertNode;
}


bool ganttUtils::isValidProject(){
    bool * visited = new bool [milestoneCount];
    bool * marked = new bool [milestoneCount];
    for(int i = 0; i < milestoneCount; i++)
        visited[i] = marked[i] = false;
    for(int i = 0; i < milestoneCount; i++)
        if(!visited[i])
            if(isCycle(i, visited, marked))
                return false;
    return true;
}
bool ganttUtils::isCycle(int i, bool * visited, bool * marked){
    if(!visited[i]){
        visited[i] = marked[i] = true;
        //loop through adjace nt nodes
        graphNode * tail = array[i].head;
        while(tail != NULL){
            int u = tail->to;
            if(!visited[u] and isCycle(u, visited, marked))
                return true;
            else if (marked[u])
                return true;
            tail = tail->link;
        }
        tail = NULL;
    }
    marked[i] = false;
    return false;
}
void ganttUtils::findGraphInformation(){
    //calculate some stuff lol
    double dbTaskCount = double(taskCount);
    double dbMilestones = double(milestoneCount);
    double tmRatio = dbTaskCount/dbMilestones;
    double density = (2.0 * dbTaskCount)/(dbMilestones * (dbMilestones - 1.0));
    
    //TODO: edit precision
    cout << "------------------------------------------------------------" << endl;
    cout <<"Graph Information" << endl;
    cout <<"   Project title: " << title << endl;
    cout <<"   Milestone Count: " << milestoneCount << endl;
    cout <<"   Task Count: " << taskCount << endl;
    cout <<"   Source Milestone: " << sourceNode << endl;
    cout <<"   Tasks/Milestones Ratio: " <<  fixed<< setprecision(6) << tmRatio << endl;
    cout <<"   Project Tasks Density: " << fixed << setprecision(6) << density << endl;
    cout << endl;
}
void ganttUtils::findKeyMilestone(int inHighFurthest){
    
    cout <<"   Key Milestone: " << inHighFurthest << ", in-degree: " << inDegreeArray[inHighFurthest] << " tasks." << endl;
}
void ganttUtils::findNodePoint(int outHighFurthest){
    
 cout <<"   Node Point: " << outHighFurthest << ", in-degree: " << outDegreeArray[outHighFurthest] << " tasks." << endl;
}
void ganttUtils::findDependencyStats(){
    //indegree stuff
    //populate array
    inDegreeArray = new int [milestoneCount];
    for(int i = 0; i < milestoneCount; i++)
        inDegreeArray[i] = 0;
    for(int i = 0; i < milestoneCount; i++){
        graphNode * tail = array[i].head;
        while(tail != NULL){
            inDegreeArray[tail->to]++;
            tail = tail->link;
        }
    }
    //array is now populated
    //traverse through array finding necesssary value



    outDegreeArray = new int [milestoneCount];
    for(int i = 0; i < milestoneCount; i++)
        outDegreeArray[i] = 0;
    for(int i = 0; i < milestoneCount; i++){
        int count = 0;
        graphNode * tail = array[i].head;
        while(tail != NULL){
            count++;
            tail = tail->link;
        }
        tail = NULL;
        outDegreeArray[i] = count;
    }
    
   
}
void ganttUtils::findAPs(){
    bool * aps = new bool [milestoneCount];
    bool * visited = new bool [milestoneCount];
    int * parent = new int [milestoneCount];
    int * low = new int [milestoneCount];
    int * discovered = new int [milestoneCount];
    
    for(int i = 0; i < milestoneCount; i++){
        aps[i] = false;
        visited[i] = false;
        parent[i] = -1;
        low[i] = 0;
        discovered[i] = 0;
    }
    
    for(int i = 0; i < milestoneCount; i++)
        if(!visited[i])
            findAPsHelper(i, visited, discovered, low, parent, aps);
    
    cout <<"Articulation Points:" << endl;
    for(int i = 0; i < milestoneCount; i++)
        if(aps[i])
            cout << " " << i;
    cout << endl << endl;
    cout << "------------------------------------------------------------" << endl;

}
void ganttUtils::findAPsHelper(int i, bool * visited, int * discovered, int * low, int * parent, bool * aps){
    int children = 0;
    int time = 0;
    visited[i] = true;
    discovered[i] = low[i] = ++time;
    
    graphNode * tail = array[i].head;
    while(tail != NULL){
        if(!visited[tail->to]){
            children++;
            parent[tail->to] = i;
            findAPsHelper(tail->to, visited, discovered, low, parent, aps);
            low[i] = min(low[i], low[tail->to]);
            
            if(parent[i] == -1 and children > 1)
                aps[i] = true;
            if(parent[i] != -1 and low[tail->to] >= discovered[i])
                aps[i] = true;
        } else if (tail->to != parent[i])
            low[i] = min(low[i], discovered[tail->to]);
        
        tail = tail->link;
    }
    tail = NULL;
}
void ganttUtils::topoSort(){
    topoNodes = new int [milestoneCount];
    linkedQueue<int> Q;
    
    int *inDegreeCopy = new int[milestoneCount];
    
    for(int i = 0; i < milestoneCount; i++){
        inDegreeCopy[i] = 0;
        topoNodes[i] = 0;
    }
    

    for(int i = 0; i < milestoneCount; i++)
    {
        graphNode * temp = array[i].head;
        while(temp != NULL){
            inDegreeCopy[temp->to]++;
            temp = temp->link;
        }
    }
    
    for (int i = 0; i < milestoneCount; i++){
        if(inDegreeCopy[i] == 0)
            Q.addItem(i);
    }
    
    topoCount = 0;
    
    while(!Q.isEmptyQueue()){
        int v = Q.front();
        Q.deleteItem();
        topoNodes[topoCount] = v;
        
        graphNode * tail = array[v].head;
        while(tail != NULL){
            if(--inDegreeCopy[tail->to] == 0)
                Q.addItem(tail-> to);
            tail = tail->link;
        }
        topoCount++;
    }
    
    
    cout << "Topological Sort:" << endl;
    for(int i = 0; i < topoCount; i++)
        cout << " " << topoNodes[i];
    cout << endl << endl;
    cout << "------------------------------------------------------------" << endl;
    
    
}
int ganttUtils::getTaskCount(){
    return taskCount;
}
void ganttUtils::criticalPath(){
    distances = new int [milestoneCount];
    linkedQueue<int> q;

    for(int i = 0; i < milestoneCount; i++)
        distances[i] = 0;
    
    int *inDegreeCopy = new int[milestoneCount];
    for(int i = 0; i < milestoneCount; i++){
        graphNode * temp = array[i].head;
        while(temp != NULL){
            inDegreeCopy[temp->to]++;
            temp = temp->link;
        }
    }
    
    for(int i = 0; i < milestoneCount; i++)
        if(inDegreeCopy[i] == 0)
            q.addItem(i);

    int v, u;
    
    while(!q.isEmptyQueue()){
        v = q.front();
        q.deleteItem();
        graphNode * tail = array[v].head;
        while(tail != NULL){
            u = tail->to;
            distances[u] = max(distances[u], distances[v] + time(v, u));
            inDegreeCopy[u]--;
            if(inDegreeCopy[u] == 0)
                q.addItem(u);
            tail = tail->link;
        }
        tail = NULL;
    }
    
    maxDistance = 0;
    lastNode = 0;
    for(int i = 0; i < milestoneCount; i++){
        if(distances[i] > maxDistance){
            maxDistance = distances[i];
            lastNode = i;
        }
    }
    
    crPath = new int [milestoneCount];
    for(int i = 0; i < milestoneCount; i++){
        crPath[i] = -1;
    }
    
    int x= lastNode;
    crPathCount = 0;
    crPath[crPathCount++] = x;
    
    while(x != sourceNode){
        for(int i =0; i < milestoneCount; i++){
            graphNode * tail = array[i].head;
            while(tail != NULL){
                u = tail->to;
                if(x == u and (distances[x] == distances[i] + time(i,u))){
                        crPath[crPathCount++] = i;
                        x = i;
                    }
                tail = tail->link;
            }
        }
    }
    
}
int ganttUtils::time(int v, int u){
    graphNode * tail = array[v].head;
    
    while(tail != NULL){
        if(tail->to != u)
            tail = tail->link;
        else break;
    }
    
    return tail->weight;
}
void ganttUtils::findSlackTimes(){
    slackTimes = new int[milestoneCount];
    for(int i = 0; i < milestoneCount; i++)
        slackTimes[i] = -1;
    
    for(int i = 0; i < crPathCount; i++)
        slackTimes[crPath[i]] = 0;
    
    graphNode * tail = new graphNode;
    for(int i = 0; i < milestoneCount; i++)
        if(slackTimes[i] == -1){
            tail = array[i].head;
            while(tail != NULL){
                int v = tail->to;
                slackTimes[i] = distances[v] - (distances[i] + tail->weight);
                tail = tail->link;
            }
        }

    
    cout << "Slack Times (task-slacktime):" << endl;
    for(int i = 0; i < milestoneCount; i++)
    if(slackTimes[i] != 0 and slackTimes[i] != -1)
        cout << " " << i << "-" << slackTimes[i];
    cout << endl << endl;
}

void ganttUtils::printGraphInformation(){
    
}
void ganttUtils::printGraph() const{

    cout << "Vertex    vrt /weight | vrt /weight | vrt /weight | ..." << endl;
    cout << "------    ----------------------------------------------"<< endl;
    for(int i = 0; i < milestoneCount; i++){
        cout << setw(6) << right << i << " -> ";
        
        graphNode * tail = array[i].head;
        if(tail == NULL)
            cout << "   None";
        while(tail != NULL){
            cout << setw(4) << tail->to << "/" << setw(6) << tail->weight << " | ";
            tail = tail->link;
        }
        
        
        cout << endl;
        
    }
//
//
//
//
//
}
void ganttUtils::printDependencyStats(){
    criticalPath();
    
    int inLow = milestoneCount;
    int inHigh = 0;
    int inLowCount = 0;
    int inHighCount = 0;
    int inLowFurthest = 0;
    int inHighFurthest = 0;
    
    for(int i = 1; i < milestoneCount; i++){
        if(inDegreeArray[i] == inLow){
            inLowFurthest = i;
            inLowCount++;
        } else if (inDegreeArray[i] < inLow) {
            inLowCount = 1;
            inLowFurthest = i;
            inLow = inDegreeArray[i];
        }
        
        if(inDegreeArray[i] == inHigh){
            inHighFurthest = i;
            inHighCount++;
        } else if (inDegreeArray[i] > inHigh){
            inHighCount = 1;
            inHighFurthest = i;
            inHigh = inDegreeArray[i];
        }
    }
    
    int outLow = milestoneCount;
    int outHigh = 0;
    int outLowCount = 0;
    int outHighCount = 0;
    int outHighFurthest = 0;
    int outLowFurthest = 0;
    
    
    
    for(int i = 0; i < milestoneCount; i++){
        if(i == lastNode)
            continue;
        if(outDegreeArray[i] == outLow){
            outLowFurthest = i;
            outLowCount++;
        } else if (outDegreeArray[i] < outLow) {
            outLowCount = 1;
            outLowFurthest = i;
            outLow = outDegreeArray[i];
        }
        
        if(outDegreeArray[i] == outHigh){
            outHighFurthest = i;
            outHighCount++;
        } else if (outDegreeArray[i] > outHigh){
            outHighCount = 1;
            outHighFurthest = i;
            outHigh = outDegreeArray[i];
        }
    }
    
    findKeyMilestone(inHighFurthest);
    findNodePoint(outHighFurthest);
    findIndependentMilestones();
    
    cout << "Dependency Statistics: (in-degree):" << endl;
    cout <<"   Highest In-Degree: " << inHigh << endl;
    cout <<"   Lowest In-Degree: " << inLow << endl;
    cout <<"   Count of Highest Degree: " << inHighCount << endl;
    cout <<"   Count of Lowest Degree: " << inLowCount << endl;
    
    cout << "Dependency Statistics: (out-degree):" << endl;
    cout << "   Highest Out-Degree: " << outHigh << endl;
    cout << "   Lowest Out-Degree: " << outLow << endl;
    cout << "   Count of Highest Degree: " << outHighCount << endl;
    cout << "   Count of Lowest Degree: " << outLowCount << endl;
    cout << endl;
    cout << "------------------------------------------------------------" << endl;
    
    topoSort();
    findAPs();
    printCriticalPath();
    findSlackTimes();
}

void ganttUtils::findIndependentMilestones(){
    cout <<"   Independent Milestones" << endl;
    for(int i = 0; i < milestoneCount; i++){
        if(outDegreeArray[i] == 0){
            cout << " "<<i;
        }
    }
    cout << endl << endl;
    cout << "------------------------------------------------------------" << endl;
}
void ganttUtils::printTopoSort() const {
    
}
void ganttUtils::printAPs() const {
    
}
void ganttUtils::printCriticalPath() const {
    
    cout<< "Critical Path:" << endl;
    cout << "   Source Node: " << sourceNode<<endl;
    cout << "   Final Task: " << lastNode << endl;
    cout<< "   Total Duration: " << maxDistance << endl;
    cout << endl;
    cout << "Critical Path:" << endl;
    for(int i = crPathCount - 1; i > -1 ; i--) {
        cout << " " << crPath[i];
        
    }
    cout << endl << endl;
    cout << "------------------------------------------------------------" << endl;

}
void ganttUtils::printSlackTimes() const {
    
}
