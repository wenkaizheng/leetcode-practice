class Solution:
    def longestPalindrome(self, s: str) -> str:
        n = len(s)
        # dp[i][j] means from i to j index all inclusive
        dp = [[False] * n  for i in range(n)]
        
        ans = ''
        # every string with one character is a palindrome
        for i in range(n):
            dp[i][i] = True
            ans = s[i]
            
        maxLen = 1
        for start in range(n-1, -1, -1):
            for end in range(start+1, n):             
				
                if s[start] == s[end]:
                    # if it's a two char. string or if the remaining string is a palindrome too
                    if end - start == 1 or dp[start+1][end-1]:
                        dp[start][end] = True
                        if maxLen < end - start + 1:
                            maxLen = end - start + 1
                            ans = s[start: end+ 1]
        
        return ans
s = Solution()
print(s.longestPalindrome("aaaadqbababaq"))
        
