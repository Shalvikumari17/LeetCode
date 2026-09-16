class Solution {
public:
    int numberOfSets(int n, int k) {
        const long long MOD = 1000000007;

        int N = n + k - 1;
        int R = 2 * k;

        long long ans = 1;

        // Calculate C(N, R)
        for (int i = 1; i <= R; i++) {
            ans = ans * (N - R + i) % MOD;

            // Modular inverse using Fermat's theorem
            long long x = MOD - 2;
            long long base = i;
            long long inv = 1;

            while (x) {
                if (x & 1)
                    inv = inv * base % MOD;
                base = base * base % MOD;
                x >>= 1;
            }

            ans = ans * inv % MOD;
        }

        return ans;
    }
};