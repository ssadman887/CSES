#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Edge {
    int src, dest, weight;
};

int findParent(int parent[], int i) {
    if (parent[i] == -1)
        return i;
    return findParent(parent, parent[i]);
}

void unionSets(int parent[], int x, int y) {
    int xset = findParent(parent, x);
    int yset = findParent(parent, y);
    if (xset != yset)
        parent[xset] = yset;
}

void KruskalMST(vector<Edge>& edges, int V, int E) {
    vector<Edge> result;
    int e = 0;
    int i = 0;

    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    int* parent = new int[V];
    fill(parent, parent + V, -1);

    while (e < V - 1 && i < E) {
        Edge nextEdge = edges[i++];

        int x = findParent(parent, nextEdge.src);
        int y = findParent(parent, nextEdge.dest);

        if (x != y) {
            result.push_back(nextEdge);
            unionSets(parent, x, y);
            e++;
        }
    }

    cout << "Minimum Spanning Tree using Kruskal's algorithm:\n";
    for (const auto& edge : result) {
        cout << edge.src << " - " << edge.dest << " : " << edge.weight << endl;
    }

    delete[] parent;
}

int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    vector<Edge> edges(E);

    cout << "Enter the edges (source, destination, weight):\n";
    for (int i = 0; i < E; i++) {
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
    }

    KruskalMST(edges, V, E);

    return 0;
}
