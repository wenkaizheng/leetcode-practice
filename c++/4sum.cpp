#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
	vector<vector<int>> fourSum(vector<int> &nums, int target)
	{

		std::vector<std::vector<int>> result;
		std::size_t n = nums.size();
		if (n < 4)
		{
			return result;
		}

		std::sort(nums.begin(), nums.end());
		for (int i = 0; i < n - 3; ++i)
		{

			if (target <= 0 and nums[i] > 0)
				break;

			if (nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3] > target)
				break;

			if (nums[i] + nums[n - 3] + nums[n - 2] + nums[n - 1] < target)
				continue;

			if (i > 0 and nums[i] == nums[i - 1])
				continue;

			for (int j = i + 1; j < n - 2; ++j)
			{

				if (nums[i] + nums[j] + nums[j + 1] + nums[j + 2] > target)
					break;

				if (nums[i] + nums[j] + nums[n - 2] + nums[n - 1] < target)
					continue;
				if (j > i + 1 and nums[j] == nums[j - 1])
					continue;

				int left = j + 1, right = n - 1;
				while (left < right)
				{
					int sum = nums[i] + nums[j] + nums[left] + nums[right];
					if (sum == target)
					{
						result.push_back({nums[i], nums[j], nums[left], nums[right]});

						int last_left = nums[left], last_right = nums[right];

						while (left < right and nums[left] == last_left)
							++left;
						while (left < right and nums[right] == last_right)
							--right;
					}
					else if (sum < target)
					{
						++left;
					}
					else
					{
						--right;
					}
				}
			}
		}
		return result;
	}
};
int main(){
	Solution s;
	int a[6] = {-1,0,1,2,-1,-4};
    vector<int> b;
    b.insert(b.begin(),a,a+6);
    vector<vector<int>> vec = s.fourSum(b,0);
    for (int i = 0; i<vec.size();i++)
       for(int j = 0; j<vec[i].size();j++)
           cout << vec[i][j] << endl;
}
