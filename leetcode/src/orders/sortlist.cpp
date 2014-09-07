#include "include/sortlist.h"
#include <iostream>
#include "include/listnode.h"
using namespace std;

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

 ListNode *getK(ListNode *head, int k)
 {
     int i = 1;
     cout<<"getK:"<< k <<endl;
     while(i < k && head)
     {
         head = head->next;
         ++i;
     }
     return head;
 }


 int getLen(ListNode *head)
 {

     int len = 0;
     cout<<"getLen"<<endl;
     while(head)
     {
         ++len;
         head = head->next;
     }
     return len;
 }

void insertNode(ListNode *head, ListNode *node, int len)
{
    using namespace std;
    //cin.get();
    cout<<"(len,node) "<<len<<'\t'<<node->val<<endl;
    printList(head);
    ListNode *mid = getK(head, (len-1)/2);
    if(len == 1)
    {
        if(node->val < head->val)
        {
            head->next = node;
        }
        else
        {
            cout<<"error"<<endl;
        }
    }
    if(mid->val == node->val)
    {
        node->next = mid->next;
        mid->next = node;
        return;
    }
    else if(mid->val < node->val && mid->next == 0)
    {
        cout<<"111111"<<endl;
        node->next = mid->next;
        mid->next = node;
        return;
    }
    else if(mid->val < node->val && mid->next->val > node->val)
    {
        cout<<"22222"<<endl;
        node->next = mid->next;
        mid->next = node;
        return;
    }
    else if(mid->val > node->val)
    {
        cout<<"3333"<<endl;
        insertNode(head, node, (len-1)/2 + 1);
    }
    else
    {
        cout<<"4444"<<endl;
        insertNode(mid, node, len - (len-1)/2);
    }
}


 ListNode *merge(ListNode *head1, ListNode *head2)
 {
     ListNode *head = 0;
     ListNode *p = head;
     while(head1 || head2)
     {
         if(head1 == 0)
         {
             if(head == 0)
             {
                 head = p = head2;
             }
             else
             {
                 p->next = head2;
                 p = p->next;
             }
             head2 = head2->next;
         }
         else if(head2 == 0)
         {
             if(head == 0)
             {
                 head = p = head1;
             }
             else
             {
                 p->next = head1;
                 p = p->next;
             }
             head1 = head1->next;
         }
         else
         {
             if(head2->val <= head1->val)
             {
                 if(head == 0)
                 {
                     head = p = head2;
                 }
                 else
                 {
                     p->next = head2;
                     p = p->next;
                 }
                 head2 = head2->next;
             }
             else
             {
                 if(head == 0)
                 {
                     head = p = head1;
                 }
                 else
                 {
                     p->next = head1;
                     p = p->next;
                 }
                 head1 = head1->next;
             }
         }
         p->next = 0;
     }
     return head;
 }

ListNode * SortList::sortList(ListNode *head)
{
        ListNode *p;
        ListNode *q;
        ListNode *pre = 0, *newHead = head;
        int len = getLen(head);
        for(int i = 1; i <= len/2; ++i)
        {
            ListNode *n1, *n2;
            printList(head);
            cout<<"merge len="<<i<<endl;
            n1 = head;
            cout<<"n1="<<n1->val<<endl;
            n2 = getK(n1, i+1);
            cout<<"n2="<<n2->val<<endl;

            while(n1 || n2)
            {
                p = n1;
                q = n2;
                n1 = getK(n2, i);
                if(n1)
                {
                    ListNode *tn = n1;
                    n1 = n1->next;
                    tn->next = 0;
                }
                n2 = getK(n1, i);
                if(n2)
                {
                    ListNode *tn = n2;
                    n2 = n2->next;
                    tn->next = 0;
                }
                cout<<"================"<<i<<endl;
                ListNode *pq = merge(p, q);
                printList(pq);
                if(pre == 0)
                {
                    pre = newHead = pq;
                }
                else
                {
                    ListNode *t = getK(pre, 2*i);
                    t->next = pq;
                    pre = pq;
                }
            }
            head = newHead;
            pre = 0;
        }
        return newHead;

}

void test_list_sort()
{

    int a[] ={3,2,4};
    ListNode *head = 0;
    for(int i = 0; i < sizeof(a)/sizeof(int); ++i)
        {
            ListNode *p = new ListNode(a[i]);
            if(head == 0)
                head = p;
            else
            {
                ListNode *t = getK(head, i);
                t->next = p;
            }
        }
    SortList sl;
    cout<<"=============="<<endl;
    sl.sortList(head);
}


