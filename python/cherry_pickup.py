from typing import List
class Solution:
    def cherryPickup(self, grid: List[List[int]]) -> int:
        N = len(grid)
        rv = {}
        def dp(r1, c1, c2):
            r2 = r1 + c1 - c2
            if (N == r1 or N == r2 or N == c1 or N == c2 or
                    grid[r1][c1] == -1 or grid[r2][c2] == -1):
                return float('-inf')
            elif r2 == c2 == N-1:
                 return grid[r2][c2]
            elif r1 == c1 == N-1:
                print(r2,c2)
                return grid[r1][c1]
            elif (r1,c1,c2) in rv:
                return rv[(r1,c1,c2)]
            else:
                ans = 0
                if c1 == c2 and r1 ==r2:
                    ans +=grid[r1][c1]
                else:
                    ans += grid[r1][c1] + grid[r2][c2]
                ans += max(dp(r1, c1+1, c2+1), dp(r1+1, c1, c2+1),
                           dp(r1, c1+1, c2), dp(r1+1, c1, c2))

            rv[(r1,c1,c2)] = ans
            return ans

        return max(0, dp(0, 0, 0))

s = Solution()
print(s.cherryPickup([[1,1,1],
                [0,0,1],
                [1,0,0]]))
