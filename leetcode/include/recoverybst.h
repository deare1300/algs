#ifndef RECOVERYBST_H
#define RECOVERYBST_H
#include "include/treenode.h"

class RecoveryBST
{
    public:
        RecoveryBST();
        virtual ~RecoveryBST();
        void recovery(TreeNode *root);
        void findNode(TreeNode *root, TreeNode *pre);
    protected:
    private:
        TreeNode *first;
        TreeNode *second;
};

void test_recovery_bst();

#endif // RECOVERYBST_H
