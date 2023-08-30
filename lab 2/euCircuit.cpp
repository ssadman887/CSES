#include <iostream>
#include <vector>
using namespace std;

// Helper function for depth-first search
void dfs(vector<vector<int>>& graph, int vertex, vector<bool>& visited) {
    visited[vertex] = true;

    for (int i = 0; i < graph[vertex].size(); i++) {
        int adjacentVertex = graph[vertex][i];
        if (!visited[adjacentVertex]) {
            dfs(graph, adjacentVertex, visited);
        }
    }
}

// Function to check if a given graph is Eulerian or not
bool isEulerian(vector<vector<int>>& graph, int V) {
    vector<bool> visited(V, false);

    // Check if the graph is connected
    dfs(graph, 0, visited);
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            return false;
        }
    }

    // Check if the degree of each vertex is even
    for (int i = 0; i < V; i++) {
        if (graph[i].size() % 2 != 0) {
            return false;
        }
    }

    return true;
}

int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    // Create the adjacency list for the graph
    vector<vector<int>> graph(V);

    // Get input for each edge
    cout << "Enter the edges:" << endl;
    for (int i = 0; i < E; i++) {
        int src, dest;
        cout << "Enter edge " << i + 1 << " source and destination: ";
        cin >> src >> dest;
        graph[src].push_back(dest);
        graph[dest].push_back(src);
    }

    // Check if the graph is an Euler circuit
    if (isEulerian(graph, V) && E > 0) {
        cout << "The given graph has an Euler circuit." << endl;
    } else {
        cout << "The given graph does not have an Euler circuit." << endl;
    }

    return 0;
}
