#include <iostream>
#include<vector>
using namespace std;
class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> seq = {0};
        if (n == 0) {
            return seq;
        }
        
        seq = grayCode(n-1);
        int len = seq.size();
        int mask = 1 << (n-1);
        for (int i = len-1; i >= 0; i--) {
            cout << (seq[i] | mask) << endl;
            //10 00
            seq.push_back(seq[i] | mask);
        }
        return seq;
        
    }
};
int main(){
    Solution s = Solution();
    vector<int> rc =  s.grayCode(2);
    for(size_t i =0; i<rc.size();i++){
        cout<< rc[i];
    }
    cout << '\n';
}