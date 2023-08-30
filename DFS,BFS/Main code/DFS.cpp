#include <iostream>
#include <vector>

using namespace std;


void dfs(int node, vector<vector<int>>& graph, vector<bool>& visited) {
    visited[node] = true;
    cout << node << " "; // Print the visited node
    
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs(neighbor, graph, visited);
        }
    }
}



int main() {
    int n; 
    cin >> n;
    vector<vector<int>> graph(n); 
    vector<bool> visited(n, false);
    int m;
    cin >> m;


    for (int i = 0; i < m; i++) {
        int u, v; 
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u); 
    }
    int src; 
    cin >> src;
    dfs(src, graph, visited);

    return 0;
}
