#ifndef MOREEFFETIVE_H
#define MOREEFFETIVE_H
#include "include/header.h"

class MoreEffetive
{
    public:
        MoreEffetive();
        virtual ~MoreEffetive();
    protected:
    private:
};

namespace Operator
{
    void test_operator();

};

class MyString
{
public:
    MyString();
    MyString(string);
    void *operator new(size_t size);
    void *operator new(size_t, void *buffer);
    void operator delete(void *buffer);
    virtual ~MyString();
private:
    char *ptr;
    size_t length;
};


namespace Myexception
{
    void test_myException();
};


namespace virtual_ptr
{
    class Base
    {
    public:
        Base();
        virtual void nosay();
        virtual void print();
    };

    void test_virtual_ptr();
};


namespace virtual_ptr
{
    class D:public Base
    {
    public:
        D();
      //  virtual void print();
    };
}
#endif // MOREEFFETIVE_H
