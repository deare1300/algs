#include "include/header.h"
#include "include/listnode.h"

ListNode::ListNode(int x):val(x),next(0)
{

}


void printList(ListNode *list)
{
    cout<<"===========listNode============"<<endl;
    while(list)
    {
        cout<<list->val<<'\t';
        list = list->next;
    }
    cout<<endl;
}
