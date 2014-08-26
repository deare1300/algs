#ifndef __PRINT_H_
#define __PRINT_H_
#include <iostream>
#include <vector.h>
using namespace std;

/*
template<class T>
void print_vector(vector<T> &v) {
    typename vector<T>::iterator it;
    for(it = v.begin(); it != v.end(); ++it) {
        cout<<*it<<'\t';
    }
    cout<<endl;
}
*/

template<class Iterator>
void dump(Iterator begin, Iterator end) {
    while(begin != end) {
        cout<<*begin<<'\t';
        ++begin;
    }
    cout<<endl;
}

#endif
