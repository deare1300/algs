#include "include/wordbreak.h"
#include <vector>
#include <set>
#include <string>
#include <iostream>

using namespace std;


WordBreak::WordBreak()
{
    //ctor
}

WordBreak::~WordBreak()
{
    //dtor
}

vector<string> WordBreak::wordBreak(string s, set<string> &dict)
{
    int len = s.length();
    vector<bool> v(len, false);
    ret.clear();
    dp.clear();
    for(int i = 0; i < len; i++)
        dp.push_back(v);
    for(int i = 0; i < len ; i++)
    {
        if(dict.find(s.substr(0, i+1)) != dict.end())
        {
            dp[0][i] = true;
        }
    }
    for(int i = 1; i < len; ++i)
    {
        for(int j = i; j < len; ++j)
        {
            if(dict.find(s.substr(i, j-i+1)) != dict.end())
            {
                dp[i][j] = true;
            }
        }
    }
    cout<<"=================================="<<endl;
    for(int i = 0; i < len; ++i)
    {
        for(int k = 0; k < i; ++k)
            cout<<"\t";
        for(int j = i; j < len; ++j)
            cout<<dp[i][j]<<"\t";
        cout<<endl;
    }
    cout<<"=================================="<<endl;
    return ret;
}

void test_word_break()
{
    WordBreak wb;
    string str("catsanddog");
    string strs[] = {"cat", "cats", "and", "sand", "dog"};
    set<string> dict(&strs[0], &strs[5]);
    wb.wordBreak(str, dict);
}
