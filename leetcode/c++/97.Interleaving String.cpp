class Solution {
public:
    bool isInterleave(const string& s1, const string& s2, const string& s3) {        
        /*
            n = s1.size()
            m = s2.size()
            O(n * m) space O(n * m) time
        */
        if (s1.size() + s2.size() != s3.size()) {
            return false;
        }

        unordered_set<int> visited;
        const auto hash = [s3](int i1, int i2) { return i1  * s3.size() + i2; };

        stack<pair<int, int>> s{{{0, 0}}};
        while (!s.empty()) {
            const auto [i1, i2] = s.top(); s.pop();
            visited.insert(hash(i1, i2));
            if (i1 + i2 == s3.size()) {
                return true;
            }
            if (i1 < s1.size() && s1[i1] == s3[i1 + i2] && !visited.count(hash(i1 + 1, i2))) {
                s.push({i1 + 1, i2});
            }
            if (i2 < s2.size() && s2[i2] == s3[i1 + i2] && !visited.count(hash(i1, i2 + 1))) {
                s.push({i1, i2 + 1});
            }
        }
        return false;
    }
};
