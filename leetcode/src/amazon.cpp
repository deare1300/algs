#include "amazon/2d.h"

#include <iostream>
using namespace std;
void test_2d() {
	cout<<"2d array test"<<endl;
	TwoArray<int> two(2, 3);
	cout<<two[0][0]<<endl;
	
}


void test_amazon() {
cout<<"amazon test"<<endl;
#define TEST_2D
#ifdef TEST_2D
	test_2d();
#endif

}
