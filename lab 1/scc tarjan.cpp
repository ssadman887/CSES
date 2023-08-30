#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

void tarjanDFS(int u, vector<int>& disc, vector<int>& low, stack<int>& st, vector<bool>& inStack, const vector<vector<int>>& graph) {
    static int time = 0;
    disc[u] = low[u] = time++;
    st.push(u);
    inStack[u] = true;

    for (int v : graph[u]) {
        if (disc[v] == -1) {
            tarjanDFS(v, disc, low, st, inStack, graph);
            low[u] = min(low[u], low[v]);
        } else if (inStack[v]) {
            low[u] = min(low[u], disc[v]);
        }
    }

    if (low[u] == disc[u]) {
        while (st.top() != u) {
            cout << st.top() << " ";
            inStack[st.top()] = false;
            st.pop();
        }
        cout << st.top() << "\n";
        inStack[st.top()] = false;
        st.pop();
    }
}

void findSCCs(const vector<vector<int>>& graph) {
    int V = graph.size();
    vector<int> disc(V, -1);
    vector<int> low(V, -1);
    vector<bool> inStack(V, false);
    stack<int> st;

    for (int u = 0; u < V; u++) {
        if (disc[u] == -1) {
            tarjanDFS(u, disc, low, st, inStack, graph);
        }
    }
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
    }

    cout << "Strongly Connected Components in the graph:" << endl;
    findSCCs(graph);

    return 0;
}
