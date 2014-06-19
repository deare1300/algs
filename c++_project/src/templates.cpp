#include "include/templates.h"
void self::test_vector()
{
    Vector<std::string> v(1);
    v.push_back("one");
    v.push_back("two");
    for(typename self::Vector<std::string>::iterator it = v.begin(); it != v.end(); ++it)
            std::cout<<*it<<std::endl;
}


void self::test_convert()
{
    using namespace std;
    string str = "0123";
    int a = self::atoi<int>(str);
    int b = 99;
    string strB = self::to_string(b);
    cout<<"test_==============================="<<endl;
    cout<<"after convert:"<<a<<"\t"<<strB<<endl;
}

/*

template<typename T>
self::Rational<T>::Rational(T r, T d)
{
    this->real = r;
    this->deno = d;
}

template<typename T>
typename const self::Rational<T> self::Rational<T>::operator*(self::Rational<T> &r)
{
    return Rational(this->real*r.real, this->deno*r.deno);
}

template<typename T>
void self::Rational<T>::print()
{
    using namespace std;
    cout<<this->real<<this->deno;
}
*/

void self::test_template_rationals()
{
        self::Rational<int> r1(1, 2);
        self::Rational<int> r2(2, 3);
        self::Rational<int> r3 = r1 * r2;
        r3.print();
}
