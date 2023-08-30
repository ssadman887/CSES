#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>

using namespace std;

const int INF = 99999;

struct Edge {
    int to;
    int weight;
    Edge(int _to, int _weight) : to(_to), weight(_weight) {}
};

void dijkstra(const vector<vector<Edge>>& graph, int start, vector<int>& distances) {
    int n = graph.size();
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

        for (const Edge& edge : graph[u]) {
            int v = edge.to;
            int weight = edge.weight;

            if (distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                pq.push({distances[v], v});
            }
        }
    }
}

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<Edge>> graph(N);

    for (int i = 0; i < M; i++) {
        int U, V, W;
        cin >> U >> V >> W;
        graph[U].emplace_back(V, W);
        graph[V].emplace_back(U, W);
    }

    int R;
    cin >> R;

    vector<int> deliveryOrder(R);
    for (int i = 0; i < R; i++) {
        cin >> deliveryOrder[i];
    }

    int totalDistance = 0;
    bool noPath = false;

    for (int i = 1; i < R; i++) {
        vector<int> distances(N, INF);
        dijkstra(graph, deliveryOrder[i - 1], distances);

        if (distances[deliveryOrder[i]] == INF) {
            noPath = true;
            break;
        }
        totalDistance += distances[deliveryOrder[i]];
    }

    if (noPath) {
        cout << "infinity" << endl;
    } else {
        cout << totalDistance << endl;
    }

    return 0;
}
