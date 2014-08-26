a#ifndef __TREE_H_
#define __TREE_H_

#include <vector>
#include <stack>
#include <cstdio>

#define DEBUG
//#undef DEBUG
using namespace std;

template<class T>
struct TreeNode {
    typedef T value_type;
    
    TreeNode *left;
    TreeNode *right;
    value_type val;
    TreeNode(T val):left(0), right(0),val(val) { }
};

template<class T>
void destroy_node(TreeNode<T> *node) {
    if(node == 0) return;
    delete node;
}

template<class T>
void destroy_tree(TreeNode<T> *root) {
    if(root == 0) return;
    destroy_tree(root->left);
    destroy_tree(root->right);
    destroy_node(root);
}

template<class T>
void __inorderTraversal(TreeNode<T> *root) {
    if(root == 0) return;
    __inorderTraversal(root->left);
    printf("%d\t", root->val);
    __inorderTraversal(root->right);
}

template<class T>
vector<T> inorderTraversal(TreeNode<T> *root) {
    vector<T> v; // empty initailize
    stack<TreeNode<T> *> s;
#ifdef DEBUG
    __inorderTraversal(root);
    printf("\n");
#endif
    while(root || !s.empty()) {
#ifdef DEBUG
#endif
        if(root) s.push(root);
        while(root && root->left) {
            s.push(root->left);
            root = root->left;
        }
#ifdef DEBUG
#endif
 
        root = 0;
        if(s.empty())
            break;
        root = s.top();
        s.pop();
        v.push_back(root->val);
#ifdef DEBUG
#endif
        root = root->right;
#ifdef DEBUG
#endif
         
    }
       return v;
}

template<class T>
void __preorderTraversal(TreeNode<T> *root) {
}

template<class T>
vector<T> preorderTraversal(TreeNode<T> *root) {
    vector<T> v;


    return v;
}
#endif
