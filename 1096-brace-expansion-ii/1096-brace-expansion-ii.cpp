class Solution {
public:
    set<string> combine(set<string> a, set<string> b) {
        set<string> ans;

        for (string x : a) {
            for (string y : b) {
                ans.insert(x + y);
            }
        }

        return ans;
    }

    set<string> solve(string &s, int &i) {
        set<string> ans;
        set<string> current;
        current.insert("");

        while (i < s.size() && s[i] != '}') {

            // Union
            if (s[i] == ',') {
                for (string x : current)
                    ans.insert(x);

                current.clear();
                current.insert("");
                i++;
            }

            // Braced expression
            else if (s[i] == '{') {
                i++; // skip '{'

                set<string> temp = solve(s, i);

                i++; // skip '}'

                current = combine(current, temp);
            }

            // Single character
            else {
                set<string> temp;
                temp.insert(string(1, s[i]));

                current = combine(current, temp);
                i++;
            }
        }

        // Add last expression
        for (string x : current)
            ans.insert(x);

        return ans;
    }

    vector<string> braceExpansionII(string expression) {
        int i = 0;

        set<string> result = solve(expression, i);

        return vector<string>(result.begin(), result.end());
    }
};