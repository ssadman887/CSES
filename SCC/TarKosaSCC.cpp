#include <iostream>
#include <list>
#include <stack>

using namespace std;

// Kosaraju's algorithm to find Strongly Connected Components

// Perform DFS and store finish time of vertices
void DFS(int node, stack<int> &st, bool visited[], list<int> adj[]) {
  visited[node] = true;
  for(auto neighbor : adj[node]) {
    if(!visited[neighbor]) {
      DFS(neighbor, st, visited, adj); 
    }
  }
  
  st.push(node);
}

// Reverse edges and perform DFS according to finish times
void revDFS(int node, bool visited[], list<int> transposeAdj[]) {
  visited[node] = true;
  cout << node << " ";
  
  for(auto neighbor : transposeAdj[node]) {
    if(!visited[neighbor]) {
      revDFS(neighbor, visited, transposeAdj);
    }
  }
}

void findSCCs(list<int> adj[], int V) {
  stack<int> st;
  bool visited[V];
  for(int i = 0; i < V; i++)
    visited[i] = false;
  
  for(int i = 0; i < V; i++) {
    if(!visited[i]) {
      DFS(i, st, visited, adj);
    }
  }
  
  list<int> transposeAdj[V];
  for(int i = 0; i < V; i++) {
    visited[i] = false; 
    for(auto neighbor : adj[i]) {
      transposeAdj[neighbor].push_back(i); 
    }
  }
  
  while(!st.empty()) {
    int node = st.top();
    st.pop();
    
    if(!visited[node]) {
      cout << "SCC: ";
      revDFS(node, visited, transposeAdj);
      cout << endl;
    }
  }
}

// Tarjan's algorithm to find Strongly Connected Components 

void SCCUtil(int node, int disc[], int low[], stack<int> &st, bool stackMember[], bool visited[], list<int> adj[]) {
  static int time = 0;
  disc[node] = low[node] = ++time;
  visited[node] = true;
  st.push(node);
  stackMember[node] = true;

  for(auto neighbor : adj[node]) {
    if(!visited[neighbor]) {
      SCCUtil(neighbor, disc, low, st, stackMember, visited, adj);
      low[node] = min(low[node], low[neighbor]); 
    } else if(stackMember[neighbor]) {
      low[node] = min(low[node], disc[neighbor]);
    }
  }

  int w = 0;
  if(disc[node] == low[node]) {
    while(st.top() != node) {
      w = st.top();
      cout << w << " ";
      stackMember[w] = false;
      st.pop();
    }
    w = st.top();
    cout << w << "\n";
    stackMember[w] = false;
    st.pop();
  }
}

void SCC(list<int> adj[], int V) {
  int *disc = new int[V];
  int *low = new int[V];
  bool *stackMember = new bool[V];
  bool *visited = new bool[V];
  stack<int> st;

  for(int i = 0; i < V; i++) {
    disc[i] = -1;
    low[i] = -1;
    stackMember[i] = false;
    visited[i] = false;
  }

  for(int i = 0; i < V; i++) {
    if(!visited[i])
      SCCUtil(i, disc, low, st, stackMember, visited, adj);
  }
}

int main() {
  int V, E;
  
  cout << "Enter number of vertices: ";
  cin >> V;
  cout << "Enter number of edges: ";
  cin >> E;
  
  list<int> adj[V];
  
  cout << "Enter edges:\n";
  for(int i = 0; i < E; i++) {
    int u, v;
    cin >> u >> v;
    adj[u].push_back(v); 
  }
  
  cout << "Kosaraju's Algorithm:\n";
  findSCCs(adj, V);
  
  cout << "\nTarjan's Algorithm:\n";  
  SCC(adj, V);

  return 0;
}