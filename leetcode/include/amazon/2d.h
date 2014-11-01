#ifndef AMA_2D_H_
#define AMA_2D_H_

#include <stdlib.h>
#include <iostream>
using namespace std;
template<class T>
class TwoArray {
	private:
		T **point;
		const int col;
		const int row;
		TwoArray(const TwoArray&) { }
		TwoArray& operator=(const TwoArray&) { }
	public:
		TwoArray():point(0), col(0), row(0) { }
		
		TwoArray(int row, int col):col(col), row(row) { 
			point = (T**) malloc(row*sizeof(T*));
			if(point == 0)
				exit(-1);
			for(int i = 0; i < row; ++i) {
				point[i] = new T[col];
			}
		}
		
		T* operator[](int row) {
			cout<<point[row]<<endl;
			return point[row];
		}
		
		~TwoArray() {
			for(int i = 0; i < row; ++i) {
				delete[] (point[i]);
			}
			if(point) {
				free(point);
			}
		}
};

void test_2d();
#endif
