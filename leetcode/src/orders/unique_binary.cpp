#include "unique_binary.h"
#include "header.h"

Unique_Binary::Unique_Binary()
{
    //ctor
}

Unique_Binary::~Unique_Binary()
{
    //dtor
}

int Unique_Binary::numTrees(int n)
{
    if(n == 0 || n == 1)
        return 1;
    vector<int> path(n+1 ,0);
    path[0] = 1;
    path[1] = 1;
    int i = 2;
    while(i <= n)
    {
        for(int j = 0; j < i; ++j)
            path[i] += path[j]*path[i-1-j];
    }
    return path[n];
}
