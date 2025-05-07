#include<iostream>
#include<unordered_map>
#include<queue>
#include<vector>

using namespace std;

class Graph {
    
    unordered_map<int, vector<int>> adjList;
    
    public:
    void addnode(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    vector<int> bfs(int src, int n) {
        queue<int> q;
        vector<int> ans;
        vector<int> vis(n+1, 0);
        q.push(src);
        vis[src] = 1;

        while(!q.empty()) {
            auto front = q.front();
            q.pop();
            ans.push_back(front);

            for(auto nbr : adjList[front])
            {
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
        ans.push_back(src);
        vis[src] = 1;
        for(auto nbr : adjList[src]) {
            if(vis[nbr] == 0) {
                dfs(nbr, vis, ans);
            }
        }
    }
};

int main() {
    Graph g;
    // Graph structure:
    //      0
    //     / \
    //    1   2
    //   / \
    //  3   4
    int n = 5;

    g.addnode(0, 1);
    g.addnode(0, 2);
    g.addnode(1, 3);
    g.addnode(1, 4);

    vector<int> bfs = g.bfs(0, n);
    for(auto i : bfs)
        cout<<i<<" ";
    cout<<endl;

    vector<int>vis(n+1, 0);
    vector<int>dfs;
    
    g.dfs(0, vis, dfs);
    for(auto i : dfs)
        cout<<i<<" ";

    return 0;
}