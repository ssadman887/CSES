#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m; // Input the number of vertices n and edges m
    vector<vector<int>> adj(n + 1); // create adjacency list

    for (int i = 0; i < m; i++) {
        // Input the edges
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Output the adjacency list
    for (int i = 1; i <= n; i++) {
        cout << i << " --> ";
        for (int j = 0; j < adj[i].size(); j++) {
            cout << adj[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
