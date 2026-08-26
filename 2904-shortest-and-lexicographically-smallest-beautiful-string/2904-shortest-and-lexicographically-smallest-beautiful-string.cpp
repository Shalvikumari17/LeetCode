class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        vector<int> pos;

        // Store positions of all 1s
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '1') {
                pos.push_back(i);
            }
        }

        // Not enough 1s
        if (pos.size() < k)
            return "";

        string ans = "";
        int minLen = INT_MAX;

        // Check every group of k consecutive 1s
        for (int i = 0; i + k - 1 < pos.size(); i++) {

            int left = pos[i];
            int right = pos[i + k - 1];

            int len = right - left + 1;

            string curr = s.substr(left, len);

            // Smaller length OR same length but lexicographically smaller
            if (len < minLen ||
                (len == minLen && curr < ans)) {

                minLen = len;
                ans = curr;
            }
        }

        return ans;
    }
};