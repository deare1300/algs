#ifndef _BEAUTYPRO_PREFIXSORT_H_
#define _BEAUTYPRO_PREFIXSORT_H_

#include <iostream>
#include "include/beautyprogram/arr.h"

using namespace std;
// pie sort
template<class T>
class PrefixSort {
	public:
		friend ostream& operator<<(ostream &os, const PrefixSort &p) {
			using namespace std;
			for(int i = 0; i < p.num; ++i) {
				cout<<p.a[i]<<'\t';
			}
			cout<<endl;
			return os;
		}
	public:
		PrefixSort():a(0), num(0) { }
		PrefixSort(T *a, int num):a(a), num(num) { }
		int sort(); 
		vector<int> get_procedure() { return best_procedure; }
	protected:
		void __sort(int times);
		bool __isSorted();
	private:
		T *a;
		int num;
		int min_times;
		vector<int> procedure;
		vector<int> best_procedure;
};

template<class T>
bool PrefixSort<T>::__isSorted() {
	for(int i = 0; i < num-1; ++i) {
		if(a[i] > a[i+1]) return false;
	}
	return true;
}

template<class T>
int PrefixSort<T>::sort() {
	min_times = 2*(num-1);
	__sort(0);
	return min_times;
}

template<class T>
void PrefixSort<T>::__sort(int times) {
//	cout<<times<<endl;
//	cout<<*this<<endl;
	if(__isSorted()) {
		if(times < min_times) {
			min_times = times;
			best_procedure = procedure;
		}
		return;
	}
	if(times >= min_times) return;
	for(int i = 2; i <= num; ++i) {
		reverse(a, i);
		procedure.push_back(i);
		__sort(times+1);
		procedure.pop_back();
		reverse(a, i);
	}
}

#endif
