#include "poj_1159.h"

poj_1159::poj_1159()
{
    //ctor
}

poj_1159::~poj_1159()
{
    //dtor
}

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
using namespace std;

int _palidrome(const string &s, int begin, int end) {
    if(begin == end || begin > end) {
        return 0;
    }
    if(s[begin] == s[end]) {
        return _palidrome(s, begin+1, end-1);
    }
    int pre_num = _palidrome(s, begin, end-1);
    int back_num = _palidrome(s, begin+1, end);
    return 1+(pre_num < back_num ? pre_num : back_num);
}

int palindrome(const string &s) {
    return _palidrome(s, 0, s.length()-1);
}



#define N 500
int dp_palindrome(const char *cp, short int dp[][N], int len) {
    for(int j = 1; j <= len; ++j) {
        for(int i = j-1; i > 0; --i) {
            if(cp[i-1] == cp[j-1]) {
                dp[i][j] = dp[i+1][j-1];
            }
            else {
                dp[i][j] = (dp[i+1][j] > dp[i][j-1] ? dp[i][j-1]:dp[i+1][j]) + 1;
            }
            //printf("dp[%d][%d]=%d\t", i, j, dp[i][j]);
        }
        //printf("\n");
    }
    return dp[1][len];
}

void test() {
    char ch[N];
    int n;
    short int dp[N][N];
    int i;
    while(cin>>n) {
        i = 0;
        memset(dp, 0, sizeof(dp));
        while(i < n)
            cin>>ch[i++];
        ch[n] = 0;
        //cout<<palindrome(s)<<endl;
        printf("%d\n",dp_palindrome(ch, dp, n));
    }
}

void test_poj1159() {
    test();
}

int stone(int m, int n) {
    if(m == n)
        return 1;
    else {
        if(m > n)
            return (m-n) % 2;
    }
}
