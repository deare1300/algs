#ifndef _BEAURYPRO_ARR_H_
#define _BEAURYPRO_ARR_H_


template<class T>
T sum(T *arr, int num) {
	T res = 0;
	for(int i = 0; i < num; ++i) {
		res += arr[i];
	}
	return res;
}

#endif
