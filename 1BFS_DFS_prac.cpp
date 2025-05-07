#include<iostream>
#include<vector>
#include<queue>
#include<unordered_map>
using namespace std;

class Graph {
public:
    unordered_map<int, vector<int>> adj;

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> bfs(int src, int n) {
        queue<int> q;
        vector<int> vis(n+1, 0);
        vector<int> ans;

        vis[src] = 1;
        q.push(src);

        while(!q.empty()) {
            int node = q.front();
            q.pop();

            ans.push_back(node);

            for(auto nbr : adj[node]) {
                if(vis[nbr] == 0)
                {
                    vis[nbr] = 1;
                    q.push(nbr);
                }
            }
        }
        return ans;
    }

    void dfs(int src, vector<int> &vis, vector<int> &ans) {
        vis[src] = 1;
        ans.push_back(src);

        for(auto nbr : adj[src]) {
            if(vis[nbr] == 0) {
                dfs(nbr, vis, ans);
            }
        }
    }

};

int main() {
    Graph g;
    int n, m;
    cout << "Enter number of nodes and edges: ";
    cin >> n >> m;

    cout << "Enter " << m << " edges (u v):\n";
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    cout << "BFS Traversal: ";
    vector<int> bfs_result = g.bfs(0, n);
    for (int node : bfs_result)  
        cout << node << " ";
    cout << endl;

    vector<int> vis(n + 1, 0);
    vector<int> dfs;
    g.dfs(0, vis, dfs);

    cout << "DFS Traversal: ";
    for (int node : dfs) cout << node << " ";
    cout << endl;

    return 0;
}
