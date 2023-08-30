#include<bits/stdc++.h>
using namespace std;


void dfs(int node,vector<vector<int>> &graph ,vector<bool> &visited){
    visited[node] =true;
    cout<<node<<" ";

    for(int neighbour: graph[node]){
        if(!visited[neighbour]){
            //            cout << "dfs called on "<< neighbours <<" from "<< node << endl ;
            dfs(neighbour,graph,visited);
        }
    }

}
int main()
{
    int v,e;
    cin >> v;
    cin>> e;

    vector<vector<int>> graph(v);
    vector<bool> visited(v,false);


    for (int i = 0; i < e; i++)
    {   
        int x,y;
        cin>> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);


    }

    int src;
    cin>> src;
    dfs(src,graph,visited);
    
    return 0;
}