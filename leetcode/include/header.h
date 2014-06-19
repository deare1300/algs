#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED

#include <vector>
#include <set>
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <new>
#include <memory>
#include <map>
#include <string.h>
#include <algorithm>
#include <queue>
#include <math.h>
#include <utility>
#include <list>
#include <stack>

using namespace std;

template <class T>
void printTVector(vector<vector<T> > &b)
{
    for(typename vector<vector<T> >::iterator it = b.begin(); it != b.end(); ++it)
    {
        for(typename vector<T>::iterator iiter = it->begin(); iiter != it->end(); ++iiter)
            cout<<*iiter<<'\t';
        cout<<endl;
    }
}

template<class T>
void printVector(vector<T> &v)
{
    for(typename vector<T>::iterator iter = v.begin(); iter != v.end(); ++iter)
    {
        cout<<*iter<<'\t';
    }
    cout<<endl;
}
#endif // HEADER_H_INCLUDED
