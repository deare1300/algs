#include "include/interview/youdao.h"
#include "include/interview/yahoo.h"
#include "include/leetcode/print.h"
#include <iostream>
using namespace std;

int test_interview() {
    YouDao<int> yd;
    int a[] = {2, 3, 4, 1};
    cout<<"all permutation"<<endl;
    YouDao<int>::all_permutation(a, sizeof(a)/sizeof(int));

    cout<<"get array"<<endl;
    Yahoo<int> yahoo;
    int aa[] = { 1, 2, 3, 4, 5};
    const int len = sizeof(aa)/sizeof(int);
    int b[len];
    dump(&aa[0], &aa[len]);
    Yahoo<int>::get_array(aa, b, len);
    dump(&b[0], &b[len]);

    cout<<"find two tiems number"<<endl;
    int a3[] = { 1, 1, 1, 1, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4};
    cout<<Yahoo<int>::find_two_times(a3, sizeof(a3)/sizeof(int))<<endl;
}
