#include "convert.h"
#include "header.h"
Convert::Convert()
{
    //ctor
}

Convert::~Convert()
{
    //dtor
}

class Window {
public:
    Window():i(0){}
    virtual void add()
    {
        using namespace std;
        cout<<"add base address:"<<this<<endl;
        ++i;
    }
    virtual void display()
    {
        using namespace std;
        cout<<"base address:"<<this<<endl;
        cout<<"base:"<<i<<'\t';
    }
private:
    int i;
};

class DWindow:public Window {
public:
    DWindow():j(0){}
    void add()
    {
        static_cast<Window>(*this).add();
        ++j;
    }
    virtual void display()
    {
        Window::display();
        cout<<"deprived:"<<j<<endl;
    }
private:
    int j;
};

void test_convert()
{
    const int cp = 1;
    int p = cp;
    const int cpp = p;
    DWindow d;
    d.add();
    d.display();
}
