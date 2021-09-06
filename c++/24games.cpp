#include <iostream>
#include<string.h>
#include<vector>
#include<unordered_set>
using namespace  std;
class Solution {
public:
    vector<string> judgePoint24_All(vector<int>& nums) {
        unordered_set<string> res;
        double eps = 0.001;
        vector<char> ops{'+', '-', '*', '/'};
        vector<double> arr(nums.begin(), nums.end());
        vector<string> vec;
        for (int num : nums) vec.push_back(to_string(num));
        helper(arr, ops, eps, vec, res);
        return vector<string>(res.begin(), res.end());
    }
    void helper(vector<double>& nums, vector<char>& ops, double eps, vector<string>& vec, unordered_set<string>& res) {
        if (nums.size() == 1) {
            if (abs(nums[0] - 24) < eps) res.insert(vec[0]);
            return;
        }
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = 0; j < nums.size(); ++j) {
                if (i == j) continue;
                vector<double> t;
                vector<string> v;
                for (int k = 0; k < nums.size(); ++k) {
                    if (k != i && k != j) {
                        t.push_back(nums[k]);
                        v.push_back(vec[k]);
                    }
                }
                for (char op : ops) {
                    if ((op == '+' || op == '*') && i > j) continue;
                    if (op == '/' && nums[j] < eps) continue;
                    switch(op) {
                        case '+':
                            t.push_back(nums[i] + nums[j]);
                            v.push_back("(" + vec[i] + "+" + vec[j] + ")");
                            break;
                        case '-':
                            t.push_back(nums[i] - nums[j]);
                            v.push_back("(" + vec[i] + "-" + vec[j] + ")");
                            break;
                        case '*':
                            t.push_back(nums[i] * nums[j]);
                            v.push_back("(" + vec[i] + "*" + vec[j] + ")");
                            break;
                        case '/':
                            t.push_back(nums[i] / nums[j]);
                            v.push_back("(" + vec[i] + "/" + vec[j] + ")");
                            break;
                    }
                    helper(t, ops, eps, v, res);
                    t.pop_back();
                    v.pop_back();
                }
            }
        }
    }
};
int main() {
    Solution s = Solution();
    vector<int> a{4,6,7,8};
    for (auto& a: s.judgePoint24_All(a)){
        std::cout << a << std::endl;
    }
}