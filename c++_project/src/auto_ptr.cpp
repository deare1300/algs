#include "include/auto_ptr.h"
#include "include/header.h"
#include "include/virtual.h"

Auto_Ptr::Auto_Ptr()
{
    //ctor
}

Auto_Ptr::~Auto_Ptr()
{
    //dtor
}

void test_auto_ptr()
{
    auto_ptr<DVirtual> p (new DVirtual());
    auto_ptr<int> pint(new int());
    *pint.get() = 10;
    cout<<pint.get()<<endl;
    int x = 2;
    x -=  *pint.get()+1;
    cout<<x<<endl;
}
