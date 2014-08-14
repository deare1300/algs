#ifndef COUNTONE_H_
#define COUNTONE_H_

#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;

template<class T>
T pow(T x, T y) {
    T result = 1;
    for(T i = 0; i < y; ++i) {
        result *= x;
    }
    return result;
}

template<typename T>
int getLen(T num) {
    int len = 0;
    while(num) {
        ++len;
        num /= 10;
    }
    return len;
}

template<typename T>
class CountOne {
    private:
        T num;
    public:
        CountOne(const T num):num(num) {}
        void setNum(const T num){ this->num = num; }
        int count();
        static vector<int> v;
        static int getCount(T num);
};

template<typename T>
vector<int> CountOne<T>::v(1000, 0);

template<typename T>
int CountOne<T>::getCount(T num) {
    if(num <= 0) {
        return 0;
    }
    if(num == 1) {
        return 1;
    }
    if(CountOne::v[num] == 0) {
        int len = getLen(num);
        int weight = pow(10, len-1);
        T div = num % weight;
        T r = num / weight;
        if(r == 1) {
            CountOne::v[num] = div+1 + getCount(div) + getCount(weight-1);
        }
        else {
            CountOne::v[num] = r*getCount(weight-1) + getCount(div) +  weight;
        }
    }
    return CountOne::v[num];
}

template<typename T>
int CountOne<T>::count() {
    return CountOne<T>::getCount(num);
}

void testCountOne();

#endif
