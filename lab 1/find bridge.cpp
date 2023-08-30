#include <iostream>
#include <vector>
using namespace std;

void findBridgesDFS(int u, int parent, vector<int>& disc, vector<int>& low, vector<bool>& visited, const vector<vector<int>>& graph, vector<pair<int, int>>& bridges) {
    static int time = 0;
    disc[u] = low[u] = time++;
    visited[u] = true;

    for (int v : graph[u]) {
        if (!visited[v]) {
            findBridgesDFS(v, u, disc, low, visited, graph, bridges);
            low[u] = min(low[u], low[v]);

            if (low[v] > disc[u]) {
                bridges.push_back({u, v});
            }
        } else if (v != parent) {
            low[u] = min(low[u], disc[v]);
        }
    }
}

vector<pair<int, int>> findBridges(const vector<vector<int>>& graph) {
    int V = graph.size();
    vector<int> disc(V, -1);
    vector<int> low(V, -1);
    vector<bool> visited(V, false);
    vector<pair<int, int>> bridges;

    for (int u = 0; u < V; u++) {
        if (!visited[u]) {
            findBridgesDFS(u, -1, disc, low, visited, graph, bridges);
        }
    }

    return bridges;
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

    vector<pair<int, int>> bridges = findBridges(graph);

    cout << "Bridges in the graph:" << endl;
    for (const pair<int, int>& bridge : bridges) {
        cout << bridge.first << " - " << bridge.second << endl;
    }

    return 0;
}
