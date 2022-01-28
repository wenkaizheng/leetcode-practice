#include <iostream>
#include<stack>
using namespace std;
class Solution {
private:
    bool next_is_op=false;
public:
    void cal(stack<double> &sd,stack<char> &st) {
        double b=sd.top();
        sd.pop();
        double a=sd.top();
        sd.pop();
        char oper=st.top();
        st.pop();
        if(oper=='+') a=a+b;
        else if(oper=='-') a=a-b;
        else if(oper=='*') a=a*b;
        else if(oper=='/') a=a/b;
        sd.push(a);
        cout << a << endl;
        return;
    }

    bool cmp(char c1,char  c2) {
        if(c1=='(') return false;
        else if((c1=='+' || c1=='-') && (c2=='*' || c2=='/')) return false;
        cout << c1 << c2 << endl;
        return true;
    }
    // sd 40 3
    // st  + (
    int solve(string s) {
        if(s[0]=='-' || s[0]=='+') s='0'+s; //pre-leading 0
        s='('+s;
        s=s+')';
        stack<double> sd;
        stack<char> st;
        std::cout << s << std::endl;
        for(int i=0;i<s.size();i++) {
            if(s[i]=='(' || s[i]=='[' || s[i]=='{') st.push('(');
            else if(s[i]==')' || s[i]==']' || s[i]=='}') {
                while(st.top()!='(') cal(sd,st);
                st.pop();
            } else if(next_is_op) {
                // 3*5 + 8
                while(cmp(st.top(),s[i])) cal(sd,st);
                st.push(s[i]);
                next_is_op=false;
            } else {
                int j=i;
                if(s[i]=='-' || s[i]=='+') i++;
                while(isdigit(s[i])) i++;
                double d=double(stoi(s.substr(j,i-j)));
                sd.push(d);
                i--;
                next_is_op=true;
            }
        }
        cout << st.size() << endl;
        return sd.top();
    }
};
int main() {
    Solution s = Solution();
    std::cout << s.solve("3+2*{1+2*[-4/(8-6)+7]}") << std::endl;
}