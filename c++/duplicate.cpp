#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        if (nums.size() > 1)
        {
            int slow = nums[0];
            int fast = nums[0];
            while (1)
            {
                slow = nums[slow];
                fast = nums[nums[fast]];
                if (slow == fast) break;
            }
            //std::cout << fast << slow << std::endl;

            fast = nums[0];
            while (fast != slow)
            {
                //std::cout << fast << slow << std::endl;
                fast = nums[fast];
                slow = nums[slow];
            }
            return slow;
        }
        return -1;
    }

};

int main(){
    vector<int> a {1,3,4,2,2};
    Solution s;
    cout << s.findDuplicate(a) << endl;
}