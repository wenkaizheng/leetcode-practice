#include <iostream>
#include<vector>
using namespace std;
class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>>res;
        DFS(res, nums, 0);
        return res;        
    }
    
    void DFS(vector<vector<int>>& res, vector<int>& nums, int pos){
        if(pos == nums.size() - 1){
            res.push_back(nums);
            return;
        }
        for(int i = pos; i < nums.size(); i++){
            swap(nums[pos], nums[i]);
            DFS(res, nums, pos + 1);
            swap(nums[pos], nums[i]);
        }
    }
};
int main(){
    Solution s = Solution();
    vector<int> group = {1,2,3};
    vector<vector<int>> rc = s.permute(group);
    size_t r = rc.size();
    for(int i=0;i<r;i++){
        for(int j =0 ;j<3;j++){
            cout << rc[i][j];
        }
        cout << "\n";
    }
}