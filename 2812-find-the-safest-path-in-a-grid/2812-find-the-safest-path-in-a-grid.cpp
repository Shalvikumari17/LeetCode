class Solution {
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> dist(n, vector<int>(n, -1));
        queue<pair<int,int>> q;

        // Multi-source BFS from all thieves
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(grid[i][j] == 1) {
                    dist[i][j] = 0;
                    q.push({i, j});
                }
            }
        }

        int dr[4] = {-1, 1, 0, 0};
        int dc[4] = {0, 0, -1, 1};

        while(!q.empty()) {
            auto [r, c] = q.front();
            q.pop();

            for(int k = 0; k < 4; k++) {
                int nr = r + dr[k];
                int nc = c + dc[k];

                if(nr >= 0 && nr < n && nc >= 0 && nc < n &&
                   dist[nr][nc] == -1) {
                    dist[nr][nc] = dist[r][c] + 1;
                    q.push({nr, nc});
                }
            }
        }

        auto can = [&](int safe) {
            if(dist[0][0] < safe || dist[n-1][n-1] < safe)
                return false;

            queue<pair<int,int>> qq;
            vector<vector<bool>> vis(n, vector<bool>(n, false));

            qq.push({0,0});
            vis[0][0] = true;

            while(!qq.empty()) {
                auto [r,c] = qq.front();
                qq.pop();

                if(r == n-1 && c == n-1)
                    return true;

                for(int k = 0; k < 4; k++) {
                    int nr = r + dr[k];
                    int nc = c + dc[k];

                    if(nr >= 0 && nr < n && nc >= 0 && nc < n &&
                       !vis[nr][nc] && dist[nr][nc] >= safe) {
                        vis[nr][nc] = true;
                        qq.push({nr,nc});
                    }
                }
            }

            return false;
        };

        int low = 0, high = 2 * n, ans = 0;

        while(low <= high) {
            int mid = low + (high - low) / 2;
            if(can(mid)) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        return ans;
    }
};