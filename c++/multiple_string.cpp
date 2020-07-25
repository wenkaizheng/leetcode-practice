#include <iostream>
#include<string>
using namespace std; 
class Solution {
public:
    string multiply(string num1, string num2) {
        size_t len1(num1.size());
		size_t len2(num2.size());
		string result(len1 + len2, '0');
		for (size_t i = len1; i >= 1; --i) {
			int carry(0);
			for (size_t j = len2; j >= 1; --j) {
				int value = (num1[i - 1] - '0') * (num2[j - 1] - '0');
				value += result[i + j - 1] - '0';
				value += carry;
				result[i + j - 1] = value % 10 + '0';
				carry = value / 10;
			}
			result[i - 1] = carry + '0';
		}
        cout << result << endl;
		for (size_t i = 0; i < len1 + len2; ++i) {
			if (result[i] != '0')
				return result.substr(i, len1 + len2 - i);
		}
		return string(1, '0');
	
    }
};
int main() {
  Solution s = Solution();
  s.multiply("199","99");
  std::cout << "Hello World!\n";
}
