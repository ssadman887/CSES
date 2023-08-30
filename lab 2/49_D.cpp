#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <climits>
using namespace std;


struct Edge {
    int src, dest, weight;
};

// initialize and return a new adjacency list
vector<vector<pair<int, int>>> createGraph(int numVertices) {
    vector<vector<pair<int, int>>> graph(numVertices);
    return graph;
}


void addEdge(vector<vector<pair<int, int>>>& graph, int source, int destination, int weight) {
    graph[source].push_back(make_pair(destination, weight));
    graph[destination].push_back(make_pair(source, weight));
}


void findMaxSpanningTree(vector<vector<pair<int, int>>>& graph) {
    int numVertices = graph.size();
    vector<int> key(numVertices, INT_MIN); // Key values used to pick maximum weight edge
    vector<int> parent(numVertices, -1); // Parent array to store MST
    vector<bool> visited(numVertices, false); // To represent if a vertex is in MST or not

    // Create a priority queue (max heap) to store edges
    priority_queue<pair<int, int>> pq;

    key[0] = 0;
    pq.push(make_pair(0, 0));

    while (!pq.empty()) {
        // Extract maximum key vertex
        int u = pq.top().second;
        pq.pop();

        visited[u] = true; // Include the vertex in MST

        // Check adjacent vertices of u
        for (auto& neighbor : graph[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (!visited[v] && weight > key[v]) {
                // Update key value and parent
                key[v] = weight;
                parent[v] = u;
                pq.push(make_pair(key[v], v));
            }
        }
    }

    // Print
    int totalWeight = 0;
    for (int i = 1; i < numVertices; i++) {
        cout << parent[i] << " -- " << i << " : " << key[i] << endl;
        totalWeight += key[i];
    }

    cout << "Total weight of the Maximum Spanning Tree (MST): " << totalWeight << endl;
}

int main() {
    int numVertices, numEdges;
  
    cin >> numVertices;
   
    cin >> numEdges;


    vector<vector<pair<int, int>>> graph = createGraph(numVertices);

    for (int i = 0; i < numEdges; i++) {
        int source, destination, weight;

        cin >> source >> destination >> weight;
        addEdge(graph, source, destination, weight);
    }

    findMaxSpanningTree(graph);

    return 0;
}
