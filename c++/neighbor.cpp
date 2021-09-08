#include <iostream>
#include<vector>
using namespace  std;
class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size(), sum = 0;
        vector<int> left(n, 0);
        vector<int> right(n, 0);
        for(int i = 0; i < n; i++){
            if(i - 1 >= 0 && ratings[i - 1] < ratings[i]) left[i] = left[i - 1] + 1;
            else left[i] = 1;
            int j = n - 1 - i;
            if(j + 1 < n && ratings[j + 1] < ratings[j]) right[j] = right[j + 1] + 1;
            else right[j] = 1;
        }
        for(int i = 0; i < n; i++){
            sum += (left[i] > right[i]) ? left[i] : right[i];
        }
        return sum;
    }
};

class Solution1{
public:
    vector<int> increasing(vector<int>& arr){
        vector<int> dp(arr.size(),1);
        for(int i = 0; i< arr.size();i++){
            for(int j = 0; j<i; j++){
                if (arr[i] > arr[j]){
                    if (dp[i] == dp[j]){
                        dp[i] = dp[j] + 1;
                    }
                }
            }
        }
        return dp;
    }
    vector<int> decreasing(vector<int>& arr){
        vector<int> dp(arr.size(),1);
        for(int i = arr.size()-1; i>=0; i--){
            for(int j = arr.size()-1;j>i; j--){
                if (arr[i] > arr[j]){
                    if (dp[i] == dp[j]){
                        dp[i] = dp[j] + 1;
                    }
                }
            }
        }
        return dp;
    }
    int people(vector<int>& arr){
        vector<int> left = increasing(arr);
        vector<int> right = decreasing(arr);
        int max = 0;
        for(int i = 0; i<arr.size(); i++){
            if (max < left[i] + right[i] -1){
                max = left[i] + right[i] -1;
            }
        }
        return arr.size() - max;
    }
};

int main(){
    Solution s = Solution();
    vector<int> test{1,0,2};
    cout << s.candy(test) <<endl;
    Solution1 s1 = Solution1();
    vector<int> test1{186,186,150,200,160,130,196,200};
    cout << s1.people(test1) << endl;
}