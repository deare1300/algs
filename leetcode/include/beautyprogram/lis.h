#ifndef _BEAUTYPROM_LIS_H_ 
#define _BEAUTYPROM_LIS_H_

#include <vector>
#include <iostream>
using namespace std;

template<class T>
class Lis {
	private:
		T *a;
		int num;
	public:
		Lis():a(0), num(0) { }
		Lis(T *a, int num): a(a), num(num) { }
		int get_max_lis();
		vector<T> get_elements();
};

template<class T>
int Lis<T>::get_max_lis(){
	return get_elements().size();
}

template<class T>
vector<T> Lis<T>::get_elements() {
	vector<T> res;
	if(num == 0 || a == 0) return res;
	
	vector<int> lis(num+1, 1);
	vector<T> maxv(num+1);

	for(int i = 0; i <= num; ++i) {
		lis[i] = 1;
	}

	maxv[1] = a[0];
	maxv[0] = INT_MIN;
	int max_lis = 1;
	for(int i = 1; i < num; ++i) {
		int j;
		for(j = max_lis; j > 0; --j) {
			if(maxv[j] < a[i]) {
				lis[i] = j+1;
				break;
			}
		}

		if(maxv[max_lis] < a[i]) {
			max_lis = lis[i];
			maxv[lis[i]] = a[i];
		}
		else if(maxv[j] < a[i] && a[i] < maxv[j+1]) {
			maxv[j+1] = a[i];
		}
		//cout<<"index:"<<i<<" max_len:"<<max_lis<<"value:"<<maxv[max_lis]<<endl;
	}

	for(int i = 0; i < max_lis; ++i) {
		res.push_back(maxv[i+1]);
	}
	return res;
}

#endif
