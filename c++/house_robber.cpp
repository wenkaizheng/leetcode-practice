#include <iostream>
using namespace std;
#define max(a, b) ((a)>(b)?(a):(b))
class Solution {
    public:
    static int rob(int num[], int s, int n) {
        int a = 0;
        int b = 0;
        int last_index = -1;
        for (int i = s; i < n; i++) {
            if (i % 2 == 0) {
                last_index = 0;
                a = max(a + num[i], b);
            } else {
                last_index = 1;
                b = max(a, b + num[i]);
            }
        }
        if (last_index == 1) {
            return b;
        } else {
            return a;
        }

        //return max(a, b);
    }
};
int rob(int* nums, int numsSize){
    if (numsSize < 2) {
        return nums[0];
    }
    return max(Solution::rob(nums,0,numsSize-2),Solution::rob(nums,1,numsSize-1));
}

 struct TreeNode {
         int val;
         TreeNode *left;
         TreeNode *right;
         TreeNode() : val(0), left(nullptr), right(nullptr) {}
         TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
         TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution1 {
public:
    int tryRob(TreeNode* root, int& l, int& r) {
        if (!root)
            return 0;

        int ll = 0, lr = 0, rl = 0, rr = 0;
        l = tryRob(root->left, ll, lr);
        r = tryRob(root->right, rl, rr);

        return max(root->val + ll + lr + rl + rr, l + r);
    }

    int rob(TreeNode* root) {
        int l, r;
        return tryRob(root, l, r);
    }
};

int main(){
    TreeNode* root = new TreeNode(3);
    TreeNode* node1 = new TreeNode(4);
    TreeNode* node2 = new TreeNode(5);
    TreeNode* node3 = new TreeNode(1);
    TreeNode* node4 = new TreeNode(3);
    TreeNode* node5 = new TreeNode(1);
    root->left = node1;
    root->right = node2;
    node1->left= node3;
    node1->right = node4;
    node2->right = node5;
    Solution1 s1 = Solution1();
    std::cout << s1.rob(root) << std::endl;
    int test[5] = {2,7,9,3,1};
    std::cout << rob(test,5) << std::endl;
    std::cout << rob(test,5) << std::endl;
    std::cout << Solution::rob(test,0,5) << std::endl;
    delete root;
    delete node1;
    delete node2;
    delete node3;
    delete node4;
    delete node5;
}