from typing import List
class Solution:
    def solveNQueens(self, n: int) -> List[List[str]]:
        rc = []
        self.value = 0
        self.dfs(0,[],[-1]*n,rc)
        return rc,self.value
    def dfs(self,index:int,tmp:List[str],res :List[int],rc:List[List[str]] ):
        if len(res) == index:
            rc.append(tmp)
            self.value+=1
            return
        else:
            for i in range(0,len(res)):
                res[index] = i
                if self.helper(res,index):
                    rv = '.' * len(res)
                    rvs = rv[0:i]+ 'Q' + rv[i+1:]
                    self.dfs(index+1,tmp+ [rvs],res,rc)
    def helper(self,res:List[int],index:int):
        for i in range(0,index):
            #column
            if res[i] == res[index]:
                return False
            # row and column (diagonal)
            if abs(res[i]-res[index]) == index-i:
                return False
        return True

s = Solution()
a,b = s.solveNQueens(9)
for group in a:
    print(group)
print(b)