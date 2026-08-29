class Solution {
public:
    vector<int> lexicographicallySmallestArray(vector<int>& nums, int limit) {
        int n = nums.size();

        // Store {value, original index}
        vector<pair<int, int>> arr;

        for (int i = 0; i < n; i++) {
            arr.push_back({nums[i], i});
        }

        // Sort by value
        sort(arr.begin(), arr.end());

        vector<int> ans(n);

        int start = 0;

        while (start < n) {
            int end = start;

            // Find one connected group
            while (end + 1 < n &&
                   arr[end + 1].first - arr[end].first <= limit) {
                end++;
            }

            // Extract values and indices of this group
            vector<int> values;
            vector<int> indices;

            for (int i = start; i <= end; i++) {
                values.push_back(arr[i].first);
                indices.push_back(arr[i].second);
            }

            // Smallest values should go to smallest indices
            sort(indices.begin(), indices.end());

            for (int i = 0; i < values.size(); i++) {
                ans[indices[i]] = values[i];
            }

            start = end + 1;
        }

        return ans;
    }
};