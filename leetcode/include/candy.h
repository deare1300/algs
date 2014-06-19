#ifndef CANDY_H
#define CANDY_H
#include "include/header.h"
/*****************************************************************************

There are N children standing in a line. Each child is assigned a rating value.

You are giving candies to these children subjected to the following requirements:

Each child must have at least one candy.
Children with a higher rating get more candies than their neighbors.
What is the minimum candies you must give?

***********************************************************************************/

class Candy
{
    public:
        Candy();
        //int candy(vector<int> &ratings, int index = 0, int peek = 0);
        int candy(vector<int> &ratings);
        virtual ~Candy();
    protected:
    private:
};

void test_candy();
#endif // CANDY_H
