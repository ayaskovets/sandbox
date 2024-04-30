class Solution {
public:
    int myAtoi(const string& s) {
        /*
            n = s.size()
            O(1) space O(n) time
        */
        long long i = 0;
        bool n = false;

        auto it = cbegin(s);
        while (*it == ' ') {
            ++it;
        }
        if (*it == '-' || *it == '+') {
            n = *it == '-'; ++it;
        }
        while (*it >= '0' && *it <= '9' && it < cend(s)) {
            i *= 10;
            i += *it - '0';
            if (!n && i >= INT_MAX) {
                return INT_MAX;
            }
            if (n && -i <= INT_MIN) {
                return INT_MIN;
            }
            ++it;
        }
        return n ? -i : i;
    }
};