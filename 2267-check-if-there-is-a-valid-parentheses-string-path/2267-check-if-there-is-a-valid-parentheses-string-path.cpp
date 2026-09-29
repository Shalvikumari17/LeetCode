class Solution {
public:
    bool hasValidPath(vector<vector<char>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // Length of every path must be even
        if ((m + n - 1) % 2 != 0)
            return false;

        int maxBal = m + n;

        // dp[j][balance]
        vector<vector<bool>> dp(n, vector<bool>(maxBal, false));

        for (int i = 0; i < m; i++) {
            vector<vector<bool>> next(n, vector<bool>(maxBal, false));

            for (int j = 0; j < n; j++) {
                int val = (grid[i][j] == '(') ? 1 : -1;

                for (int bal = 0; bal < maxBal; bal++) {
                    int newBal = bal + val;

                    if (newBal < 0 || newBal >= maxBal)
                        continue;

                    if (i == 0 && j == 0) {
                        if (grid[i][j] == '(')
                            next[j][1] = true;
                    }
                    else {
                        if (i > 0 && dp[j][bal])
                            next[j][newBal] = true;

                        if (j > 0 && next[j - 1][bal])
                            next[j][newBal] = true;
                    }
                }
            }

            dp = next;
        }

        return dp[n - 1][0];
    }
};