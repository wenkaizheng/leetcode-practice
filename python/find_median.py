from typing import List
class Solution:
    def findMedianSortedArrays(self, nums1: List[int], nums2: List[int]) -> float:
        m = len(nums1)
        n = len(nums2)
        return (self.helper(nums1,nums2,(m+n+1)//2) + self.helper(nums1,nums2,(n+m+2)//2))/2.0
    
    def helper(self, nums1: List[int], nums2: List[int],k:int)->float:
        if len(nums1) == 0:
            return nums2[k-1]
        if len(nums2) == 0:
            return nums1[k-1]
        if k == 1:
            return min(nums1[0],nums2[0])
        i = min(len(nums1),k//2 )
        j = min(len(nums2),k//2 )
        if nums1[i-1] < nums2[j-1]:
            return self.helper(nums1[i:],nums2,k-i)
        else:
            return self.helper(nums1,nums2[j:],k-j)
        return 0

s = Solution()
print(s.findMedianSortedArrays([1,3],[2]))
print(s.findMedianSortedArrays([1,2],[3,4]))
