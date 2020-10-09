#include <iostream>
#include <vector>
using namespace std;
 
struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
      TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
 
class Solution {
public:
    TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
        vector<TreeNode*> stk;
        for (int i = 0; i < nums.size(); ++i)
        {
            TreeNode* cur = new TreeNode(nums[i]);
            while (!stk.empty() && stk.back()->val < nums[i])
            {
                cur->left = stk.back();
                stk.pop_back();
            }
            if (!stk.empty())
                stk.back()->right = cur;
            stk.push_back(cur);
        }
        return stk.front();
        
    }
    void in_order (TreeNode* t){
        if (!t) {
            return;
        }
        if(t->left){
            in_order(t->left);
        }
        cout << t->val << endl;
        if (t->right){
            in_order(t->right);
        }
    }
};  

int main(){
    Solution s;
    int a[6] = {3,2,1,6,0,5};
    vector<int> b;
    b.insert(b.begin(),a,a+6);
    TreeNode* rc = s.constructMaximumBinaryTree(b);
    s.in_order(rc);
    
    delete rc;
}
