#include <iostream>
#include<vector>
#include<string>
using namespace std;
class Solution {
public:
   string shortestPalindrome(string s)
{
    int n = s.size();
    string rv(s);
    reverse(rv.begin(), rv.end());
    string s_new = s + "#" + rv;
    int size= s_new.size();
    vector<int> f(size, 0);
    for (int i = 1; i < size; i++) {
        int t = f[i - 1];
        while (t > 0 && s_new[i] != s_new[t])
            t = f[t - 1];
        if (s_new[i] == s_new[t])
            ++t;
        f[i] = t;
    }
    return rv.substr(0, n - f[size - 1]) + s;
}
};
int main(){
    Solution s = Solution();
    string a = s.shortestPalindrome("aAab");
    cout << a << endl;
    return 0;
}
