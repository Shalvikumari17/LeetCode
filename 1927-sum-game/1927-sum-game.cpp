class Solution {
public:
    bool sumGame(string num) {
        int n = num.size();
        int half = n / 2;

        int leftSum = 0;
        int rightSum = 0;

        int leftQ = 0;
        int rightQ = 0;

        // First half
        for (int i = 0; i < half; i++) {
            if (num[i] == '?') {
                leftQ++;
            } else {
                leftSum += num[i] - '0';
            }
        }

        // Second half
        for (int i = half; i < n; i++) {
            if (num[i] == '?') {
                rightQ++;
            } else {
                rightSum += num[i] - '0';
            }
        }

        int diff = leftSum - rightSum;
        int qDiff = leftQ - rightQ;

        // Odd number of unmatched '?'
        if (abs(qDiff) % 2 == 1) {
            return true;
        }

        // Bob can force equality only in this case
        return diff != -9 * qDiff / 2;
    }
};