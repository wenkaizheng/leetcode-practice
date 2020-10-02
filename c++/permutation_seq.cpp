#include <iostream>
using namespace std;
class Solution {
public:
    string getPermutation(int n, int k) {
        string res;
        string nums = "123456789";
        int f[9] = { 1,1, 2, 6, 24, 120, 720, 5040, 40320};
        --k;
        for (int i = n; i >= 1; --i) {
            int j = k / f[i-1];
            k %= f[i-1];
            res.push_back(nums[j]);
            nums.erase(nums.begin() + j);
        }
        return res;
    }
};
int main(){
    Solution s = Solution();
    cout << s.getPermutation(5,29) << endl;
}