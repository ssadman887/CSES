#include <iostream>
#include <limits.h>

using namespace std;

const int inf = 99999;

void floydWarshall(int** adjacencyMatrix, int numVertices) {

  int** shortestDistances = new int*[numVertices];
  for(int i = 0; i < numVertices; i++)
    shortestDistances[i] = new int[numVertices]; 

  for(int srcVertex = 0; srcVertex < numVertices; srcVertex++) {
    for(int dstVertex = 0; dstVertex < numVertices; dstVertex++) {
      shortestDistances[srcVertex][dstVertex] = adjacencyMatrix[srcVertex][dstVertex];
    }
  }

  for(int intermediateVertex = 0; intermediateVertex < numVertices; intermediateVertex++) {
    for(int srcVertex = 0; srcVertex < numVertices; srcVertex++) {
      for(int dstVertex = 0; dstVertex < numVertices; dstVertex++) {
      
        if(shortestDistances[srcVertex][intermediateVertex] != inf &&
           shortestDistances[intermediateVertex][dstVertex] != inf &&
           shortestDistances[srcVertex][intermediateVertex] + shortestDistances[intermediateVertex][dstVertex] <
           shortestDistances[srcVertex][dstVertex]) {
           
           shortestDistances[srcVertex][dstVertex] = shortestDistances[srcVertex][intermediateVertex] +
                                                    shortestDistances[intermediateVertex][dstVertex];
        }
      }
    }
  }

  for(int srcVertex = 0; srcVertex < numVertices; srcVertex++) {
    for(int dstVertex = 0; dstVertex < numVertices; dstVertex++) {
      
      if(srcVertex != dstVertex) {
        cout << srcVertex << " to " << dstVertex << ": ";
        
        if(shortestDistances[srcVertex][dstVertex] == inf) {
          cout << "infinity";
        }
        else {
          cout << shortestDistances[srcVertex][dstVertex]; 
        }
        
        cout << endl;
      }
    }
  }
}

int main() {

  int numVertices, numEdges;
  cin >> numVertices >> numEdges;

  int** adjacencyMatrix = new int*[numVertices];
  for(int i = 0; i < numVertices; i++) 
    adjacencyMatrix[i] = new int[numVertices];

  for(int srcVertex = 0; srcVertex < numVertices; srcVertex++) {
    for(int dstVertex = 0; dstVertex < numVertices; dstVertex++) {
    
      if(srcVertex == dstVertex) 
        adjacencyMatrix[srcVertex][dstVertex] = 0;
      else
        adjacencyMatrix[srcVertex][dstVertex] = inf;
    }
  }

  for(int i = 0; i < numEdges; i++) {
    int src, dst, weight;
    cin >> src >> dst >> weight;
    adjacencyMatrix[src][dst] = min(adjacencyMatrix[src][dst], weight); 
  }

  floydWarshall(adjacencyMatrix, numVertices);

  return 0;
}