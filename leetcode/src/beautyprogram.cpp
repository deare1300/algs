#include "include/beautyprogram/lis.h"
#include "include/beautyprogram/arr.h"
#include "include/beautyprogram/arrsplit.h"
#include "include/beautyprogram/seqplus.h"
#include "leetcode/print.h"

#include <iostream>

void test_lis() {
	cout<<"test_lis<"<<endl;
	int a[] = { 2, 1, 3, -1, -0, -2, -1, 0,1, 2, };
	Lis<int> l(a, sizeof(a)/sizeof(a[0]));
	dump(&a[0], &a[sizeof(a)/sizeof(a[0])]);
	vector<int> res = l.get_elements();
	cout<<l.get_max_lis()<<endl;
	dump(res.begin(), res.end());
}

void test_arrsplit() {
	cout<<"arr split"<<endl;
	int a[] = { 1, 2, 3, 4, 5, 6, 7, 8};
	int total = sum(&a[0], sizeof(a)/sizeof(a[0]));
	dump(&a[0], &a[sizeof(a)/sizeof(a[0])]);
	ArrSplit<int> arrspl(a, sizeof(a)/sizeof(a[0]));
	cout<<"total sum:"<<total<<"\tsplits:"<<arrspl.split()<<endl;
	
	arrspl.split();
}
	
void test_analysis() {
	const int num = 30;
	int rg[num];
	
	for(int i = 0; i < num; ++i)
		rg[i] = 2+i;

	int hit;
	for(int i = 1; i < INT_MAX; ++i) {
		int hit = 0;
		int hit1, hit2;
		for(int j = 0; j < num && hit <= 2; ++j) {
			if(i % rg[j] != 0) {
				if(hit == 0) {
					hit1 = j;
				}
				else if(hit == 1) {
					hit2 = j;
				}
				++hit;
			}
			
		}

		if(hit == 2 && hit1+1 == hit2) {
			cout<<"num:"<<i<<"\thit1:"<<hit1<<"\thit2:"<<hit2<<endl;
		}
	}
}

void test_seqplus() {
	cout<<"seqplus:------------------------"<<endl;
	SeqPlus<int> seq;
	const int MAX = INT_MAX;
	for(int i = 1; i < MAX; ++i) {
		seq.setNum(i);
		if(seq.hasPlus() == false)
			cout<<i<<"---->"<<seq.hasPlus()<<endl;
	}
}

void test_beauty() {

#define LIS
#ifdef LIS
	test_lis();
#endif


//#define ARRSPLIT
#ifdef ARRSPLIT
test_arrsplit();
#endif
//test_analysis();

#define SEQPLUS
#ifdef SEQPLUS
//cout<<"SEQPLUS"<<endl;
test_seqplus();
#endif
}
