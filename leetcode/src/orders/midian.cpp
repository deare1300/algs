/*
#include "include/midian.h"

Midian::Midian()
{
    //ctor
}

Midian::~Midian()
{
    //dtor
}

double Midian::findMedianSortedArrays(int A[], int m, int B[], int n)
{
    int k = (m+n)/2;
    if((m+n) & 1)
        return findMinK(A, m, B, n, k);
    else
        return (findMinK(A, m, B, n, k) + findMinK(A, m, B, n, k+1))/2;
}

double Midian::findMinK(int A[], int m, int B[], int n, int k)
{
    if(n > m)
        return findMinK(B, n, A, m, k);
    int a = min(k/2, m);
    int b = k/2;
    if(A[a-1] < B[b-1])
    {
        return findMinK(A+a, m-a, B, n, k-a);
    }
    else if(B[b-1] < A[a-1])
    {
        return findMinK(A, m, B+b, n-b, k-b);
    }
    else
    {
        return A[a-1];
    }
}
*/
