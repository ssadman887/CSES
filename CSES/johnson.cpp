#include <bits/stdc++.h>

using namespace std; 

// Structure to represent a edge between two vertices
struct Edge {
  int src, dest, weight;
};

// Structure to represent a connected, directed and weighted graph
struct Graph {
  // V-> Number of vertices, E-> Number of edges
  int V, E;

  // graph is represented as an array of edges.
  struct Edge* edge; 
};

// Function to find the vertex with minimum distance from the source
int minDistance(int dist[], bool sptSet[]) {
  int min = INT_MAX, min_index;

  for(int i = 0; i < V; i++) {
    if(sptSet[i] == false && dist[i] <= min) {
      min = dist[i], min_index = i; 
    }
  }

  return min_index;
}

// Function to dijkstra's shortest path algorithm for a graph 
// represented using adjacency matrix representation
void dijkstra(int graph[V][V], int src) {
  
  int dist[V]; // dist values used to pick minimum weight edge in cut

  // sptSet[i] will true if vertex i is included / in shortest
  // path tree or shortest distance from src to i is finalized
  bool sptSet[V]; 
  
  // Initialize all distances as INFINITE and stpSet[] as false
  for (int i = 0; i < V; i++)
    dist[i] = INT_MAX, sptSet[i] = false;

  // Distance of source vertex from itself is always 0    
  dist[src] = 0;

  // Find shortest path for all vertices
  for (int count = 0; count < V-1; count++) {
    // Pick the minimum distance vertex from the set of vertices not yet processed. 
    // u is always equal to src in first iteration.
    int u = minDistance(dist, sptSet);

    // Mark the picked vertex as processed
    sptSet[u] = true;

    // Update dist value of the adjacent vertices of the picked vertex.
    for (int v = 0; v < V; v++)

      // Update dist[v] only if is not in sptSet, there is an edge from 
      // u to v, and total weight of path from src to  v through u is  
      // smaller than current value of dist[v]
      if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX 
        && dist[u]+graph[u][v] < dist[v])
        dist[v] = dist[u] + graph[u][v];
  }
}

// Function to run Johnson's algorithm
void JohnsonAlgorithm(Graph* graph) {

  /* Step 1: Add a dummy vertex to the graph with index V. 
   * Initialize its incoming edge weights from all other vertices as 0.
   * Initialize its outgoing edge weights to all other vertices as initial 
   * weight in graph.
   */

  graph->V++; // increment vertex count
  graph->E += graph->V - 1; // increment edge count

  // Initialize new edges
  for(int i = 0; i < graph->V-1; i++) {
    graph->edge[graph->E].src = graph->V-1; 
    graph->edge[graph->E].dest = i;
    graph->edge[graph->E].weight = 0;
    graph->E++;
  }

  for(int i = 0; i < graph->E-graph->V+1; i++) {
    graph->edge[i].weight = graph->edge[i].weight; //copy old weight
  }

  // Step 2: Run Dijkstra's on modified graph starting from newly added vertex V 
  // Compute shortest path distances and store them in array dist[]
  
  int dist[graph->V]; 
  dijkstra(graph, graph->V-1);

  // Step 3: Use computed distances to reweight the edges
  for(int i = 0; i < graph->E; i++) {
    int u = graph->edge[i].src;
    int v = graph->edge[i].dest;
    graph->edge[i].weight = graph->edge[i].weight + dist[u] - dist[v]; 
  }

  // Step 4: Remove the added vertex from the graph
  graph->V--;
  graph->E -= graph->V; // reset edge count

  // Step 5: Run Dijkstra's algorithm for every vertex as source vertex and
  // compute shortest distances.
  
  for(int i = 0; i < graph->V; i++) {
    dijkstra(graph, i);

    // Print distances
    for(int j = 0; j < graph->V; j++) {
      if(i != j) {
        cout << "Shortest distance from " << i << " to " << j << " is " << dist[j] << endl; 
      }
    }
  }
}


// Johnson(Graph G):
//   add new vertex s to G
//   for each vertex u in V(G) 
//     add edge (s, u) with weight 0
    
//   dist[] = Dijkstra(G, s) // run Dijkstra's from s
  
//   for each edge (u, v) in E(G)
//     w'(u, v) = w(u, v) + dist[u] - dist[v] // reweight edge
    
//   remove vertex s from G
  
//   for each vertex u in V(G)
//     shortestPaths[] = Dijkstra(G, u) // run Dijkstra's 
//     print shortestPaths[] // print shortest path distances

// Dijkstra(Graph G, source s):
//   dist[v] = infinity for all v in V(G)
//   dist[s] = 0
  
//   S = empty set
  
//   while S != V(G):
//     u = vertex in V(G) - S with min dist[u]  
//     add u to S
//     for each neighbor v of u:
//       if dist[v] > dist[u] + w(u, v):
//         dist[v] = dist[u] + w(u, v)
        
//   return dist[]