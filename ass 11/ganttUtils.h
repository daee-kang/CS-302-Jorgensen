//
//  ganttUtils.hpp
//  ass 11
//
//  Created by Daee Kang on 11/26/18.
//  Copyright © 2018 Daee Kang. All rights reserved.
//

#ifndef ganttUtils_hpp
#define ganttUtils_hpp
#include <iostream>



using namespace std;


struct graphNode{
    int to;
    int weight;
    graphNode * link;
};
struct adjList{
    struct graphNode * head;
};

class ganttUtils{
private:
    struct adjList * array;
    int * inDegreeArray;
    int * outDegreeArray;
//    minHeap<int> minQueue;
//    maxHeap<int> maxQueue;
    int * articulationNodes;
    int * topoNodes;
    int * crPath;
    int * slackTimes;
    int * distances;
    int milestoneCount;
    int maxDistance;
    int taskCount;
    int topoCount;
    int crPathCount;
//    outValues nodePoint;
//    outValues keyMilestone;
    int independentMilestones;
    int sourceNode;
    int lastNode;
    string title;
    int time(int, int);
    graphNode * newNode(int, int);
public:
    ganttUtils();
    ~ganttUtils();
    void destroyGraph();
    bool getArguments(int, char*[], string&, bool&);
    bool readGraph(const string);
    bool isValidProject();
    bool isCycle(int, bool *, bool *);
    void findGraphInformation();
    void findKeyMilestone(int);
    void findNodePoint(int);
    void findDependencyStats();
    void findIndependentMilestones();
    void findAPs();
    void findAPsHelper(int, bool *, int *, int *, int *, bool *);
    void topoSort();
    int getTaskCount();
    void criticalPath();
    void findSlackTimes();
    void printGraphInformation();
    void printGraph() const;
    void printDependencyStats();
    void printTopoSort() const;
    void printAPs() const;
    void printCriticalPath() const;
    void printSlackTimes() const;
};
#endif /* ganttUtils_hpp */
