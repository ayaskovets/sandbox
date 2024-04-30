class Solution {
public:
    int longestConsecutive(vector<int> &nums) {
        /*
            n = nums.size()
            O(n) space O(n) time
        */
        if (nums.empty())
            return 0;

        unordered_set<int> cons(begin(nums), end(nums));
        int ans = 1;
        for (const int num : nums) {
            if (!cons.count(num))
                continue;
            cons.erase(num);

            int prev = num - 1, next = num + 1;
            while (cons.count(prev)) cons.erase(prev--);
            while (cons.count(next)) cons.erase(next++);
            ans = max(ans, next - prev - 1);
        }
        return ans;
    }
};