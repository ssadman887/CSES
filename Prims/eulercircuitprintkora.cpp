#include<iostream>
#include <vector>
using namespace std;

// Function to add an edge to the graph
void addEdge(vector<vector<int>>& adj, int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);  // Note: the graph is undirected
}

// Function to do DFS starting from v. Used in isConnected();
void DFSUtil(vector<vector<int>>& adj, int v, vector<bool>& visited)
{
    // Mark the current node as visited
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    for (int i : adj[v])
    {
        if (!visited[i])
        {
            DFSUtil(adj, i, visited);
        }
    }
}

// Method to check if all non-zero degree vertices are connected
bool isConnected(vector<vector<int>>& adj, int V)
{
    // Mark all the vertices as not visited
    vector<bool> visited(V, false);

    // Find a vertex with non-zero degree
    int i;
    for (i = 0; i < V; i++)
    {
        if (!adj[i].empty())
        {
            break;
        }
    }

    // If there are no edges in the graph, return true
    if (i == V)
    {
        return true;
    }

    // Start DFS traversal from a vertex with non-zero degree
    DFSUtil(adj, i, visited);

    // Check if all non-zero degree vertices are visited
    for (i = 0; i < V; i++)
    {
        if (!visited[i] && !adj[i].empty())
        {
            return false;
        }
    }

    return true;
}

// Function to check if a given graph is Eulerian or not
int isEulerian(vector<vector<int>>& adj, int V)
{
    // Check if all non-zero degree vertices are connected
    if (!isConnected(adj, V))
    {
        return 0;
    }

    // Count vertices with odd degree
    int odd = 0;
    for (int i = 0; i < V; i++)
    {
        if (adj[i].size() % 2 != 0)
        {
            odd++;
        }
    }

    // If count is more than 2, then graph is not Eulerian
    if (odd > 2)
    {
        return 0;
    }

    // If odd count is 2, then semi-eulerian.
    // If odd count is 0, then eulerian
    // Note that odd count can never be 1 for an undirected graph
    return odd ? 1 : 2;
}

// Function to print Euler circuit
void printEulerCircuit(vector<vector<int>>& adj, int V)
{
    // Create a copy of the adjacency list
    vector<vector<int>> adjCopy = adj;

    // Initialize the stack and the circuit
    vector<int> circuit;
    vector<int> stack;

    // Start from vertex 0
    int currVertex = 0;

    while (!stack.empty() || adjCopy[currVertex].size() > 0)
    {
        // If current vertex has no adjacent vertices
        if (adjCopy[currVertex].empty())
        {
            // Add it to the circuit
            circuit.push_back(currVertex);

            // Remove the last vertex from the stack and set it as the current vertex
            currVertex = stack.back();
            stack.pop_back();
        }
        else
        {
            // Add the current vertex to the stack
            stack.push_back(currVertex);

            // Take any adjacent vertex
            int nextVertex = adjCopy[currVertex].back();

            // Remove the edge between current vertex and next vertex
            adjCopy[currVertex].pop_back();
            for (int i = 0; i < adjCopy[nextVertex].size(); i++)
            {
                if (adjCopy[nextVertex][i] == currVertex)
                {
                    adjCopy[nextVertex].erase(adjCopy[nextVertex].begin() + i);
                    break;
                }
            }

            // Set the next vertex as the current vertex
            currVertex = nextVertex;
        }
    }

    // Print the Euler circuit
    for (int i = circuit.size() - 1; i >= 0; i--)
    {
        cout << circuit[i];
        if (i != 0)
        {
            cout << " -> ";
        }
    }
    cout << endl;
}

// Driver program to test above functions
int main()
{
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    // Create adjacency list for the graph
    vector<vector<int>> adj(V);

    // Add edges to the graph
    cout << "Enter the edges (u v):" << endl;
    for (int i = 0; i < E; i++)
    {
        int u, v;
        cin >> u >> v;
        addEdge(adj, u, v);
    }

    // Check if the graph is Eulerian
    int result = isEulerian(adj, V);

    // Print the result
    if (result == 0)
    {
        cout << "The graph is not Eulerian" << endl;
    }
    else if (result == 1)
    {
        cout << "The graph has an Euler path" << endl;
    }
    else
    {
        cout << "The graph has an Euler circuit" << endl;
        cout << "Euler circuit: ";
        printEulerCircuit(adj, V);
    }

    return 0;
}
