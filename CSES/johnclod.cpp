#include <iostream>
#include <limits.h>
#include <vector>
#include <queue>

using namespace std;

vector<vector<pair<int, int>>> adjList; 


int V;


vector<int> dijkstra(int src) {
  vector<int> dist(V, INT_MAX);
  dist[src] = 0;
  
  priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
  pq.push({0, src});
  
  while(!pq.empty()) {
    int u = pq.top().second; 
    pq.pop();
    
    for(auto x: adjList[u]) {
      int v = x.first;
      int weight = x.second;
      
      if (dist[v] > dist[u] + weight) {
        dist[v] = dist[u] + weight;
        pq.push({dist[v], v});  
      }
    }
  }
  
  return dist;
}

// Johnson's algorithm 
vector<vector<int>> johnsonAlgorithm() {
  // Add a dummy vertex to graph with 0-weight edges to all
  adjList.resize(V+1);
  
  for(int i=0; i<V; i++) {
    adjList[V].push_back({i, 0}); 
  }
  
  // Run Bellman-Ford from the dummy vertex   
  vector<int> h(V, INT_MAX);
  h[V] = 0;
  
  for(int i=0; i<V-1; i++) {
    for(int u=0; u<=V; u++) {
      for(auto x: adjList[u]) {
        int v = x.first;
        int weight = x.second;
        
        if (h[v] > h[u] + weight) {
          h[v] = h[u] + weight; 
        }
      }
    }
  }
  
  // Reweight edges 
  for(int u=0; u<V; u++) {
    for(auto &x: adjList[u]) {
      int v = x.first;
      int weight = x.second;
      
      x.second = weight + h[u] - h[v];
    }
  }
  
  // Run Dijkstra's from each vertex
  vector<vector<int>> dist(V, vector<int>(V)); 
  for(int i=0; i<V; i++) {
    vector<int> d = dijkstra(i);
    for(int j=0; j<V; j++) {
      dist[i][j] = d[j] + h[i] - h[j]; 
    }
  }

  return dist;
}

