#include <vector> // for 2D vector
#include <iostream>
#include <array>
#include <string>
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

int main(){
    Solution s = Solution(); 
    vector<int> a {1,2,5};
    vector<int> c = {1,2,5};
    cout << s.coinChange(a,5) <<endl;
    Solution2 s2 = Solution2();
    cout << s2.change(5,c) <<endl;
}