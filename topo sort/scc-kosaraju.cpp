#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// Helper function for first DFS pass
void dfs1(vector<vector<int>>& graph, vector<bool>& visited, int vertex, stack<int>& finishTimes) {
    visited[vertex] = true;
    for (int neighbor : graph[vertex]) {
        if (!visited[neighbor]) {
            dfs1(graph, visited, neighbor, finishTimes);
        }
    }
    finishTimes.push(vertex);
}

// Helper function for second DFS pass
void dfs2(vector<vector<int>>& transposeGraph, vector<bool>& visited, int vertex, vector<int>& scc) {
    visited[vertex] = true;
    scc.push_back(vertex);
    for (int neighbor : transposeGraph[vertex]) {
        if (!visited[neighbor]) {
            dfs2(transposeGraph, visited, neighbor, scc);
        }
    }
}

// Function to find strongly connected components
vector<vector<int>> findSCCs(vector<vector<int>>& graph, int numVertices) {
    vector<bool> visited(numVertices, false);
    stack<int> finishTimes;
    for (int i = 0; i < numVertices; ++i) {
        if (!visited[i]) {
            dfs1(graph, visited, i, finishTimes);
        }
    }

    vector<vector<int>> transposeGraph(numVertices);
    for (int i = 0; i < numVertices; ++i) {
        for (int neighbor : graph[i]) {
            transposeGraph[neighbor].push_back(i);
        }
    }

    vector<vector<int>> stronglyConnectedComponents;
    visited.assign(numVertices, false);
    while (!finishTimes.empty()) {
        int vertex = finishTimes.top();
        finishTimes.pop();
        if (!visited[vertex]) {
            vector<int> scc;
            dfs2(transposeGraph, visited, vertex, scc);
            stronglyConnectedComponents.push_back(scc);
        }
    }

    return stronglyConnectedComponents;
}

int main() {
    int numVertices, numEdges;
    cout << "Enter the number of vertices and edges: ";
    cin >> numVertices >> numEdges;

    vector<vector<int>> graph(numVertices);
    cout << "Enter the edges (source and destination):" << endl;
    for (int i = 0; i < numEdges; ++i) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }

    vector<vector<int>> SCCs = findSCCs(graph, numVertices);

    cout << "Strongly Connected Components:" << endl;
    for (const vector<int>& scc : SCCs) {
        for (int vertex : scc) {
            cout << vertex << " ";
        }
        cout << endl;
    }

    return 0;
}
