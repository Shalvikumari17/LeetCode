class Solution {
public:
    long long sumAndMultiply(int n) {
        long long x = 0;
        int sum = 0;

        if (n == 0) return 0;

        vector<int> digits;

        while (n > 0) {
            digits.push_back(n % 10);
            n /= 10;
        }

        reverse(digits.begin(), digits.end());

        for (int d : digits) {
            if (d != 0) {
                x = x * 10 + d;
                sum += d;
            }
        }

        return x * sum;
    }
};