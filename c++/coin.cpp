#include <vector> // for 2D vector
#include <iostream>
#include <array>
#include <string>
#include <numeric>
using namespace std;
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> need(amount+1, amount+1);
        need[0] = 0;
        for (int c : coins)
            for (int a=c; a<=amount; a++)
                 need[a] = min(need[a], need[a-c] + 1);
        return need.back() > amount ? -1 : need.back();
    }

};

class Solution2 {
public:
    int change(int amount, vector<int>& coins) {
        
        int dp[amount + 1];
        memset(dp,0,sizeof(dp));
        dp[0] = 1;
        for (const auto & c : coins) 
            for (int i = c; i <= amount; ++i) 
                dp[i] += dp[i - c];    
        
        return dp[amount];

    }
};

class Solution3 {
public:
    int change(int amount, vector<int>& coins) {

        int dp[amount + 1];
        memset(dp,0,sizeof(dp));
        dp[0] = 1;
        for (int i = 1; i<=amount; i++) {
            for (const auto &c : coins) {
                if (i >= c) {
                    dp[i] += dp[i - c];
                }
            }
        }
        return dp[amount];

    }
};

class Solution4 {
public:
    bool canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0), target = sum >> 1;
        if (sum & 1) return false;
        vector<int> dp(target + 1, 0);
        dp[0] = 1;
        for(auto num : nums)
            for(int i = target; i >= num; i--)
                dp[i] = dp[i] || dp[i - num];
        return dp[target];
    }
};

class Solution5 {
public:
    int canPartition(vector<int>& nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0), target = sum >> 1;
        if (sum & 1) return false;
        vector<int> dp(target + 1, 0);
        dp[0] = 1;
        for(auto num : nums)
            for(int i = target; i >= num; i--)
                dp[i] += dp[i - num];
        return dp[target];
    }
};

int main(){
    Solution s = Solution(); 
    vector<int> a {1,2,5};
    vector<int> c = {1,2,5};
    vector<int> d {1,5,11,5,3,3};
    cout << s.coinChange(a,5) <<endl;
    Solution2 s2 = Solution2();
    cout << s2.change(5,c) <<endl;
    Solution3 s3 = Solution3();
    cout << s3.change(5,c) <<endl;
    Solution4 s4 = Solution4();
    cout << s4.canPartition(d) << endl;
    Solution5 s5 = Solution5();
    cout << s5.canPartition(d) << endl;
}