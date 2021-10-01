#include <iostream>
#include<string.h>
#include<vector>
#include<unordered_set>
using namespace std;
class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        vector<int> ans(n + 1);
        for (const auto& b : bookings) {
            ans[b[0] - 1] += b[2];
            ans[b[1]] -= b[2];
        }
        for (int i = 1; i < n+1; ++i)
            ans[i] += ans[i - 1];
        assert(ans.back() == 0);
        ans.pop_back();
        return ans;
    }
};
int main(){
    Solution s = Solution();
    vector<vector<int>> test {{1,2,10},{2,3,20},{2,5,25}};
    vector<int> rv = s.corpFlightBookings(test,5);
    for(int i=0;i<5;i++){
        if (i == 4){
            cout << rv[i] ;
        }
        else{
            cout << rv[i] << ",";
        }
    }
    cout << "\n";
    return 0;
}