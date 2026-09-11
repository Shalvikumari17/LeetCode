class Solution {
public:
    int totalNumbers(vector<int>& digits) {
        set<int> st;

        for (int num = 100; num <= 998; num += 2) {
            int a = num / 100;
            int b = (num / 10) % 10;
            int c = num % 10;

            vector<int> cnt(10, 0);

            for (int d : digits)
                cnt[d]++;

            if (cnt[a] > 0) {
                cnt[a]--;

                if (cnt[b] > 0) {
                    cnt[b]--;

                    if (cnt[c] > 0) {
                        st.insert(num);
                    }
                }
            }
        }

        return st.size();
    }
};