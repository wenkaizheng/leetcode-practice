#include <vector> // for 2D vector
#include <iostream>
using namespace std;
class Solution
{
public:
    vector<int> coll;
    vector<vector<int>> rc;
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>> &graph)
    {
        dfs(0, graph);
        return rc;
    }
    void dfs(int node, vector<vector<int>> &graph)
    {
        coll.push_back(node);
        if (node == graph.size() - 1)
        {
            rc.push_back(coll);
        }
        for (int i = 0; i < graph[node].size(); i++)
        {
            dfs(graph[node][i], graph);
        }
        // cur one should be delete for next avaliable one
        coll.pop_back();
    }
};
int main()
{
    Solution s;
    vector<vector<int>> vect{{1, 2}, {3}, {3}, {}};
    vector<vector<int>> vect1 = s.allPathsSourceTarget(vect);
    for (int i = 0; i < vect1.size(); i++)
    {
        for (int j = 0; j < vect1[i].size(); j++)
        {
            if ( j != vect1[i].size()-1)
               cout << vect1[i][j] << "->";
            else cout << vect1[i][j];
        }
        cout << endl;
    }
}