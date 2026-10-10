class Solution {
public:
    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        long long k = 1LL * k1 + k2;
        vector<int> diff(nums1.size());
        int mx = 0;

        for (int i = 0; i < nums1.size(); i++) {
            diff[i] = abs(nums1[i] - nums2[i]);
            mx = max(mx, diff[i]);
        }

        if (k >= accumulate(diff.begin(), diff.end(), 0LL))
            return 0;

        int low = 0, high = mx;

        while (low < high) {
            int mid = low + (high - low) / 2;
            long long need = 0;

            for (int d : diff) {
                if (d > mid)
                    need += d - mid;
            }

            if (need <= k)
                high = mid;
            else
                low = mid + 1;
        }

        long long ans = 0, used = 0;

        for (int d : diff) {
            if (d > low) {
                ans += 1LL * low * low;
                used += d - low;
            } else {
                ans += 1LL * d * d;
            }
        }

        long long remaining = k - used;

        // Distribute remaining operations among differences equal to low.
        for (int d : diff) {
            if (remaining == 0) break;

            if (d >= low && low > 0) {
                ans -= 2LL * low - 1;
                remaining--;
            }
        }

        return ans;
    }
};