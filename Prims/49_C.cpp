#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <climits>
using namespace std;


struct Edge {
    int src, dest, weight;
};

vector<vector<pair<int, int>>> initializeGraph(int vertices) {
    vector<vector<pair<int, int>>> graph(vertices);
    return graph;
}

// Function to add an edge to the graph
void addEdge(vector<vector<pair<int, int>>>& graph, int source, int destination, int weight) {
    graph[source].push_back(make_pair(destination, weight));
    graph[destination].push_back(make_pair(source, weight));
}

// Eager Prim's algorithm to find the Minimum Spanning Tree (MST)
void eagerPrimMST(vector<vector<pair<int, int>>>& graph) {
    int vertices = graph.size();
    vector<int> key(vertices, INT_MAX); // Key values used to pick minimum weight edge
    vector<int> parent(vertices, -1); // Parent array to store MST
    vector<bool> visited(vertices, false); // To represent if a vertex is in MST or not

    // Create a priority queue (min heap) to store edges
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Start with vertex 0
    key[0] = 0;
    pq.push(make_pair(0, 0));

    while (!pq.empty()) {
        // Extract minimum key vertex
        int u = pq.top().second;
        pq.pop();

        visited[u] = true; // Include the vertex in MST

        // Check adjacent vertices of u
        for (auto& neighbor : graph[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (!visited[v] && weight < key[v]) {
                // Update key value and parent
                key[v] = weight;
                parent[v] = u;
                pq.push(make_pair(key[v], v));
            }
        }
    }

    // Print the Minimum Spanning Tree (MST) edges
    //cout << "Minimum Spanning Tree (MST) using Eager Prim's algorithm:\n";
    int totalWeight = 0;
    for (int i = 1; i < vertices; i++) {
        cout << parent[i] << " -- " << i << " : " << key[i] << endl;
        totalWeight += key[i];
    }

    cout << "Total weight of the Minimum Spanning Tree (MST): " << totalWeight << endl;
}

int main() {
    int vertices, edges;
    cin >> vertices;
    cin >> edges;
    vector<vector<pair<int, int>>> graph = initializeGraph(vertices);
    
    for (int i = 0; i < edges; i++) {
        int source, destination, weight;
       // cout << "Enter edge " << i + 1 << " source, destination, and weight: ";
        cin >> source >> destination >> weight;
        addEdge(graph, source, destination, weight);
    }
    eagerPrimMST(graph);

    return 0;
}
