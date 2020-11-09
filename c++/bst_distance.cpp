#include <iostream>
#include <vector>
using namespace std;
typedef struct node{
    int key;
    struct node* left;
    struct node* right;
    node(int x):key(x),left(nullptr),right(nullptr){}
}node;


node* insert(int key, node* root){
    if(root == nullptr){
        return new node(key);
    }
    if(key < root->key){
        root->left = insert(key,root->left);
    }
    else if(key > root->key){
        root->right = insert(key,root->right);
    }
    return root;
}
node* find_ancestor(node* root,int a ,int b){
    if(root == nullptr){
        return nullptr;
    }
    if(root->key == a  || root->key == b){
        return root;
    }
    node* left = find_ancestor(root->left,a,b);
    node* right = find_ancestor(root->right,a,b);
    // four situations to be listed  
    if (left != nullptr && right!=nullptr){
       return root;
    }
    if(left == nullptr && right == nullptr){
        return nullptr;
    }
    if(left!= nullptr && right == nullptr){
        return find_ancestor(root->left,a,b);
    }
    return find_ancestor(root->right,a,b);
}
int level(node* root,int start, int find){
    if(root == nullptr){
        return -1;
    }
    if(find == root->key){
        return start;
    }
    int left = level(root->left,start +1,find);
    if(left != -1){
        return left;
    }
    return level(root->right,start +1,find);
}
int BSTdistance(const vector<int>& values, int nodeA, int nodeB)
{
    int checkA = 0;
    int checkB = 0;
    for(int i:values){
        if(i == nodeA){
            checkA = 1;
        }
        if (i == nodeB){
            checkB =1;
        }
    }
    if ( !(nodeA && nodeB)){
        return -1;
    }
    node* root = nullptr;
    for(int i: values){
      root = insert(i,root);
    }
    
    node* ancestor = find_ancestor(root,nodeA,nodeB);
    int a =  level(ancestor,0,nodeB);
    int b =  level(ancestor,0,nodeA);
    

    return a+b;
}
int main() {
 int rc =  BSTdistance({ 8, 7, 13, 6, 2, 5, 1, 9, 11, 3, 4, 10}, 4, 2);
 cout << rc <<endl;
}