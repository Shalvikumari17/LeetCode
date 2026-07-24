class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        const int MAXX = 2048;

        vector<bool> present(MAXX, false);

        // Mark all unique numbers
        for (int x : nums) {
            present[x] = true;
        }

        // dp2[x] = can we make XOR x using 2 elements?
        vector<bool> dp2(MAXX, false);

        for (int a = 0; a < MAXX; a++) {
            if (!present[a]) continue;

            for (int b = 0; b < MAXX; b++) {
                if (!present[b]) continue;

                dp2[a ^ b] = true;
            }
        }

        // dp3[x] = can we make XOR x using 3 elements?
        vector<bool> dp3(MAXX, false);

        for (int x = 0; x < MAXX; x++) {
            if (!dp2[x]) continue;

            for (int a = 0; a < MAXX; a++) {
                if (!present[a]) continue;

                dp3[x ^ a] = true;
            }
        }

        int answer = 0;

        for (int x = 0; x < MAXX; x++) {
            if (dp3[x]) {
                answer++;
            }
        }

        return answer;
    }
};