class Solution {    
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        /*
            m = grid.size()
            n = grid[0].size()
            O(m * n) max space O(m * n) time
        */
        const int m = grid.size();
        const int n = grid[0].size();

        int maxArea = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0) { continue; }

                stack<pair<int, int>> visit{{pair{i, j}}};
                int area = 0;
                while (!visit.empty()) {
                    const auto [i1, j1] = visit.top(); visit.pop();
                    if (i1 < 0 || j1 < 0 || i1 >= m || j1 >= n || grid[i1][j1] == 0) { continue; }

                    grid[i1][j1] = 0;
                    ++area;
                    visit.push({i1 + 1, j1}); visit.push({i1, j1 + 1});
                    visit.push({i1 - 1, j1}); visit.push({i1, j1 - 1});
                }
                maxArea = max(maxArea, area);
            }
        }
        return maxArea;
    }
};