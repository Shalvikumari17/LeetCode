
class Solution {
public:
    static const int MOD = 1e9 + 7;
    
    vector<long long> sum, sq;
    vector<int> lazy;
    int n;

    void push(int node, int l, int r) {
        if (lazy[node] == 0) return;

        int mid = (l + r) / 2;
        int left = node * 2;
        int right = left + 1;
        long long d = lazy[node];

        sum[left] = (sum[left] + d * (mid - l + 1)) % MOD;
        sq[left] = (sq[left] + 2 * d * sum[left] % MOD
                    - d * d % MOD * (mid - l + 1) % MOD
                    + MOD) % MOD;

        sum[right] = (sum[right] + d * (r - mid)) % MOD;
        sq[right] = (sq[right] + 2 * d * sum[right] % MOD
                     - d * d % MOD * (r - mid) % MOD
                     + MOD) % MOD;

        lazy[left] += lazy[node];
        lazy[right] += lazy[node];
        lazy[node] = 0;
    }

    void update(int node, int l, int r, int ql, int qr) {
        if (ql > r || qr < l) return;

        if (ql <= l && r <= qr) {
            long long d = 1;
            sq[node] = (sq[node] + 2 * sum[node] + (r - l + 1)) % MOD;
            sum[node] = (sum[node] + (r - l + 1)) % MOD;
            lazy[node]++;
            return;
        }

        push(node, l, r);
        int mid = (l + r) / 2;

        update(node * 2, l, mid, ql, qr);
        update(node * 2 + 1, mid + 1, r, ql, qr);

        sum[node] = (sum[node * 2] + sum[node * 2 + 1]) % MOD;
        sq[node] = (sq[node * 2] + sq[node * 2 + 1]) % MOD;
    }

    int sumCounts(vector<int>& nums) {
        n = nums.size();
        sum.assign(4 * n, 0);
        sq.assign(4 * n, 0);
        lazy.assign(4 * n, 0);

        vector<int> last(100001, -1);
        long long ans = 0;

        for (int r = 0; r < n; r++) {
            int l = last[nums[r]] + 1;
            update(1, 0, n - 1, l, r);
            last[nums[r]] = r;
            ans = (ans + sq[1]) % MOD;
        }

        return ans;
    }
};
