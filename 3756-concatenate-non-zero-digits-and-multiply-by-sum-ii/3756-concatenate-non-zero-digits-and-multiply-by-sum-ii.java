import java.util.*;

class Solution {
    static final int MOD = 1_000_000_007;

    public int[] sumAndMultiply(String s, int[][] queries) {
        int n = s.length();

        ArrayList<Integer> pos = new ArrayList<>();
        ArrayList<Integer> dig = new ArrayList<>();

        // Store positions and values of non-zero digits
        for (int i = 0; i < n; i++) {
            int d = s.charAt(i) - '0';
            if (d != 0) {
                pos.add(i);
                dig.add(d);
            }
        }

        int m = pos.size();

        long[] pow10 = new long[m + 1];
        pow10[0] = 1;
        for (int i = 1; i <= m; i++) {
            pow10[i] = (pow10[i - 1] * 10) % MOD;
        }

        long[] prefVal = new long[m + 1];
        long[] prefSum = new long[m + 1];

        for (int i = 1; i <= m; i++) {
            prefVal[i] = (prefVal[i - 1] * 10 + dig.get(i - 1)) % MOD;
            prefSum[i] = prefSum[i - 1] + dig.get(i - 1);
        }

        int[] ans = new int[queries.length];

        for (int i = 0; i < queries.length; i++) {
            int l = queries[i][0];
            int r = queries[i][1];

            int left = lowerBound(pos, l);
            int right = upperBound(pos, r) - 1;

            if (left > right) {
                ans[i] = 0;
                continue;
            }

            int cnt = right - left + 1;

            long sum = prefSum[right + 1] - prefSum[left];

            long x = (prefVal[right + 1]
                    - (prefVal[left] * pow10[cnt]) % MOD + MOD) % MOD;

            ans[i] = (int) ((x * (sum % MOD)) % MOD);
        }

        return ans;
    }

    private int lowerBound(ArrayList<Integer> arr, int target) {
        int l = 0, r = arr.size();
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (arr.get(mid) >= target)
                r = mid;
            else
                l = mid + 1;
        }
        return l;
    }

    private int upperBound(ArrayList<Integer> arr, int target) {
        int l = 0, r = arr.size();
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (arr.get(mid) > target)
                r = mid;
            else
                l = mid + 1;
        }
        return l;
    }
}