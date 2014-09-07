#include "include/recoverybst.h"

RecoveryBST::RecoveryBST()
{
    //ctor
}

RecoveryBST::~RecoveryBST()
{
    //dtor
}

void RecoveryBST::recovery(TreeNode *root)
{
    first = NULL;
    second = NULL;
}


void RecoveryBST::findNode(TreeNode *root, TreeNode *pre)
{
    if(root == NULL) return;
    if(pre && root->val < pre->val)
    {
        if(first == NULL)
        {
            first = pre;
        }
        second = root;
    }
    findNode(root->right, root);
}
