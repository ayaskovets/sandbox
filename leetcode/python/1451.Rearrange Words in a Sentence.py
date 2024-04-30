class Solution:
    def arrangeWords(self, text: str) -> str:
        """
            n = len(text)
            w = len(text.split())
            O(n) space O(w * log(w)) time
        """
        return ' '.join(sorted(text.split(), key=len)).capitalize()
