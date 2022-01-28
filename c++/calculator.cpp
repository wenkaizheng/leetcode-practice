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
      //  cout << a << endl;
        return;
    }

    bool cmp(char c1,char  c2) {
        if(c1=='(') return false;
        else if((c1=='+' || c1=='-') && (c2=='*' || c2=='/')) return false;
       // cout << c1 << c2 << endl;
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
       // std::cout << s << std::endl;
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
       // cout << st.size() << endl;
        return sd.top();
    }
};

class Solution1 {
public:
    bool isDigit(char c) {
        if (c >= '0' && c <= '9') return true;
        return false;
    }
    int calculate(string s) {
        stack <int> pre, pre_sign;
        long long sum = 0;
        short sign = 1;
        for (int i=0; i<s.length(); ++i) {
            if (isDigit(s[i])) {
                long long num = 0;
                while (isDigit(s[i])) {
                    num = num*10 + s[i] - '0';
                    ++i;
                }
                --i;
                sum+= num*sign;
                sign = 1;
            }

            if (s[i] == '(') {
                pre.push(sum);
                pre_sign.push(sign);
                sum = 0;
                sign = 1;
            }
            if (s[i] == ')') {
                sum = pre_sign.top()*sum + pre.top();
                pre.pop();
                pre_sign.pop();
                sign = 1;
            }

            if (s[i] == '-') {
                sign = -1;
            }
        }
        return sum;
    }
};

class Solution2 {
public:
    int calculate(string s) {
        int len = s.length();
        if (len == 0) return 0;
        stack<int> stack;
        int currentNumber = 0;
        char operation = '+';
        for (int i = 0; i < len; i++) {
            char currentChar = s[i];
            if (isdigit(currentChar)) {
                currentNumber = (currentNumber * 10) + (currentChar - '0');
            }
            if (!isdigit(currentChar) && !iswspace(currentChar) || i == len - 1) {
                if (operation == '-') {
                    stack.push(-currentNumber);
                } else if (operation == '+') {
                    stack.push(currentNumber);
                } else if (operation == '*') {
                    int stackTop = stack.top();
                    stack.pop();
                    stack.push(stackTop * currentNumber);
                } else if (operation == '/') {
                    int stackTop = stack.top();
                    stack.pop();
                    stack.push(stackTop / currentNumber);
                }
                operation = currentChar;
                currentNumber = 0;
            }
        }
        int result = 0;
        while (stack.size() != 0) {
            result += stack.top();
            stack.pop();
        }
        return result;
    }
};
int main() {
   Solution s = Solution();
   std::cout << s.solve("3+2*{1+2*[-4/(8-6)+7]}") << std::endl;
   Solution1 s1 = Solution1();
   std::cout << s1.calculate("(1+(4+5+2)-3)+(6+8)") << std::endl;
   Solution2 s2 = Solution2();
   std::cout << s2.calculate("3+2-1*3/2") << std::endl;
}