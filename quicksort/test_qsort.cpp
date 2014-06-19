#include "qsort.h"
#include <stdio.h>

int main() {
	int a[] = {3,1,3,2,5,2};
	int b[] = {3,1,3,2,5,2};
	qsort(a, sizeof(a)/sizeof(a[0]));
	qsort2(b, sizeof(b)/sizeof(b[0]));
	for(int i = 0; i < sizeof(a)/sizeof(a[0]); ++i)
		printf("%d\t", a[i]);
	printf("\n");
	for(int i = 0; i < sizeof(b)/sizeof(b[0]); ++i)
		printf("%d\t", b[i]);
	printf("\n");
	return 0;
}
