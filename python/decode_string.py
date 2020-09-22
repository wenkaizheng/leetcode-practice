class Solution:
    def decodeString(self, s: str) -> str:
        stack, curNum, curString = [], 0, ''
        for c in s:
            if c == '[':
                stack.append((curString, curNum))
                curString, curNum = '', 0
            elif c == ']':
                prevString, num = stack.pop()
                curString = prevString + num*curString
            elif c.isdigit():
                curNum = curNum*10 + int(c)
            else:
                curString += c
        return curString
s = Solution()
print(s.decodeString("3[a]2[bc]"))
print(s.decodeString("3[a2[c]]"))