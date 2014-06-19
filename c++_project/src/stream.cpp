#include "include/stream.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
stream::stream()
{
    //ctor
}

stream::~stream()
{
    //dtor
}

void test_stream()
{
    cout<<"test_stream==========================="<<endl;
    test_sstream();
    cout<<"test_stream==========================="<<endl;
}

void test_sstream()
{
    string str;
    int a;
    string b;
    string c;
    cout<<"input a string num and string"<<endl;
    cin>>str;
    istringstream ss(str);
    ss>>a>>b>>c;
    cout<<"input num:"<<a<<"\t"<<"stringb:"<<b<<" string c:"<<c<<endl;
}

void test_fstream()
{
    cout<<"test_stream ==================="<<endl;
    string str;
    char output[100]={0};
    ifstream fin;
    fin.open("main.cpp");
    if(fin.is_open())
    {
        while(!fin.eof())
        {
            fin.getline(output,100);
            cout<<output<<endl;
        }
    }
    cout<<"end test  ==================="<<endl;
}
