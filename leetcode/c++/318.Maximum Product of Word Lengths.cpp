class Solution {
public:
    int maxProduct(const vector<string>& words) {
        /*
            n = words.size()
            O(n) space O(n^2) time
        */
        auto letters = vector<int>(words.size(), 0);
        for (size_t i = 0; i < words.size(); ++i)
            for (char c : words[i])
                letters[i] |= 1 << (c - 'a');
        
        int maxProd = 0;
        for (int i = 0; i < words.size(); ++i)
            for (int j = i + 1; j < words.size(); ++j)
                if ((letters[i] & letters[j]) == 0)
                    maxProd = max<int>(maxProd, words[i].size() * words[j].size());
        return maxProd;
    }
};