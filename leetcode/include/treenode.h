#ifndef TREENODE_H
#define TREENODE_H
#include "include/header.h"
struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

void printTree(TreeNode *root, int space = 0);
#endif // TREENODE_H
