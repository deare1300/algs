#ifndef CONSTRUCTOR_H
#define CONSTRUCTOR_H


class Little_Member
{
public:
    Little_Member();
};

class Constructor
{
    public:
        Constructor();
        virtual ~Constructor();
    protected:
    private:
        Little_Member little;
};

class OnlyHeap
{
public:
    OnlyHeap();
    void destroy();

protected:
    ~OnlyHeap();
};

class DOnly_Heap:public OnlyHeap
{

};
void test_only_head();

#endif // CONSTRUCTOR_H
