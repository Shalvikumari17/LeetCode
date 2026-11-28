
import java.util.*;

class Solution {
    public int maximumSaleItems(int[][] items, int budget) {
        int n = items.length;

        // Step 1: Count frequency of each factor
        int[] freq = new int[n + 1];

        int minPrice = Integer.MAX_VALUE;

        for (int[] item : items) {
            freq[item[0]]++;
            minPrice = Math.min(minPrice, item[1]);
        }

        // Step 2: Count how many items each factor divides
        int[] multiples = new int[n + 1];

        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j += i) {
                multiples[i] += freq[j];
            }
        }

        // Step 3: Calculate free-copy opportunities
        int[][] candidates = new int[n][2];

        for (int i = 0; i < n; i++) {
            int factor = items[i][0];
            int price = items[i][1];

            candidates[i][0] = price;
            candidates[i][1] = multiples[factor] - 1;
        }

        // Step 4: Sort by price
        Arrays.sort(candidates, (a, b) ->
            Integer.compare(a[0], b[0])
        );

        long remaining = budget;
        long answer = 0;

        // Step 5: Buy profitable copies (each gives 2 items)
        for (int[] item : candidates) {
            long price = item[0];
            long gain = item[1];

            if (price >= 2L * minPrice) {
                break;
            }

            long count = Math.min(gain, remaining / price);

            answer += count * 2;
            remaining -= count * price;
        }

        // Step 6: Spend remaining budget on cheapest item
        answer += remaining / minPrice;

        return (int) answer;
    }
}
