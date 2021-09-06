#include <iostream>
#include <vector>

using namespace std;
class bag{
public:
    int KnapSack(vector<int>& weight,vector<int>& value,int W ){
        int dp[W+1];
        memset(dp, 0, sizeof(dp));
        for(int i = 0; i< weight.size();i++){
            for(int j = W;j>=weight[i] ;j--){
                dp[j] = max(dp[j],dp[j-weight[i]]+value[i]);
            }
        }
        return dp[W];
    }
};
//total money <32000
int dp[32000];
int main() {
    int N, m;
    cin >> N >> m;

    // dp array
    vector<int> zj(m + 1), zjvw(m + 1),  fj1(m + 1),  fj2(m + 1), fj1vw(m + 1),fj2vw(m + 1);
   // m is the number of item
    for(int i = 1; i <= m; i++)
    {
        int v, p, q;
        cin >> v >> p >> q;
        // main
        if(q == 0)
        {
            zj[i] = v;
            zjvw[i] = v * p;
        }
        // item1
        else if(fj1[q] == 0)
        {
            fj1[q] = v;
            fj1vw[q] = v * p;
        }
        // item2
        else if(fj2[q] == 0)
        {
            fj2[q] = v;
            fj2vw[q] = v * p;
        }
    }
    for(int i = 1; i <= m; i++)
    {
        for(int j = N; j >=1; j--)
        {
            // main
            if(j >= zj[i])
                dp[j] = max(dp[j], dp[j - zj[i] ] + zjvw[i]);
            // main + item1
            if(j >= zj[i] + fj1[i]) {
                dp[j] = max(dp[j], dp[j - zj[i] - fj1[i]] + zjvw[i] + fj1vw[i]);
            }
            // main  + item2
            if(j >= zj[i] + fj2[i]) {
                dp[j] = max(dp[j], dp[j - zj[i] - fj2[i]] + zjvw[i] + fj2vw[i]);
            }
           // main  + item1 + item2
            if(j >= zj[i] + fj1[i] + fj2[i]) {
                dp[j] = max(dp[j], dp[j - zj[i] - fj1[i] - fj2[i]] + zjvw[i] + fj1vw[i] + fj2vw[i]);
            }
        }
    }
    cout <<dp[N] << endl;
    bag b = bag();
    std::vector<int> value {7,8,4};
    std:: vector<int> weight{3,8,6};
    std::cout<< b.KnapSack(weight,value,10) << std::endl;
    return 0;
}