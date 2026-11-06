class Solution {
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        sort(logs.begin(), logs.end(), [](auto &a, auto &b) {
            return a[1] < b[1];
        });

        int m = queries.size();
        vector<pair<int,int>> q;

        for (int i = 0; i < m; i++)
            q.push_back({queries[i], i});

        sort(q.begin(), q.end());

        vector<int> ans(m);
        unordered_map<int, int> mp;

        int left = 0, right = 0, active = 0;

        for (auto [time, idx] : q) {
            while (right < logs.size() && logs[right][1] <= time) {
                int id = logs[right][0];

                if (mp[id]++ == 0)
                    active++;

                right++;
            }

            while (left < right && logs[left][1] < time - x) {
                int id = logs[left][0];

                if (--mp[id] == 0)
                    active--;

                left++;
            }

            ans[idx] = n - active;
        }

        return ans;
    }
};