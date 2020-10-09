# Definition for a binary tree node.
class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right
from typing import List
class Solution:
    def rightSideView(self, root: TreeNode) -> List[int]:
        if not root:
            return []
        rc = [root.val]
        rv = [root]
        while rv:
            level = []
            for node in rv:
                print(node.val)
                if node.left:
                     level.append(node.left) 
                if node.right:
                     print("19th")
                     level.append(node.right) 
            if level:
                print("21th")
                rc.append(level[-1].val)
            rv = level
        return rc