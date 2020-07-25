#include <iostream>
using namespace std;
class Solution {
public:
    int num;
    string s;
    Solution(int num){
         Solution::num = num;
    }
    Solution(string s){
         Solution::s= s;
    }
    string intToRoman() {
        string roman[] = {"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"};
        int integer[] = {1000,900,500,400,100,90,50,40,10,9,5,4,1};
        int length = sizeof(roman)/sizeof(roman[0]);
        string rc = "";
        for (int i = 0; i<length; i++){
            if (num == 0){
                break;
            }
            while(num >= integer[i]){
                rc += roman[i];
                num -= integer[i];
            }
        }
        return rc;
    }
    int romanToInt() {
        int rc = 0;
        int length = s.length();
        for (int i = 0; i<length; i++){
            if(s.at(i)=='M'){
                rc += 1000;
            }
            else if(s.at(i)=='D'){
                rc += 500;
            }
            else if(s.at(i) == 'C'){
                if(i!=length-1 && s.at(i+1)=='M'){
                    rc += 900;
                    i++;
                }
                else if(i!=length-1 && s.at(i+1)=='D'){
                    rc += 400;
                    i++;
                }
                else {
                    rc +=100;
                }
            }
            else if(s.at(i) == 'L'){
                rc += 50;
            }
            else if(s.at(i) == 'X'){
                if(i!=length-1 && s.at(i+1)=='C'){
                    rc += 90;
                    i++;
                }
                else if (i!=length-1 && s.at(i+1)=='L'){
                    rc += 40;
                    i++;
                }
                else {
                    rc += 10;
                }
            }
            else if(s.at(i) == 'V'){
                rc +=5;
            }
        
            else if(s.at(i) == 'I'){
                if (i!=length-1 && s.at(i+1)=='X'){
                    rc += 9;
                    i++;
                }
                else if (i!=length-1 && s.at(i+1)=='V'){
                    rc += 4;
                    i++;
                }
                
                else {
                    rc +=1;
                }
            }
        }
        return rc;
    
}
};
int main(){
     Solution* s1 = new Solution(1994);
     Solution* s2 = new Solution("MCMXCIV");
     cout << s1->intToRoman() <<endl;
     cout << s2->romanToInt() << endl;
     delete s1;
     delete s2;
}