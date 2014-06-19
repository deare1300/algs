#include "algorithms.h"

algorithms::algorithms()
{
    //ctor
}

algorithms::~algorithms()
{
    //dtor
}

void test_partion()
{
    int arr[] = {1,2,3,4,5,6,9,8,7,6,5,4,3,2,1,0,7,8,9,0};
    int size = sizeof(arr)/sizeof(int);
    for(int i = 0; i < sizeof(arr)/sizeof(int); ++i)
        cout<<arr[i]<<'\t';
    cout<<endl;
   // int r = partion(arr, 0, sizeof(arr)/sizeof(int));
   // quick_sort(arr, 0, size);
   heap_sort(arr, size);
    for(int i = 0; i < sizeof(arr)/sizeof(int); ++i)
        cout<<arr[i]<<'\t';
    cout<<endl;
}
