# each ij represent how many score you can win (more than opponent)
class Solution(object):
    def PredictTheWinner(self, nums):
       
         dp = [[0] * len(nums) for _ in range(len(nums))]
         for i in range(len(nums)):
                dp[i][i] = nums[i]
         for lens in range(1,len(nums)):
             i = 0
             for j in range(lens,len(nums)):
                 dp[i][j] = max(nums[j] - dp[i][j-1], nums[i] - dp[i+1][j])
                 i+= 1   
         return dp[0][-1] >= 0
        

class Solution1(object):
    def canIWin(self, maxChoosableInteger, desiredTotal):
        """
        :type maxChoosableInteger: int
        :type desiredTotal: int
        :rtype: bool
        """
        if (1 + maxChoosableInteger) * maxChoosableInteger/2 < desiredTotal:
            return False
        self.memo = {}
        return self.helper([i for i in range(1,maxChoosableInteger+1)], desiredTotal)

        
    def helper(self, nums, desiredTotal):
        
        hash = str(nums)
        if hash in self.memo:
            return self.memo[hash]
        
        if nums[-1] >= desiredTotal:
            return True
            
        for i in range(len(nums)):
            if not self.helper(nums[:i] + nums[i+1:], desiredTotal - nums[i]):
                self.memo[hash]= True
                return True
        self.memo[hash] = False
        return False

s = Solution()
s1 = Solution1()
print(s.PredictTheWinner([1,5,2]))
print(s.PredictTheWinner([1,5,6]))
print(s1.canIWin(10,11))
print(s1.canIWin(10,15))