/*
    int a[] = {1,3,3,1,3,1,3,3,2,3,2,2,1,1,1,3,2,2,1,1,2,2,2,3,3,1,1,2,2,2,1,2,1,1,2,3,3,2,2,3,2,3,2,2,2,1,1,3,2,3,3,1,1,1,2,2,1,2,2,2,2,3,1,3,1,1,1,2,1,2,2,2,1,3,2,2,2,3,3,2,3,3,1,1,2,2,1,2,1,3,2,1,3,3,1,2,1,1,1,1,1,2,1,2,2,2,2,3,
    3,3,1,1,3,2,1,1,2,1,3,3,2,2,1,3,1,3,1,3,2,2,3,2,3,2,2,1,2,3,1,3,1,2,3,3,2,3,3,3,1,1,2,3,1,2,3,2,1,1,
    2,3,1,1,3,1,2,2,3,2,1,3,1,2,1,3,2,1,1,2,2,2,1,3,1,3,2,3,3,1,1,3,1,2,1,2,3,1,2,1,1,3,1,3,3,1,1,1,2,2,
    1,3,1,2,2,3,2,1,3,2,1,3,2,2,3,3,2,2,1,3,2,2,2,2,2,3,2,2,3,1,3,2,1,3,2,1,2,3,3,3,1,2,2,3,1,1,2,2,3,2,
    1,1,1,1,1,3,2,2,2,1,3,2,1,2,3,2,1,1,2,1,3,3,1,3,1,2,2,1,2,3,2,3,3,1,2,3,2,2,3,3,2,1,3,2,2,2,3,3,3,1,
    1,2,1,1,2,3,3,3,1,3,2,2,1,2,2,1,2,3,1,3,2,2,3,3,3,1,2,3,2,1,3,1,1,2,2,1,1,1,2,2,3,1,3,1,2,3,3,3,2,2,
    3,1,1,1,3,2,1,1,3,1,2,3,3,3,2,1,2,3,2,3,2,1,3,2,2,2,2,1,1,3,1,1,1,3,2,2,2,1,2,3,2,3,2,2,1,2,3,2,1,1,
    3,1,3,3,1,1,1,1,1,2,3,3,3,1,3,2,2,3,1,1,3,1,1,1,3,1,1,2,2,2,1,1,1,1,2,1,3,3,3,1,2,2,2,2,3,3,1,2,2,3,
    1,3,1,2,1,2,2,3,3,1,3,3,2,1,3,1,1,3,1,2,3,3,3,3,1,1,3,3,3,3,2,2,2,1,1,3,2,2,2,3,1,3,3,3,1,1,3,1,3,2,
    3,1,2,3,2,2,3,3,3,1,2,1,2,1,2,3,1,2,2,2,1,1,1,2,2,1,2,1,1,1,3,2,1,2,3,2,2,2,1,2,3,2,2,1,3,3,3,1,2,3,
    3,1,1,3,3,1,1,2,1,2,3,1,2,3,2,2,3,2,1,3,1,3,1,2,2,2,2,1,2,3,3,2,2,2,3,2,2,1,2,2,3,1,3,1,1,1,2,3,3,2,
    2,3,3,2,3,1,1,2,2,2,3,2,2,1,1,3,2,2,3,3,3,3,1,2,3,3,1,3,3,1,2,2,1,3,2,3,3,2,3,2,1,2,1,2,2,3,3,2,3,3,
    1,1,2,1,3,2,2,3,1,2,1,3,1,1,3,3,3,3,2,3,3,3,1,3,2,2,2,3,3,1,2,1,2,3,2,2,2,2,3,3,1,1,3,3,2,1,3,2,2,3,
    2,3,2,2,2,3,1,2,1,3,2,2,1,2,2,3,2,2,2,2,2,1,1,2,1,3,3,2,2,2,1,3,3,3,3,2,3,3,2,3,3,1,3,3,1,3,2,2,2,2,
    2,1,2,2,3,3,3,1,2,3,1,3,2,2,2,2,3,1,1,1,3,2,3,3,2,3,1,2,1,2,2,1,2,2,3,3,1,2,3,2,2,3,3,1,1,1,2,1,2,3,
    3,2,2,2,2,3,1,1,1,3,3,1,1,1,3,3,3,2,3,3,1,1,1,2,3,2,2,2,2,1,2,2,3,1,3,1,2,3,1,3,3,1,2,3,2,2,3,3,1,1,
    2,1,2,3,3,3,2,1,2,1,2,3,1,2,2,1,2,2,2,1,2,3,3,3,3,1,2,1,3,1,1,2,1,3,1,3,2,3,2,3,3,1,2,2,2,3,3,2,1,1,
    3,1,2,1,3,1,2,1,2,2,2,1,3,1,1,2,2,1,2,1,2,3,3,1,1,3,1,1,1,2,2,3,1,3,3,3,3,2,2,1,3,2,3,2,2,1,3,3,2,1,
    2,1,2,2,3,1,2,2,1,2,2,3,1,3,3,2,3,1,1,1,3,3,3,3,3,3,1,1,1,3,3,2,2,1,1,3,2,2,2,3,3,3,1,2,2,1,1,3,3,3,
    2,2,2,2,3,1,2,1,2,2,3,3,3,2,2,2,1,1,1,3,1,1,1,1,1,1,1,2,3,1,3,1,1,3,1,2,1,3,2,2,3,1,2,3,3,2,3,1,1,2,
    2,3,3,2,2,1,2,2,1,2,2,1,2,1,3,2,1,2,3,1,1,2,3,2,2,2,3,2,3,3,1,1,1,3,3,1,1,2,1,1,1,2,3,3,2,3,3,3,1,2,
    3,2,2,2,2,2,2,2,1,1,2,2,1,3,1,1,2,3,1,2,3,2,1,2,2,1,3,3,2,2,1,2,1,3,1,3,2,1,1,3,2,3,1,1,2,3,1,1,1,3,
    2,2,3,2,3,1,2,2,3,1,3,2,1,1,3,2,2,1,3,2,1,2,3,3,1,3,3,3,1,1,2,1,1,2,3,3,2,2,3,2,1,1,2,3,1,1,3,2,3,2,
    1,2,3,2,1,1,1,1,3,2,3,2,3,1,3,2,1,3,1,3,3,2,2,3,2,3,1,3,2,1,2,2,2,3,3,2,1,2,3,1,1,3,1,2,2,2,3,2,3,1,
    1,2,1,1,3,1,3,2,1,1,1,3,1,1,3,3,3,3,1,2,3,2,3,2,1,2,1,3,1,3,1,2,2,3,2,3,2,3,3,3,3,1,1,2,2,3,1,1,3,2,
    1,1,2,1,2,1,1,1,1,1,1,2,3,3,3,3,2,3,1,2,3,3,1,1,3,1,1,1,2,1,1,2,2,2,2,2,1,2,2,2,2,2,2,1,3,3,1,2,2,1,
    2,1,1,1,1,2,2,3,2,2,2,3,1,3,1,2,2,2,3,3,3,2,1,2,1,1,3,3,2,3,1,2,1,2,2,3,2,3,3,3,3,1,1,1,1,1,1,2,3,1,
    1,3,1,3,2,3,1,1,1,2,1,1,2,2,2,3,2,2,2,1,3,1,1,1,1,2,3,2,3,2,2,1,3,1,2,1,2,1,2,2,3,1,2,3,3,2,1,1,3,2,
    3,1,3,1,1,1,2,3,2,1,3,3,1,3,3,3,3,2,2,3,3,1,3,2,2,3,3,2,3,3,3,1,1,2,2,2,2,1,3,3,1,3,2,2,3,1,2,1,1,3,
    1,1,2,1,1,3,1,1,3,2,2,2,2,2,3,2,1,3,3,2,1,1,2,2,3,2,1,2,1,2,1,2,1,1,1,3,2,2,2,1,3,3,2,3,2,1,1,3,3,1,
    3,1,3,3,3,3,3,3,3,3,3,2,3,2,2,2,2,2,2,1,1,1,2,3,1,2,2,2,3,1,2,2,1,2,2,1,1,2,3,1,2,2,2,3,3,1,1,3,2,3,
    2,2,3,1,2,1,1,1,2,3,3,1,1,2,1,2,3,3,2,2,3,1,3,3,3,3,1,1,3,2,2,3,2,1,3,1,3,2,1,2,1,2,1,3,2,3,1,3,2,2,
    3,3,3,1,2,3,3,1,1,2,1,2,1,3,2,1,1,1,2,2,2,2,2,1,2,1,3,2,1,2,2,1,1,2,3,3,1,3,2,2,3,3,2,1,3,2,1,3,3,2,
    2,1,3,2,1,3,2,3,2,2,1,2,1,1,3,1,1,3,3,3,3,1,2,3,3,3,3,2,3,2,3,3,3,3,1,1,2,2,1,2,2,2,3,2,1,2,1,2,3,1,
    1,1,3,1,2,3,2,3,2,2,2,3,1,2,3,2,1,1,1,1,1,2,3,1,3,2,2,3,3,3,2,1,2,2,1,3,2,2,1,2,3,1,3,3,1,3,3,2,2,1,
    1,2,3,1,1,3,3,1,3,3,3,3,2,3,1,2,2,1,1,1,1,1,3,1,3,2,3,2,1,2,2,1,2,3,2,1,1,3,2,3,2,3,3,1,2,1,2,3,3,2,
    3,3,2,3,2,3,3,3,1,2,3,2,1,2,3,2,2,1,3,3,3,1,2,3,3,1,2,1,1,2,1,2,1,2,2,3,3,2,1,3,1,1,1,2,2,1,3,3,1,1,
    2,2,3,2,3,2,3,3,1,3,1,2,3,3,1,2,2,1,1,2,1,1,3,3,2,3,3,1,2,3,3,2,2,3,1,2,3,3,3,3,1,2,3,1,2,2,1,1,3,1,
    };
    */