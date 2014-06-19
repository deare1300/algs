#ifndef TEMPLATES_H
#define TEMPLATES_H
#include <iostream>
#include <fstream>
#include <sstream>


namespace self
{
    void test_vector();
    template<class T>
    int compare(T t1, T t2);
    class templates
    {
        public:
            templates();
            virtual ~templates();
        protected:
        private:
    };

    template<typename T>
    class Rational
    {
    public:
        Rational(T r, T d);
        const Rational operator *(const Rational &r);
        void print();
    private:
        T real;
        T deno;
    };


    template<typename T>
    Rational<T>::Rational(T r, T d)
    {
        this->real = r;
        this->deno = d;
    }

    template<typename T>
    const Rational<T> Rational<T>::operator *(const Rational<T> &r)
    {
        return Rational(this->real * r.real, this->deno * r.deno);
    }

    template<typename T>
    void self::Rational<T>::print()
    {
        using namespace std;
        cout<<this->real<<'\t'<<this->deno;
    }


};


namespace self
{
    template<class T>
    class Vector
    {
    public:
        typedef T value_type;
        typedef value_type *value_type_p;
        typedef value_type_p iterator;

        explicit Vector(int capacity = 0);
        void push_back(T d);
        void pop_back();
        T &operator[](int index);
        value_type_p begin();
        value_type_p end();
       // value_type_p iterator();
        size_t size();
        void ralloc();

    private:
        value_type_p first;
        value_type_p finish;
        value_type_p point;
        value_type_p store_end;
        size_t capacity;
        value_type_p data;
    };
};

template<class T>
self::Vector<T>::Vector(int capacity):capacity(capacity),first(0),finish(0)
{
    if(capacity != 0)
    {
        data  = new T[capacity];
        first = &data[0];
        finish = &data[0];
        store_end = &data[capacity];
    }
}


template<class T>
void self::Vector<T>::push_back(T d)
{
    if(finish == store_end)
    {
        ralloc();
    }
    *finish = d;
    ++finish;
}

template<class T>
void self::Vector<T>::pop_back()
{
    if(finish != first)
    {
        --finish;
    }
}

template<class T>
void self::Vector<T>::ralloc()
{
    typename self::Vector<T>::value_type_p temp = new T[2*capacity];
    int i = 0;
    int len = size();
    for(typename self::Vector<T>::value_type_p it = first; it != finish; ++it)
    {
        temp[i++] = *it;
    }
    delete [] data;

    data = temp;

    first = &temp[0];
    finish = &temp[len];
}

template<class T>
T& self::Vector<T>::operator[](int index)
{
    if(index < size())
    {
        return data[index];
    }
    //return NULL;
}

template<class T>
size_t self::Vector<T>::size()
{
    return (finish-first);
}

template<class T>
inline typename self::Vector<T>::value_type_p self::Vector<T>::begin()
{
    return first;
}

template<class T>
inline typename self::Vector<T>::value_type_p self::Vector<T>::end()
{
    return finish;
}
template<class T>
int self::compare(T t1, T t2)
{
    return t1 < t2;
}

namespace self
{
    void test_convert();
    template<class T>
    T atoi(std::string s)
    {
        T a;
        std::istringstream ss(s);
        ss>>a;
        return a;
    }

    template<class T>
    std::string to_string(T a)
    {
        std::ostringstream os;
        os<<a;
        return os.str();
    }
}
namespace self
{
    void test_template_rationals();
}
#endif // TEMPLATES_H
