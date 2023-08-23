#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9; 

struct Edge {
  int src, dest, wt;  
};

vector<Edge> g;
int d[150];
int V, E;

void bellmanFord(int src) {
  for(int i = 0; i < V; i++) {
    d[i] = INF;
  }
  d[src] = 0;
  
  for(int i = 0; i < V-1; i++) {
    for(auto e: g) {
      if(d[e.src] != INF && d[e.src] + e.wt < d[e.dest]) {
        d[e.dest] = d[e.src] + e.wt;  
      }
    }
  }
  
  // detect negative cycle
  for(auto e: g) {
    if(d[e.src] != INF && d[e.src] + e.wt < d[e.dest]) {
      cout << "g contains negative cycle\n";
      return;
    }
  }
}

int main() {
  cin >> V >> E;
  
  for(int i = 0; i < E; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    g.push_back({u, v, w}); 
  }
  
  int Q;
  cin >> Q;
  
  bellmanFord(0); // run BellmanFord from source 0
  
  while(Q--) {
    int x, y;
    cin >> x >> y;
    
    if(d[y] == INF) {
      cout << "Impossible\n";
    }
    else {
      cout << d[y] << "\n";  
    }
  }
  
  return 0;
}