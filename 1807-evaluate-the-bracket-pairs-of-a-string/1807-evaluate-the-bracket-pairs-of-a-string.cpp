class Solution {
public:
    string evaluate(string s, vector<vector<string>>& knowledge) {
        unordered_map<string, string> mp;

        // Store key-value pairs
        for (auto &k : knowledge) {
            mp[k[0]] = k[1];
        }

        string ans;

        for (int i = 0; i < s.size(); i++) {
            if (s[i] != '(') {
                ans += s[i];
            } 
            else {
                int j = i + 1;
                string key;

                // Extract key
                while (s[j] != ')') {
                    key += s[j];
                    j++;
                }

                // Replace key with value or '?'
                if (mp.count(key))
                    ans += mp[key];
                else
                    ans += '?';

                // Skip to character after ')'
                i = j;
            }
        }

        return ans;
    }
};