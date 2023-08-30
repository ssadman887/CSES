#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> adj;
vector<bool> visited; 
vector<int> cc;

void dfs(int v) {
  visited[v] = true;
  cc.push_back(v);
  
  for(int u : adj[v]) {
    if(!visited[u])
      dfs(u);
  }
}

vector<vector<int>> connectedComponents() {

  int V = adj.size();
  visited.assign(V, false);
  
  vector<vector<int>> components;

  for(int v=0; v<V; v++) {
    if(!visited[v]) {
      cc.clear();
      dfs(v);
      components.push_back(cc); 
    }
  }

  return components;
}

int main() {

  int V, E;
  cout << "Enter number of vertices: ";
  cin >> V;

  adj.resize(V);

  cout << "Enter number of edges: ";
  cin >> E;

  for(int i=0; i<E; i++) {
    int u, v;
    cin >> u >> v;

    adj[u].push_back(v);
    adj[v].push_back(u); 
  }

  vector<vector<int>> components = connectedComponents();

  for(auto c : components) {
    for(int v : c) {
      cout << v << " ";
    }
    cout << endl;
  }

  return 0;
}