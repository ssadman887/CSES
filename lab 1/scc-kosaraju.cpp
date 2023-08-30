#include <bits/stdc++.h>
using namespace std;

void fillOrder(int v, vector<vector<int>>& adj, vector<bool>& visited, stack<int>& Stack) {
    visited[v] = true;

    for (int i : adj[v]) {
        if (!visited[i]) {
            fillOrder(i, adj, visited, Stack);
        }
    }

    Stack.push(v);
}

void DFSUtil(int v, vector<vector<int>>& adj, vector<bool>& visited) {
    visited[v] = true;
    cout << v << " ";

    for (int i : adj[v]) {
        if (!visited[i]) {
            DFSUtil(i, adj, visited);
        }
    }
}

void printSCCs(vector<vector<int>>& adj) {
    int V = adj.size();
    vector<bool> visited(V, false);
    stack<int> Stack;

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            fillOrder(i, adj, visited, Stack);
        }
    }

    vector<vector<int>> transpose(V);
    for (int i = 0; i < V; i++) {
        for (int j : adj[i]) {
            transpose[j].push_back(i);
        }
    }

    fill(visited.begin(), visited.end(), false);

    while (!Stack.empty()) {
        int v = Stack.top();
        Stack.pop();

        if (!visited[v]) {
            DFSUtil(v, transpose, visited);
            cout << endl;
        }
    }
}

int main() {
    int V, E;
    //cout << "Enter the number of vertices: ";
    cin >> V;
    //cout << "Enter the number of edges: ";
    cin >> E;

    vector<vector<int>> adj(V);

    //cout << "Enter the edges (source and destination):" << endl;
    for (int i = 0; i < E; i++) {
        int src, dest;
        cin >> src >> dest;
        adj[src].push_back(dest);
    }

    //cout << "Strongly Connected Components (SCCs):" << endl;
    printSCCs(adj);

    return 0;
}
