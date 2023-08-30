#include <bits/stdc++.h>

using namespace std;

const int INF = 99999;
const int MAX_V = 100;

void calculateShortestPaths(int graph[][MAX_V], int V) {
  int dist[MAX_V][MAX_V];
  
  // Initialize distance matrix same as input graph matrix
  for(int i=0; i<V; i++) 
    for(int j=0; j<V; j++)
      dist[i][j] = graph[i][j];

  // Floyd-Warshall algorithm
  for(int k=0; k<V; k++) {
    for(int i=0; i<=k; i++) {
      for(int j=0; j<=k; j++) {
        if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j])
          dist[i][j] = dist[i][k] + dist[k][j];  
      }
    }

    // Calculate the sum of all pair shortest paths
    int sum = 0;
    for(int i=0; i<=k; i++) {
      for(int j=0; j<=k; j++) {
        if(dist[i][j] != INF)
          sum += dist[i][j];
      }
    }

    // Print the sum
    cout << sum << endl;
  }
}

int main() {
  int V, E;
  cin >> V >> E;

  int graph[MAX_V][MAX_V]; 
  for(int i=0; i<V; i++) {
    for(int j=0; j<V; j++) {
      if(i == j)
        graph[i][j] = 0;
      else
        graph[i][j] = INF;
    }
  }

  for(int i=0; i<E; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    graph[u][v] = w;
    graph[v][u] = w;
  }
  
  calculateShortestPaths(graph, V);

  return 0;
}
