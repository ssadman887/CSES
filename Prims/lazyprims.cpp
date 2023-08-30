#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <algorithm>
using namespace std;

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Function to compare edges based on weights
class Compare {
public:
    bool operator()(Edge& e1, Edge& e2) {
        return e1.weight > e2.weight;
    }
};

// Lazy Prim's algorithm to find the Minimum Spanning Tree (MST)
void lazyPrimMST(vector<vector<pair<int, int>>>& adjList) {
    int V = adjList.size();
    vector<bool> visited(V, false);
    
    // Priority queue to store the MST edges
    priority_queue<Edge, vector<Edge>, Compare> pq;

    // Start from vertex 0
    visited[0] = true;

    // Adding all edges connected to vertex 0 to the priority queue
    for (auto& edge : adjList[0]) {
        pq.push({0, edge.first, edge.second});
    }

    int totalWeight = 0;
    while (!pq.empty()) {
        // Get the minimum weight edge
        Edge minEdge = pq.top();
        pq.pop();

        int u = minEdge.src;
        int v = minEdge.dest;
        int weight = minEdge.weight;

        // If the edge leads to an unvisited vertex, add it to the MST
        if (!visited[v]) {
            cout << u << " -- " << v << " : " << weight << endl;
            totalWeight += weight;
            visited[v] = true;

            // Add all edges connected to the newly visited vertex to the priority queue
            for (auto& edge : adjList[v]) {
                if (!visited[edge.first]) {
                    pq.push({v, edge.first, edge.second});
                }
            }
        }
    }

    cout << "Total weight of the Minimum Spanning Tree (MST): " << totalWeight << endl;
}

int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    // Create the adjacency list for the graph
    vector<vector<pair<int, int>>> adjList(V);

    // Get input for each edge
    for (int i = 0; i < E; i++) {
        int src, dest, weight;
        cout << "Enter edge " << i + 1 << " source, destination, and weight: ";
        cin >> src >> dest >> weight;
        adjList[src].push_back(make_pair(dest, weight));
        adjList[dest].push_back(make_pair(src, weight));
    }

    cout << "Edges of the Minimum Spanning Tree (MST) using Lazy Prim's algorithm:\n";
    lazyPrimMST(adjList);

    return 0;
}
