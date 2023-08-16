#include <bits/stdc++.h>
using namespace std;

int minDistance(vector<int> dist, vector<bool> sptSet) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < dist.size(); v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void printSolution(vector<int> dist) {
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < dist.size(); i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

void dijkstra(vector<vector<int>> graph, int src) {
    vector<int> dist(graph.size());

    vector<bool> sptSet(graph.size());

    for (int i = 0; i < graph.size(); i++)
        dist[i] = INT_MAX, sptSet[i] = false;

    dist[src] = 0;

    for (int count = 0; count < graph.size() - 1; count++) {
        int u = minDistance(dist, sptSet);

        sptSet[u] = true;

        for (int v = 0; v < graph.size(); v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    printSolution(dist);
}

int main() {
    int vertices;
    cin >> vertices;

    vector<vector<int>> graph(vertices, vector<int>(vertices));

    printf("Enter the adjacency matrix:\n");
    for(int i=0; i<vertices; i++) {
        for(int j=0; j<vertices; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    dijkstra(graph, 0);

    return 0;
}
