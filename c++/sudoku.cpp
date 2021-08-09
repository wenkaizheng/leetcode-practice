#include <iostream>
#include<vector>
#include<set>
using namespace std;
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        vector<set<int>> rows(9), cols(9), blocks(9);

        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {

                if (board[i][j] == '.') continue;

                int curr = board[i][j] - '0';
                if (rows[i].count(curr) || cols[j].count(curr) || blocks[(i/3)*3+j/3].count(curr))
                    return false;

                rows[i].insert(curr);
                cols[j].insert(curr);
                blocks[(i/3)*3+j/3].insert(curr);
            }
        }

        return true;
    }
};

class Solution1 {
public:

    bool check(vector<vector<char>> &board, int i, int j, char val)
    {
        int row = i - i%3, column = j - j%3;
        for(int x=0; x<9; x++) if(board[x][j] == val) return false;
        for(int y=0; y<9; y++) if(board[i][y] == val) return false;
        for(int x=0; x<3; x++)
            for(int y=0; y<3; y++)
                if(board[row+x][column+y] == val) return false;
        return true;
    }
    bool solveSudoku(vector<vector<char>> &board, int i, int j)
    {
        
        if(i==9) return true;
        if(j==9) return solveSudoku(board, i+1, 0);
        if(board[i][j] != '.') return solveSudoku(board, i, j+1);

        for(char c='1'; c<='9'; c++)
        {
            if(check(board, i, j, c))
            {
                board[i][j] = c;
                if(solveSudoku(board, i, j+1)) return true;
                board[i][j] = '.';
            }
        }

        return false;
    }
    bool solveSudoku(vector<vector<char>>& board) {
        return solveSudoku(board,0,0);
    }

};

int main(){
    vector<vector<char>> test {
            {'5','3','.','.','7','.','.','.','.'}
            ,{'6','.','.','1','9','5','.','.','.'}
            ,{'.','9','8','.','.','.','.','6','.'}
            ,{'8','.','.','.','6','.','.','.','3'}
            ,{'4','.','.','8','.','3','.','.','1'}
            ,{'7','.','.','.','2','.','.','.','6'}
            ,{'.','6','.','.','.','.','2','8','.'}
            ,{'.','.','.','4','1','9','.','.','5'}
            ,{'.','.','.','.','8','.','.','7','9'}
    };
    Solution s = Solution();
    Solution1 s1 = Solution1();
    std::cout << s.isValidSudoku(test) << std::endl;
    std::cout << s1.solveSudoku(test) << std::endl;
    for(int i = 0; i<9; i++){
        for(int j = 0; j<9; j++){
            std::cout << test[i][j];
        }
        std::cout << '\n';
    }
    return 0;
}
