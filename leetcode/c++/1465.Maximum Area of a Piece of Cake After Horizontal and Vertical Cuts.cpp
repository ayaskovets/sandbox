class Solution {
public:
    int maxArea(int h, int w, vector<int>& horizontalCuts, vector<int>& verticalCuts) {
        /*
            n = horizontalCuts.size()
            m = verticalCuts.size()
            O(1) space O(n * log(n) + m * log(m) + n + m) time
        */
        sort(begin(horizontalCuts), end(horizontalCuts));
        sort(begin(verticalCuts), end(verticalCuts));

        int maxh = max(horizontalCuts.front(), h - horizontalCuts.back());
        int maxw = max(verticalCuts.front(), w - verticalCuts.back());

        for (int i = 1; i < horizontalCuts.size(); ++i)
            maxh = max(maxh, horizontalCuts[i] - horizontalCuts[i - 1]);
        for (int i = 1; i < verticalCuts.size(); ++i)
            maxw = max(maxw, verticalCuts[i] - verticalCuts[i - 1]);

        return ((long)maxh * maxw) % 1000000007;
    }
};