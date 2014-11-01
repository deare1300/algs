#ifndef _LONGESTSUBSTR_H_
#define	_LONGESTSUBSTR_H_

#include <algorithm>

template<class T>
class LongestInc {
	private:
		T *arr;
		int num;
	public:
		LongestInc():arr(0), num(0) { }
		LongestInc(T *arr, int num):arr(arr), num(num) { }
		int getLongest();
};

template<class T>
int LongestInc<T>::getLongest() {
	sort(&arr[0], &arr[num]);
	int longest_len = 1;
	
}

#endif
