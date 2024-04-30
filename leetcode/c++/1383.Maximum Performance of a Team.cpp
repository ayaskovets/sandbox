class Solution {
public:
    int maxPerformance(int n, vector<int>& speed, vector<int>& efficiency, int k) {
        /*
            n = n
            O(n) space O(n * log(n) + n * log(k)) time
        */
        vector<pair<int, int>> performance(n);
        for (int i = 0; i < n; ++i)
            performance[i] = {efficiency[i], speed[i]};
        sort(rbegin(performance), rend(performance));

        long team_speed = 0, ans = 0;
        priority_queue<int, vector<int>, greater<int>> q;
        for (const auto [e, s] : performance) {
            q.push(s);
            team_speed += s;
            if (q.size() > k) {
                team_speed -= q.top(); q.pop();
            }
            ans = max(ans, team_speed * e);
        }
        return ans % 1000000007;
    }
};