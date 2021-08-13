#include <iostream>
#include <vector>
#include <deque>
#include <unordered_map>
using namespace std;
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        vector<int> res;
        deque<int> q;
        for (int i = 0; i < nums.size(); ++i) {
            if (!q.empty() && q.front() == i - k) q.pop_front();
            while (!q.empty() && nums[q.back()] < nums[i]) q.pop_back();
            q.push_back(i);
            if (i >= k - 1) res.push_back(nums[q.front()]);
        }
        return res;
    }
};

class Solution1 {
public:
    int equalSubstring(string s, string t, int k) {
        int n = s.length(), j;
        int diff[n];
        for (j = 0; j < n; ++j) {
            diff[j] = (s[j] - t[j]) >0? s[j] - t[j]: t[j]-s[j] ;
        }
        int start = 0;
        int rv = INT_MIN;
        int cost = 0;
        for (j = 0; j<n ; j++){
            cost += diff[j];
            while(cost >  k){
                cost -= diff[start];
                start ++;
            }
            rv = max(rv,j-start + 1);
        }
        //std::cout << i << std::endl;
        return rv;
    }
};

class Solution2 {
public:
    int minSubArrayLen(int s, vector<int>& nums)
    {
        int n = nums.size();
        int ans = INT_MAX;
        int left = 0;
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += nums[i];
            while (sum >= s) {
                //  if(sum == s){
                ans = min(ans, i + 1 - left);
                //}
                sum -= nums[left];
                left ++;
            }
        }
        return (ans != INT_MAX ) ? ans : 0;
    }
};
class Solution3 {
public:
    int characterReplacement(string s, int k) {
        if(s.length()==0) return 0;
        int low = 0, most_frequent_count = 0, max_length = 1;
        unordered_map<char, int> letters;
        for(int high = 0; high < s.length(); high++) {
            int current_letter_count = ++letters[s[high]];
            most_frequent_count = max(most_frequent_count, current_letter_count);
            if(high-low+1 - most_frequent_count > k) {
                letters[s[low]]--;
                low++;
            }
            max_length = max(max_length, high-low+1);
        }
        return max_length;

    }
};

class Solution4 {
public:
    int maxSatisfied(vector<int>& customers, vector<int>& grumpy, int X) {
        int sum = 0, start = 0, total = 0, max_sum = 0;
        for(int i = 0; i < customers.size(); i++){
            if(i - start < X){
                //Window size smaller than X, add entry
                if(grumpy[i]) sum += customers[i];
            }else{
                //Window size exceeds, move window
                if(grumpy[start]) sum -= customers[start];
                if(grumpy[i]) sum += customers[i];
                start++;
            }
            //Keep track of max_sum of unsatisfied customers in sliding window
            max_sum = max(max_sum, sum);
            //Keep track of total customers satisfied
            if(!grumpy[i]) total += customers[i];
        }

        return total+max_sum;
    }
};

int main(){
    vector<int> list2 {2,3,1,2,4,3};
    Solution2 s2;
    cout << s2.minSubArrayLen(7,list2) << endl;

    vector<int> list {1,3,-1,-3,5,3,6,7};
    Solution s;
    vector<int> rv = s.maxSlidingWindow(list,3);
    for (int& i : rv) {
        cout << i << endl;
    }

    Solution1 s1;
    string a = "abcde";
    string b = "bcdf";
    cout << s1.equalSubstring(a,b,3) <<endl;

    Solution3 s3;
    cout << s3.characterReplacement("AABABBA",1) << endl;
    cout << s3.characterReplacement("ABAB",2) << endl;

    Solution4 s4;
    vector<int> test{1,0,1,2,1,1,7,5};
    vector<int> test1{0,1,0,1,0,1,0,1};
    std::cout << s4.maxSatisfied(test,test1,3) << std::endl;
    return 0;

}