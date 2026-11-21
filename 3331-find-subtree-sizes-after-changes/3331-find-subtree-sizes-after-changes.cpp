class Solution {
public:
    vector<int> findSubtreeSizes(vector<int>& parent, string s) {
        int n = parent.size();

        vector<vector<int>> adj(n);
        for (int i = 1; i < n; i++) {
            adj[parent[i]].push_back(i);
        }

        vector<int> newParent(n, -1);
        vector<int> last(26, -1);

        function<void(int)> dfs = [&](int u) {
            int c = s[u] - 'a';
            int old = last[c];

            if (old != -1)
                newParent[u] = old;
            else
                newParent[u] = parent[u];

            last[c] = u;

            for (int v : adj[u]) {
                dfs(v);
            }

            last[c] = old;
        };

        dfs(0);

        vector<vector<int>> tree(n);
        for (int i = 1; i < n; i++) {
            tree[newParent[i]].push_back(i);
        }

        vector<int> ans(n, 0);

        function<int(int)> calc = [&](int u) {
            ans[u] = 1;

            for (int v : tree[u]) {
                ans[u] += calc(v);
            }

            return ans[u];
        };

        calc(0);

        return ans;
    }
};