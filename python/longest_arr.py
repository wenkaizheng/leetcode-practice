from typing import List
import bisect
#CONSECUTIVE
class Solution:
   def longestConsecutive(self, nums):
        nums = set(nums)
        best = 0
        for x in nums:
            if x + 1 not in nums:
                 y = x - 1
                 while y in nums:
                    y -= 1
                 best = max(best,x-y)
        return best
# COMMON PREFIX
class Solution1:
    def longestCommonPrefix(self, strs: List[str]) -> str:
        if not strs: return ''
        m, M, i = min(strs), max(strs), 0
        
        for i in range(min(len(m),len(M))):
            if m[i] != M[i]: break
            else: i += 1
        return m[:i]
#INCREASING
class Solution2:
    def lengthOfLIS(self,nums: List[int]) ->int:
        helper = []
        for num in nums:
            pos = bisect.bisect_left(helper, num)
            if (pos == len(helper)):
                helper.append(num)
            else:
                helper[pos] = num 
        return len(helper)                     
#DIFFERENCE
class Solution3:
    def longestSubsequence(self, arr: List[int], diff: int) -> int:
        res = {}
        for num in arr:
            res[num] = res[num - diff] + 1 if (num - diff) in res else 1
        return max(res.values())

#INTERVAL
class Solution4:
    def longestWPI(self, hours):
        res = score = 0
        seen = {}
        seen[0] = -1
        for i, h in enumerate(hours):
            score = score + 1 if h > 8 else score - 1
            if score > 0:
                res = i - seen[0]
                continue
            if score not in seen:
                seen[score] = i
            if score - 1 in seen:
                res = max(res, i - seen[score - 1])
        return res   
#SAME NUMBER WOTH 0 AND ZERO
class Solution5:
    def findMaxLength(self,nums):
        res = sums = 0
        n = len(nums)
        m = {}
        m[0] = -1
        for i in range(0,n):
            sums += 1 if nums[i] else -1
            if sums in m:
                res = max(res,i-m[sums])
            else:
                m[sums] = i
        return res   


class Solution6:
    def maxSubArrayLen(self,nums,k):
        res = 0
        sums = 0
        m = {}
        m[0] = -1
        for i in range(0,len(nums)):
            sums += nums[i]
            if sums not in m:
                m[sums] = i     
            if sums -k in m:
                res = max(res,i-m[sums-k])      
                
        return res                     

s = Solution()
print(s.longestConsecutive([100,4,200,1,3,2]))
s1 = Solution1()
print(s1.longestCommonPrefix(["flower","flow","flight"]))
s2 = Solution2()
print(s2.lengthOfLIS([10,9,2,5,3,7,101,18]))
s3 = Solution3()   
print(s3.longestSubsequence([1,5,7,8,5,3,4,2,1],-2))
s4 = Solution4()
print(s4.longestWPI([9,9,6,0,6,6,9]))
s5 = Solution5()
print(s5.findMaxLength([0,1,1,0,0,1,1]))
s6 = Solution6()
print(s6.maxSubArrayLen([1,-1,5,-2,3],3))
               