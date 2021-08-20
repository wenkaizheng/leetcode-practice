#include <iostream>
#include <vector>
#include<queue>
using namespace std;
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid)
    {

        //vector<int> dir={-1,0,1,0,-1}; //used for finding all 4 adjacent coordinates
        vector<pair<int,int>> dir = {{0,1},{1,0},{0,-1},{-1,0}};
        int m=grid.size();
        int n=grid[0].size();

        queue<pair<int,int>> q;
        int fresh=0; //To keep track of all fresh oranges left
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
            {
                if(grid[i][j]==2)
                    q.push({i,j});
                if(grid[i][j]==1)
                    fresh++;
            }
        int ans=-1; //initialised to -1 since after each step we increment the time by 1 and initially all rotten oranges started at 0.
        while(!q.empty())
        {
            int sz=q.size();
            while(sz--)
            {
                pair<int,int> p=q.front();
                q.pop();
                for(int i=0;i<4;i++)
                {
                    int r=p.first+dir[i].first;
                    int c=p.second+dir[i].second;
                    if(r>=0 && r<m && c>=0 && c<n &&grid[r][c]==1)
                    {
                        grid[r][c]=2;
                        q.push({r,c});
                        fresh--; // decrement by 1 foreach fresh orange that now is rotten
                    }

                }
            }
            ans++; //incremented after each minute passes
        }
        if(fresh>0) return -1; //if fresh>0 that means there are fresh oranges left
        if(ans==-1) return 0; //we initialised with -1, so if there were no oranges it'd take 0 mins.
        return ans;

    }
};

class Solution1 {
public:

    bool isvalid(int i,int j,int m,int n)
    {
        if(i==m||j==n||j<0||i<0)
            return false;
        return true;
    }

    vector<vector<int>> dir={{1,0},{0,1},{0,-1},{-1,0}};
    int maxDistance (vector<vector<int>>& matrix)
    {
        queue<pair<int,int>> q;
        int m=matrix.size();
        int n=matrix[0].size();
        vector<vector<int>> dis(m,vector<int>(n,-1));
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++)
            {
                if(matrix[i][j]==1)
                {
                    q.push({i,j});
                    dis[i][j]=0;
                }
            }
        }
        if(q.size() == m*n or q.size()==0){
            return -1;
        }
        while(!q.empty())
        {
            pair<int,int> curr=q.front();
            q.pop();
            for(auto& x:dir)
            {
                int a=curr.first+x[0];
                int b=curr.second+x[1];
                if(isvalid(a,b,m,n)&&dis[a][b]==-1)
                {
                    q.push({a,b});
                    dis[a][b]=dis[curr.first][curr.second]+1;
                }
            }
        }
        int max = -1;
        for(int i =0; i<m;i++){
            for(int j =0;j<n; j++){
                if (dis[i][j] > max){
                    max = dis[i][j];
                }
            }
        }
        return max;
    }
};

int main(){
    Solution1 s1 = Solution1();
    vector<vector<int>> test1 {{1,0,1},{0,0,0},{1,0,1}};
    std::cout << s1.maxDistance(test1) << std::endl;

    Solution s = Solution();
    vector<vector<int>> test {{2,1,1},{1,1,0},{0,1,1}};
    std::cout << s.orangesRotting(test) << std::endl;
}