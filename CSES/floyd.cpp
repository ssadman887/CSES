#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

void floydWarshall(vector<vector<int>> &graph, int V) {

  int dist[V][V];
  
  for(int i=0; i<V; i++) {
    for(int j=0; j<V; j++) {
      dist[i][j] = graph[i][j];
    }
  }

  // Floyd-Warshall algorithm
  for(int k=0; k<V; k++) {
    for(int i=0; i<V; i++) {
      for(int j=0; j<V; j++) {
        if(dist[i][k] + dist[k][j] < dist[i][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
        }
      }
    }
  }

  // Print shortest distances
  for(int i=0; i<V; i++) {
    for(int j=0; j<V; j++) {
      if(dist[i][j] == INT_MAX) {
        cout << "INF ";
      }
      else {
        cout << dist[i][j] << " ";
      }
    }
    cout << endl;
  }

}

int main() {

  int V, E;
  cin >> V >> E;
  
  vector<vector<int>> graph(V, vector<int>(V, INT_MAX));

  // Read E edges
  for(int i=0; i<E; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    graph[u][v] = w;
  }

  floydWarshall(graph, V);

  return 0;
}