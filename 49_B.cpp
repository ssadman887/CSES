#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> My_Pair;
typedef vector<int> vi;

vector<vi> paths;
vector<My_Pair> adj[100005];

void addEdge(int u, int v, int w) {
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}

void dijkstra(int V, int src) {
    priority_queue< My_Pair, vector <My_Pair> , greater<My_Pair> > pq;
    vector<int> dist(V, INT_MAX);
    pq.push(make_pair(0, src));
    dist[src] = 0;
    paths[src].push_back(src);

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        for (auto x : adj[u]) {
            int v = x.first;
            int wt = x.second;

            if (dist[v] > dist[u] + wt || (dist[v] == dist[u] + wt && paths[v] > paths[u])) {
                dist[v] = dist[u] + wt;
                paths[v] = paths[u];
                paths[v].push_back(v);
                pq.push(make_pair(dist[v], v));
            }
        }
    }
}

int main() {
    int V, E;
    cin >> V >> E;
    paths.resize(V);

    for(int i=0; i<E; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        addEdge(u, v, w);
    }

    dijkstra(V, 0);

    if(paths[1].empty()) {
        cout << "NOT REACHABLE" << endl;
    } else {
        for(int i : paths[1]) {
            cout << i << endl;
        }
    }

    return 0;
}
