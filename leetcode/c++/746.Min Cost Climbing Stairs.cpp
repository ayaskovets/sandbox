class Solution {
public:
    int minCostClimbingStairs(const vector<int>& cost) {
        /*
            n = cost.size()
            O(n) space O(n) time
        */
        vector<int> dp;
        dp.reserve(cost.size() + 1);
        dp.push_back(0);
        dp.push_back(0);
        for (size_t i = 2; i < cost.size() + 1; ++i) {
            dp.push_back(min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2]));
        }
        return dp.back();
    }
};