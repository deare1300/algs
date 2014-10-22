#include "heapsort.h"
#include "hpsort.h"
#include <stdio.h>

bool max_int(int &a, int &b) { return b > a; }

int main() {
	int a[] = {3,1,3,2,5,2};
	int b[] = {3,1,3,2,5,2};
	heap_sort(&a[0], &a[sizeof(a)/sizeof(a[0])], max_int);
	for(int i = 0; i < sizeof(a)/sizeof(a[0]); ++i)
		printf("%d\t", a[i]);
	printf("\n");
	return 0;
}
