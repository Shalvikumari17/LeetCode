class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums,
                                     int maxDiff,
                                     vector<vector<int>>& queries) {

        vector<pair<int,int>> arr;
        for(int i = 0; i < n; i++)
            arr.push_back({nums[i], i});

        sort(arr.begin(), arr.end());

        vector<int> pos(n), comp(n);

        int cid = 0;
        for(int i = 0; i < n; i++) {
            if(i && arr[i].first - arr[i - 1].first > maxDiff)
                cid++;

            comp[arr[i].second] = cid;
            pos[arr[i].second] = i;
        }

        vector<int> nxt(n);
        int r = 0;

        for(int l = 0; l < n; l++) {
            while(r + 1 < n &&
                  arr[r + 1].first <= arr[l].first + maxDiff)
                r++;

            nxt[l] = r;
        }

        int LOG = 18;

        vector<vector<int>> up(LOG, vector<int>(n));

        for(int i = 0; i < n; i++)
            up[0][i] = nxt[i];

        for(int k = 1; k < LOG; k++) {
            for(int i = 0; i < n; i++) {
                up[k][i] = up[k - 1][up[k - 1][i]];
            }
        }

        vector<int> ans;

        for(auto &q : queries) {
            int u = q[0];
            int v = q[1];

            if(u == v) {
                ans.push_back(0);
                continue;
            }

            if(comp[u] != comp[v]) {
                ans.push_back(-1);
                continue;
            }

            int a = pos[u];
            int b = pos[v];

            if(a > b) swap(a, b);

            int cur = a;
            int jumps = 0;

            for(int k = LOG - 1; k >= 0; k--) {
                if(up[k][cur] < b) {
                    cur = up[k][cur];
                    jumps += (1 << k);
                }
            }

            ans.push_back(jumps + 1);
        }

        return ans;
    }
};