#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void DFS(vector<vector<int>>& graph, int u, vector<int>& disc, vector<int>& low, vector<int>& parent, vector<bool>& visited, vector<bool>& isAP) {
    static int time = 0;
    int children = 0;
    disc[u] = low[u] = time++;
    visited[u] = true;

    for (int v : graph[u]) {
        if (!visited[v]) {
            children++;
            parent[v] = u;
            DFS(graph, v, disc, low, parent, visited, isAP);
            low[u] = min(low[u], low[v]);

            // Check if u is an articulation point
            if (parent[u] != -1 && low[v] >= disc[u])
                isAP[u] = true;
        } else if (v != parent[u])
            low[u] = min(low[u], disc[v]);
    }

    // Check if u is the root node and has more than one child
    if (parent[u] == -1 && children > 1)
        isAP[u] = true;
}

void findArticulationPoints(vector<vector<int>>& graph) {
    int V = graph.size();
    vector<int> disc(V, -1);
    vector<int> low(V, -1);
    vector<int> parent(V, -1);
    vector<bool> visited(V, false);
    vector<bool> isAP(V, false);

    for (int u = 0; u < V; u++) {
        if (!visited[u])
            DFS(graph, u, disc, low, parent, visited, isAP);
    }

    cout << "Articulation points: ";
    for (int u = 0; u < V; u++) {
        if (isAP[u])
            cout << u << " ";
    }
    cout << endl;
}

int main() {
    int V, E;

    cout << "Enter the number of vertices: ";
    cin >> V;

    cout << "Enter the number of edges: ";
    cin >> E;

    vector<vector<int>> graph(V);
    cout << "Enter the edges (source and destination):" << endl;
    for (int i = 0; i < E; i++) {
        int src, dest;
        cin >> src >> dest;
        graph[src].push_back(dest);
        graph[dest].push_back(src);
    }

    findArticulationPoints(graph);

    return 0;
}
