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

// Function to check if a given graph is connected
bool isConnected(vector<vector<int>>& graph, int V) {
    vector<bool> visited(V, false);

    // Perform DFS
    dfs(graph, 0, visited);

    // Check if all vertices are visited
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            return false;
        }
    }

    return true;
}

// Function to check if the degree of each vertex is even
bool hasEvenDegree(vector<vector<int>>& graph, int V) {
    for (int i = 0; i < V; i++) {
        if (graph[i].size() % 2 != 0) {
            return false;
        }
    }

    return true;
}

// Function to check if a given graph is Eulerian or not
bool isEulerian(vector<vector<int>>& graph, int V) {
    // Check if the graph is connected
    /*if (!isConnected(graph, V)) {
        return false;
    }*/

    // Check if the degree of each vertex is even
    if (isConnected(graph, V) && hasEvenDegree(graph, V)) {
        return true;
    }

    else return false;  // Modified condition
}

int main() {
    int V, E;
    cin >> V >> E;

    // Create the adjacency list for the graph
    vector<vector<int>> graph(V);

    // Get input for each edge
    for (int i = 0; i < E; i++) {
        int src, dest;
        cin >> src >> dest;
        graph[src].push_back(dest);
        graph[dest].push_back(src);
    }

    // Check if the graph is Eulerian
    if (isEulerian(graph, V)) {
        cout << "The given graph is Eulerian." << endl;
    } else {
        cout << "The given graph is not Eulerian." << endl;
    }

    return 0;
}
