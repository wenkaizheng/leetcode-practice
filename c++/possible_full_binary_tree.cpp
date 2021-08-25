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
    vector<TreeNode*> allPossibleFBT(int N) {
        if (N % 2 == 0) return {};
        if (N == 1) return {new TreeNode(0)};
        vector<TreeNode*> res;
        for (int i = 1; i < N; i += 2) {
            vector<TreeNode*> left = allPossibleFBT(i), right = allPossibleFBT(N - i - 1);
            for (auto a : left) {
                for (auto b : right) {
                    TreeNode *cur = new TreeNode(0);
                    cur->left = a;
                    cur->right = b;
                    res.push_back(cur);
                }
            }
        }
        return res;
    }
};

void in_order (TreeNode* t){

    if (!t) {
        return;
    }

    in_order(t->left);
    cout << t->val;
    in_order(t->right);

}

int main(){
    Solution s;
    vector<TreeNode*> coll =  s.allPossibleFBT(7);
    for(auto& t: coll){
        in_order(t);
        std::cout << '\n';
    }
    return 0;
}