class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        rc = [[False] * (len(s)+1) for i in range(0,len(p)+1)]
        rc[0][0] = True
        for i in range(1,len(p)+1):
            rc[i][0] = i>1 and rc[i-2][0] and p[i-1] == '*'    #  0 time
        for i in range(1,len(p)+1):
            for j in range(1,len(s)+1):
                if p[i-1] == s[j-1] or p[i-1] == '.':    
                    rc[i][j] = rc[i-1][j-1]
                elif p[i-1] == '*':
                    rc[i][j] |= rc[i-1][j]                  #  1 time 
                    rc[i][j] |= i>1 and rc[i-2][j]          #  0 time
                    if  i>1 and s[j-1] == p[i-2] or p[i-2] == '.':    
                        rc[i][j] |= rc[i][j-1]              # add one more times
        return rc[-1][-1]


class Solution1:
    def isMatch(self, s, p):
        dp = [[False for _ in range(len(s)+1)] for i in range(len(p)+1)]
        dp[0][0] = True
        for j in range(1, len(p)+1):
            if p[j-1] != '*':
                break
            dp[j][0] = True
                
        for i in range(1, len(p)+1):
            for j in range(1, len(s)+1):
                if p[i-1] == s[j-1] or p[i-1] == '?':
                    dp[i][j] = dp[i-1][j-1]
                
                elif p[i-1] == '*':
                    dp[i][j] = dp[i-1][j-1] or dp[i-1][j] or dp[i][j-1]
        return dp[-1][-1]

s =Solution()
print(s.isMatch("aab","c*a*b"))
print(s.isMatch("mississippi","mis*is*p*"))

s1 = Solution1()
print(s1.isMatch("adceb","*a*b"))
print(s1.isMatch("acdcb","a*c?b"))