class Solution:
    def sortString(self, s: str) -> str:
        """
            n = len(s)
            O(n) space O(n * log(n) + n) time
        """
        counts = sorted(Counter(s).items(), key=lambda item: item[0])
        s = ''
        popempty = lambda c: c[1] > 0
        decrcount = lambda c: (c[0], c[1] - 1)
        while len(counts) > 0:
            s += ''.join(c[0] for c in counts)
            counts[:] = filter(popempty, map(decrcount, counts))
            counts.reverse()
        return s