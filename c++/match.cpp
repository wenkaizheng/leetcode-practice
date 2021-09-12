#include <iostream>
#include <vector>
using namespace std;

int t[100][100];
vector<int> modd(100,-1);
vector<int> meven(100,-1);
vector<int> visit(100,0);

bool IsPrimer(int n)
{
    for(int i=2;i*i<=n;i++)
    {
        if(n%i==0)
            return false;
    }
    return true;
}
int dfs(int i)
{
    for(int j=0;j<100;++j)
    {
        if(t[i][j]==1&&!visit[j])
        {
            visit[j]=1;

            if(meven[j]==-1||dfs(meven[j]))
            {
                modd[i]=j;
                meven[j]=i;
                return 1;
            }
        }
    }
    return 0;
}
int main()
{
    int number;
    vector<int> even,odd;
    memset(t,0,sizeof (t));
    while(cin>>number)
    {
        for(int i=0;i<number;++i)
        {
            int temp;cin>>temp;
            if(temp%2!=0)
                odd.push_back(temp);
            else
                even.push_back(temp);
        }
        for(int i=0;i<odd.size();++i)
        {
            for(int j=0;j<even.size();++j)
            {
                if(IsPrimer(odd[i]+even[j]))
                    t[i][j]=1;
            }
        }
        // 匈牙利算法
        int res=0;
        for(int i=0;i<odd.size();++i)
        {
            if(modd[i]==-1)
            {
                for(int j=0;j<visit.size();++j)
                {
                    visit[j]=0;
                }
                res+=dfs(i);
            }
        }
        cout<<res<<endl;
        even.clear();
        odd.clear();

        for(int i=0;i<100;i++)
        {
            for(int j=0;j<100;j++)
            {
                t[i][j]=0;
            }
        }
        for(int i=0;i<100;i++)
        {
            meven[i]=-1;
            modd[i]=-1;
        }
    }
    return 0;
}