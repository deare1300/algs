#include <iostream>
using namespace std;

template<class T>
void merge(T a[], int alen, T b[], int blen, T c[]) {
	int i = 0, j = 0;
	//T *c = new T[alen+blen];
	while(i < alen && j < blen) {
		if(a[i] < b[j]) {
			c[i+j] = a[i];
			++i;
		}
		else {
			c[i+j] = b[j];
			++j;
		}
	}
	while(i < alen) {
		c[i+j] = a[i];
		++i;
	}
	while(j < blen) {
		c[i+j] = b[j];
		++j;
	}
	//return c;
}

template<class T>
void print(T a[], int len){
	for(int i = 0; i < len; ++i)
		cout<<a[i]<<'\t';
	cout<<endl;
}

template<class T>
void mergesort(T a[], int len) {
	if(len <= 1)
		return;
	mergesort(a, len/2);
	mergesort(&a[len/2], len-len/2);
	
	T *res = new T[len];
	merge(&a[0], len/2, &a[len/2], len-len/2, res);
	for(int i = 0; i < len; ++i)
		a[i] = res[i];
	delete[] res;
}

