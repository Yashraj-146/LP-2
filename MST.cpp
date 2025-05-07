#include<iostream>
#include<vector>
#include<queue>
using namespace std;

class Solution {
    typedef pair<int, int> P;
public:
    int spanningTree(int V, vector<vector<int>> adj[])
    {
        priority_queue<P, vector<P>, greater<P>> pq;
        pq.push({0, 0});
        int sum = 0;
        vector<bool> inMST(V, false);

        while(!pq.empty()) {
            auto current = pq.top();
            pq.pop();

            int weight = current.first;
            int node = current.second;

            if(inMST[node])
                continue;
            inMST[node] = true;
            sum += weight;

            for(auto tmp : adj[node]) {
                int neighbor = tmp[0];
                int neighbor_weight = tmp[1];

                if(!inMST[neighbor])
                    pq.push({neighbor_weight, neighbor});
            }
        }
        return sum;
    }
};

int main() {
    int V, E;
    cout<<"Enter number of vertices and edges: ";
    cin >> V >> E;

    vector<vector<int>> adj[V];
    cout<<"Enter values in order of u,v,w: ";
    for(int i = 0; i < E; i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v, w});
        adj[v].push_back({u, w}); //if undirected.
    }

    Solution obj;
    int res = obj.spanningTree(V, adj);
    cout<<"Sum of cost of edges is: "<<res<<endl;

    return 0;
}