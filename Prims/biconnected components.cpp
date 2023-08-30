#include <iostream>
#include <vector>
#include <stack>
using namespace std;

void DFS(vector<vector<int>>& graph, int u, int parent, int& time, vector<int>& disc, vector<int>& low, stack<pair<int, int>>& st, vector<vector<int>>& bcc) {
    disc[u] = low[u] = ++time;
    int children = 0;

    for (int v : graph[u]) {
        if (v == parent)
            continue;

        if (disc[v] == -1) {
            children++;
            st.push({u, v});
            DFS(graph, v, u, time, disc, low, st, bcc);

            low[u] = min(low[u], low[v]);

            if ((parent == -1 && children > 1) || (parent != -1 && low[v] >= disc[u])) {
                vector<int> component;
                while (!st.empty() && st.top() != make_pair(u, v)) {
                    component.push_back(st.top().first);
                    component.push_back(st.top().second);
                    st.pop();
                }
                component.push_back(st.top().first);
                component.push_back(st.top().second);
                st.pop();
                bcc.push_back(component);
            }
        } else if (disc[v] < disc[u]) {
            low[u] = min(low[u], disc[v]);
            st.push({u, v});
        }
    }
}

vector<vector<int>> findBiconnectedComponents(vector<vector<int>>& graph) {
    int V = graph.size();
    vector<int> disc(V, -1);
    vector<int> low(V, -1);
    stack<pair<int, int>> st;
    vector<vector<int>> bcc;
    int time = 0;

    for (int i = 0; i < V; i++) {
        if (disc[i] == -1) {
            DFS(graph, i, -1, time, disc, low, st, bcc);
        }
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

    cout << "Biconnected Components:" << endl;
    for (const auto& component : bcc) {
        for (int v : component) {
            cout << v << " ";
        }
        cout << endl;
    }

    return 0;
}
