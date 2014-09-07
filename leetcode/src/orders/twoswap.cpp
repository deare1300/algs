#include "include/twoswap.h"
#include "include/header.h"

TwoSwap::TwoSwap()
{
    //ctor
}

TwoSwap::~TwoSwap()
{
    //dtor
}

void TwoSwap::recovery(vector<int> &a)
{
    int n = a.size();
    int target = 0;
    int pre;
    for(int i = 0; i < n-1; ++i)
    {
        if(a[i] > a[i+1])
        {
            if(target == 0)
            {
                ++target;
                pre = i;
            }
            else
            {
                swap(a[pre], a[i+1]);
                return;
            }
        }
    }
    swap(a[pre], a[pre+1]);
}

void test_swap_two()
{
    TwoSwap ts;
    vector<int> v;
    const int n = 10;
    for(int i = 1; i <= n; ++i)
        v.push_back(i);
    cout<<"---------"<<endl;
    swap(v[0], v[1]);
    printVector(v);
    ts.recovery(v);
    printVector(v);
    cout<<"---------"<<endl;
    swap(v[0], v[n/2]);
    ts.recovery(v);
    printVector(v);
    cout<<"---------"<<endl;
    swap(v[1], v[n-1]);
    ts.recovery(v);
    printVector(v);


}
