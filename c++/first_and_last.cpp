#include <vector> 
#include <iostream>
using namespace std;
class Solution {
public:
  vector<int> searchRange(vector<int>& nums, int target) {
    int start = 0, end = nums.size(), mid, left, right;
    while (start < end) {
        mid = (start + end) / 2;
        if (nums[mid] >= target)
            end = mid;
        else
            start = mid + 1;
    }
    left = start;
    end = nums.size();
    while (start < end) {
        mid = (start + end) / 2;
        if (nums[mid] > target)
            end = mid;
        else
            start = mid + 1;
    }
    right = start;
    //cout << right << left << endl;
    return left == right ? vector<int> {-1,-1} : vector<int> {left,right-1};
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
