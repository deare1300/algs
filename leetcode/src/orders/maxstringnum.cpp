#include "maxstringnum.h"
#include "header.h"

bool strcatcmp(const std::string &s, const std::string &t)
{
    std::string st(s+t);
    std::string ts(t+s);
    return st > ts;
}

maxStringNum::maxStringNum()
{
    //ctor
}

maxStringNum::maxStringNum(vector<std::string> num):num(num)
{

}

string maxStringNum::get_max_num()
{
    std::sort(num.begin(), num.end(), strcatcmp);
    string res;
    int len = num.size();
    for(int i = 0; i < len; ++i)
        res += num[i];
    return res;
}

maxStringNum::~maxStringNum()
{
    //dtor
}

void test_max_string_num()
{
    using namespace std;
    string s[] = {"123456","123456123456","798","7988","981","1234","432"};
    vector<string> v;
    for(int i = 0; i < sizeof(s)/sizeof(string); ++i)
        v.push_back(s[i]);
    maxStringNum m(v);
    cout<<m.get_max_num()<<endl;;
}
