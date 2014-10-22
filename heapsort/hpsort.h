#ifndef HPSORT_H_
#define HPSORT_H_

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

/*
 *default maxHeap and Iterator max the random iterator
 */



template<class T>
static inline bool __min(T &it1, T &it2) {
	return it1 < it2;
}

template<class T>
static inline bool __max(T &it1, T &it2) {
	return !(__min(it1, it2));
}

template<class Iterator, class CMP>
void heap_sort(Iterator begin, Iterator end, CMP cmp);

template<class Iterator, class CMP>
static void __make_heap(Iterator begin, Iterator end, CMP cmp);

template<class Iterator, class CMP>
static void __up_adjust(Iterator begin, Iterator adjust, CMP cmp);

template<class Iterator, class CMP>
static void __down_adjust(Iterator begin, Iterator end, CMP cmp);

template<class Iterator, class CMP>
void heap_sort(Iterator begin, Iterator end, CMP cmp) {
	__make_heap(begin, end, cmp);
	swap(*begin, *(--end));
	while(begin != end) {
		__down_adjust(begin, end, cmp);
		swap(*begin, *(--end));
	}
}

template<class Iterator, class CMP>
static void __make_heap(Iterator begin, Iterator end, CMP cmp) {
	int n = std::distance(begin, end);
	for(Iterator it = begin; it != end; ++it) {
		__up_adjust(begin, it, cmp);
	}
}

template<class Iterator, class CMP>
static void __up_adjust(Iterator begin, Iterator adjust, CMP cmp) {
	int n = std::distance(begin, adjust) + 1;
	Iterator parent;
	while(adjust != begin) {
		parent = begin + n/2 - 1;
		if(cmp(*parent, *adjust)) {
			break;
		}
		swap(*parent, *adjust);
		adjust = parent;
		n /= 2;
	}
}

template<class Iterator, class CMP>
static void __down_adjust(Iterator begin, Iterator end, CMP cmp) {
	int n = std::distance(begin, end);
	Iterator p;
	Iterator left, right;
	Iterator max;
	int i;
	int next;
	for(i = 0; i < n/2;) {
		p = begin + i;
		max = left = begin + 2*i + 1;
		right = begin + 2*i + 2;
		next = 2*i + 1;
		if(2*i+2 < n && cmp(*right, *left)) {
			max = right;
			next = 2*i + 2;
		}
		if(cmp(*p, *max)) {
			break;
		}
		swap(*p, *max);
		i = next;
	}
}

#endif
