from typing import List
class Solution:
    def spiralOrder(self, M: List[List[int]]) -> List[int]:
        if not M:  # corner case
            return []
        rows, cols, res = len(M), len(M[0]), []
        left, right, top, bottom, n = 0, cols - 1, 0, rows - 1, rows * cols
        while len(res) < n:
            for i in range(left, right+1):  # first row
                res.append(M[top][i])
            top += 1
            for i in range(top, bottom+1):  # last col
                res.append(M[i][right])
            right -= 1
            for i in range(right, left-1, -1):  # last row
                if len(res) >= n:
                    return res
                res.append(M[bottom][i])
            bottom -= 1
            for i in range(bottom, top-1, -1):  # first col
                if len(res) >= n:
                    return res
                res.append(M[i][left])
            left += 1
        return res
s = Solution()
print(s.spiralOrder([[1,2,3],[4,5,6],[7,8,9]]))
