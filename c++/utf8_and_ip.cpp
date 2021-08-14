#include <iostream>
#include <vector>
#include <string.h>
#include <sstream>

using namespace std;

class Solution {
public:
    bool validUtf8(vector<int> &data) {
        int count = 1;
        for (auto c : data) {
            if (count == 1) {
                if ((c >> 5) == 0b110) count = 2;
                else if ((c >> 4) == 0b1110) count = 3;
                else if ((c >> 3) == 0b11110) count = 4;
                else if ((c >> 7)) return false;
            } else {
                if ((c >> 6) != 0b10) return false;
                count--;
            }
        }
        return count == 1;
    }
};

class Solution1 {
public:
    string validIPAddress(string ip) {


        if (count(ip.begin(), ip.end(), '.') == 3) {

            stringstream ss(ip);
            string word = "";
            while (getline(ss, word, '.')) {

                if (word.length() == 0 || word.length() > 3) {
                    return "Neither";
                }

                if (word[0] == '0' && word.length() != 1) {
                    return "Neither";
                }

                for (char ch:word) {

                    if (isdigit(ch) == false) return "Neither";

                }

                int val = stoi(word);

                if (val < 0 || val > 255) return "Neither";
            }
            if (ip.back() == '.') return "Neither";
            return "IPv4";


        } else if (count(ip.begin(), ip.end(), ':') == 7) {

            stringstream ss(ip);
            string word;
            while (getline(ss, word, ':')) {

                if (word.length() == 0 || word.length() > 4) {
                    return "Neither";
                }

                for (char c : word) {

                    if (!(c >= '0' && c <= '9') && !(c >= 'a' && c <= 'f') && !(c >= 'A' && c <= 'F')) return "Neither";

                }

            }

            if (ip.back() == ':') return "Neither";
            return "IPv6";
        }
        return "Neither";
    }
};

int main() {
    Solution s = Solution();
    vector<int> test{235, 140, 4};
    std::cout << s.validUtf8(test) << std::endl;
    Solution1 s1 = Solution1();
    std::cout << s1.validIPAddress("172.16.254.1") << std::endl;
    std::cout << s1.validIPAddress("2001:0db8:85a3:0:0:8A2E:0370:7334") << std::endl;
    std::cout << s1.validIPAddress("256.256.256.256")<<std::endl;
    std::cout << s1.validIPAddress("2001:0db8:85a3:0:0:8A2E:0370:7334:") << std::endl;
    return 0;
}