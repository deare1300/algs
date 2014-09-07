#include "include/best_time.h"
#include "include/header.h"

Best_Time::Best_Time()
{
    //ctor
}

Best_Time::~Best_Time()
{
    //dtor
}

int Best_Time::maxProfit(vector<int> &prices)
{
    int res = 0;
    vector<int>::iterator first = prices.begin(), next = first;
    if(first == prices.end())
        return 0;
    std::advance(next, 1);
    while(next != prices.end())
    {
        if(*next > *first)
            res += *next - *first;
        ++first;
        ++next;
    }
    return res;
}
