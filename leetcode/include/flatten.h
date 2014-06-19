#ifndef FLATTEN_H
#define FLATTEN_H

#include "include/treenode.h"

class Flatten
{
    public:
        Flatten();
        virtual ~Flatten();
        void flatten(TreeNode *root);
        void sortTree(TreeNode *root);
        void buildRight(TreeNode *root);
    protected:
    private:
        TreeNode *right;
};

void test_flatten();
#endif // FLATTEN_H
