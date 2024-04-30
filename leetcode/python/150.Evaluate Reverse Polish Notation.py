class Solution:
    def evalRPN(self, tokens: List[str]) -> int:
        """
            n = len(tokens)
            O(n) space O(n) time
        """
        ops = {'+': add, '-': sub, '*': mul, '/': lambda a, b: int(a / b)}
        stack = []
        for token in tokens:
            if op := ops.get(token):
                stack.append(op(stack.pop(-2), stack.pop()))
            else:
                stack.append(int(token))
        return stack[0]
