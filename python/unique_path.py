class Solution:
    def uniquePaths(self, m: int, n: int) -> int:
        rc = [[ 0 for i in range(0,m)] for j in range(0,n)]
        for i in range(0,n):
            for j in range(0,m):
                if i == 0 or j == 0:
                    rc[i][j] = 1
                else:
                    rc[i][j] =  rc[i-1][j] + rc[i][j-1]
        return rc[-1][-1]
s = Solution()
print(s.uniquePaths(3,7))
print(s.uniquePaths(3,2))
