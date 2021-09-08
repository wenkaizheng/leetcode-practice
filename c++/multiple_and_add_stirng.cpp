#include <iostream>
#include<string>
using namespace std; 
class Solution {
public:
    string multiply(string num1, string num2) {
        string sum(num1.size() + num2.size(), '0');

        for (int i = num1.size() - 1; 0 <= i; --i) {
            int carry = 0;
            for (int j = num2.size() - 1; 0 <= j; --j) {
                int tmp = (sum[i + j + 1] - '0') + (num1[i] - '0') * (num2[j] - '0') + carry;
                sum[i + j + 1] = tmp % 10 + '0';
                carry = tmp / 10;
            }
            sum[i] += carry;
        }

        size_t start_pos = sum.find_first_not_of("0");
        if (string::npos != start_pos) {
            return sum.substr(start_pos);
        }
        return "0";
    }
    string add (string a, string b){
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        auto it1 = a.begin();
        auto it2 = b.begin();
        int carry = 0;
        string c = "";
        while (it1 != a.end() && it2 != b.end()) {
            int tmp = *it1 - '0' + *it2 - '0' + carry;
            carry = tmp / 10;
            c.push_back(tmp % 10 + '0');
            ++it1;
            ++it2;
        }

        while (it1 != a.end()) {
            int tmp = *it1 - '0' + carry;
            carry = tmp / 10;
            c.push_back(tmp % 10 + '0');
            ++it1;
        }

        while (it2 != b.end()) {
            int tmp = *it2 - '0' + carry;
            carry = tmp / 10;
            c.push_back(tmp % 10 + '0');
            ++it2;
        }

        while (carry) {
            c.push_back(carry % 10 + '0');
            carry /= 10;
        }
        reverse(c.begin(), c.end());
        return c;
    }
};
int main() {
  Solution s = Solution();
  std::cout << s.multiply("199","98") << std::endl;
  std::cout <<  s.add("199","99") << std::endl;
}
