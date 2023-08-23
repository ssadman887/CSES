#include <iostream>
#include <limits.h>

using namespace std;

#define V 4 

void floydWarshall(int graph[][V]) {
  int dist[V][V];
  
  // Initialize distance matrix same as input graph matrix
  for(int i=0; i<V; i++) 
    for(int j=0; j<V; j++)
      dist[i][j] = graph[i][j];

  // Floyd-Warshall algorithm
  for(int k=0; k<V; k++) {
    for(int i=0; i<V; i++) {
      for(int j=0; j<V; j++) {
        if (dist[i][k] + dist[k][j] < dist[i][j])
          dist[i][j] = dist[i][k] + dist[k][j];  
      }
    }
  }

  // Print shortest distances
  cout << "All Pairs Shortest Paths: \n";
  for(int i=0; i<V; i++) {
    for(int j=0; j<V; j++) {
      if (dist[i][j] == INT_MAX) 
        cout << "INF" << " ";
      else
        cout << dist[i][j] << " ";
    }
    cout << endl;
  }
}

int main() {


  int graph[V][V];
  cout << "Enter the adjacency matrix: \n";
  for(int i=0; i<V; i++) {
    for(int j=0; j<V; j++) {
      cin >> graph[i][j];
    }
  }
  
  floydWarshall(graph);

  return 0;
}