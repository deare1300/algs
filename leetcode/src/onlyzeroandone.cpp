#include "include/onlyzeroandone.h"
#include "include/header.h"

OnlyZeroAndOne::OnlyZeroAndOne()
{
    //ctor
}

OnlyZeroAndOne::~OnlyZeroAndOne()
{
    //dtor
}

int Pow(int r, int k)
{
    int res = 1;
    for(int i = 0; i < k; ++i)
        res *= r;
    return res;
}

int OnlyZeroAndOne::getNum(int N)
{
    if(N == 0|| N == 1)
        return N;
    int *divs = new int[N];
    //取余数的结果（0~n-1）
    int *temp = new int[N];
    for(int i = 0; i < N; ++i)
        temp[i] = divs[i] = -1;
    divs[1] = 1; //1
    //i表示数的位数 从10^i次方开始 j 表示 10^j % N
    for(int i = 1, j = 10 % N; divs[0] == -1; ++i, j = (j*10) % N)
    {

        for(int i = 0; i < N; ++i)
            temp[i] = -1;
        int begin = Pow(10 ,i);
        if(divs[j] == -1)
            temp[j] = Pow(10, i);
        for(int k = 1; k < N; ++k)
        {
            int temp_div = (j + k) % N;
            if(divs[k] != -1 && temp[temp_div] == -1 && divs[temp_div] == -1 )
            {
                int add = begin+divs[k];
                temp[temp_div] = add;
            }
        }
        for(int i = 0; i < N; ++i)
        {
            if(temp[i] != -1)
                divs[i] = temp[i];
        }
    }

    int res = divs[0];
   // cout<<"res:"<<res<<endl;
    delete[] divs;
    delete[] temp;
    return res;
}

string convertToInt(vector<int> location)
{
    string big;//(location[0], '0');
    int last = 0;
    for(int i = 0; i < location.size(); ++i)
    {
        for(last; last < location[i]; ++last)
            big = '0' + big;
        big = '1' + big;
        last = location[i]+1;
    }
    return big;
}

string BigOne(int N)
{
    if(N == 0 || N == 1)
        return string(1,N+'0');
    vector<vector<int> > nums(N, vector<int>());
    nums[1].push_back(0);
    for(int i = 1, j = 10 % N; nums[0].size() == 0; ++i, j = (j*10) % N)
    {
        if(nums[j].size() == 0)
        {
            nums[j].push_back(i);
        }
        for(int k = 1; k < N; ++k)
        {
            int div_num = (k+j) % N;
            if(nums[k].size() != 0 && nums[k][nums[k].size()-1] < i && nums[div_num].size() == 0)
            {
                for(vector<int>::iterator it = nums[k].begin(); it != nums[k].end(); ++it)
                    nums[div_num].push_back(*it);
                nums[div_num].push_back(i);
            }
        }
    }
    return convertToInt(nums[0]);
}

void test_only()
{

   for(int i = 0; i < 10; ++i)
   {
       int temp = pow(10, i);
       cout<<temp<<endl;
   }
   int  N = 31;
   while(cin>>N)
   {
        OnlyZeroAndOne zo;
        cout<<zo.getNum(N)<<endl;;
        string big = BigOne(N);
        cout<<big<<endl;
   }
   // cout<<endl;
}
