#include <iostream>
using namespace std;

extern void test_beauty();
extern void test_solution();
extern void test_all();
extern void test_amazon();
int main()
{
	cout<<"leetcode solution"<<endl;
	test_solution();	
	cout<<"beauty"<<endl;
	test_beauty();
	cout<<"test"<<endl;
	test_all();
	test_amazon();
	return 0;
}
