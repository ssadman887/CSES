#include<bits/stdc++.h>
using namespace std;

void DFS1(int i, vector<int> adj[], vector<bool> &visited, stack<int> &Stack) {
    visited[i] = true;
    for(int j: adj[i])
        if(!visited[j])
            DFS1(j, adj, visited, Stack);
    Stack.push(i);
}

void DFS2(int i, vector<int> adj[], vector<bool> &visited) {
    cout << i << " ";
    visited[i] = true;
    for(int j: adj[i])
        if(!visited[j])
            DFS2(j, adj, visited);
}

void findSCCs(int V, vector<int> adj[]) {
    stack<int> Stack;
    vector<bool> visited(V, false);
    for(int i = 0; i < V; i++)
        if(!visited[i])
            DFS1(i, adj, visited, Stack);
    vector<int> adjT[V];
    for(int i = 0; i < V; i++)
        for(int j: adj[i])
            adjT[j].push_back(i);
    for(int i = 0; i < V; i++)
        visited[i] = false;
    while(!Stack.empty()) {
        int i = Stack.top();
        Stack.pop();
        if(!visited[i]) {
            DFS2(i, adjT, visited);
            cout << endl;
        }
    }
}

int main() {
    int V, E;
    cin >> V >> E;
    vector<int> adj[V];
    for(int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    findSCCs(V, adj);
    return 0;
}
