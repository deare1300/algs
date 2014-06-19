#include "poj_1061.h"
#include <iostream>

poj_1061::poj_1061()
{
    //ctor
}

poj_1061::~poj_1061()
{
    //dtor
}

int gcd(int a, int b, int &x, int &y) {
    if(b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    else {
        int d = gcd(b, a%b, x, y);
        int t = x - a/b*y;
        x = y;
        y = t;
        return d;
    }
}

//(m-n)t+ kl = (x-y)
bool meeting(int x, int y, int m, int n, int l) {
    int x0, y0;
    int r;
    int d = gcd(n-m, l,x0, y0);
    r = l/d;
    if((x-y)%d != 0) {
        std::cout<<"impossible"<<std::endl;
        return false;
    }
    else {
        std::cout<<((x - y) / d * x0 % r + r) % r<<std::endl;
    }
    return true;
}

static void test() {
    int x, y, m, n, l;
    while(std::cin>>x>>y>>m>>n>>l) {
        meeting(x, y, m, n, l);
    }
}

void test_poj1061() {
    test();
}
