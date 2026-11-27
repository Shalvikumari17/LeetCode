
import java.util.*;

class Solution {
    public int maximumSaleItems(int[][] items, int budget) {
        int n = items.length;

        int[] benefit = new int[n];

        // Calculate free items for each item type
        for (int i = 0; i < n; i++) {
            benefit[i] = 1;

            for (int j = 0; j < n; j++) {
                if (i != j && items[j][0] % items[i][0] == 0) {
                    benefit[i]++;
                }
            }
        }

        // Sort items by price in descending order
        Integer[] order = new Integer[n];

        for (int i = 0; i < n; i++) {
            order[i] = i;
        }

        Arrays.sort(order, (a, b) ->
            Integer.compare(items[b][1], items[a][1])
        );

        int[] dp = new int[budget + 1];
        Arrays.fill(dp, -1000000000);
        dp[0] = 0;

        int ans = 0;
        int idx = 0;

        while (idx < n) {
            int price = items[order[idx]][1];

            int[] has = new int[budget + 1];
            Arrays.fill(has, -1000000000);

            while (idx < n && items[order[idx]][1] == price) {
                int id = order[idx];
                int cost = items[id][1];
                int val = benefit[id];

                for (int b = budget; b >= cost; b--) {
                    has[b] = Math.max(has[b],
                        Math.max(has[b - cost] + val,
                                 dp[b - cost] + val));

                    dp[b] = Math.max(dp[b],
                        dp[b - cost] + val);
                }

                idx++;
            }

            // Add extra copies of the cheapest activated item
            for (int b = 0; b <= budget; b++) {
                if (has[b] >= 0) {
                    ans = Math.max(ans,
                        has[b] + (budget - b) / price);
                }
            }
        }

        return ans;
    }
}
