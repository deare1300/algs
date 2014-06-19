#include "include/constructor.h"
#include "include/header.h"

Little_Member::Little_Member()
{
    cout<<"this is little member"<<endl;
}

Constructor::Constructor()
{
    //ctor
    /**before the constructor every member of none intern type will call the default constructor
    **/
    cout<<"in the constructor"<<endl;
    little = Little_Member();
}

Constructor::~Constructor()
{
    //dtor
}

OnlyHeap::OnlyHeap()
{
    cout<<"product onlyhead"<<endl;
}

OnlyHeap::~OnlyHeap()
{
    cout<<" ~onlyHead"<<endl;
}

void OnlyHeap::destroy()
{
    delete this;
}

void test_only_head()
{
    try{
        //error happend when compile
       // OnlyHeap oh;
    }catch(...)
    {

    }
    OnlyHeap *ohp = new OnlyHeap();
    ohp->destroy();
    DOnly_Heap donp;
}
