#include "include/reference.h"
#include "include/header.h"
#include "include/moreeffetive.h"
using namespace std;
Reference::Reference()
{
    //ctor
}

Reference::~Reference()
{
    //dtor
}

MyString& getRefrence()
{
    MyString *p = new MyString();
    return *p;
}


void Reference::test_reference()
{
    MyString &rstr = getRefrence();
    delete &rstr;
}
