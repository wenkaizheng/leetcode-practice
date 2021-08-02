#include <iostream>
#include<vector>
using namespace std;
class Solution1 {
public:
    int jump(vector<int>& nums) {
        int res = 0, n = nums.size(), i = 0, cur = 0;
        while (cur < n - 1) {
            ++res;
            int pre = cur;
            for (; i <= pre; ++i) {
                cur = max(cur, i + nums[i]);
            }
        }
        return res;
    }
};

class Solution {
public:
    bool canJump(vector<int>& nums) {
        vector<bool> dp(nums.size(), false);
        dp[nums.size()-1] = true;
        int check = nums.size()-1;
        for(int i=nums.size()-2; i>=0; i--){
            if(nums[i]+i>=check){
                dp[i] = true;
                check = i;                // Every time we update our check index
            }
        }
        return dp[0];
    }
};

int main(){

    Solution s = Solution();
    Solution1 s1 = Solution1();
    vector<int> test = {2,3,1,1,4};
    std::cout << s.canJump(test) << std::endl;
    std::cout << s1.jump(test) << std::endl;
    return 0;
}