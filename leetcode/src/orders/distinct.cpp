#include "include/distinct.h"
#include "include/header.h"

Distinct::Distinct()
{
    //ctor
}

Distinct::~Distinct()
{
    //dtor
}

int Distinct::numDistinct(string S, string T)
{
        int slen = S.length();
        int tlen = T.length();
        vector<vector<int> > dp;
        for(int i = 0; i <= slen; ++i)
            dp.push_back(vector<int>(tlen+1, 0));
        for(int i = 0; i <= slen; ++i)
            dp[i][0] = 1;
        printTVector(dp);
        cout<<"-------------------"<<endl;
        for(int i = 1; i <= tlen; ++i)
        {
            for(int j = 1; j <= slen; ++j)
            {
                if(T[i-1] == S[j-1])
                {
                    cout<<"equal"<<dp[j-1][i]<<'\t'<<dp[j-1][i]<<endl;
                    dp[j][i] = dp[j-1][i]+dp[j-1][i-1];

                }
                else
                {
                    dp[j][i] = dp[j-1][i];
                }
            }
        }
        printTVector(dp);
        return dp[slen][tlen];
       // return dfs(S, 0, T, 0);


}

int dfs(string &S, int sIndex, string &T, int tIndex)
{
    int slen = S.length();
    int tlen = T.length();
    if(tIndex == tlen)
        return 1;
    if(slen - sIndex < tlen - tIndex)
        return 0;
    if(S[sIndex] != T[tIndex])
        return dfs(S, sIndex+1, T, tIndex);
    return dfs(S, sIndex+1, T, tIndex)+dfs(S, sIndex+1, T, tIndex+1);
}

void test_distict()
{
    Distinct ds;
    ds.numDistinct("eee", "e");
}
