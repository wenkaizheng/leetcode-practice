#include <vector> 
#include <iostream>
using namespace std;
class Solution {
public:
    int maxRotateFunction(vector<int>& A) {
        if(A.empty()) return 0;
		long long cur=0;
		long long res=0;
		long long tol=0;
		for(int i=0;i<A.size();i++){
			tol+=A[i];
			cur+=i*A[i];
		}
		res=cur;
		reverse(A.begin(),A.end());
        //cout<< tol << endl;
        //cout<< res << endl;
		for(int i=0;i<A.size();i++){
			cur=cur+tol-A.size()*A[i];
			res=max(res,cur);
		}
		return res;

    }
};
int main(){
    Solution s = Solution();
    int a[4] = {4,3,2,6};
    vector<int> b;
    b.insert(b.begin(),a,a+4);
    cout << s.maxRotateFunction(b) << endl;

}