#include <iostream>
#include <vector>
#include <algorithm>
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
                bridges.push_back({ u, v });
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
    int numberOfVertices, numberOfEdges;

    cin >> numberOfVertices;
    cin >> numberOfEdges;

    vector<vector<int>> graph(numberOfVertices);

    for (int i = 0; i < numberOfEdges; i++) {
        int source, destination;
        cin >> source >> destination;
        graph[source].push_back(destination);
        graph[destination].push_back(source);
    }

    vector<pair<int, int>> bridges = findBridges(graph);

    // Sort bridges in increasing order based on the first element
    sort(bridges.begin(), bridges.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.first < b.first;
    });

    // Print the bridge vertices
    for (const pair<int, int>& bridge : bridges) {
        cout << bridge.first << " " << bridge.second << endl;
    }

    return 0;
}
