#ifndef GRAPH_H
#define GRAPH_H
#include <stack>
#include <queue>
#include <list>
#include <stack>
#include <vector>
#include <iostream>
#include <set>
#include <utility>

using std::endl;
using std::cout;
using std::ostream;
using std::stack;
using std::vector;
using std::set;
using std::pair;
using std::list;
using std::queue;

template <typename T>
class Graph;

template <typename T>
ostream& operator<< (ostream& out, Graph<T> g);

template <typename T>
class Graph {
private:
    list<T> vertexSet;//stores all vertices in graph
    list<pair<T, T>> edgeSet;//stores all edges between vertices
    int maxVertices{ 0 };
    int numVertices{ 0 };
    //Declare any variables needed for your graph

public:
    Graph();
    Graph(int);
    void addVertex(T vertex);
    void addEdge(T source, T target);
    vector<T> getPath(T, T);
    bool checkAdj(T vertex, set<T> visitedSet);//check to see if vertex in graph is a dead end which mush be backtracked from
    int findVertexPos(T item);
    int getNumVertices();
    friend ostream& operator << <>(ostream& out, Graph<T> g);
};



/*********************************************
* Constructs an empty graph with a max number of verticies of 100
*
*********************************************/
template<typename T>
Graph<T>::Graph() {
    maxVertices = 100;
    numVertices = 0;
}

/*********************************************
* Constructs an empty graph with a given max number of verticies
*
*********************************************/
template<typename T>
Graph<T>::Graph(int maxVertices) {
    this->maxVertices = maxVertices;
    numVertices = 0;
}




/*********************************************
* Adds a Vertex to the GraphIf number of verticies is less than the
* Max Possible number of verticies.
*********************************************/
template <typename T>
void Graph<T>::addVertex(T vertex) {
    if (numVertices < maxVertices) {
        vertexSet.push_back(vertex);
        numVertices++;
    }
}

/*********************************************
* Returns the current number of vertices
*
*********************************************/
template<typename T>
int Graph<T>::getNumVertices() {

    return numVertices;
}



/*********************************************
* Returns the position in the verticies list where the given vertex is located, -1 if not found.
*
*********************************************/
template <typename T>
int Graph<T>::findVertexPos(T item) {
    int i = 0;
    for (auto& vertex : vertexSet) {
        if (vertex == item) { return i; }
        i++;
    }
    return -1; //return negative one
}//End findVertexPos

/*********************************************
* Adds an edge going in the direction of source going to target
*
*********************************************/
template <typename T>
void Graph<T>::addEdge(T source, T target) {
    edgeSet.emplace_back(source, target);
}


/*********************************************
* Returns a display of the graph in the format
* vertex: edge edge
Your display will look something like the following
    9: 8 5
    2: 7 0
    1: 4 0
    7: 6 2
    5: 6 8 9 4
    4: 5 1
    8: 6 5 9
    3: 6 0
    6: 7 8 5 3
    0: 1 2 3
*********************************************/

template <typename T>
ostream& operator << (ostream& out, Graph<T> g) {
    for (auto& vertex : g.vertexSet) {
        out << vertex << ": ";
        for (auto& edge : g.edgeSet) {
            //sync up the vertex from vertex set with the first value of edge set to find its adjacent vertices
            if (vertex == edge.first) {
                out << edge.second << " ";
            }
        }
        out << endl;
    }
    return out;
}




/*
  getPath will return the shortest path from source to dest.
  If you would like a challenge, use a depth first search to traverse
  graph to find the solution.  With that sais, you are not limited to
  that altorihtm, you may use breadth first, shortest path first, or any
  other graph algorithm.
  You will return a vector with the solution.  The source will be in position 1
  the destination is in the last position of the solution, and each node in between
  are the verticies it will travel to get to the destination.  There will not be any
  other verticies in the list.

  Given the test graph:

[0]-----------[2]
|  \            \
|   \            \
[1]  [3]----[6]---[7]
|          /  \
|         /    \
|        /      \
|     [5]--------[8]
|    /   \       /
|   /     \     /
|  /       \   /
[4]         [9]

getPath(0, 5) should return
0 -> 1 -> 4 -> 5   or   0 -> 3 -> 6 -> 5

  Hint: As you find the solution store it in a stack, pop all the items of the stack
  into a vector so it will be in the correct order.

*/

template <typename T>
vector<T> Graph<T>::getPath(T source, T dest) {
    vector<T> solution; //stores complete path from source to destination
    stack<T> pathStack; //used to navigate graph with Depth First Search
    set<T> visitedSet; //used to keep track of vertices we've already visited
    
    
    pathStack.push(source);
    while (!pathStack.empty()) {
        auto currV = pathStack.top();
        pathStack.pop();
        if (!visitedSet.count(currV)) {
            //perform check to avoid adding dead ends in graph to solution path
            if (checkAdj(currV, visitedSet) || currV == dest) {
                solution.push_back(currV);
            }
            visitedSet.emplace(currV);
            //break from while loop if we've found our destination vertex
            if (currV == dest) {
                break;
            }
            //sync up the vertex with the first value of edge set to find its adjacent vertices
            for (auto& edge : edgeSet) {
                if (currV == edge.first) {
                    auto adjV = edge.second;
                    pathStack.push(adjV);
                }
            }// end for each on edgeSet
        }// end if
    }//end of while
    
    return solution;
}


/*********************************************
* returns true if the vertex being visited in DFS is NOT a dead end which must be backtracked from
* i.e. we've already visited all of the vertex's adjacent vertices
*********************************************/
template <typename T>
bool Graph<T>::checkAdj(T vertex, set<T> visitedSet) {

    for (auto& edge : edgeSet) {
        if (vertex == edge.first) {
            auto adjV = edge.second;
            if (!visitedSet.count(adjV)) {
                return true;
            }
        }
    }
    return false;
}

#endif