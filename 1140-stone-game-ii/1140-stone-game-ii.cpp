class Solution {
public:
    int n;
    vector<int> suffix;
    vector<vector<int>> dp;

    int solve(int i, int M) {
        // All piles are taken
        if (i >= n)
            return 0;

        // If we can take all remaining piles
        if (2 * M >= n - i)
            return suffix[i];

        // Already calculated
        if (dp[i][M] != -1)
            return dp[i][M];

        int ans = 0;

        // Try taking X piles
        for (int X = 1; X <= 2 * M && i + X <= n; X++) {

            // Stones taken now
            int taken = suffix[i] - suffix[i + X];

            // Opponent's best score
            int opponent = solve(i + X, max(M, X));

            // Total stones current player can finally get
            int current = taken + (suffix[i + X] - opponent);

            ans = max(ans, current);
        }

        return dp[i][M] = ans;
    }

    int stoneGameII(vector<int>& piles) {
        n = piles.size();

        // suffix[i] = sum of piles[i ... n-1]
        suffix.assign(n + 1, 0);

        for (int i = n - 1; i >= 0; i--) {
            suffix[i] = suffix[i + 1] + piles[i];
        }

        dp.assign(n, vector<int>(n + 1, -1));

        return solve(0, 1);
    }
};