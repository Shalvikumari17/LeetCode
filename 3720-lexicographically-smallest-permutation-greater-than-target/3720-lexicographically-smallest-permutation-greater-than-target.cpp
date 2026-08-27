class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();

        // Count characters of s
        vector<int> cnt(26, 0);
        for (char c : s) {
            cnt[c - 'a']++;
        }

        string prefix = "";

        // Try to match target from left to right
        for (int i = 0; i < n; i++) {
            int x = target[i] - 'a';

            // If target[i] is available, keep it equal
            if (cnt[x] > 0) {
                cnt[x]--;
                prefix += target[i];
            } 
            else {
                // Cannot continue equal.
                // Try a character greater than target[i].
                for (int c = x + 1; c < 26; c++) {
                    if (cnt[c] > 0) {
                        string ans = prefix;
                        ans += char('a' + c);
                        cnt[c]--;

                        // Add remaining characters in sorted order
                        for (int k = 0; k < 26; k++) {
                            while (cnt[k] > 0) {
                                ans += char('a' + k);
                                cnt[k]--;
                            }
                        }

                        return ans;
                    }
                }

                // No bigger character here,
                // so we need to backtrack.
                break;
            }
        }

        // Backtrack
        for (int i = (int)prefix.size() - 1; i >= 0; i--) {

            // Put the previously used character back
            cnt[prefix[i] - 'a']++;

            int x = target[i] - 'a';

            // Find smallest character greater than target[i]
            for (int c = x + 1; c < 26; c++) {
                if (cnt[c] > 0) {
                    string ans = prefix.substr(0, i);

                    ans += char('a' + c);
                    cnt[c]--;

                    // Remaining characters in sorted order
                    for (int k = 0; k < 26; k++) {
                        while (cnt[k] > 0) {
                            ans += char('a' + k);
                            cnt[k]--;
                        }
                    }

                    return ans;
                }
            }
        }

        // No permutation is greater than target
        return "";
    }
};