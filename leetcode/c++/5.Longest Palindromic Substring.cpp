class Solution {
public:
    string longestPalindrome(string s) {
        /*
            n = s.size()
            O(1) space O(n^2) time
        */
        if (s.size() < 2)
            return s;

        int max_len = 0;
        int start_idx = 0;
        int i = 0;
        while (i < s.size()) {
            int r = i; 
            int l = i;

            while (r < s.size() - 1 && s[r] == s[r + 1])
                ++r;
            
            i = r + 1;

            while (r < s.size() - 1 && l > 0 && s[r + 1] == s[l - 1]) {
                r++;
                l--;
            }

            int new_len = r - l + 1;
            if (new_len > max_len) {
                start_idx = l;
                max_len = new_len;
            }
        }
        return s.substr(start_idx, max_len);
    }
};