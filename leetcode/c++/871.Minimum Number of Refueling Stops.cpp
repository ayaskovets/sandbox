class Solution {
public:
    int minRefuelStops(int target, int fuel, vector<vector<int>>& stations) {
        /*
            n = stations.size()
            O(n) space O(n * log(n)) time
        */
        int stops = 0, s = 0;
        for (priority_queue<int> q; fuel < target; ++stops) {
            while (s < stations.size() && fuel >= stations[s][0]) {
                q.push(stations[s++][1]);
            }
            if (q.empty()) {
                return -1;
            }
            fuel += q.top(); q.pop();
        }
        return stops;
    }
};