class Solution {
public:
    int maximumUniqueSubarray(vector<int>& nums) {
        /*
            n = nums.size()
            O(n) space O(n) time
        */
        auto subarray = unordered_set<int>{{nums[0]}};

        int runsum = nums[0];
        int maxsum = nums[0];
        for (int l = 0, r = 1; r < nums.size(); ++r) {
            while (subarray.count(nums[r])) {
                subarray.erase(nums[l]);
                runsum -= nums[l++];
            }
            subarray.insert(nums[r]);
            runsum += nums[r];

            maxsum = max(maxsum, runsum);
        }
        return maxsum;
    }
};