#ifndef __SOLUTION_H_
#define __SOLUTION_H_

#include "leetcode/tree.h"
#include "leetcode/list.h"

#include <cstdio>
#include <vector>
using namespace std;

template<class T>
class Solution {
public:
    typedef TreeNode<T> TreeNode;
    typedef ListNode<T> ListNode;
private:
    struct dynamic {
        static T maxSubArray(T A[], int n);
    };

public:
    /*
     *recursion algs
     */
    /*
     *1) positive recursion
     */
    T climbStairs(T n);
    /*
     *2) none positive recursion
     */
    T totalNQueens(T n);
    /*
     *the algs about array
     */
    template<typename INT>
    INT maxProfit(std::vector<INT> &price); 
    int searchInsert(T a[], int n, T target);
    int __threeSingleNumber(int a[], int n);
    T maxSubArray(T A[], int n) { return dynamic::maxSubArray(A, n); }
    int removeElement(T A[], int n, T elem);


    /*
     *the algs about tree
     */
    int maxDepth(TreeNode *root);
   
    bool hasCycle(ListNode *head);
    ListNode *__deleteSortedDuplicates(ListNode *head);
    ListNode *deleteDuplicates(ListNode *head, bool sorted = true);
private:
    /*
     * total queen 
     */
    T __addQueen(vector<T> &flag, T line);
    bool __isLegalQueen(vector<T> &flag, T line, T col);
};

template<class T>
typename Solution<T>::ListNode* Solution<T>::deleteDuplicates(ListNode* head, bool sorted) {
    if(sorted) return __deleteSortedDuplicates(head);
    else throw "not compeleted the unsorted deleteDuplicates";
    return 0;
}

template<class T>
typename Solution<T>::ListNode* Solution<T>::__deleteSortedDuplicates(ListNode* head) {
    typename Solution<T>::ListNode *pre = head, *newHead, *tmp;
    newHead = head;
    if(head == 0) return head;
    head = head->next;
    while(head) {
        if(head->val == pre->val) {
            tmp = head;
            head = head->next;
            pre->next = head;
            //destroy_node(tmp);
            delete tmp;
        }
        else {
            pre = head;
            head = head->next;
        }
    }
    return newHead;
}

template<class T>
int Solution<T>::maxDepth(TreeNode *root) {
    if(root == 0) return 0;
    int left = maxDepth(root->left);
    int right = maxDepth(root->right);
    return left > right ? (left+1):(right+1);
}

template<class T>
template<typename INT>
INT Solution<T>::maxProfit(std::vector<INT> &price) {
    int result = 0;
    typename vector<INT>::iterator pre = price.begin();

    for(typename std::vector<INT>::iterator it = price.begin(); it != price.end(); ++it) {
        if(*it > *pre) {
            result = (*it) - (*pre);
        }
        pre = it;
    }
    return result;
}


template<class T>
bool Solution<T>::hasCycle(ListNode *head) {
    if(head == 0) return false;
    ListNode *one_step = head;
    ListNode *two_step = head;
    
    two_step = two_step->next;
    while(one_step != two_step) {
        if(two_step == 0 || two_step->next == 0) return false;
        one_step = one_step->next;
        two_step = two_step->next->next;
    }
    return true;
}

template<class T>
int Solution<T>::searchInsert(T A[], int n, T target) {
    int left = 0;
    int right = n-1;
    int mid;
    while(left <= right) {
        mid = left+(right-left)/2;
        if(A[mid] == target) return mid;
        else if(A[mid] < target) {
            left = mid+1;
        }
        else {
            right = mid-1;
        }
    }

    if(right < 0)
        return 0;
    if(left == n)
        return n;
    return left;
}

template<class T>
T Solution<T>::climbStairs(T n) {
    if(n <= 0) return 0;
    T *a = new T[n+1]; 
    T result;
    a[0] = 0;
    a[1] = 1;
    for(T i = 2; i <= n; ++i) {
        a[i] = a[i-1] + a[i-2];
    }
    result = a[n];
    delete[] a;
    return result;
}

template<class T>
int Solution<T>::__threeSingleNumber(int A[], int n) {
    const int size_int = sizeof(int)*8;
    int result = 0;
#ifdef DEBUG 
#endif
    for(int i = 0; i < size_int; ++i) {
        int count = 0;
        unsigned int flag = (unsigned int)1 << i;

#ifdef DEBUG
#endif
        for(int j = 0; j < n; ++j) {
            if(A[j] & flag) {
#ifdef DEBUG
#endif
                ++count;
            }
        }
        if(count % 3 != 0) {
            result |= flag;
        }
#ifdef DEBUG
        //std::cout<<count<<'\t'<<result<<endl;
#endif
    }
    return result;
}

template<class T>
T Solution<T>::dynamic::maxSubArray(T A[], int n) {
    if(n <= 0) return 0;
    T max = A[0];
    T sum = 0;
    for(int i = 0; i < n; ++i) {
        if(sum < 0) 
            sum = A[i];
        else 
            sum += A[i];
        if(sum > max) {
            max = sum;
        }
    }
    return max;
}

template<class T>
int Solution<T>::removeElement(T A[], int n, T elem) {
    if(n == 0) return 0;
    int last = n-1;
    for(int i = 0; i < last; ) {
        if(A[i] == elem) {
            std::swap(A[i], A[last]);
            --last;
        }
        else {
            ++i;
        }
    }
    return last+1;
}

template<class T>
T Solution<T>::totalNQueens(T n) {
    //throw "not complete nqueen";
    vector<T> flag(n, 0);
    return __addQueen(flag, 0);
}

template<class T>
T Solution<T>::__addQueen(vector<T> &flag, T line) {
    size_t len = flag.size();
    T result = 0;
    if(len == line) {  return 1; }
    for(T i = 0; i < len; ++i) {
        if(__isLegalQueen(flag, line, i)) {
            flag[line] = i;
            result += __addQueen(flag, line+1);
        }
    }
    return result;
}

template<class T>
bool Solution<T>::__isLegalQueen(vector<T> &flag, T line, T col) {
    for(T i = 0; i < line; ++i) {
        if(flag[i] == col) return false;
        if(abs(i - line) == abs(flag[i] - col)) return false;
    }
    return true;
}

void test_solution();
#endif
