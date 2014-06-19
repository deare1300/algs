#include "mergesort.h"
#include <stdio.h>

int main() {
	int a[] = {3,1,3,2,5,2};
	int b[] = {3,1,3,2,5,2};
	mergesort(a, sizeof(a)/sizeof(a[0]));
	for(int i = 0; i < sizeof(a)/sizeof(a[0]); ++i)
		printf("%d\t", a[i]);
	printf("\n");
	return 0;
}
