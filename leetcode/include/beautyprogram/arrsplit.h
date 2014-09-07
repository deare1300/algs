#ifndef _BEAUTYPRO_ARRSPLIT_H_
#define _BEAUTYPRO_ARRSPLIT_H_

#include <iostream>
#include <vector>

#include "include/beautyprogram/arr.h"

using namespace std;
template<class T>
class ArrSplit {
	public:
		ArrSplit():arr(0), num(0) { }
		ArrSplit(T *arr, int num):arr(arr), num(num) { }
		T split(int def);
		T split() { return split(num/2); }
	private:
		T *arr;
		int num;
};

template<class T>
T ArrSplit<T>::split(int def) { //split the num has def len
	T total = sum(arr, num);
	T res = total/2;
	// ibool[elements][sum]
	vector<vector<bool> > ibool(def+1, vector<bool>(total/2+1, false));
	
	//vector<vector<T> > sums(def+1, vector<T>(total/2+1, 0));
	ibool[0][0] = true;
	for(int i = 0; i < num; ++i) {
		for(int j = min(i, def); j > 0; --j) {
			for(int v = 1; v <= total/2; ++v) {
				if(ibool[j][v] == false && ibool[j-1][v-arr[i]] == true) {
					ibool[j][v] = true;
					cout<<"nums:"<<j<<"\tvalues:"<<v<<endl;
				}
			}
		}
	}

	
	for(vector<bool>::reverse_iterator it = ibool[def].rbegin(); it != ibool[def].rend(); ++it) {
		if(*it == true)
			return res;
		--res;
	}
		
	return -1;
	
	
}
		

#endif

