class Solution:
    def readBinaryWatch(self, turnedOn: int) -> List[str]:
        """
            O(1) space O(12 * 60) time
        """
        return ['%d:%02d' % (h, m)
                for h in range(12) for m in range(60)
                if bin(h).count('1') + bin(m).count('1') == turnedOn]
