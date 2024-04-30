class Solution {
    /* big-endian style lock values */
    using lock_t = unsigned int;

    /* Get the value of n-th wheel of the lock */
    int nth_get(lock_t l, int n) {
        return (l >> ((3 - n) * 8)) & 0xff;
    }
    /* Set n-th wheel value to val */
    lock_t nth_set(lock_t l, int n, int val) {
        return (l & (UINT_MAX ^ (0xff << ((3 - n) * 8)))) | val << ((3 - n) * 8);
    }
    /* Rotate n-th wheel of the lock in the direction of the greater digit */
    lock_t nth_upw(lock_t l, int n) {
        auto nth = nth_get(l, n);
        return nth_set(l, n, nth == 9 ? 0 : nth + 1);
    }
    /* Rotate n-th wheel of the lock in the direction of the smaller digit */
    lock_t nth_dwn(lock_t l, int n) {
        auto nth = nth_get(l, n);
        return nth_set(l, n, nth == 0 ? 9 : nth - 1);
    }
    /* Convert std::string to lock_t */
    lock_t s2w(string s) {
        auto l = lock_t{};
        for (int i = 0; i < 4; ++i) {
            l = nth_set(l, i, s[i] - '0');
        }
        return l;
    }

public:
    int openLock(vector<string>& deadends, string& target) {
        unordered_set<lock_t> ds;
        for (string& deadend : deadends) {
            ds.insert(s2w(deadend));
        }

        auto t = s2w(target);
        auto s = INT_MAX;

        auto q = queue<pair<lock_t, int>>({{0, 0}});
        while (!q.empty()) {
            const auto [fl, fs] = q.front(); q.pop();

            if (ds.count(fl)) {
                continue;
            }

            ds.insert(fl);

            if (fl == t) {
                s = min(s, fs);
            }

            for (int i = 0; i < 4; ++i) {
                if (fs < s) {
                    auto upw = nth_upw(fl, i);
                    if (!ds.count(upw)) {
                        q.push({upw, fs + 1});
                    }
                    auto dwn = nth_dwn(fl, i);
                    if (!ds.count(dwn)) {
                        q.push({dwn, fs + 1});
                    }
                }
            }
        }

        return s == INT_MAX ? -1 : s;
    }
};