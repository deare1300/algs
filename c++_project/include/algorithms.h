#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "header.h"
using namespace std;

class algorithms
{
    public:
        algorithms();
        virtual ~algorithms();
    protected:
    private:
};

template<typename T>
int partion(T arr[], int start, int end)
{
    T tg = arr[start];
    while(start < end)
    {
        while(start < end && arr[end] >= tg)
            --end;
        std::swap(arr[start], arr[end]);
        while(start < end && arr[start] <= tg)
            ++start;
        std::swap(arr[start], arr[end]);
    }
    return end;
}

template<typename T>
void quick_sort(T arr[], int start, int end)
{
    if(start >= end)
        return;
    int mid = partion(arr, start, end);
    quick_sort(arr, start, mid-1);
    quick_sort(arr, mid+1, end);
}

template<typename T>
void print_arr(T arr[], int start, int end)
{
    while(start <= end)
    {
        std::cout<<arr[start]<<'\t';
    }
    std::cout<<std::endl;
}


template<typename T>
void heap_sort(T arr[], int len)
{
    if(len < 2)
        return;
    makeHeap(arr, len);
    std::swap(arr[0], arr[len-1]);
    --len;
    while(len > 1)
    {
        adjust_down(arr, 0, len);
        std::swap(arr[0], arr[len-1]);
        --len;
    }
}

template<typename T>
void adjust_down(T arr[], int i, int len)
{
    while(i < len/2)
    {
        int r = 2*i + 2;
        int l = 2*i + 1;
        int next = i;
        if(arr[i] < arr[l])
        {
            std::swap(arr[i], arr[l]);
            next = l;
        }
        if(r < len && arr[i] < arr[r])
         {
             std::swap(arr[i], arr[r]);
             next = r;
         }
         if(next == i)
            break;
         i = next;
    }
}
template<typename T>
void makeHeap(T arr[], int len)
{
    int proot = len/2-1;
    while(proot > -1)
    {
        adjust_down(arr, proot, len);
        --proot;
    }
}
void test_partion();
#endif // ALGORITHMS_H
