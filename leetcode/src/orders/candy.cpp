#include "include/candy.h"
#include "include/header.h"
Candy::Candy()
{
    //ctor
}

Candy::~Candy()
{
    //dtor
}

int Candy::candy(vector<int> &ratings)
{
    int len = ratings.size();
    vector<int> cand(len, 1);
    int num = 1;
    for(int i = 1; i < len; ++i)
    {
        if(ratings[i] > ratings[i-1])
            cand[i] = max(cand[i], ++num);
        else
            num = 1;
    }
    num = 1;
    for(int i = len - 1; i > 0; --i)
    {
        if(ratings[i-1] > ratings[i])
        {
            cand[i-1] = max(cand[i-1], ++num);
        }
        else
        {
            num = 1;
        }
    }
    int res = 0;
    for(int i = 0; i < len; ++i)
    {
        cout<<cand[i]<<'\t';
        res += cand[i];
    }
    cout<<endl;
    return res;

}
/*
int Candy::candy(vector<int> &ratings, int index = 0, int peek = 0)
{
    int trend = 0;
    int res = 0;
    int len = ratings.size();
    if(index >= len)
        return 0;
    if(index == len - 1)
    {
        return 1;
    }
    if(ratings[index] == ratings[index+1])
        return 1 + candy(ratings, index+1);
    trend = ratings[index+1] > ratings[index] ? 1 : -1;
    int i;
    for(i = index+1; i < len; ++i)
    {
        if(trend == 1)
        {
            if(ratings[i] <= ratings[i-1])
                break;
        }
        else if(trend == -1)
        {
            if(ratings[i] >= ratings[i-1])
                break;
        }

    }
    int top = i - index;
    res = (top+1)*top/2;
    if(trend == 1)
    {
        cout<<trend<<":"<<res<<endl;
        return res + candy(ratings, i, top);

    }
    if(trend == -1)
    {

        if(peek != 0)
            res -= min(top, peek);
        cout<<trend<<":"<<res<<endl;
        return res + candy(ratings, i);
    }
}
*/
void test_candy()
{
    int a[]={1,3,4,3,4,2,1};
    for(int i = 0; i < sizeof(a)/sizeof(int); ++i)
        cout<<a[i]<<"\t";
    cout<<endl;
    vector<int> ratings(&a[0], &a[sizeof(a)/sizeof(int)]);
    Candy c;
    cout<<c.candy(ratings)<<endl;
}
