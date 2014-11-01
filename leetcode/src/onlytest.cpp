#include <iostream>
#include <vector>

#include "include/test/all.h"
void test_all();
void test_tst_default_avgs() {
	using namespace std;
	int a[] = { 1, 2, 3};
	//const size_t len = sizeof(a)/sizeof(a[0]);
	int *p = 0;
	int *res =  _tst_default_avgs(a[0], p);
	cout<<res<<endl;
}

void test_all() {
	test_tst_default_avgs();
}
