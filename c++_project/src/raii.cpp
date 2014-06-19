#include "raii.h"
#include "header.h"
RAII::RAII()
{
    //ctor
}

RAII::~RAII()
{
    //dtor
}

class FontHandle
{
public:
    explicit FontHandle(string fh):fh(fh)
    {

    }
    void print()
    {
        cout<<fh<<endl;
    }
    ~FontHandle()
    {
        cout<<this<<"~FontHandle"<<endl;
    }
    operator string() const
    {
        cout<<"string()"<<endl;
        return fh;
    }
private:
    string fh;
};

class Font
{
public:
    explicit Font(FontHandle fh):fh(fh)
    {

    }
    ~Font()
    {
        cout<<"~font()"<<endl;
    }
private:
    FontHandle fh;
};
void test_raii()
{
    //using std::tr1::shared_ptr;
    FontHandle fh("my fh");

    //std::tr1::shared_ptr<Font>(new Font(fh));
    Font f(fh);
    string str = fh;
    cout<<str<<endl;
}


//temperory save
