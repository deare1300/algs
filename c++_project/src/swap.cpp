#include "swap.h"

#include <string>
#include <iostream>

Swap::Swap()
{
    //ctor
}

Swap::~Swap()
{
    //dtor
}



namespace MySwap
{
    class Win
    {
    public:
        Win(std::string *p = 0)
        {
            this->p = p;
        }
        void swap(Win &w)
        {
            using std::swap;
            swap(this->p, w.p);
            std::cout<<"myself"<<std::endl;
        }
        ~Win()
        {
            delete p;
        }
    private:
         std::string *p;
    };
}

namespace MySwap
{
    template<class T>
    class WinT
    {
    public:
        WinT(T *p = 0)
        {
            this->p = p;
        }
        void swap(WinT w)
        {
            using std::swap;
            swap(this->p, w.p);
        }
        void display()
        {
            std::cout<<*p<<std::endl;
        }
        ~WinT()
        {
            delete p;
        }
    private:
        T *p;
    };

    template<class T>
    void swap(WinT<T> &w1, WinT<T> &w2)
    {
        w1.swap(w2);
    }
}

namespace std
{
    /*
    **************ÌØ»¯ ********************
    */
    template<>
    void swap<MySwap::Win>(MySwap::Win &w1, MySwap::Win &w2)
    {
        std::cout<<"defined swap"<<std::endl;
        w1.swap(w2);
    }
}

void test_swap()
{
    using std::swap;
    MySwap::Win w1(new std::string("this is swap string1"));
    MySwap::Win w2(new std::string("this is swap string2"));
    swap(w1, w2);

    MySwap::WinT<std::string> wt1(new std::string("one temp"));
    MySwap::WinT<std::string> wt2(new std::string("two temp"));
}

