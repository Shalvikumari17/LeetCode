class Solution {
public:
    long long countMajoritySubarrays(vector<int>& nums, int target) {
        int n = nums.size();

        vector<int> pref(n + 1, 0);
        for (int i = 0; i < n; i++) {
            pref[i + 1] = pref[i] + (nums[i] == target ? 1 : -1);
        }

        vector<int> vals = pref;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        int m = vals.size();
        vector<int> bit(m + 2, 0);

        auto upd = [&](int idx) {
            while (idx <= m) {
                bit[idx]++;
                idx += idx & -idx;
            }
        };

        auto qry = [&](int idx) {
            int s = 0;
            while (idx > 0) {
                s += bit[idx];
                idx -= idx & -idx;
            }
            return s;
        };

        long long ans = 0;

        for (int x : pref) {
            int id = lower_bound(vals.begin(), vals.end(), x) - vals.begin() + 1;
            ans += qry(id - 1);
            upd(id);
        }

        return ans;
    }
};