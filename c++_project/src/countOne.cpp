#include "include/countOne.h"

void testCountOne() {
    CountOne<int> one(0);
    for(int i = 1; i < 100; ++i) {
        one.setNum(i);
        cout<<i<<'\t'<<one.count()<<endl;
    }
}
