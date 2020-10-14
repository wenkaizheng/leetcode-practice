from typing import List
class Solution:
    def combine(self, n: int, k: int) -> List[List[int]]:
           rc = []
           self.helper(0,0,n,k,rc,[])
           return rc
    def helper(self,index:int, late:int,n:int,k:int,coll:List,tmp:List):
       
        if late  == k:
            assert(late == len(tmp))
            coll.append(tmp[0:])
            return
        
        for i in range(index,n):
            tmp.append(i+1)
            self.helper(i+1,late+1, n,k,coll,tmp)
            tmp.pop()
        
s = Solution()
rc = s.combine(4,2)
for i in rc:
    print(i)