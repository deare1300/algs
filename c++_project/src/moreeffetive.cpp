#include "include/moreeffetive.h"
#include "include/header.h"

#include <stdio.h>
#include <stdlib.h>
#include <new>
//#include <delete>

using namespace std;

typedef void (*func)();
MoreEffetive::MoreEffetive()
{
    //ctor
}

MoreEffetive::~MoreEffetive()
{
    //dtor
}


MyString::MyString():ptr(0), length(0)
    {
        cout<<"default string"<<endl;
    }
    MyString::MyString(string msg)
    {
        ptr = new char[msg.length() + 1];
        for(int i = 0; i < msg.length(); ++i)
        {
            ptr[i] = msg[i];
        }
        ptr[msg.length()] = 0;
        cout<<"MyString(msg)"<<endl;
    }
    void *MyString::operator new(size_t size)
    {
        cout<<" operator new(size) "<<endl;
        return ::operator new(size);
    }
    void *MyString::operator new(size_t, void *buffer)
    {
        cout<<"operator new(size, buffer)"<<endl;
        return buffer;
    }
    void MyString::operator delete(void *buffer)
    {
        cout<<"operator delete"<<endl;
        ::operator delete(buffer);
    }

    MyString::~MyString()
    {
        cout<<" ~MyString()"<<endl;
        delete ptr;
    }


void Operator::test_operator()
{
    cout<<"test operator ============================="<<endl;
    cout << "----------------------placement new test------------" <<endl;
    /* *****placement test*****/


    void *raw_memory = operator new(sizeof(MyString));
    cout<<"raw_memory address:"<<raw_memory<<endl;
    MyString *mstr = new(raw_memory) MyString(" what "); //placement new
    delete mstr;
    cout<<"mstr_memory address:"<<mstr<<endl;
    operator delete(raw_memory);
    cout<<"raw_memory address:"<<raw_memory<<endl;


    /******************** operator new test ********************/

    cout << "----------------------operator new test------------" <<endl;
    MyString *mystr2 = new MyString("this tests operator new");
    delete mystr2;
    cout<<"test operator ============================="<<endl;
}

class Exceptions
{
public:
    explicit Exceptions(string msg):msg(msg){}
    explicit Exceptions():msg(""){}
private:
    string msg;
};

void Myexception::test_myException()
{
    cout<<"=================================my exception"<<endl;
    try
    {
        //strlen(NULL);
        size_t  len = strlen(NULL);
       // cout<<strlen(NULL)<<endl;
        Exceptions e("this is exception");
        cout<<"original e address:"<<&e<<endl;
        throw e;
    }
    catch(Exceptions &e)
    {
        cout<<"reference e address:"<<&e<<endl;
        //throw ;
    }
    catch(...)
    {
        cout<<"catch all"<<endl;
    }


    cout<<"=================================my exception"<<endl;
}

namespace virtual_ptr
{
    Base::Base()
    {
    }

    void Base::nosay()
    {
        cout<<"no say() base"<<endl;
    }

    void Base::print()
    {
        cout<<"this is Base print"<<endl;
    }

    void test_virtual_ptr()
    {
        Base b = D();
        cout<<(int *) (&b)<<endl;
        cout<<(int *)*(int *) (&b)<<endl;
        func f = (func)*((int *)*(int *) (&b));
        f();
        //f();
        //func a = b->vptr;
       // func arr[] = &b;
        //arr[0]();
    }
}

namespace virtual_ptr
{
    D::D()
    {

    }
}


