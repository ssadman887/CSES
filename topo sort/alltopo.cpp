#include<bits/stdc++.h>
using namespace std;

void allTopologicalSorts(vector<int> adj[], vector<int>& indegree, vector<bool>& visited, vector<int>& result, int V) {
    bool flag = false;
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0 && !visited[i]) {
            for (int j : adj[i])
                indegree[j]--;
            result.push_back(i);
            visited[i] = true;
            allTopologicalSorts(adj, indegree, visited, result, V);
            visited[i] = false;
            result.erase(result.end() - 1);
            for (int j : adj[i])
                indegree[j]++;
            flag = true;
        }
    }
    if (!flag) {
        for (int i : result)
            cout << i << " ";
        cout << endl;
    }
}

int main() {
    int V, E;
    cin >> V >> E;
    vector<int> adj[V];
    for(int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    vector<int> indegree(V, 0);
    for (int i = 0; i < V; i++)
        for (int j : adj[i])
            indegree[j]++;
    vector<int> result;
    vector<bool> visited(V, false);
    allTopologicalSorts(adj, indegree, visited, result, V);
    return 0;
}
