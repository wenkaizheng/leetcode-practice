#include <iostream>
#include <vector>
#include <set>
using namespace std;
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {

        int pre = 0;
        int sum = 0;
        set<int> reminder;
        for(int i = 0; i<nums.size();i++){
            sum += nums[i];
            int cur;
            cur = sum % k;

            if (reminder.count(cur) > 0){
                return true;
            }
            reminder.insert(pre);
            pre = cur;
        }
        return false;
    }
};

int main(){
    vector<int> test{23,2,4,6,7};
    Solution s = Solution();
    std::cout << s.checkSubarraySum(test,6) << std::endl;
}