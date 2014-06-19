#include <iostream>
using namespace std;

template<class T>
void heapsort(T a[], int len);
template<class T>
void build_max_heap(T a[], int len);
template<class T>
void down_adjust(T a[], int index, int len);

template<class T>
void print(T a[], int len){
        for(int i = 0; i < len; ++i)
                cout<<a[i]<<'\t';
        cout<<endl;
}

template<class T>
void heapsort(T a[], int len) {
	if(len <= 1)
		return;
	build_max_heap(a, len);
	while(len > 0) {
		//print(a, len);
		swap(a[0], a[len-1]);
		--len;
		down_adjust(a, 0, len);
	}
}

template<class T>
void build_max_heap(T a[], int len) {
	for(int i = len/2; i > -1; --i)
		down_adjust(a, i, len);
}


template<class T>
void down_adjust(T a[], int index, int len) {
	int left = index*2+1;
	int right = index*2+2;
	if(left >= len)
		return;
	int max_index = index;
	if(a[left] > a[max_index])
		max_index = left;
	if(right < len && a[right] > a[max_index])
		max_index = right;
	if(max_index != index) {
		swap(a[index], a[max_index]);
		down_adjust(a, max_index, len);
	}
}
