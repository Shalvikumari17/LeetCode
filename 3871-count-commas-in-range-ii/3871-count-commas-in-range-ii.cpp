class Solution {
public:
    long long countCommas(long long n) {
        long long ans = 0;

        // First number having 1 comma
        long long start = 1000;

        while (start <= n) {
            ans += n - start + 1;

            // Move to next comma level
            if (start > n / 1000)
                break;

            start *= 1000;
        }

        return ans;
    }
};