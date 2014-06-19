#include "include/test_class.h"
#include "include/header.h"
#include <stdio.h>

namespace test_space
{
    void const_referenced(const string &str)
    {
        cout<<str<<endl;
    }

    void referenced(string &str)
    {

        cout<<str<<endl;
    }
    void test_class()
    {
       //
        const_referenced(string("const temp string"));
        //referenced(string("temp string")); temp wrong
        printf("ok");
    }
}

Test_Class::Test_Class()
{
    //ctor
}

Test_Class::~Test_Class()
{
    //dtor
}
