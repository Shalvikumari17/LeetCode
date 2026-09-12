class Solution {
public:
    struct Node {
        long long score = 0;
        vector<int> ids;
    };

    bool better(const Node& a, const Node& b) {
        if (a.score != b.score)
            return a.score > b.score;

        return a.ids < b.ids;
    }

    vector<int> maximumWeight(vector<vector<int>>& intervals) {
        int n = intervals.size();

        // {left, right, weight, original_index}
        vector<array<long long, 4>> a;

        for (int i = 0; i < n; i++) {
            a.push_back({
                intervals[i][0],
                intervals[i][1],
                intervals[i][2],
                i
            });
        }

        sort(a.begin(), a.end());

        // Find first interval whose left > current right
        vector<int> nxt(n);

        for (int i = 0; i < n; i++) {
            int lo = i + 1, hi = n;

            while (lo < hi) {
                int mid = lo + (hi - lo) / 2;

                if (a[mid][0] > a[i][1])
                    hi = mid;
                else
                    lo = mid + 1;
            }

            nxt[i] = lo;
        }

        // dp[k][i] = best answer using at most k intervals
        // from position i onward
        vector<vector<Node>> dp(5, vector<Node>(n + 1));

        for (int k = 1; k <= 4; k++) {

            for (int i = n - 1; i >= 0; i--) {

                // Option 1: don't take this interval
                Node skip = dp[k][i + 1];

                // Option 2: take this interval
                Node take = dp[k - 1][nxt[i]];

                take.score += a[i][2];  // weight

                take.ids.push_back((int)a[i][3]); // original index

                sort(take.ids.begin(), take.ids.end());

                if (better(take, skip))
                    dp[k][i] = take;
                else
                    dp[k][i] = skip;
            }
        }

        return dp[4][0].ids;
    }
};