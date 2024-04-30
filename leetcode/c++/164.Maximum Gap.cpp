class Solution {
public:
    int maximumGap(vector<int>& nums) {
        /*
            n = nums.size()
            O(1) space O(n) time
        */
        for (int bit = 0; bit < 31; ++bit)
            stable_partition(nums.begin(), nums.end(), [bit](int a){
                return !(a & (1 << bit));
            });
        int gap = 0;
        for(size_t i = 1; i < nums.size(); ++i)
            gap = max(gap, nums[i] - nums[i - 1]);
        return gap;
    }
};