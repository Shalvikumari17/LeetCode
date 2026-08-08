class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        // suf[i] = maximum number of characters from the END
        // of word2 that can be matched exactly using word1[i...n-1].
        vector<int> suf(n + 1, 0);

        int j = m - 1;

        for (int i = n - 1; i >= 0; i--) {
            suf[i] = suf[i + 1];

            if (j >= 0 && word1[i] == word2[j]) {
                suf[i]++;
                j--;
            }
        }

        vector<int> ans;

        int cur = 0;
        bool mismatchUsed = false;

        for (int j = 0; j < m; j++) {

            bool found = false;

            while (cur < n) {

                // Case 1:
                // Current character matches.
                //
                // We choose it immediately because choosing
                // a smaller index is always better.
                if (word1[cur] == word2[j]) {
                    ans.push_back(cur);
                    cur++;
                    found = true;
                    break;
                }

                // Case 2:
                // Current character does not match.
                // We can use our one allowed mismatch here.
                //
                // The remaining characters must be matched
                // exactly.
                if (!mismatchUsed) {

                    int remaining = m - j - 1;

                    if (suf[cur + 1] >= remaining) {
                        ans.push_back(cur);
                        cur++;
                        mismatchUsed = true;
                        found = true;
                        break;
                    }
                }

                cur++;
            }

            if (!found)
                return {};
        }

        return ans;
    }
};