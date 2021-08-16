#include <iostream>
#include<vector>
#include <queue>
#include<map>
using namespace std;
class Solution {
public:
    bool canPartitionKSubsets(vector<int> &nums, int k) {
        int sum = 0;
        for (int num:nums)sum += num;
        if (k <= 0 || sum % k != 0)return false;
        // return true;
        vector<int> visited(nums.size(), 0);
        return canPartition(nums, visited, 0, k, 0, sum / k);
    }

    bool canPartition(vector<int> &nums, vector<int> &visited, int start_index, int k, int cur_sum, int target) {
        if (k == 1)return true;
        if (cur_sum == target)return canPartition(nums, visited, 0, k - 1, 0, target);
        for (int i = start_index; i < nums.size(); i++) {
            if (!visited[i]) {
                visited[i] = 1;
                if (canPartition(nums, visited, i + 1, k, cur_sum + nums[i], target))return true;
                visited[i] = 0;
            }
        }
        return false;
    }

};

class Solution1 {
public:
    vector<int> findClosestElements(vector<int> &arr, int k, int x) {
        vector<int> result;
        priority_queue <pair<int, int>> maxh;
        for (int i = 0; i < arr.size(); i++) {
            maxh.push({abs(arr[i] - x), arr[i]});
            if (maxh.size() > k)
                maxh.pop();
        }

        while (!maxh.empty()) {
            result.push_back(maxh.top().second);
            maxh.pop();
        }
        sort(result.begin(), result.end());
        return result;

    }
};

class Solution2 {
public:
    bool isPossibleDivide(vector<int> &nums, int k) {

        int n = nums.size();
        if (n % k != 0) {
            return false;
        }
        map<int, int> mp;

        for (int &num: nums) {
            mp[num]++;
        }
        int l = n / k;
        for (int i = 1; i <= l; i++) {
            auto it = mp.begin();
            int tmp = it->first;
            for (int j = tmp; j < tmp + k; j++) {
                if (mp.find(j) == mp.end()) {
                    return false;
                }
                mp[j]--;
                if (mp[j] == 0) {
                    mp.erase(j);
                }

            }
        }
        return true;
    }
};
int main(){
    Solution s = Solution();
    vector<int> test{4,3,2,3,5,2,1};
    std::cout << s.canPartitionKSubsets(test,4) << std::endl;

    Solution1 s1 = Solution1();
    vector<int> test1 {1,2,3,4,5};
    vector<int> rv = s1.findClosestElements(test1,4,-1);
    for(int i = 0;i<4;i++){
        std::cout << rv[i] << std::endl;
    }

    Solution2 s2 = Solution2();
    vector<int> test2 {3,2,1,2,3,4,3,4,5,9,10,11};
    std::cout <<s2.isPossibleDivide(test2,3) << std::endl;
}