#include <iostream>
#include<string>
using namespace std; 
class Solution {
public:
    string multiply(string num1, string num2) {
       
        int len1 = (int)num1.size();
	int len2 = (int) num2.size();
	string result(len1 + len2, '0');
	for (int i = len1-1; i >= 0; --i) {
	      for (int j = len2-1; j >= 0; --j) {
			//	int value = (num1[i] - '0') * (num2[j] - '0')+(result[i + j + 1 ] - '0');
                int v1 = num1[i] - '0';
                int v2 = num2[j] - '0';
                int v3 = result[i+j+1] -'0';
                int value = v1*v2 + v3;
		result[i + j ] += value / 10;
		result[i + j + 1] = (value % 10)  + '0';
	    }
	}
        cout << result << endl;
        int  p = 0;
        while (p < len1+len2-1 && result[p] == '0'){
            p++;
        }
        return result.substr(p, len1 + len2 -p);
	
    }
};
int main() {
  Solution s = Solution();
  s.multiply("199","99");
  std::cout << "Hello World!\n";
}
