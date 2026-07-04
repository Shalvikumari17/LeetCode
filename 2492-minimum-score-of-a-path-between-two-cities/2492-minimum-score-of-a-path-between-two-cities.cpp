class Solution {
public:
    int ans = INT_MAX;

    void dfs(int node, vector<vector<pair<int,int>>>& adj, vector<int>& vis) {
        vis[node] = 1;

        for (auto &it : adj[node]) {
            int nxt = it.first;
            int wt = it.second;

            ans = min(ans, wt);

            if (!vis[nxt])
                dfs(nxt, adj, vis);
        }
    }

    int minScore(int n, vector<vector<int>>& roads) {
        vector<vector<pair<int,int>>> adj(n + 1);

        for (auto &r : roads) {
            adj[r[0]].push_back({r[1], r[2]});
            adj[r[1]].push_back({r[0], r[2]});
        }

        vector<int> vis(n + 1, 0);
        dfs(1, adj, vis);

        return ans;
    }
};