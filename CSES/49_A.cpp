#include <iostream>
#include <limits.h>

using namespace std;

const int inf = 99999;

void floydWarshall(int adjacencyMatrix[][100], int numVertices) {

  int shortestDistances[numVertices][numVertices];
  
  for(int row = 0; row < numVertices; row++) {
    for(int col = 0; col < numVertices; col++) {
      shortestDistances[row][col] = adjacencyMatrix[row][col];
    }
  }

  for(int intermediateVertex = 0; intermediateVertex < numVertices; intermediateVertex++) {
    for(int row = 0; row < numVertices; row++) {
      for(int col = 0; col < numVertices; col++) {
        if(shortestDistances[row][intermediateVertex] != inf &&
           shortestDistances[intermediateVertex][col] != inf &&
           shortestDistances[row][intermediateVertex] + shortestDistances[intermediateVertex][col] < shortestDistances[row][col]) {
            shortestDistances[row][col] = shortestDistances[row][intermediateVertex] + shortestDistances[intermediateVertex][col];
        }
      }
    }
  }

  for(int row = 0; row < numVertices; row++) {
    for(int col = 0; col < numVertices; col++) {
      if(row < col) {
        cout << row << " to " << col << ": ";
        if(shortestDistances[row][col] == inf) {
          cout << "infinity" << endl;
        } else {
          cout << shortestDistances[row][col] << endl;
        }
      }
    }
  }
}

int main() {

  int numVertices, numEdges;
  cin >> numVertices >> numEdges;

  int adjacencyMatrix[100][100];
  for(int row = 0; row < numVertices; row++) {
    for(int col = 0; col < numVertices; col++) {
      adjacencyMatrix[row][col] = inf;
    }
  }

  for(int i=0; i<numEdges; i++) {
    int src, dst, weight;
    cin >> src >> dst >> weight;
    adjacencyMatrix[src][dst] = min(adjacencyMatrix[src][dst], weight);
    adjacencyMatrix[dst][src] = min(adjacencyMatrix[dst][src], weight);
  }

  floydWarshall(adjacencyMatrix, numVertices);

  return 0;
}