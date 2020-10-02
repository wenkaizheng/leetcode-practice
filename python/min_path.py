from typing import List
class Solution:
    def minPathSum(self, grid: List[List[int]]) -> int:
        self.m = len(grid)-1
        self.n = len(grid[0])-1
        
        return self.dfs((0,0),grid,{})
        
    def dfs(self,pos:tuple,grid: List[List[int]],coll:dict)->int:
        if pos[0] == self.m and pos[1] == self.n:
            return grid[self.m][self.n]
        if pos not in coll:
            right = (pos[0],pos[1]+1) 
            down = (pos[0]+1,pos[1])
            right_path = float("inf")
            down_path = float("inf")
            if down[0]<= self.m:
                down_path = self.dfs(down,grid,coll)
            if right[1] <= self.n:
                right_path = self.dfs(right,grid,coll)
            coll[pos] = min(right_path,down_path) + grid[pos[0]][pos[1]]
        return coll[pos]
    
s = Solution()
print(s.minPathSum([[1,3,1],[1,5,1],[4,2,1]]))