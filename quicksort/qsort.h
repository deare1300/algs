#include <iostream>
#include <stack>
using namespace std;

template<class T>
int partition(T a[], int low, int high) {
	T p = a[low];
	while(low < high) {
		while(low < high && a[high] >= p)
			--high;
		a[low] = a[high];
		while(low < high && a[low] <= p)
			++low;
		a[high] = a[low];
	}   
	a[low] = p;
	return low;
}

template<class T>
void qsort(T a[], int len) {
	if(len <= 1)
		return;
	int mid = partition(a, 0, len-1);
	qsort(a, mid);
	qsort(&a[mid+1], len-mid-1);
}

template<class T>
void qsort2(T a[], int len) {
	if(len <= 1)
		return;
	stack<T> s;
	s.push(0);
	s.push(len-1);
	while(s.empty() == false) {
		int high = s.top();
		s.pop();
		int low = s.top();
		s.pop();
		int mid = partition(a, low, high);
		if(mid-1 > low) {
			s.push(low);
			s.push(mid-1);
		}
		if(mid+1 < high) {
			s.push(mid+1);
			s.push(high);
		}
	}	
}
