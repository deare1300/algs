#ifndef _YOUDAO_H_
#define _YOUDAO_H_

#include <vector>
#include <set>
//#include <unordered_map>
//#include <unordered_set>
#include <algorithm>
#include <string>
#include <tr1/unordered_map>
#include <tr1/unordered_set>
#include "leetcode/tree.h"
#include "leetcode/print.h"

using namespace std;

template<class T>
class YouDao {
    public:
        
    private:
        /*
         * first interview 
         * three problems
         *
         */

        /*
         * problem one from n+1 numbers find the duplicate number
         * the number is range 1...n
         */
        T __findDuplicate(vector<T> &arr, T n);
        
        /*
         * is tree contain the other tree
         */
        bool __isContain(TreeNode<T> *tr1, TreeNode<T> *tr2);

        /*
         *find the min length of the substring that contain all the chars in a set
         */
        int __minLength(const string &str, tr1::unordered_set<char> &sets);

        
        /*
         * second interview
         * three problems 
         * 1.write a binaryTree with object program
         * 2.red hat problem
         * 3.permutation
         */
        /*
         *
         */

        static bool next_permutation(T a[], int n);
        static void all_permutation(T a[], int n);
};

template<class T>
T YouDao<T>::__findDuplicate(vector<T> &arr, T n) {
    vector<int> flag(n+1, 0);
    typedef typename vector<T>::iterator Auto;
    for(Auto it = arr.begin(); it != arr.end(); ++it) {
        ++flag[*it];
        if(flag[*it] == 2)
            return *it;
    }
    return -1;
}


template<class T>
int YouDao<T>::__minLength(const string &str, std::tr1::unordered_set <char> &sets) {
    int len = str.length();
    int sLen = sets.size();
    int pre = 0;
    int back = 0;
    using namespace std::tr1;
    unordered_map<char, int> maps;
    int minLen = len+1;
    for(; pre < len; ++pre) {
        if(sets.find(str[pre]) != sets.end()) {
            ++maps[str[pre]];
            if(maps.size() == sLen) {
                if(pre-back+1 < minLen) {
                    minLen = pre-back+1;
                    if(minLen == sLen) 
                        return minLen;
                }
                while(maps.size() == sLen) {
                    for(; pre < back; ++ pre) {
                       if(sets.find(str[pre]) != sets.end()) {
                           if(--maps[str[pre]] == 0) {
                               maps.erase(str[pre]);
                           }
                       }
                    }
                }
            }
        }

    }
    return minLen;
}

template<class T>
bool YouDao<T>::next_permutation(T a[], int n) {
    int i = n-1;
    while(i > 0) {
        if(a[i] > a[i-1]) {
            for(int j = n-1; j >= i; --j) {
                if(a[j] > a[i-1]) {
                    swap(a[i-1], a[j]);
                    sort(&a[i], &a[n]);
                    return true;
                }
            }
        }
    }
    return false;
}

template<class T>
void YouDao<T>::all_permutation(T a[], int n) {
    dump(&a[0], &a[n]);
    sort(&a[0], &a[n]);
    while(next_permutation(a, n)) {
        dump(&a[0], &a[n]);
    }

}

#endif
