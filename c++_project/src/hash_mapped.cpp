#include "hash_mapped.h"
#include "header.h"
#include <hash_map>
using namespace std;

hash_mapped::hash_mapped()
{
    //ctor
}

hash_mapped::~hash_mapped()
{
    //dtor
}


void test_hash_map()
[
    hash_map<string, string> hmap;
    hmap.insert(pair<string, string>("1","one"));
    hmap.insert(pair<string, string>("1","one_two"));
    hmap.insert(pair<string, string>("2","two"));
    for(hash_map<string, string>::iterator iter = hmap.begin(); iter != hmap.end(); ++iter)
    {
        cout<<iter->first<<'\t'<<iter->second<<endl;
    }

]
