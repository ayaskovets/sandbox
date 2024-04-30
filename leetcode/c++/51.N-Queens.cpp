class Solution {
    int n;

    vector<bool> cols;
    vector<bool> dasc;
    vector<bool> ddsc;

    vector<vector<string>> solutions;
    vector<string> solution;

    void backtrack(int r) {
        if (r == n) {
            solutions.push_back(solution);
            return;
        }
        for (int c = 0; c < n; ++c) {
            if (cols[c] || dasc[r + c] || ddsc[n - r + c]) { continue; }
            cols[c] = dasc[r + c] = ddsc[n - r + c] = true;
            solution[r][c] = 'Q';
            backtrack(r + 1);
            solution[r][c] = '.';
            cols[c] = dasc[r + c] = ddsc[n - r + c] = false;
        }
    }
public:
    vector<vector<string>> solveNQueens(int n) {
        /*
            n = n
            O(n^2) space O(n!) time
        */
        this->n = n;
        cols.resize(n, false);
        dasc.resize(n * 2, false);
        ddsc.resize(n * 2, false);
        solution.resize(n, string(n, '.'));
        backtrack(0);
        return solutions;
    }
};