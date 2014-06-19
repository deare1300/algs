#ifndef MAXSTRINGNUM_H
#define MAXSTRINGNUM_H

#include "include/header.h"

class maxStringNum
{
    public:
        maxStringNum();
        maxStringNum(vector<std::string> num);
        std::string get_max_num();
        virtual ~maxStringNum();
    protected:
    private:
        vector<std::string> num;
};

void test_max_string_num();
#endif // MAXSTRINGNUM_H
