#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

const int INF = 99999;

class Graph {
private:
    int numVertices;
    vector<vector<pair<int, int>>> adjacencyList;

public:
    Graph(int V) : numVertices(V), adjacencyList(V) {}

    void addEdge(int source, int destination, int weight) {
        adjacencyList[source].emplace_back(destination, weight);
        adjacencyList[destination].emplace_back(source, weight);
    }

    int getNumVertices() const {
        return numVertices;
    }

    const vector<pair<int, int>>& getNeighbors(int vertex) const {
        return adjacencyList[vertex];
    }
};

class Dijkstra {
private:
    const Graph& graph;
    vector<int> distances;

public:
    Dijkstra(const Graph& g) : graph(g), distances(g.getNumVertices(), INF) {}

    void shortestPath(int start) {
        distances[start] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            int u = pq.top().second;
            int dist_u = pq.top().first;
            pq.pop();

            if (dist_u > distances[u]) {
                continue; // Skip outdated entries in priority queue
            }

            for (const auto& neighbor : graph.getNeighbors(u)) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                    pq.push({distances[v], v});
                }
            }
        }
    }

    int getDistance(int vertex) const {
        return distances[vertex];
    }
};

int main() {
    int numVertices, numEdges;
    cin >> numVertices >> numEdges;

    Graph mahibGraph(numVertices);

    for (int i = 0; i < numEdges; i++) {
        int source, destination, weight;
        cin >> source >> destination >> weight;
        mahibGraph.addEdge(source, destination, weight);
    }

    int numDeliveries;
    cin >> numDeliveries;

    vector<int> deliveryOrder(numDeliveries);
    for (int i = 0; i < numDeliveries; i++) {
        cin >> deliveryOrder[i];
    }

    int totalDistance = 0;
    bool noPath = false;

    for (int i = 1; i < numDeliveries; i++) {
        Dijkstra mahibDijkstra(mahibGraph);
        mahibDijkstra.shortestPath(deliveryOrder[i - 1]);

        int distance = mahibDijkstra.getDistance(deliveryOrder[i]);
        if (distance == INF) {
            noPath = true;
            break;
        }
        totalDistance += distance;
    }

    if (noPath) {
        cout << "infinity" << endl;
    } else {
        cout << totalDistance << endl;
    }

    return 0;
}
