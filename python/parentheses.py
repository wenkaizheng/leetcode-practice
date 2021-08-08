from typing import List
class Solution1(object):
    def generateParenthesis(self, N):
        ans = []
        def backtrack(S = '', left = 0, right = 0):
            if len(S) == 2 * N:
                ans.append(S)
                return
            if left < N:
                backtrack(S+'(', left+1, right)
            if right < left:
                backtrack(S+')', left, right+1)

        backtrack()
        return ans

class Solution2(object):
    def scoreOfParentheses(self, S):
        stack = [0] #The score of the current frame

        for x in S:
            if x == '(':
                stack.append(0)
            else:
                v = stack.pop()
                stack[-1] += max(2 * v, 1)

        return stack.pop()

class Solution3:
    def isValid(self, s: str) -> bool:
        d = {'(':')', '{':'}','[':']'}
        stack = []
        for i in s:
            if i in d:  # 1
                stack.append(i)
            elif len(stack) == 0 or d[stack.pop()] != i:  # 2
                return False
        return len(stack) == 0 # 3
        
class Solution4:
    def diffWaysToCompute(self, input: str) -> List[int]:
        if input.isdigit():
            return [int(input)]
        res = []
        for i in range(len(input)):
            if input[i] in "-+*":
                left = self.diffWaysToCompute(input[:i])
                right = self.diffWaysToCompute(input[i+1:])
                for l in left:
                    for r in right:
                        if input[i] == '+':
                            res.append(l+r)
                        elif input[i] == '-':
                            res.append(l-r)
                        elif input[i] == '*':
                            res.append(l*r)
        return res

class Solution5:
    def longestValidParentheses(self, s: str) -> int:
        st,m=[-1],0
        for i in range(len(s)):
            if s[i]=='(':st.append(i)
            else:
                st.pop()
                if not st: st.append(i)
                else: m=max(m,i-st[-1])
        return m
  
        
s1 = Solution1()
print(s1.generateParenthesis(5))
s2 = Solution2()
print(s2.scoreOfParentheses("(()(()))"))      
s3 = Solution3()
print(s3.isValid("([]{})"))
s4 = Solution4()
print(s4.diffWaysToCompute("2*3-4*5"))

s5 = Solution5()
print(s5.longestValidParentheses(")()()))"))      