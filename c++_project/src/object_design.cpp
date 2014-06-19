#include "object_design.h"
#include <iostream>
object_design::object_design()
{
    //ctor
}

object_design::~object_design()
{
    //dtor
}

class Base
{
public:
    Base(){}
    int get(){return 1;}
};

class Derived:public Base
{
};

void test_base()
{
    using namespace std;
    Derived d;
    std::cout<<d.get();;
}
