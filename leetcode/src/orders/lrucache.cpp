#include "include/lrucache.h"
#include "include/header.h"

LRUCache::LRUCache(int ca):max_pages(ca)
{
    //ctor
}

LRUCache::~LRUCache()
{
    //dtor
}

list<pair<int, int> >::iterator find_if_equal(list<pair<int, int> > &l, int &value)
{
    for(list<pair<int, int> >::iterator iter = l.begin(); iter != l.end(); ++iter)
    {
        if(iter->first == value)
            return iter;
    }
    return l.end();
}

void LRUCache::set(int key, int value)
{
    list<pair<int, int> >::iterator iter = find_if_equal(caches, key);
    if(iter != caches.end())
    {
        pair<int, int> temp(*iter);
        caches.erase(iter);
        temp.second = value;
        caches.push_front(temp);

    }
    else
    {
        pair<int, int> temp = make_pair(key, value);
        if(max_pages == caches.size())
        {
            caches.pop_back();
            caches.push_front(temp);
        }
        else
        {
            caches.push_front(temp);
        }
    }
}

int LRUCache::get(int key)
{
    list<pair<int, int> >::iterator iter = find_if_equal(caches, key);
    if(iter == caches.end())
        return -1;
    return iter->second;

}


class ListNode1
{
public:
    int key;
    int value;
    ListNode1 *next;
    ListNode1 *pre;
    ListNode1(int key, int value):key(key), value(value), next(NULL), pre(NULL) {}
};

class LRULink
{
public:
    ListNode1 *head;
    ListNode1 *tail;
    int len;
    LRULink():head(NULL), tail(NULL), len(0){}
};


class LRUCache1{
private:
    int capacity;
    LRULink *link;
    ListNode1 *target;
public:
    LRUCache1(int capacity):capacity(capacity) {
        link = new LRULink();
    }

    int get(int key)
    {
        ListNode1 *p = link->head;
        target = NULL;
        for(; p ; p = p->next)
        {
            if(p->key == key)
            {
                target = p;
                return p->value;
            }
        }
        return -1;
    }

    LRUCache1& set(int key, int value) {
        cout<<"in set"<<endl;
        int index = get(key);
        if(capacity == 0)
        {
            return *this;
        }
        if(index == -1)
        {
            cout<<"not found key:"<<key<<endl;
            if(link->len < capacity)
            {
                cout<<"not found key little"<<endl;
                ListNode1 *temp = new ListNode1(key, value);
                if(link->head == NULL)
                {
                    link->head = link->tail = temp;
                }
                else
                {
                    //set pre here
                    link->head->pre = temp;
                    temp->next = link->head;
                    link->head = temp;
                }
                printCache();
                link->len++;
            }
            else
            {
                if(capacity == 1 || link->len == 1)
                {
                    delete link->head;
                    link->head = link->tail = new ListNode1(key, value);
                }
                else
                {
                    ListNode1 *temp = new ListNode1(key, value);
                    //delete the tail Node !!!
                    ListNode1 *tails = link->tail;
                    link->tail = link->tail->pre;
                    link->tail->next = NULL;
                    link->head->pre = temp;
                    temp->next = link->head;
                    link->head = temp;
                    delete tails;
                }
            }
        }
        else
        {
            cout<<"found key:"<<key<<endl;
            target->value = value;
            if(target == link->head)
            {
                return *this;
            }
            else
            {
                cout<<"found key not head:"<<key<<endl;
                if(target == link->tail)
                {
                    cout<<"found key tail:"<<key<<endl;
                    link->tail = link->tail->pre;
                    link->tail->next = NULL;
                    link->head->pre = target;
                    target->next = link->head;
                    link->head = target;
                    cout<<"found key tail end:"<<key<<endl;
                }
                else
                {
                    target->pre->next = target->next;
                    target->next->pre = target->pre;
                    link->head->pre = target;
                    target->next = link->head;
                    link->head = target;
                }
            }

        }
        cout<<"return"<<endl;
        return *this;
    }
    void printCache()
    {
        ListNode1 *p = link->head;
        while(p)
        {
            cout<<'('<<p->key<<','<<p->value<<')'<<'\t';
            p = p->next;
        }
        cout<<endl;
    }
};


void test_caches()
{
    /*
    LRUCache lru(2);
    lru.set(1, 1);
    cout<<lru.get(1)<<'\t'<<endl;
    lru.set(1, 0);
    cout<<lru.get(1)<<'\t'<<endl;
    lru.set(2, 2);
    lru.set(3, 3);
    cout<<lru.get(2)<<'\t'<<endl;
    */
    LRUCache1 LC(2);
    cout<<"---------------------------------------------1"<<endl;
    LC.set(2,1).set(1,1);
    LC.printCache();
    //cin.get();
    cout<<LC.get(2)<<endl;
    cout<<"---------------------------------------------2"<<endl;
    LC.set(4,1);
    LC.printCache();
    //cin.get();
    cout<<LC.get(1)<<endl;
    cout<<"---------------------------------------------3"<<endl;
}
