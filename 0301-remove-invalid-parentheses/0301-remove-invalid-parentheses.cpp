class Solution {
public:
    vector<string> ans;

    bool isValid(string s) {
        int count = 0;

        for (char c : s) {
            if (c == '(') count++;
            else if (c == ')') {
                if (count == 0) return false;
                count--;
            }
        }

        return count == 0;
    }

    void solve(string s, int start, int removeCount) {
        if (removeCount == 0) {
            if (isValid(s))
                ans.push_back(s);
            return;
        }

        for (int i = start; i < s.size(); i++) {

            // Skip duplicate parentheses
            if (i > start && s[i] == s[i - 1])
                continue;

            // Only parentheses can be removed
            if (s[i] != '(' && s[i] != ')')
                continue;

            string next = s.substr(0, i) + s.substr(i + 1);

            solve(next, i, removeCount - 1);
        }
    }

    vector<string> removeInvalidParentheses(string s) {

        // Find minimum number of removals needed
        int left = 0, right = 0;

        for (char c : s) {
            if (c == '(') {
                left++;
            } 
            else if (c == ')') {
                if (left > 0)
                    left--;
                else
                    right++;
            }
        }

        // left = extra '('
        // right = extra ')'
        solve(s, 0, left + right);

        // Remove duplicate answers
        sort(ans.begin(), ans.end());
        ans.erase(unique(ans.begin(), ans.end()), ans.end());

        return ans;
    }
};