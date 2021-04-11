#include <vector> 
#include <iostream>
using namespace std;
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> rv{ -1,-1 };
        int low_bound = search_range_helper(nums,target,0);
        if (low_bound == -1){
            return rv;
        }
        int high_bound = search_range_helper(nums,target,1);
        return vector<int>{low_bound,high_bound};
    }
    int search_range_helper(vector<int>& nums, int target, int flag){
        int low = 0;
        int high = nums.size() - 1;
        while(low <= high){
            int mid = (low + high) / 2;
            if (nums[mid] == target){
                if (flag){
                    if (mid == high || nums[mid + 1] != target){
                        return mid;
                    }
                    else{
                        low = mid + 1;
                    }
                }

                else{
                    if (mid == low || nums[mid-1] != target){
                        return mid;
                    }
                    else{
                        high = mid -1;
                    }
                }

            }
            else if (nums[mid] > target){
                high = mid -1;
            }
            else{
                low = mid + 1;
            }
        }
        return -1;
    }


};
int main(){
    int a[9] = {-1,0,1,2,3,4,5,6,6};
    vector<int> b;
    b.insert(b.begin(),a,a+9);
    Solution s = Solution();
    vector<int> rc = s.searchRange(b,6);
    cout<< rc[0] << rc[1] <<endl;

}
