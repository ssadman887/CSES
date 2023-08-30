#include <iostream>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    // Create an adjacency matrix of size n x n
    int adj[n][n] = {0};

    // Take m edges as input from the user and add them to the matrix
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u-1][v-1] = 1;
        adj[v-1][u-1] = 1;
    }

    // Output the adjacency matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << adj[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
