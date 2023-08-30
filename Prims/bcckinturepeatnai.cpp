#include <iostream>
#include <vector>
#include <stack>
#include <unordered_set>
using namespace std;

void DFS(vector<vector<int>>& graph, int u, vector<int>& disc, vector<int>& low, vector<int>& parent, vector<bool>& visited, stack<pair<int, int>>& st, vector<vector<int>>& bcc) {
    static int time = 0;
    disc[u] = low[u] = time++;
    visited[u] = true;

    for (int v : graph[u]) {
        if (!visited[v]) {
            parent[v] = u;
            st.push({u, v});
            DFS(graph, v, disc, low, parent, visited, st, bcc);
            low[u] = min(low[u], low[v]);

            if (low[v] >= disc[u]) {
                vector<int> component;
                unordered_set<int> uniqueVertices;
                while (st.top() != make_pair(u, v)) {
                    uniqueVertices.insert(st.top().first);
                    uniqueVertices.insert(st.top().second);
                    st.pop();
                }
                uniqueVertices.insert(st.top().first);
                uniqueVertices.insert(st.top().second);
                st.pop();
                for (int v : uniqueVertices) {
                    component.push_back(v);
                }
                bcc.push_back(component);
            }
        } else if (v != parent[u] && disc[v] < disc[u]) {
            st.push({u, v});
            low[u] = min(low[u], disc[v]);
        }
    }
}

vector<vector<int>> findBiconnectedComponents(vector<vector<int>>& graph) {
    int V = graph.size();
    vector<int> disc(V, -1);
    vector<int> low(V, -1);
    vector<int> parent(V, -1);
    vector<bool> visited(V, false);
    stack<pair<int, int>> st;
    vector<vector<int>> bcc;

    for (int u = 0; u < V; u++) {
        if (!visited[u])
            DFS(graph, u, disc, low, parent, visited, st, bcc);
    }

    return bcc;
}

int main() {
    int V, E;

    cout << "Enter the number of vertices: ";
    cin >> V;

    cout << "Enter the number of edges: ";
    cin >> E;

    vector<vector<int>> graph(V);
    cout << "Enter the edges (source and destination):" << endl;
    for (int i = 0; i < E; i++) {
        int src, dest;
        cin >> src >> dest;
        graph[src].push_back(dest);
        graph[dest].push_back(src);
    }

    vector<vector<int>> bcc = findBiconnectedComponents(graph);

    cout << "Biconnected components:" << endl;
    for (const vector<int>& component : bcc) {
        for (int v : component) {
            cout << v << " ";
        }
        cout << endl;
    }

    return 0;
}
