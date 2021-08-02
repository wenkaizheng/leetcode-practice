#include <iostream>
#include<vector>
using namespace std;
class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int res = 0, mx = 0, n = nums.size();
        vector<int> len(n, 1), cnt(n, 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < i; ++j) {
                if (nums[i] <= nums[j]) continue;
                if (len[i] == len[j] + 1) cnt[i] += cnt[j];
                else if (len[i] < len[j] + 1) {
                    len[i] = len[j] + 1;
                    cnt[i] = cnt[j];
                }
            }
            mx = max(mx, len[i]);
        }
        for (int i = 0; i < n; ++i) {
            if (mx == len[i]) res += cnt[i];
        }
        return res;
    }
};
class Solution1 {
public:
    int findLength(vector<int>& A, vector<int>& B) {
        int l1=A.size(),l2=B.size();
        vector<vector<int>> dp(l1,vector<int> (l2,0));
        int mx=0;
        for(int i=0;i<l1;i++)
        {
            for(int j=0;j<l2;j++)
            {
                if(A[i]==B[j])
                {
                    if(i-1>=0&&j-1>=0)
                    {
                        dp[i][j]=dp[i-1][j-1]+1;
                        mx=max(mx,dp[i][j]);
                    }
                    else
                    {  dp[i][j]=1;mx=max(mx,dp[i][j]);}
                }
            }
        }
        return mx;

    }
};

int main(){
    Solution s = Solution();
    vector<int> test = {1,3,5,4,7};
    std::cout << s.findNumberOfLIS(test) << std::endl;
    vector<int> test1  = {1,2,3,2,1};
    vector<int> test2 = {3,2,1,4,7};
    Solution1 s1 = Solution1();
    std::cout << s1.findLength(test1,test2) << std::endl;
    return 0;
}