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
                else if (len[i] == len[j]) {
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
class Solution2 {
public:
    vector<int> largestDivisibleSubset(vector<int>& nums)
    {
        std::sort(nums.begin(), nums.end());

        std::vector<int> dp(nums.size(), 1);
        std::vector<int> pre(nums.size(), -1);

        for(int i = 1; i < nums.size(); ++i){
            for(int j = 0; j < i; ++j){
                if(nums[i] % nums[j] == 0 && dp[j] == dp[i]){
                    dp[i] = dp[j] + 1;
                    pre[i] = j;
                }
            }
        }

        int maxindex = std::distance(dp.begin(), std::max_element(dp.begin(), dp.end()));
        std::vector<int> result;

        while(maxindex >= 0){
            result.push_back(nums[maxindex]);
            maxindex = pre[maxindex];
        }

        std::reverse(result.begin(), result.end());
        return result;
    }
};

class Solution4 {
public:

    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(),pairs.end());
        //cout<<pairs[1][0] <<endl;
        vector<int>lis(pairs.size(),1);
        int ans= 1;
        for(int i=1;i<pairs.size();i++)
        {
            for(int j=0;j<i;j++)
            {
                if((pairs[i][0]>pairs[j][1])&&(lis[i]==lis[j]))
                    lis[i]=1+lis[j];
                ans = max(ans,lis[i]);
            }
        }

        return ans;
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
    Solution2 s2 = Solution2();
    vector<int> test3  = {1,2,4,8};
    for (auto& i: s2.largestDivisibleSubset(test3)){
        std::cout << i;
    }
    std::cout << "\n";
    Solution4 s4 = Solution4();
    vector<vector<int>> vect1 = {
            {1,2},
            {2,3},
            {3,4},
    };
    cout << s4.findLongestChain(vect1) <<endl;
    return 0;
}