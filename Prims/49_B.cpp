#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

void findBiconnectedComponentsDFS(vector<vector<int>>& graph, int u, vector<int>& disc, vector<int>& low, vector<int>& parent, vector<bool>& visited, stack<pair<int, int>>& st, vector<vector<pair<int, int>>>& bcc) {
    static int time = 0;
    disc[u] = low[u] = time++;
    visited[u] = true;

    for (int v : graph[u]) {
        if (!visited[v]) {
            parent[v] = u;
            st.push({ min(u, v), max(u, v) });  // Ensure the first component is smaller
            findBiconnectedComponentsDFS(graph, v, disc, low, parent, visited, st, bcc);
            low[u] = min(low[u], low[v]);
            
            if (low[v] > disc[u]) {
                vector<pair<int, int>> component;
                while (st.top() != make_pair(min(u, v), max(u, v))) {
                    component.push_back(st.top());
                    st.pop();
                }
                component.push_back(st.top());
                st.pop();
                sort(component.begin(), component.end()); // Sort the edges within each component
                bcc.push_back(component);
            }
        } else if (v != parent[u] && disc[v] < disc[u]) {
            st.push({ min(u, v), max(u, v) });  // Ensure the first component is smaller
            low[u] = min(low[u], disc[v]);
        }
    }
}

vector<vector<pair<int, int>>> findBCC(vector<vector<int>>& graph) {
    int numberOfVertices = graph.size();
    vector<int> disc(numberOfVertices, -1);
    vector<int> low(numberOfVertices, -1);
    vector<int> parent(numberOfVertices, -1);
    vector<bool> visited(numberOfVertices, false);
    stack<pair<int, int>> st;
    vector<vector<pair<int, int>>> bcc;

    for (int u = 0; u < numberOfVertices; u++) {
        if (!visited[u]) {
            findBiconnectedComponentsDFS(graph, u, disc, low, parent, visited, st, bcc);
        }
    }

    return bcc;
}

bool comparator(const vector<pair<int, int>>& a, const vector<pair<int, int>>& b) {
    return a < b; // Compare the components directly
}

int main() {
    int numberOfVertices, numberOfEdges;

    cin >> numberOfVertices;
    cin >> numberOfEdges;

    vector<vector<int>> graph(numberOfVertices);

    for (int i = 0; i < numberOfEdges; i++) {
        int src, dest;
        cin >> src >> dest;
        graph[src].push_back(dest);
        graph[dest].push_back(src);
    }

    vector<vector<pair<int, int>>> bcc = findBCC(graph);

    sort(bcc.begin(), bcc.end(), comparator);

    for (const vector<pair<int, int>>& component : bcc) {
        for (const pair<int, int>& edge : component) {
            cout << edge.first << " - " << edge.second << "\n";
        }
        cout << "-\n";
    }

    return 0;
}
