from typing import List
class Solution:
    def maxSubArray(self, nums: List[int]) -> int:
        if len(nums) == 0:
            return 0
        else:
            max_value = nums[0]
            dp = [max_value] * len(nums)
            for i in range(1,len(nums)):
                dp[i]= nums[i]+dp[i-1] if dp[i-1]>0  else nums[i] 
                max_value = max(max_value,dp[i])
            return max_value
class Solution1:
    def maxProduct(self, nums: List[int]) -> int:
        max_rc = nums[0]
       # min_rc = nums[0]
        max_dp = [0]*len(nums)
        min_dp = [0]*len(nums)
        max_dp[0] = max_rc
        min_dp[0] = max_rc
        for i in range(1,len(nums)):
            if nums[i] > 0:
                max_dp[i] = max(nums[i],max_dp[i-1]*nums[i])
                min_dp[i] = min(nums[i],min_dp[i-1]*nums[i])
            else:
                max_dp[i] = max(nums[i],min_dp[i-1]* nums[i])
                min_dp[i] = min(nums[i],max_dp[i-1]*nums[i])
            max_rc = max(max_dp[i],max_rc)
        return max_rc

s = Solution()
s1 = Solution1()
print(s.maxSubArray([-2,1,-3,4,-1,2,1,-5,4]))
print(s1.maxProduct([2,3,-2,4]))             