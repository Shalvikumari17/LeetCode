class Solution {
    public int[] gcdValues(int[] nums, long[] queries) {
        int max = 0;
        for (int x : nums) max = Math.max(max, x);

        int[] freq = new int[max + 1];
        for (int x : nums) freq[x]++;

        long[] exact = new long[max + 1];

        // Count pairs divisible by each g
        for (int g = 1; g <= max; g++) {
            long cnt = 0;
            for (int j = g; j <= max; j += g)
                cnt += freq[j];
            exact[g] = cnt * (cnt - 1) / 2;
        }

        // Inclusion-Exclusion
        for (int g = max; g >= 1; g--) {
            for (int j = g + g; j <= max; j += g)
                exact[g] -= exact[j];
        }

        // Prefix counts
        long[] pref = new long[max + 1];
        for (int g = 1; g <= max; g++)
            pref[g] = pref[g - 1] + exact[g];

        int[] ans = new int[queries.length];

        for (int i = 0; i < queries.length; i++) {
            long q = queries[i];

            int l = 1, r = max;
            while (l < r) {
                int mid = (l + r) >>> 1;
                if (pref[mid] > q)
                    r = mid;
                else
                    l = mid + 1;
            }
            ans[i] = l;
        }

        return ans;
    }
}