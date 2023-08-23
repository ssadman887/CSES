#include <bits/stdc++.h>
using namespace std;

int findMinDistance(vector<int> distance, vector<bool> visitedSet) {
    int minValue = INT_MAX, minIndex;

    for (int v = 0; v < distance.size(); v++)
        if (visitedSet[v] == false && distance[v] <= minValue)
            minValue = distance[v], minIndex = v;

    return minIndex;
}

void displaySolution(vector<int> distance) {
    cout << "Vertex \t\t Distance from Source\n";
    for (int i = 0; i < distance.size(); i++)
        cout << i << "\t\t" << distance[i] << "\n";
}

void dijkstraAlgorithm(vector<vector<int>> adjacencyMatrix, int source) {
    vector<int> distance(adjacencyMatrix.size());

    vector<bool> visitedSet(adjacencyMatrix.size());

    for (int i = 0; i < adjacencyMatrix.size(); i++)
        distance[i] = INT_MAX, visitedSet[i] = false;

    distance[source] = 0;

    for (int count = 0; count < adjacencyMatrix.size() - 1; count++) {
        int u = findMinDistance(distance, visitedSet);

        visitedSet[u] = true;

        for (int v = 0; v < adjacencyMatrix.size(); v++)
            if (!visitedSet[v] && adjacencyMatrix[u][v] && distance[u] != INT_MAX
                && distance[u] + adjacencyMatrix[u][v] < distance[v])
                distance[v] = distance[u] + adjacencyMatrix[u][v];
    }

    displaySolution(distance);
}

int main() {
    int totalVertices;
    cin >> totalVertices;

    vector<vector<int>> adjacencyMatrix(totalVertices, vector<int>(totalVertices));

    cout << "Enter the adjacency matrix:\n";
    for(int i=0; i<totalVertices; i++) {
        for(int j=0; j<totalVertices; j++) {
            cin >> adjacencyMatrix[i][j];
        }
    }

    dijkstraAlgorithm(adjacencyMatrix, 0);

    return 0;
}
