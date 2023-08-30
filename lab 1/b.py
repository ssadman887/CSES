def findValidTopologicalOrders(N, M, edges):
    # Step 1: Parse input to retrieve number of nodes, edges, and edge connections
    graph = {i: [] for i in range(N)}  # Step 2: Create adjacency list representation of the graph
    inDegree = [0] * N  # Step 3: Initialize in-degree list
    for u, v in edges:
        graph[u].append(v)
        inDegree[v] += 1
    
    visited = [False] * N  # Step 4: Initialize visited list
    dp = [0] * N  # Step 5: Initialize dp list

    # Step 6: DFS traversal
    def dfs(node):
        visited[node] = True
        count = 1
        for neighbor in graph[node]:
            inDegree[neighbor] -= 1
            if inDegree[neighbor] == 0 and not visited[neighbor]:
                count += dfs(neighbor)
        dp[node] = count
        return count

    # Perform DFS on each node with an in-degree of 0
    total_count = 0
    for node in range(N):
        if inDegree[node] == 0:
            total_count += dfs(node)

    return total_count  # Step 7: Return the total count

# Example usage:
N, M = map(int, input().split())
edges = [list(map(int, input().split())) for _ in range(M)]
result = findValidTopologicalOrders(N, M, edges)
print(result)
