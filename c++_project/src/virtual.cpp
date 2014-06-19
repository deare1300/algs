#include "include/virtual.h"


void test_virtual()
{
    vector<DVirtual> vdv;
    DVirtual dv(2);
  //  Virtual& v =  dv;

    DVirtual dvv(3);
    cout<<&dv<<'\t'<<&dvv<<endl;
    vdv.push_back(dv);
    vdv.push_back(dvv);
    dv.~DVirtual();
    dv.~DVirtual();
    dvv.~DVirtual();
    dv.print();
    cout<<"------"<<endl;


}
