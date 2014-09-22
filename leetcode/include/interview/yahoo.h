#ifndef __YAHOO_H_
#define __YAHOO_H_

/*
 *Yahoo total 4 problems
 */
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

template<class T>
struct Mice {
    friend ostream& operator<<(ostream &os, Mice &m) {
       return  os<<m.weight<<','<<m.speed;
    }
    int weight;
    int speed;
    bool operator<(const Mice &m) { return this->speed > m.speed || (this->speed == m.speed && this->weight < m.weight); } 
};

template<class T>
class Yahoo {
    private:
        bool __find_number(vector<vector<int> > &matrix, int row, int column, int target);
    public:
        /*
         *1. given a[1....n] caculate b[1...n]  b[i] = a[1]*a[2] ...*a[i-1]*a[i+1]*...a[n]  time O(n) space O(1) 
         *2. 4k+2 given 4k+2 numbers only 2 appear two times others appear four get the number
         *3. matrix every row is sorted and every column is sorted asc find the number and caculate the complexity
         *4. lis and print
         */

        static void get_array(int a[], int b[], int n);
        static int find_two_times(int a[], int n);
        static bool find_number(vector<vector<int> > &matrix, int target);
        static int find_lis(Mice<T>  mices[], int n);
};


template<class T>
void Yahoo<T>::get_array(int a[], int b[], int n) {
    b[0] = a[0];
    for(int i = 1; i < n; ++i) {
        b[i] = a[i]*a[i-1];
    }

    for(int i = n-2; i > -1; --i) {
        a[i] = a[i-1]*a[i];
    }
    b[0] = a[1];
    a[0] = b[0];
    for(int i = 1; i < n-1; ++i) {
        a[i] = b[i];
        b[i] = a[i-1] * a[i+1];
    }
    b[n-1] = a[n-2];
}

template<class T>
int Yahoo<T>::find_two_times(int a[], int n) {
    int iSize = sizeof(int) * 8;
    int res = 0;
    int flag = 1;
    int count;
    for(int i = 0; i < iSize; ++i) {
        count = 0;
        flag = 1 << i;
        for(int j = 0; j < n; ++j) {
            if(flag & a[j]) {
                ++count;
            }
        }
        if(count % 4 == 2) {
            res = res | flag;
        }
    }
    return res;
}

template<class T>
bool Yahoo<T>::__find_number(vector<vector<int> > &matrix, int row, int col, int target) {
    if(row < 0 || col < 0)
        return false;
    if(matrix[row][col] == target)
        return true;
    if(matrix[row][col] > target)
        return __find_number(matrix, row, col-1, target);
    return __find_number(matrix, row+1, col, target);
}

template<class T>
bool Yahoo<T>::find_number(vector<vector<int> > &matrix, int target) {
    int row = matrix.size();
    int col = row > 0 ? matrix[0].size(): 0;
    return __find_number(matrix, 0, col-1, target);
}

template<class T>
int Yahoo<T>::find_lis(Mice<T> mices[], int n) {
    sort(&mices[0], &mices[n]);
    vector<Mice<T> > v;
    int max = 1;
    v.push_back(mices[0]);
    typename vector<Mice<T> >::iterator it;
    for(int i = 1; i < n; ++i) {
        it = std::lower_bound(v.begin(), v.end(), mices[i]);
        if(it == v.end()) {
            ++max;
            v.push_back(mices[i]);
        }
        else {
            *it = mices[i];
        }
    }
    for(it = v.begin(); it != v.end(); ++it) {
        std::cout<<*it<<std::endl;
    }
    return max;
}

/*
 *
 *
 *
 */
#endif
