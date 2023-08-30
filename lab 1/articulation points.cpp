#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void findArticulationPoints(vector<vector<int>>& adjList) {
    int numVertices = adjList.size();
    vector<int> disc(numVertices, -1);
    vector<int> low(numVertices, -1);
    vector<int> parent(numVertices, -1);
    vector<bool> visited(numVertices, false);
    vector<bool> isArticulationPoint(numVertices, false);

    int time = 0;
    
    for (int vertex = 0; vertex < numVertices; vertex++) {
        if (!visited[vertex]) {
            int rootChildren = 0;
            DFS(vertex, adjList, disc, low, parent, visited, isArticulationPoint, rootChildren, time);
            
            // Check if the root node is an articulation point
            if (rootChildren > 1)
                isArticulationPoint[vertex] = true;
        }
    }

    cout << "Articulation Points: ";
    for (int vertex = 0; vertex < numVertices; vertex++) {
        if (isArticulationPoint[vertex])
            cout << vertex << " ";
    }
    cout << endl;
}

void DFS(int vertex, vector<vector<int>>& adjList, vector<int>& disc, vector<int>& low, vector<int>& parent, vector<bool>& visited, vector<bool>& isArticulationPoint, int& rootChildren, int& time) {
    visited[vertex] = true;
    disc[vertex] = low[vertex] = time++;
    int childCount = 0;

    for (int neighbor : adjList[vertex]) {
        if (!visited[neighbor]) {
            childCount++;
            parent[neighbor] = vertex;
            DFS(neighbor, adjList, disc, low, parent, visited, isArticulationPoint, rootChildren, time);

            low[vertex] = min(low[vertex], low[neighbor]);

            if (parent[vertex] == -1 && childCount > 1)
                rootChildren++;

            if (parent[vertex] != -1 && low[neighbor] >= disc[vertex])
                isArticulationPoint[vertex] = true;
        } else if (neighbor != parent[vertex]) {
            low[vertex] = min(low[vertex], disc[neighbor]);
        }
    }
}

int main() {
    int numVertices, numEdges;

    cout << "Enter the number of vertices: ";
    cin >> numVertices;

    if (numVertices <= 0) {
        cout << "Invalid number of vertices. Exiting..." << endl;
        return 0;
    }

    cout << "Enter the number of edges: ";
    cin >> numEdges;

    if (numEdges < 0) {
        cout << "Invalid number of edges. Exiting..." << endl;
        return 0;
    }

    vector<vector<int>> adjacencyList(numVertices);
    cout << "Enter the edges (source and destination):" << endl;
    for (int i = 0; i < numEdges; i++) {
        int src, dest;
        cin >> src >> dest;

        if (src < 0 || src >= numVertices || dest < 0 || dest >= numVertices) {
            cout << "Invalid edge. Exiting..." << endl;
            return 0;
        }

        adjacencyList[src].push_back(dest);
        adjacencyList[dest].push_back(src);
    }

    findArticulationPoints(adjacencyList);

    return 0;
}
