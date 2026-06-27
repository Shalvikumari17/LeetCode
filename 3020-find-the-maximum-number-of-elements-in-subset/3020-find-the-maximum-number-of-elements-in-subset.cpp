class Solution {
public:
    int maximumLength(vector<int>& nums) {
        unordered_map<long long, int> cnt;
        for (int x : nums) cnt[x]++;

        int ans = 1;

        // Special handling for 1
        if (cnt.count(1)) {
            ans = max(ans, cnt[1] % 2 ? cnt[1] : cnt[1] - 1);
        }

        for (auto &[x, f] : cnt) {
            if (x == 1) continue;

            long long cur = x;
            int len = 0;

            while (cnt.count(cur) && cnt[cur] >= 2) {
                len += 2;
                if (cur > 1000000000LL / cur) break;
                cur *= cur;
            }

            if (cnt.count(cur) && cnt[cur] == 1)
                len++;
            else
                len--;

            ans = max(ans, max(1, len));
        }

        return ans;
    }
};