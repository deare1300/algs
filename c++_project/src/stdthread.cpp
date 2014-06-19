#include "include/stdthread.h"
#include "include/header.h"

STDThread::STDThread()
{
    //ctor
}

STDThread::~STDThread()
{
    //dtor
}

void foo()
{
    cout<<"foo"<<endl;
}

void bar(int x)
{
    while(x-- > 0)
    {
        cout<<x<<endl;
    }
}

void test_thread()
{
    #define THREAD_ERROR 1
    //std::thread p(foo);
    cout<<endl;
}
