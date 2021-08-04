#include <iostream>
#include <vector>
using namespace std;
class Solution{
    public:
        vector<int> spiralOrder(vector<vector<int>>& m) {
            int rows = m.size();
            int cols = m[0].size();
            int n = rows * cols;
            vector<int> rv;
            int left = 0;
            int right = cols-1;
            int top = 0;
            int bottom = rows - 1;
            while(rv.size() < n){
                for(int i = left; i < right+1; i++){
                    rv.push_back(m[top][i]);
                }
                top += 1;
                for(int i = top; i<bottom+1; i++){
                    rv.push_back(m[i][right]);
                }
                right -= 1;
                for (int i = right; i>left-1; i--){
                    if (rv.size()<n){
                        rv.push_back(m[bottom][i]);
                    }
                }
                bottom -= 1;
                for(int i = bottom; i>top-1; i--){
                    if(rv.size()<n){
                        rv.push_back(m[i][left]);
                    }
                }
                left += 1;

            }
            return rv;

        }
    };

class Solution1 {
public:

    vector<vector<int>> generateMatrix(int n) {

        vector<vector<int>> result (n, vector<int>(n));
        int cnt = 1;
        for (int layer = 0; layer < (n+1) / 2; layer++) {
            // direction 1 - traverse from left to right
            for (int ptr = layer; ptr < n - layer; ptr++) {
                result[layer][ptr] = cnt++;
            }
            // direction 2 - traverse from top to bottom
            for (int ptr = layer + 1; ptr < n - layer; ptr++) {
                result[ptr][n - layer - 1] = cnt++;
            }
            // direction 3 - traverse from right to left
            for (int ptr = n - layer - 2; ptr >= layer; ptr--) {
                result[n - layer - 1][ptr] = cnt++;
            }
            // direction 4 - traverse from bottom to top
            for (int ptr = n - layer - 2; ptr > layer; ptr--) {
                result[ptr][layer] = cnt++;
            }

        }

        return result;
    }
};

int main(){
    Solution s = Solution();
    vector<vector<int>> test{
            {1,2,3},
            {4,5,6},
            {7,8,9}
    };
    vector<int> rv = s.spiralOrder(test);
    for(int i = 0; i<9; i++){
        cout << rv[i] << endl;
    }
    Solution1 s1 = Solution1();
    vector<vector<int>> rv1 = s1.generateMatrix(3);

    for(int i = 0; i<3; i++){
        for(int j = 0; j<3; j++) {
            cout << rv1[i][j] << endl;
        }
    }
}