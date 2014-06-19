#ifndef VIRTUAL_H
#define VIRTUAL_H

#include "include/header.h"

class Virtual
{
    public:
  //      Virtual();
        virtual ~Virtual()
        {
            cout<<"~virutal()"<<endl;
        }
    protected:
    private:
};

class BVirtual:public Virtual
{
public:
    virtual ~BVirtual()
    {
        cout<<"~bvirutal()"<<endl;
    }
};

class DVirtual:public BVirtual
{
public:
    DVirtual(){}
    DVirtual(int d):d(d){}
    ~DVirtual()
    {
        cout<<"~dvirutal()"<<this<<endl;
    };
    void print()
    {
        cout<<"d=="<<d<<endl;
    }
    int d;
};

void test_virtual();
#endif // VIRTUAL_H
