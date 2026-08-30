class Solution {
public:
    int minimumDeletions(vector<int>& nums) {
        int n = nums.size();

        int minIndex = 0;
        int maxIndex = 0;

        // Find index of minimum and maximum
        for (int i = 1; i < n; i++) {
            if (nums[i] < nums[minIndex])
                minIndex = i;

            if (nums[i] > nums[maxIndex])
                maxIndex = i;
        }

        // Make minIndex the smaller index
        // and maxIndex the larger index
        if (minIndex > maxIndex)
            swap(minIndex, maxIndex);

        // 1. Remove both from front
        int front = maxIndex + 1;

        // 2. Remove both from back
        int back = n - minIndex;

        // 3. Remove smaller index from front
        //    and larger index from back
        int bothSides = (minIndex + 1) + (n - maxIndex);

        return min({front, back, bothSides});
    }
};