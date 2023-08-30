#include <iostream>
#include <vector>

using namespace std;

int countValidTopologicalOrders(vector<vector<int>>& customGraph, vector<int>& customIndegree, vector<bool>& customVisited) {
    int customCount = 0;
    //int doublecount=  0;

    bool customFlag = false;

    for (int i = 0; i < customGraph.size(); i++) {
        if (!customVisited[i] && customIndegree[i] == 0) {
            customVisited[i] = true;
            for (int j : customGraph[i]) {
                customIndegree[j]--;
            }
            customCount += countValidTopologicalOrders(customGraph, customIndegree, customVisited);
            customVisited[i] = false;
            for (int j : customGraph[i]) {
                customIndegree[j]++;
            }
            customFlag = true;
        }
    }

    if (!customFlag) {
        return 1;
    }

    return customCount;
}

int findNumValidTopologicalOrders(int n, int m, const vector<pair<int, int>>& customEdges) {
    vector<vector<int>> customGraph(n);
    vector<int> customIndegree(n, 0);
    vector<bool> customVisited(n, false);

    for (const auto& edge : customEdges) {
        int u = edge.first;
        int v = edge.second;
        customGraph[u].push_back(v);
        customIndegree[v]++;
    }

    return countValidTopologicalOrders(customGraph, customIndegree, customVisited);
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<pair<int, int>> customEdges(m);
    for (int i = 0; i < m; i++) {
        cin >> customEdges[i].first >> customEdges[i].second;
    }

    int numValidTopologicalOrders = findNumValidTopologicalOrders(n, m, customEdges);
    cout << numValidTopologicalOrders << endl;

    return 0;
}