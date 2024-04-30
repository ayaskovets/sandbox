class MyCalendar {
    map<int, int> events;
public:
    bool book(int s, int e) {
        /*
            n = events.size()
            O(n) space O(n * log(n)) time
        */
        const auto next = events.upper_bound(s);
        if (next != end(events) && next->second < e) {
            return false;
        }
        events.insert({e, s});
        return true;
    }
};