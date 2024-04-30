class Solution {
    int n;

    vector<bool> cols;
    vector<bool> dasc;
    vector<bool> ddsc;

    int solutions = 0;

    void backtrack(int r) {
        if (r == n) {
            solutions += 1;
            return;
        }
        for (int c = 0; c < n; ++c) {
            if (cols[c] || dasc[r + c] || ddsc[n - r + c]) { continue; }
            cols[c] = dasc[r + c] = ddsc[n - r + c] = true;
            backtrack(r + 1);
            cols[c] = dasc[r + c] = ddsc[n - r + c] = false;
        }
    }
public:
    int totalNQueens(int n) {
        /*
            n = n
            O(n) space O(n!) time
        */
        this->n = n;
        cols.resize(n, false);
        dasc.resize(n * 2, false);
        ddsc.resize(n * 2, false);
        backtrack(0);
        return solutions;
    }
};