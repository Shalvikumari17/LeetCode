class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, int> mp;

        // Store reserved seats as a bitmask for each row
        for (auto &seat : reservedSeats) {
            int row = seat[0];
            int s = seat[1];

            mp[row] |= (1 << s);
        }

        long long ans = 2LL * n;

        // Masks for the three possible groups
        int left  = (1 << 2) | (1 << 3) | (1 << 4) | (1 << 5);
        int middle = (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);
        int right = (1 << 6) | (1 << 7) | (1 << 8) | (1 << 9);

        // Only rows having reservations need to be checked
        for (auto &[row, mask] : mp) {
            bool canLeft = (mask & left) == 0;
            bool canMiddle = (mask & middle) == 0;
            bool canRight = (mask & right) == 0;

            // We initially counted 2 for every row.
            // Recalculate this reserved row.

            if (canLeft && canRight) {
                // Still 2 groups
                continue;
            }
            else if (canLeft || canMiddle || canRight) {
                // Only 1 group possible
                ans--;
            }
            else {
                // No group possible
                ans -= 2;
            }
        }

        return (int)ans;
    }
};