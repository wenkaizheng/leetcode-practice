class Solution:
    def isMatch(self, s: str, p: str) -> bool:
        rc = [[False] * (len(s)+1) for i in range(0,len(p)+1)]
        rc[0][0] = True
        for i in range(1,len(p)+1):
            rc[i][0] = i>1 and rc[i-2][0] and p[i-1] == '*'    # repeat 0 times
        for i in range(1,len(p)+1):
            for j in range(1,len(s)+1):
                if p[i-1] == s[j-1] or p[i-1] == '.':    
                    rc[i][j] = rc[i-1][j-1]
                elif p[i-1] == '*':
                    rc[i][j] |= rc[i-1][j]                  # repeat 1 times
                    rc[i][j] |= i>1 and rc[i-2][j]          # repeat 0 times
                    if  i>1 and s[j-1] == p[i-2] or p[i-2] == '.':    
                        rc[i][j] |= rc[i][j-1]              # repeat two times
        return rc[-1][-1]

s =Solution()
print(s.isMatch("aab","c*a*b"))
print(s.isMatch("mississippi","mis*is*p*"))
