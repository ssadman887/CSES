#include<bits/stdc++.h>
using namespace std;

struct Edge {
    int src, dest, weight;
};

void BellmanFord(struct Edge* edges, int V, int E, int src, int dest) {
    int dist[V], pred[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        pred[i] = -1;
    }
    dist[src] = 0;

    for (int i = 1; i <= V-1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pred[v] = u;
            }
        }
    }

    for (int i = 0; i < E; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int weight = edges[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
            cout << "Graph contains negative weight cycle" << endl;
    }

    cout << "Shortest Path from " << src << " to " << dest << ": ";
    vector<int> path;
    for (int v = dest; v != -1; v = pred[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    for (int v : path)
        cout << v << " ";
    cout << endl;
}

int main() {
    int V, E, dest;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    struct Edge* edges = new Edge[E];

    for (int i = 0; i < E; i++) {
        cout << "Enter source, destination and weight for edge " << i+1 << ": ";
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
    }

    cout << "Enter destination vertex: ";
    cin >> dest;

    BellmanFord(edges, V, E, 0, dest);

    delete[] edges;

    return 0;
}
