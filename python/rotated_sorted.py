from typing import List
class Solution:
    def search(self, nums: List[int], target: int) -> int:
        start = 0
        end = len(nums)-1
        while start <= end:
            mid = (start + end) // 2
            if target == nums[mid]:
                return mid
            if mid == start == end:
                return -1
            if nums[start] <= nums[mid]:
                if nums[start] <= target < nums[mid]:
                    end  = mid-1
                else:
                    start = mid + 1
            else:
                if nums[mid] < target < nums[start]:
                    start = mid + 1
                else:
                    end = mid-1
        return -1
s = Solution()
print(s.search([4,5,6,7,0,1,2],0))
print(s.search([4,5,6,7,0,1,2],3))               
