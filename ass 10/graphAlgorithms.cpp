//so many functions lol

#include "graphAlgorithms.h"
#include "minHeap.h"
#include "linkedQueue.h"

#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
#include <limits>
#include <iomanip>

using namespace std;

//constructor
graphAlgorithms::graphAlgorithms(int inputVertexCount) {
	title = "";
	graphMatrix = NULL;
	dist = prev = topoNodes = NULL;
	topoCount = 0;
	if (inputVertexCount >= 5) {
		vertexCount = inputVertexCount;
		newGraph(vertexCount);
	}
	else {
        cout << "graphAlgorithms: Error, invalid graph size." << endl;
        newGraph(inputVertexCount);
		return;
	}
}
//destructor
graphAlgorithms::~graphAlgorithms() {
	destroyGraph();
}
//allocates double dynamic array for graphMatrix
void graphAlgorithms::newGraph(int v) {
    if(v < 5){
        cout << "newGraph: Error, invalid graph size." << endl;
        return;
    }
	destroyGraph();
    vertexCount = v;
	//allocate double pointer array
	graphMatrix = new int*[vertexCount];
	for (int i = 0; i < vertexCount; i++) {
		graphMatrix[i] = new int[vertexCount];
	}
	//set values to 0
	for (int i = 0; i < vertexCount; i++) 
		for (int k = 0; k < vertexCount; k++)
			graphMatrix[i][k] = 0;
}
//adds edge, this function is used in read Graph. sets values to graph
void graphAlgorithms::addEdge(int from, int to, int weight) {
	//check if vertexes are valid.
	if (from == to)
        cout << "addEdge: error, vertex to and from can not be the same." << endl;
	else if (from >= vertexCount or from < 0 or to < 0 or to >= vertexCount)
        cout << "addEdge: error, invalid vertex." << endl; //wrong lol
	//vertex are correct so set it to weight. 
	else {
		graphMatrix[from][to] = weight;
	}
	return;
}
//read in values from file and put it into graph using addEdge
bool graphAlgorithms::readGraph(const string graphFile) {
	//create if stream and read in file name, return false if error
	ifstream in;
	in.open(graphFile);
	if (!in.is_open()) return false;
	
	//time to read in value bro 
		//setup variables
	int from, to, weight;

	//read in title
	getline(in, title);
	//read in vertex count
    destroyGraph();
	string temp;
	getline(in, temp);
	vertexCount = stoi(temp);

	//check if vertex count is > 5 and break if true
	if (vertexCount < 5) {
		cout << "Error: vertex counter must be greater than 5" << endl;
		return false;
	}

	//initialize graph with vertex count
	newGraph(vertexCount);
	//read in data into graph using addEdge()
	while (in >> from >> to >> weight)
		addEdge(from, to, weight);
	//done
	return true;
}
int graphAlgorithms::getVertexCount() const {
	return vertexCount;
}
void graphAlgorithms::printMatrix() const {
    if (vertexCount < 5){
        cout << "printMatrix: Error, no graph data." << endl;
        return;
    }
    
    cout << "Graph Adjacency Matrix:" << endl;
    cout << "   Graph Title: " << getGraphTitle() <<endl << endl;
    //top row lol
    cout << "       ";
    for(int i = 0; i < vertexCount; i++){
        cout << setw(2) << right << i << "  ";
    }
    cout << endl;
    //dash thing, this formatting so bad lol
    cout << "      ";
    for(int i = 0; i < vertexCount; i++)
        cout << "----";
    cout << endl;
    //print rows - this is terrible code
    for(int i = 0; i < vertexCount; i++){
        cout << setw(3) << right << i << "| ";
        for(int k = 0; k < vertexCount; k++){
            
            if(graphMatrix[i][k] == 0 and i != k){
                cout << setw(4) << right << "--";
            } else if (i == k){
                cout << setw(4) << right << "0";
            } else cout << setw(4) << right << graphMatrix[i][k];
        }
        cout << endl;
    }
}
void graphAlgorithms::topoSort() {
    
    if(vertexCount < 5){
        cout << "topoSort: Error, no graph data." << endl;
        return;
    }
    
    int * indegreeArray = new int [vertexCount];
    topoCount = 0;
    topoNodes = new int [vertexCount];
    
    for(int i = 0; i < vertexCount; i++){
        topoNodes[i] = 0;
        indegreeArray[i] = 0;
    }
    
    for(int i = 0; i < vertexCount; i++)
        for(int k = 0; k < vertexCount; k++)
            if(graphMatrix[k][i] != 0 and i != k)
                indegreeArray[i]++;
    
    linkedQueue<int> q;
    for(int i = 0; i < vertexCount; i++)
        if(indegreeArray[i] == 0)
            q.addItem(i);
    
    while(!q.isEmptyQueue()){
        int u = q.front();
        q.deleteItem();
        topoNodes[topoCount] = u;
        topoCount++;
        
        for(int i = 0; i < vertexCount; i++){
            if(graphMatrix[u][i] != 0){
                indegreeArray[i]--;
                if(indegreeArray[i] == 0)
                    q.addItem(i);
            }
        }
    }
    cout << endl;
    cout << "Topological Sort:" << endl;
    for(int i = 0; i < topoCount; i++){
        cout << topoNodes[i] << " ";
    }
    cout << endl << endl;
    
}
void graphAlgorithms::dijkstraSP(int startNode) {
	//display error if startNode is incorrect value
	if (startNode < 0 or startNode >= vertexCount) {
        cout << "dijkstra: Error, no graph data." << endl;
		return;
	}
	else if (vertexCount < 5) {
        cout << "dijkstra: error, invalid source." << endl;
		return;
	}
	//allocate arrays
	dist = new int[vertexCount];
	prev = new int[vertexCount];
    //initialize to infinite ("max value of int")
    for(int i = 0; i < vertexCount; i++){
        dist[i] = numeric_limits<int>::max();
        prev[i] = -1;
    }
    //node structured custom queue inserts -> vertex num, distance
    minHeap<int> priorityQueue;
    
    //not gonna comment this cos its in pdf
    priorityQueue.insert(startNode, 0);
    dist[startNode] = 0;
    
    while(!priorityQueue.isEmpty()){
        int u = priorityQueue.deleteMin();
        for(int i = 0; i < vertexCount; i++){
            if(graphMatrix[u][i] != 0 and i != u){
                int newDistance = dist[u] + graphMatrix[u][i];
                if(newDistance < dist[i]){
                    dist[i] = newDistance;
                    prev[i] = u;
                    priorityQueue.insert(i, newDistance);
                }
            }
        }
    }
    //print arrays
    printDistances(startNode);
}
void graphAlgorithms::printPath(const int startNode, const int destNode) const {
    cout << "Path from " << startNode << " to " << destNode << endl;
    if(destNode >= numeric_limits<int>::max()){
        cout << "error not reachable" << endl;
        return;
    }
    
    showPath( destNode);
    
}
string graphAlgorithms::getGraphTitle() const {
	return title;
}
void graphAlgorithms::setGraphTitle(const string insertTitleWhyIsThisAFunction) {
	title = insertTitleWhyIsThisAFunction;
}
void graphAlgorithms::printDistances(const int startNode) const {
    cout << "Shortest Paths:" << endl;
    cout << "From Node: " << startNode<< " to:" << endl;
    cout << setw(10) << right << "Vertex" << setw(10) << "Dist" << setw(10) << "From" << endl;
    for(int i = 0; i < vertexCount; i++){
        if(dist[i] < numeric_limits<int>::max()){
            cout << setw(10) << i << setw(10) << dist[i];
            if(prev[i] < 0){
                cout << setw(10) << "-" << endl;
            } else cout << setw(10) << prev[i] << endl;
        }
        else cout << setw(10) << i << " " << setw(20) << "not reachable" << endl;
    }
    cout << endl;

}
//argc, argv, doTesting, graphFile, startNode, destNode, showMatrix
bool graphAlgorithms::getArgs(int argc, char * argv[], bool& doTesting, string& graphFile,
	int& startNode, int& destNode, bool& showMatrix) {
	//usage message
	if (argc == 1) {
		cout << "Usage: -gf <fileName> -sn <sourceNode> -dn <destNode> (-sm). " << endl;
		cout << "For testing error message only, use -t." << endl;
		return false;
	}
	//testing bool
	else if (argc == 2) {
		if (string(argv[1]) == "-t") {
			doTesting = true;
			return true;
        } else {
            cout << "Invalid command line options. " << endl;
            return false;
        }
	}
	//argc doesn't match
	else if (argc != 7)
		if (argc != 8)
			return false;
	//argc is right here, argv not verified yet
	else {
		//verify argv
		//TODO: could check if node values are numbers??? nahhh

		if (string(argv[1]) == "-gf")
			graphFile = string(argv[2]);
		else {
			cout << "Invalid graph specifier." << endl;
			return false;
		}

        if (string(argv[3]) == "-sn"){
			string temp = string(argv[4]);
            startNode = stoi(temp);
        }
		else {
			cout << "Error, invalid ssource node specifier." << endl;
			return false;
		}

        if (string(argv[5]) == "-dn"){
            string temp = string(argv[6]);
            destNode = stoi(temp);
        }
		else {
			cout << "Error, invalid destination node specifier." << endl;
			return false;
		}

		if (argc == 8) {
			if (string(argv[7]) == "-sm")
				showMatrix = true;
            else {
                cout << "Error, invalid show matrix specifier. " << endl;
                showMatrix = false;
                return false;
            }
		}

		//verify node is greater than 0
		if (startNode < 0 or destNode < 0 or startNode == destNode) {
			cout << "Invalid node values." << endl;
			return false;
		}
		//everything passes at this point
		return true;
	}
    cout << "Invalid command line options." << endl;
	return false;
}
void graphAlgorithms::showPath(const int destNode) const{
    if(prev[destNode] == -1){
        cout << "  " << destNode;
        return;
    }
    showPath(prev[destNode]);
    cout << " - " << destNode;
    return;


}
//destroys ALL dynamic arrays and resets variables
void graphAlgorithms::destroyGraph() {
	//delete dynamic arrays
	if (graphMatrix != NULL) {
		for (int i = 0; i < vertexCount; i++)
			delete[] graphMatrix[i];
		delete[] graphMatrix;
	}
	if(dist != NULL) delete[] dist;
	if(prev != NULL) delete[] prev;
	if(topoNodes != NULL) delete[] topoNodes;
	//reset variables
	graphMatrix = NULL;
	dist = prev = topoNodes = NULL;
	topoCount = 0;
}
