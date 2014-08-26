#include "leetcode/solution.h"
#include "leetcode/tree.h"
#include "leetcode/print.h"

#include <iostream>
#include <vector>
#include <string>

typedef TreeNode<int> treeNode;
typedef ListNode<int> listNode;
/*     1
 * 2       4
 *   3  4    5
 *       2
 */


treeNode *process_tree() {
    treeNode *root = new treeNode(1);
    treeNode *tmp = root->left = new treeNode(2);
    tmp->right = new treeNode(3);

    tmp = root->right = new treeNode(4);
    tmp = tmp->left = new treeNode(4);
    tmp->right = new treeNode(2);

    tmp = root->right;
    tmp->right = new treeNode(5);
    return root;
}

void test_deleteDuplicates() {
    int a[] = {1, 1, 2, 3, 3, 4, 5, 6, 6};
    listNode *head = process_list(&a[0], &a[sizeof(a)/sizeof(a[0])], (int*)0);
    print_list(head);
    Solution<int> solution;
    listNode *result = solution.deleteDuplicates(head);
    print_list(result);
}

void test_maxDepth() {
    Solution<int> solution;
    treeNode *tr = process_tree();
    std::cout<<solution.maxDepth(tr)<<std::endl;
   /*
    *
    * something wrong with this method
    */
    
    vector<int> v = inorderTraversal(tr);
    //print_vector(v);
    dump(v.begin(), v.end());
    destroy_tree(tr);
}

void test_maxProfit() {
    Solution<int> solution;
    int a[] = {3, 1, 5, 4, 2, 4, 1, 6};
    const int size = sizeof(a)/sizeof(a[0]);
    dump(&a[0], &a[size]);
    std::vector<int> v(&a[0], &a[size]);
    std::cout<<solution.maxProfit(v)<<std::endl;
}

void test_searchInsert() {
    Solution<int> solution;
    int a[] = {1, 2, 3, 4, 5, 6, 9, 10, 12};
    const int size = sizeof(a)/sizeof(a[0]);
    dump(&a[0], &a[size]);
    std::cout<<solution.searchInsert(a, size, -1)<<"=0"<<std::endl;
    std::cout<<solution.searchInsert(a, size, 1)<<"=0"<<std::endl;
    std::cout<<solution.searchInsert(a, size, 2)<<"=1"<<std::endl;
    std::cout<<solution.searchInsert(a, size, 7)<<"=6"<<std::endl;
    std::cout<<solution.searchInsert(a, size, 12)<<"=8"<<std::endl;
    std::cout<<solution.searchInsert(a, size, 15)<<"=9"<<std::endl;
}

void test_climbStairs() {
    Solution<int> solution;
    for(int i = 0; i < 21; ++i)
        std::cout<<solution.climbStairs(i)<<'\t';
    std::cout<<std::endl;
}

void test_threeSingleNumber() {
    Solution<int> solution;
    int a[] = {1, 1, 1, 2, 2, 2, 3, 3, 3, 5};
    const int size = sizeof(a)/sizeof(a[0]);
    dump(&a[0], &a[size]);
    std::cout<<solution.__threeSingleNumber(a, size)<<endl;
}

void test_maxSubArray() {
    int a[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    const int size = sizeof(a)/sizeof(a[0]);
    dump(&a[0], &a[size]);
    Solution<int> solution;
    std::cout<<solution.maxSubArray(a, size)<<std::endl;
}

void test_removeElement() {
    int a[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    const int size = sizeof(a)/sizeof(a[0]);
    dump(&a[0], &a[size]);
    Solution<int> solution;
    cout<<solution.removeElement(a, size, 1)<<endl;
    cout<<"after remove the element"<<endl;
    dump(&a[0], &a[size]);
}

#define maxDepth
#define maxProfit

void test_solution() {
    using namespace std;

#define removeElement
#ifdef removeElement
    cout<<"remove the element"<<endl;
    test_removeElement();
#endif

#define maxSubArray
#ifdef maxSubArray
    cout<<"maxSubArray"<<endl;
    test_maxSubArray();
#endif

#define threeSingleNumber
#ifdef  threeSingleNumber
    cout<<"find the single number in an array"<<endl;
    test_threeSingleNumber();
#endif

#define climbStairs
#ifdef  climbStairs
    cout<<"climbStairs as the Fib"<<endl;
    test_climbStairs();
#endif

#define searchInsert
#ifdef  searchInsert
    cout<<"search if in return index otherwise the rightmost index"<<endl;
    test_searchInsert();
#endif

#define deleteSortedDuplicates
#ifdef  deleteSortedDuplicates
    cout<<"delete sorted duplicates elements from the listnode"<<endl;
    test_deleteDuplicates();
#endif
#ifdef maxDepth
    cout<<"maxDepth()"<<endl;
    test_maxDepth();
#endif

#ifdef maxProfit
    cout<<"maxProfit"<<endl;
    test_maxProfit();
#endif
}
