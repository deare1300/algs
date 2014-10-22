#ifndef _BEAURYPRO_ARR_H_
#define _BEAURYPRO_ARR_H_

#include <iostream>
using namespace std;

template<class T, typename Iterator>
static T __sum(Iterator begin, Iterator end, Iterator it = (T*) 0) {
	T res = 0;
	while(begin != end) {
		res += *begin++;
	}
	return res;
}

template<class T>
T sum(T *arr, int num) {
	return __sum<T>(&arr[0], &arr[num]);
}

template<class T, typename Iterator>
static void __reverse(Iterator begin, Iterator end, Iterator it = (T*) 0) {
	Iterator last = end-1;
	int len = std::distance(begin, end);
	int i = 0;
	while(i++ < len/2) {
	//	cout<<"reverse:"<<*begin<<"\t"<<*last<<endl;
		T tmp = *begin;
		*begin =*last;
		*last = tmp;
		++begin;
		--last;
	}
}

template<class T>
void reverse(T *arr, int num) {
	__reverse<T>(&arr[0], &arr[num]);
}

#endif
