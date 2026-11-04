
class Solution {
public:
    using ll = long long;

    struct BIT {
        int n;
        vector<ll> bit;

        BIT(int n) : n(n), bit(n + 1, 0) {}

        void update(int i, ll val) {
            for (; i <= n; i += i & -i)
                bit[i] += val;
        }

        ll query(int i) {
            ll sum = 0;
            for (; i > 0; i -= i & -i)
                sum += bit[i];
            return sum;
        }

        int kth(ll k) {
            int idx = 0;
            for (int step = 1 << 17; step; step >>= 1) {
                int next = idx + step;
                if (next <= n && bit[next] < k) {
                    idx = next;
                    k -= bit[next];
                }
            }
            return idx + 1;
        }
    };

    long long minOperations(vector<int>& nums, int x, int k) {
        int n = nums.size();

        vector<int> vals = nums;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());

        int m = vals.size();

        BIT cnt(m), sum(m);

        vector<ll> cost(n - x + 1);

        ll totalSum = 0;
        int left = 0;

        auto add = [&](int idx, int sign) {
            int p = lower_bound(vals.begin(), vals.end(), nums[idx])
                    - vals.begin() + 1;
            cnt.update(p, sign);
            sum.update(p, 1LL * sign * nums[idx]);
        };

        auto getCost = [&]() -> ll {
            int mid = cnt.kth((x + 1) / 2);
            ll median = vals[mid - 1];

            int p = lower_bound(vals.begin(), vals.end(), median)
                    - vals.begin() + 1;

            ll leftCount = cnt.query(p);
            ll leftSum = sum.query(p);

            ll rightCount = x - leftCount;
            ll rightSum = totalSum - leftSum;

            return median * leftCount - leftSum
                   + rightSum - median * rightCount;
        };

        for (int i = 0; i < n; i++) {
            add(i, 1);
            totalSum += nums[i];

            if (i >= x) {
                add(i - x, -1);
                totalSum -= nums[i - x];
            }

            if (i >= x - 1)
                cost[i - x + 1] = getCost();
        }

        const ll INF = LLONG_MAX / 4;

        vector<ll> prev(n + 1, 0), curr(n + 1, INF);

        for (int j = 1; j <= k; j++) {
            fill(curr.begin(), curr.end(), INF);

            for (int i = 1; i <= n; i++) {
                curr[i] = curr[i - 1];

                if (i >= x && prev[i - x] != INF) {
                    curr[i] = min(curr[i],
                                  prev[i - x] + cost[i - x]);
                }
            }

            prev.swap(curr);
        }

        return prev[n];
    }
};
