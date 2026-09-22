class Solution {
public:
    struct Node {
        int prod = 1;
        long long pref[5] = {};
        long long suff[5] = {};
        long long all[5] = {};
    };

    int n, k;
    vector<Node> tree;

    Node mergeNode(const Node &L, const Node &R) {
        Node res;

        res.prod = (L.prod * R.prod) % k;

        // Prefixes
        // 1) Prefix entirely inside L
        for (int r = 0; r < k; r++)
            res.pref[r] += L.pref[r];

        // 2) Whole L + prefix of R
        for (int r = 0; r < k; r++) {
            int nr = (L.prod * r) % k;
            res.pref[nr] += R.pref[r];
        }

        // Suffixes
        // 1) Suffix entirely inside R
        for (int r = 0; r < k; r++)
            res.suff[r] += R.suff[r];

        // 2) Suffix of L + whole R
        for (int r = 0; r < k; r++) {
            int nr = (r * R.prod) % k;
            res.suff[nr] += L.suff[r];
        }

        // All subarrays completely inside L/R
        for (int r = 0; r < k; r++) {
            res.all[r] = L.all[r] + R.all[r];
        }

        // Subarray crossing L and R
        for (int i = 0; i < k; i++) {
            if (L.suff[i] == 0) continue;

            for (int j = 0; j < k; j++) {
                if (R.pref[j] == 0) continue;

                int rem = (i * j) % k;
                res.all[rem] += L.suff[i] * R.pref[j];
            }
        }

        return res;
    }

    Node makeNode(int val) {
        Node res;

        int rem = val % k;

        res.prod = rem;
        res.pref[rem] = 1;
        res.suff[rem] = 1;
        res.all[rem] = 1;

        return res;
    }

    void build(int idx, int l, int r, vector<int> &nums) {
        if (l == r) {
            tree[idx] = makeNode(nums[l]);
            return;
        }

        int mid = (l + r) / 2;

        build(idx * 2, l, mid, nums);
        build(idx * 2 + 1, mid + 1, r, nums);

        tree[idx] = mergeNode(tree[idx * 2], tree[idx * 2 + 1]);
    }

    void update(int idx, int l, int r, int pos, int val) {
        if (l == r) {
            tree[idx] = makeNode(val);
            return;
        }

        int mid = (l + r) / 2;

        if (pos <= mid)
            update(idx * 2, l, mid, pos, val);
        else
            update(idx * 2 + 1, mid + 1, r, pos, val);

        tree[idx] = mergeNode(tree[idx * 2], tree[idx * 2 + 1]);
    }

    Node query(int idx, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr)
            return tree[idx];

        int mid = (l + r) / 2;

        if (qr <= mid)
            return query(idx * 2, l, mid, ql, qr);

        if (ql > mid)
            return query(idx * 2 + 1, mid + 1, r, ql, qr);

        Node left = query(idx * 2, l, mid, ql, qr);
        Node right = query(idx * 2 + 1, mid + 1, r, ql, qr);

        return mergeNode(left, right);
    }

    vector<int> resultArray(
        vector<int>& nums,
        int k,
        vector<vector<int>>& queries
    ) {
        this->n = nums.size();
        this->k = k;

        tree.resize(4 * n + 5);

        build(1, 0, n - 1, nums);

        vector<int> ans;
        ans.reserve(queries.size());

        for (auto &q : queries) {
            int index = q[0];
            int value = q[1];
            int start = q[2];
            int x = q[3];

            // Persistent update
            update(1, 0, n - 1, index, value);

            // Remaining array = nums[start ... n-1]
            Node res = query(1, 0, n - 1, start, n - 1);

            // Every possible suffix removal corresponds
            // to one prefix of this range.
            ans.push_back(res.pref[x]);
        }

        return ans;
    }
};