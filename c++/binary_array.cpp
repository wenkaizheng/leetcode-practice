#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
class Solution {
public:
    int numSubarraysWithSum(vector<int>& A, int S) {
        int res = 0, curSum = 0;
        unordered_map<int, int> m{{0, 1}};
        for (int num : A) {
            curSum += num;
            res += m[curSum - S];
            ++m[curSum];
        }
        return res;
    }
};
int main(){
    Solution s = Solution();
    vector<int> test{1,0,1,0,1};
    std::cout << s.numSubarraysWithSum(test,2) << std::endl;
}