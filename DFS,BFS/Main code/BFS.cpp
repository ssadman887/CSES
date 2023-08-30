#include<bits/stdc++.h>
using namespace std;

void BFS(int start, vector<int> adj[], bool visited[]) {
    queue<int> q;
    visited[start] = true;
    q.push(start);
    while(!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";
        for(int i: adj[node]) {
            if(!visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
}

int main() {
    int V, E;
    cin >> V >> E;
    bool visited[V];
    memset(visited, false, sizeof(visited));
    vector<int> adj[V];
    for(int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); // For undirected graph
    }
    
    BFS(0, adj, visited); // Starting BFS from node 0
    return 0;
}
