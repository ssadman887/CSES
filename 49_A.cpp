#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> My_Pair;

void addEdge(vector <pair<int, int> > adj[], int u, int v, int wt) {
    adj[u].push_back(make_pair(v, wt));
    adj[v].push_back(make_pair(u, wt));
}

void shortestPath(vector<pair<int,int> > adj[], int V, int src) {
    priority_queue< My_Pair, vector <My_Pair> , greater<My_Pair> > pq;

    vector<int> dist(V, INT_MAX);

    pq.push(make_pair(0, src));
    dist[src] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto x : adj[u]) {
            int v = x.first;
            int wt = x.second;

            if (dist[v] > dist[u] + wt) {
                dist[v] = dist[u] + wt;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    for (int i = 0; i < V; ++i) {
        if(dist[i] == INT_MAX) {
            cout << i << ": " << -1 << endl;
        } else {
            cout << i << ": " << dist[i] << endl;
        }
    }
}

int main() {
    int V, E;
    cin >> V >> E;

    vector<My_Pair > adj[V];

    for(int i=0; i<E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        addEdge(adj, u, v, w);
    }

    shortestPath(adj, V, 0);

    return 0;
}
