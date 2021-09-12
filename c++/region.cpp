#include <iostream>
#include <vector>
using namespace std;
class Solution {
public:
    void DFS(vector<vector<char>>& grid, int i, int j) {
        // boundary checking
        if(i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size())
            return;
        // return if current position is of water or is already visited
        if(grid[i][j] != '1')
            return;

        // mark the current as visited
        grid[i][j] = '0';

        // do DFS in all 4 directions
        DFS(grid, i+1, j);
        DFS(grid, i, j-1);
        DFS(grid, i-1, j);
        DFS(grid, i, j+1);
    }

    int numIslands(vector<vector<char>>& grid) {
        // We can treat the matrix grid as a grid. Each Island is a
        // connected component. The task is to find no. of disconnectedd components
        // in the graph.

        int islands = 0;
        // We make each 1 as 2 in when it is visited
        for(int i = 0; i < grid.size(); i++) {
            for(int j = 0; j < grid[0].size(); j++) {
                // do DFS in case has not been visited and there is land
                if(grid[i][j] == '1') {
                    DFS(grid, i, j);
                    ++islands;
                }
            }
        }
        return islands;
    }
};
class Solution1 {
public:
    void DFS(vector<vector<char>>& board,int r,int c,int rsize,int csize){
        if(r<0||c<0||r>=rsize||c>=csize||board[r][c]!='O')return;
        board[r][c] = 'P';
        DFS(board,r+1,c,rsize,csize);
        DFS(board,r,c+1,rsize,csize);
        DFS(board,r-1,c,rsize,csize);
        DFS(board,r,c-1,rsize,csize);
    }
    void solve(vector<vector<char>>& board) {
        if(board.empty())return;
        int row = board.size(),col = board[0].size();
        for(int i=0;i<col;i++)DFS(board,0,i,row,col),DFS(board,row-1,i,row,col);
        for(int i=0;i<row;i++)DFS(board,i,0,row,col),DFS(board,i,col-1,row,col);

        for(int i=0;i<row;i++)
            for(int j=0;j<col;j++)
                if(board[i][j]=='O')board[i][j]='X';
                else if(board[i][j]=='P')board[i][j]='O';
    }
};
class Solution2 {
    void util(vector<vector<int>>& grid, int i, int j) {
        if(i<0 || j<0 || i>=grid.size() || j>=grid[0].size() || grid[i][j])
            return;
        grid[i][j] = 1;
        util(grid,i-1,j);
        util(grid,i,j-1);
        util(grid,i+1,j);
        util(grid,i,j+1);
    }
public:
    int closedIsland(vector<vector<int>>& grid) {
        int c = 0;
        int n = grid.size();
        int m = grid[0].size();
        for(int i=0; i<n; i++)
            util(grid,i,0), util(grid,i,m-1);
        for(int j=0; j<m; j++)
            util(grid,0,j), util(grid,n-1,j);
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
                if(!grid[i][j])
                    util(grid,i,j), c++;
        return c;
    }
};
int main() {
    Solution s = Solution();
    vector <vector<char>> test{
            {'1', '1', '1', '1', '0'},
            {'1', '1', '0', '1', '0'},
            {'1', '1', '0', '0', '0'},
            {'0', '0', '0', '0', '0'}
    };
    cout << s.numIslands(test) << endl;
    Solution1 s1 = Solution1();
    vector <vector<char>> test1{
            {'X', 'X', 'X', 'X'},
            {'X', 'O', 'O', 'X'},
            {'X', 'X', 'O', 'X'},
            {'X', 'O', 'X', 'X'}
    };
    s1.solve(test1);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            cout << test1[i][j] << " ";
        }
        cout << "\n";
    }
    Solution2 s2 = Solution2();
    vector <vector<int>> test2{
            {1, 1, 1, 1, 1, 1, 1, 0},
            {1, 0, 0, 0, 0, 1, 1, 0},
            {1, 0, 1, 0, 1, 1, 1, 0},
            {1, 0, 0, 0, 0, 1, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 0}};
    cout << s2.closedIsland(test2) << endl;
    return 0;
}