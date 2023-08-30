#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Helper function for DFS
void dfs(auto &adjList, auto &visited, int vertex, auto &result) {
    visited[vertex] = true;
    for (int neighbor : adjList[vertex]) {
        if (!visited[neighbor]) {
            dfs(adjList, visited, neighbor, result);
        }
    }
    result.push(vertex);
}

vector<int> topologicalSort(vector<vector<int>>& adjList, int numVertices) {
    vector<int> ordering;
    stack<int> result;
    vector<bool> visited(numVertices, false);

    for (int i = 0; i < numVertices; ++i) {
        if (!visited[i]) {
            dfs(adjList, visited, i, result);
        }
    }

    while (!result.empty()) {
        ordering.push_back(result.top());
        result.pop();
    }

    return ordering;
}

int main() {
    int numVertices, numEdges;
    cin >> numVertices >> numEdges;

    vector<vector<int>> adjList(numVertices);

    for (int i = 0; i < numEdges; ++i) {
        int u, v;
        cin >> u >> v;
        adjList[u].push_back(v);
    }

    vector<int> result = topologicalSort(adjList, numVertices);

    for (int vertex : result) {
        cout << vertex << " ";
    }
    cout << endl;

    return 0;
}

