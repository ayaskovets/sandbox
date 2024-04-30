class Solution {
public:
    int stoneGameVII(const vector<int>& stones) {
        /*
            n = stones.size()
            O(n) space O(n^2) time
        */
        vector<vector<int>> dp(stones.size(), vector<int>(stones.size()));
        const function<int(int, int, int)> dfs = [&dfs, &stones, &dp](int i, int j, int sum) {
            return i == j ? 0
                : dp[i][j] ? dp[i][j]
                    : dp[i][j] = max(sum - stones[i] - dfs(i + 1, j, sum - stones[i]),
                                     sum - stones[j] - dfs(i, j - 1, sum - stones[j]));
        };
        return dfs(0, stones.size() - 1, accumulate(begin(stones), end(stones), 0));
    }
};