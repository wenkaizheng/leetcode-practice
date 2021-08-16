#include <iostream>
#include<stack>
using namespace std;
struct TreeNode {
     int value;
     TreeNode *left;
     TreeNode *right;

     TreeNode() : value(0), left(nullptr), right(nullptr) {}

     TreeNode(int x) : value(x), left(nullptr), right(nullptr) {}

     TreeNode(int x, TreeNode *left, TreeNode *right) : value(x), left(left), right(right) {}
 };

void preorder(TreeNode* root){
    cout << "Pre Order:" << endl;
    if (root != nullptr){
        stack<TreeNode*> sta;
        sta.push(root);
        TreeNode* cur = root;
        while(!sta.empty()){
            cur = sta.top();
            sta.pop();
            cout << cur->value << " ";
            if (cur->right != nullptr){
                sta.push(cur->right);
            }
            if (cur->left != nullptr){
                sta.push(cur->left);
            }
        }
    }
    cout << endl;
}
void inorder(TreeNode* root){
    cout << "In Order:" << endl;
    if(root != nullptr){
        stack<TreeNode*> sta;
        TreeNode* cur = root;
        while(!sta.empty() || cur != nullptr){
            if(cur != nullptr){
                sta.push(cur);
                cur = cur->left;
            }else{
                cur = sta.top();
                sta.pop();
                cout << cur->value << " ";
                cur = cur->right;
            }
        }
    }
    cout << endl;
}

void postorder(TreeNode* root){
    cout << "Post Order:" << endl;
    if (root != nullptr){
        stack<TreeNode*> sta1;
        stack<TreeNode*> sta2;
        TreeNode* cur = root;
        sta1.push(cur);
        while(!sta1.empty()){
            cur = sta1.top();
            sta1.pop();
            sta2.push(cur);
            if(cur->left != nullptr){
                sta1.push(cur->left);
            }
            if(cur->right != nullptr){
                sta1.push(cur->right);
            }
        }
        while(!sta2.empty()){
            cur = sta2.top();
            sta2.pop();
            cout << cur->value << " ";
        }
    }
    cout << endl;
}
int main(){
    TreeNode* root = new TreeNode(0);
    TreeNode* node1 = new TreeNode(1);
    TreeNode* node2 = new TreeNode(2);
    TreeNode* node3 = new TreeNode(3);
    TreeNode* node4 = new TreeNode(4);
    TreeNode* node5 = new TreeNode(5);
    TreeNode* node6 = new TreeNode(6);
    TreeNode* node7 = new TreeNode(7);
    TreeNode* node8 = new TreeNode(8);
    TreeNode* node9 = new TreeNode(9);
    root->left = node1;
    root->right = node2;
    node1->left = node3;
    node1->right = node4;
    node2->left = node5;
    node2->right = node6;
    node3->left = node7;
    node3->right = node8;
    node4->left = node9;
    preorder(root);
    inorder(root);
    postorder(root);
    delete root;
    delete node1;
    delete node2;
    delete node3;
    delete node4;
    delete node5;
    delete node6;
    delete node7;
    delete node8;
    delete node9;

    return 0;
}