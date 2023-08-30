#include<bits/stdc++.h>
using namespace std;

void topologicalSort(vector<int> adj[], int V) {
    vector<int> in_degree(V, 0);
    for (int u=0; u<V; u++) {
        for (int v: adj[u])
            in_degree[v]++;
    }
    queue<int> q;
    for (int i=0; i<V; i++)
        if (in_degree[i] == 0)
            q.push(i);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        cout << u << " ";
        for (int v: adj[u])
            if (--in_degree[v] == 0)
                q.push(v);
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
    topologicalSort(adj, V);
    return 0;
}
