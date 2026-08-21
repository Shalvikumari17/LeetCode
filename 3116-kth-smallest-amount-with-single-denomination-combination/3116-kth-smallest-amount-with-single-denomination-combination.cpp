class Solution {
public:
    long long gcdll(long long a, long long b) {
        while (b) {
            long long temp = a % b;
            a = b;
            b = temp;
        }
        return a;
    }

    long long lcmll(long long a, long long b, long long limit) {
        long long g = gcdll(a, b);

        // Avoid overflow and values greater than limit
        if (a / g > limit / b)
            return limit + 1;

        return a / g * b;
    }

    long long countNumbers(long long x, vector<int>& coins) {
        int n = coins.size();
        long long ans = 0;

        int totalMasks = 1 << n;

        for (int mask = 1; mask < totalMasks; mask++) {

            long long lcm = 1;
            int bits = 0;
            bool tooLarge = false;

            for (int i = 0; i < n; i++) {

                if (mask & (1 << i)) {
                    bits++;

                    lcm = lcmll(lcm, coins[i], x);

                    if (lcm > x) {
                        tooLarge = true;
                        break;
                    }
                }
            }

            if (tooLarge)
                continue;

            long long cnt = x / lcm;

            if (bits % 2 == 1)
                ans += cnt;
            else
                ans -= cnt;
        }

        return ans;
    }

    long long findKthSmallest(vector<int>& coins, int k) {

        long long low = 1;

        long long high = 1LL * (*min_element(coins.begin(), coins.end())) * k;

        while (low < high) {

            long long mid = low + (high - low) / 2;

            if (countNumbers(mid, coins) >= k) {
                high = mid;
            }
            else {
                low = mid + 1;
            }
        }

        return low;
    }
};