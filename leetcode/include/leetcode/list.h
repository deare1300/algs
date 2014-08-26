#ifndef __LIST_H_
#define __LIST_H_

#include <iostream>

template<class T>
struct ListNode {
    T val;
    ListNode *next;
    ListNode(T val): val(val), next(0) { } 
    ListNode(const ListNode&) { throw "deep copy may be cost a lot so forbidden"; }
};

template<class Iterator, class T>
ListNode<T> *process_list(Iterator begin, Iterator end, T*) {
    ListNode<T> *head = 0, *p;
    if(begin == end) return head;
    p = head = new ListNode<T>(*begin);
    while(++begin != end) {
        p->next = new ListNode<T>(*begin);
        p = p->next;
    }
    return head;
}

template<class T>
void print_list(ListNode<T> *head) {
    using namespace std;
    while(head) {
        cout<<head->val<<'\t';
        head = head->next;
    }
    cout<<endl;
}

template<class T>
ListNode<T> *copyList(ListNode<T> *list) {
    ListNode<T> *head = 0;
    if(list == 0) return head;
    
    ListNode<T> *p = head = new ListNode<T>(list->val);
    list = list->next;
    while(list) {
        p->next = new ListNode<T>(list->val);
        p = p->next;
    }
    return head;
}

template<class T>
ListNode<T> *mergeTwoLists(ListNode<T> *l1, ListNode<T> *l2) {
    //throw "not compelte yet";
    ListNode<T> *head = 0;
    ListNode<T> *tail = 0;
    if(l1 == 0)
        return copyList(l2);
    if(l2 == 0)
        return copyList(l1);
    
    if(l1->val < l2->val) {
        head = tail = new ListNode<T>(l1->val);
        l1 = l1->next;
    }
    else {
        head = tail = new ListNode<T>(l2->val);
        l2 = l2->next;
    }

    while(l1 && l2) {
        if(l1->val < l2->val) {
            tail->next =  new ListNode<T>(l1->val);
            l1 = l1->next;
        }
        else {
            tail->next = new ListNode<T>(l2->val);
            l2 = l2->next;
        }
        tail = tail->next;
    }
    
    if(l1) {
        tail->next = copyList(l1);
    }
    if(l2) {
        tail->next = copyList(l2);
    }
    return head;
}

#endif
