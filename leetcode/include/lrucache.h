#ifndef LRUCACHE_H
#define LRUCACHE_H
#include "include/header.h"

class LRUCache
{
    public:
        LRUCache(int);
        virtual ~LRUCache();
        void set(int key, int value);
        int get(int key);
    protected:
    private:
        list<pair<int, int> > caches;
        int max_pages;
};
void test_caches();
#endif // LRUCACHE_H
