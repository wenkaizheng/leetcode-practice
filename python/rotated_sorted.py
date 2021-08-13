from typing import List
class Solution:
    def search(self, nums: List[int], target: int) -> int:
        start = 0
        end = len(nums)-1
        while start <= end:
            mid = (start + end) // 2
            if target == nums[mid]:
                return mid
            #[0,1,2] 
            elif target == nums[start]:
               return start
            elif target == nums[end]:
                return end
            # [1,3] find 3
            if nums[start] < nums[mid]:
                if nums[start] < target < nums[mid]:
                    end  = mid-1
                else:
                    start = mid + 1
            elif nums[start] > nums[mid]:
                #assert(nums[start]!=nums[mid])
                if nums[mid] < target < nums[start]:
                    start = mid + 1
                else:
                    end = mid-1
            else:
                return -1;
        return -1
        
        #[7,0,1,2,4,5,6]
        
    def search2(self,nums:List[int],target:int) -> int:
        if not nums: 
            return 0
        
        low = 0
        high = len(nums)-1 
        #[0,0,1,2,2,5,6]
        #[2,5,6,0,0,1,2]
        #[1,2,2,5,6,0,0] 
        while low<=high:

            mid = (low+high)//2

            if nums[mid] == target or nums[low] == target : 
                return 1 
           
            if nums[mid]<nums[low]:
                if nums[mid]<target<nums[low]:
                    low = mid+1
                else:
                    high = mid-1
          
          
            elif nums[mid]>nums[low]:
           
                 if nums[low] < target < nums[mid]:
                    high = mid-1
                 else:
                    low = mid+1
              
            else:
                 
                  low+=1
                 
        return 0
        
s = Solution()
print(s.search([4,5,6,7,0,1,2],0))
print(s.search([4,5,6,7,0,1,2],3))
print(s.search2([2,5,6,0,0,1,2],0))
print(s.search2([2,5,6,0,0,1,2],3))
