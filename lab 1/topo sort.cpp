#include <bits/stdc++.h>
using namespace std;

void topologicalSortUtil(int v, vector<bool>& visited, vector<vector<int>>& adj, stack<int>& Stack) {
    visited[v] = true;

    for (int i : adj[v]) {
        if (!visited[i]) {
            topologicalSortUtil(i, visited, adj, Stack);
        }
    }

    Stack.push(v);
}

void topologicalSort(vector<vector<int>>& adj) {
    int V = adj.size();
    vector<bool> visited(V, false);
    stack<int> Stack;

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            topologicalSortUtil(i, visited, adj, Stack);
        }
    }

    //cout << "Topological Sorting: ";
    while (!Stack.empty()) {
        cout << Stack.top() << " ";
        Stack.pop();
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

    topologicalSort(adj);

    return 0;
}
