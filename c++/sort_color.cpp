#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    void sortColors(vector<int>& nums) {
        for(int i = 0, left = 0, right = nums.size() - 1; i <= right;i++){ 
            if(nums[i] ==0) swap(nums[i], nums[left++]);         
            else if(nums[i] ==2) swap(nums[i--], nums[right--]);
        }
    }
};
int main(){
    Solution s = Solution();
    int a[6] = {2,0,2,1,1,0};
    vector<int> b;
    b.insert(b.begin(),a,a+6);
    s.sortColors(b);
    for (int i=0;i<6;i++){
        cout<< b[i] <<endl;
    }
}