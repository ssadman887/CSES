#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class PriorityQueue {
private:
    vector<pair<int, int>> pq; // Elements stored in the format: (priority, value)

public:
    // Constructor
    PriorityQueue() {}

    // Function to check if the priority queue is empty
    bool empty() {
        return pq.empty();
    }

    // Function to insert an element into the priority queue
    void push(pair<int, int> element) {
        pq.push_back(element);
        int i = pq.size() - 1;
        int parent = (i - 1) / 2;

        while (i > 0 && pq[i].first < pq[parent].first) {
            swap(pq[i], pq[parent]);
            i = parent;
            parent = (i - 1) / 2;
        }
    }

    // Function to remove and return the element with the highest priority
    pair<int, int> pop() {
        if (empty()) {
            cerr << "Error: Priority queue is empty!" << endl;
            return make_pair(INT_MAX, -1);
        }

        pair<int, int> topElement = pq[0];
        pq[0] = pq[pq.size() - 1];
        pq.pop_back();

        int i = 0;
        while (true) {
            int leftChild = 2 * i + 1;
            int rightChild = 2 * i + 2;
            int smallest = i;

            if (leftChild < pq.size() && pq[leftChild].first < pq[smallest].first) {
                smallest = leftChild;
            }
            if (rightChild < pq.size() && pq[rightChild].first < pq[smallest].first) {
                smallest = rightChild;
            }

            if (smallest == i) {
                break;
            }

            swap(pq[i], pq[smallest]);
            i = smallest;
        }

        return topElement;
    }
};

typedef pair<int, int> iPair;
vector<iPair> adj[1001]; //Adjacency list
vector<int> dist(1001, INT_MAX); //Distances to vertices
vector<bool> visited(1001, false); //Visited vertices


void prim(int x, int V, vector<pair<int, int>> adj[]) {
    vector<int> dist(V + 1, INT_MAX);
    vector<bool> visited(V + 1, false);
    PriorityQueue pq;

    dist[x] = 0;
    pq.push(make_pair(0, x));
    while (!pq.empty()) {
        int a = pq.pop().second;
        if (visited[a]) continue;
        visited[a] = true;
        for (auto u : adj[a]) {
            int b = u.first, w = u.second;
            if (w < dist[b]) {
                dist[b] = w;
                pq.push(make_pair(w, b));
            }
        }
    }

    // Print the minimum distances
    for (int i = 1; i <= V; i++) {
        if (i != x) { // Skip the starting vertex
            cout << "Minimum distance from vertex " << x << " to vertex " << i << " is " << dist[i] << endl;
        }
    }
}

int main() {
    int V, E; // Number of vertices and edges

    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    // Create empty adjacency list
    vector<pair<int, int>> adj[V + 1];

    // Add edges to the adjacency list
    cout << "Enter the edges and their weights in the format: source destination weight" << endl;
    for (int i = 0; i < E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }

    int startVertex;
    cout << "Enter the starting vertex: ";
    cin >> startVertex;

    // Run Prim's algorithm
    prim(startVertex, V, adj);

    return 0;
}
