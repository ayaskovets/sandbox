class Solution:
    def canConstruct(self, ransomNote: str, magazine: str) -> bool:
        """
            n1 = len(ransomNote)
            n2 = len(magazine)
            O(n1) space O(n1 + n2) time
        """
        magazine = Counter(magazine)
        magazine.subtract(ransomNote)
        return magazine.most_common()[-1][1] >= 0
