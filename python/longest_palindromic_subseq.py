from typing import List
class Solution:
    def longestPalindromeSubseq(self, s: str) -> int:
        n = len(s)
        # Form a bottom-up dp 2d array
        # dp[i][j] will be 'true' if the string from index i to j is a palindrome. 
        dp = [[0] * n  for _ in range(n)]
        
        #ans = ''
        # every string with one character is a palindrome
        for i in range(n):
            dp[i][i] = 1
            #ans = s[i]
            
        for start in range(n-2, -1, -1):
            for end in range(start+1, n):             
				# palindrome condition
                if s[start] == s[end]:
                    dp[start][end] = dp[start+1][end-1] + 2;
                else:
                    dp[start][end] = max(dp[start+1][end],dp[start][end-1]);
        
        return dp[0][-1]
s = Solution()
print(s.longestPalindromeSubseq("bbbab"))