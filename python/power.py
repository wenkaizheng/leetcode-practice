class Solution:
    def myPow(self, x: float, n: int) -> float:
        if x == 0:
            return 0
        
        if n < 0:
            return self.helper(1/x, -n)
        else:
            return self.helper(x,n)
        
    def helper(self,x:float,n:int) -> float:
        if n == 1:
            return x
        if n == 0:
            return 1.0
        if n % 2 == 0:
            return self.helper(x*x,n//2)
        else:
            return self.helper(x,n-1) * x
s = Solution()
print(s.myPow(2.0,3))      
