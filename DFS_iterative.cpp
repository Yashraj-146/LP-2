#include<iostream>
#include<queue>
#include<unordered_map>
#include<vector>
#include<stack>
using namespace std;

class Graph {
public:
    unordered_map<int, vector<int>> adj;

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Recursive BFS Helper
    void bfsRecursive(queue<int>& q, vector<int>& visited, vector<int>& ans) {
        if (q.empty()) return;

        int node = q.front();
        q.pop();
        ans.push_back(node);

        for (auto& nbr : adj[node]) {
            if (visited[nbr] == 0) {
                visited[nbr] = 1;
                q.push(nbr);
            }
        }

        bfsRecursive(q, visited, ans); // recursive call
    }

    // Wrapper for recursive BFS
    vector<int> bfs(int src, int n) {
        vector<int> visited(n + 1, 0);
        vector<int> ans;
        queue<int> q;

        visited[src] = 1;
        q.push(src);

        bfsRecursive(q, visited, ans);
        return ans;
    }

    // Iterative DFS using stack
    vector<int> dfs(int src, int n) {
        vector<int> visited(n + 1, 0);
        vector<int> ans;
        stack<int> st;

        st.push(src);

        while (!st.empty()) {
            int node = st.top();
            st.pop();

            if (!visited[node]) {
                visited[node] = 1;
                ans.push_back(node);

                // Push neighbors in reverse order for correct DFS order
                for (auto it = adj[node].rbegin(); it != adj[node].rend(); ++it) {
                    if (!visited[*it]) {
                        st.push(*it);
                    }
                }
            }
        }

        return ans;
    }
};

int main() {
    Graph g;
    int V, E;
    cout << "Enter the number of vertices & edges = ";
    cin >> V >> E;

    cout << "Enter the values of u and v to add edges: ";
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    vector<int> bfs_result = g.bfs(0, V);
    cout << "BFS (recursive): ";
    for (auto i : bfs_result) {
        cout << i << " ";
    }
    cout << endl;

    vector<int> dfs_result = g.dfs(0, V);
    cout << "DFS (iterative): ";
    for (auto i : dfs_result) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
