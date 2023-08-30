#include <bits/stdc++.h>
#define INF 99999
using namespace std;

// Function to find the vertex with minimum distance
int minDistance(int dist[], bool sptSet[], int vertices) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < vertices; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// Function to print the solution
void printSolution(int **dist, int vertices) {
    //printf("Following matrix shows the shortest distances between every pair of vertices \n");
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            if (dist[i][j] == INF)
                printf("%s", "INF");
            else
                printf("%7d", dist[i][j]);
        }
        printf("\n");
    }
}

// Function to implement Floyd-Warshall
void floydWarshall(int **graph, int vertices) {
    int **dist = new int*[vertices];
    for(int i=0; i<vertices; i++)
        dist[i] = new int[vertices];

    for (int i = 0; i < vertices; i++)
        for (int j = 0; j < vertices; j++)
            dist[i][j] = graph[i][j];

    for (int k = 0; k < vertices; k++) {
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    // Print the shortest distance matrix
    printSolution(dist, vertices);

    // Deallocate memory
    for(int i=0; i<vertices; i++)
        delete [] dist[i];
    delete [] dist;
}

int main() {
    int vertices;
    //cout << "Enter the number of vertices: ";
    cin >> vertices;

    int **graph = new int*[vertices];
    for(int i=0; i<vertices; i++)
        graph[i] = new int[vertices];

    for(int i = 0; i < vertices; i++){
        for(int j = 0; j<vertices; j++){
            //cout << "Distance from vertex "<< i <<" to " << j << ": ";
            cin >> graph[i][j];
        }
    }

    // Call the algorithm
    floydWarshall(graph, vertices);

    // Deallocate memory
    for(int i=0; i<vertices; i++)
        delete [] graph[i];
    delete [] graph;

    return 0;
}
