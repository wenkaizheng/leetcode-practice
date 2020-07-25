#ifndef PT
#define PT
#define SIZE (26+1)
#include <iostream>
#include <vector>
using namespace std;
namespace tree
{
class prefix_tree
{
  public:
    vector<string> arr;
    bool isLeaf;
    prefix_tree *children[SIZE];
    prefix_tree(vector<string> strs);
    ~prefix_tree(); 
    void insert(string key);
    int countChildren( prefix_tree *node,int &index);
    string walkTrie();
    void constructTrie();
    bool search(string key);
};
}
#endif