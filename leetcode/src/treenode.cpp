#include "include/treenode.h"
#include "header.h"

void printTree(TreeNode *root, int space)
{
    if(root == NULL) return;
    cout<<string(space, '-')<<root->val<<endl;
    printTree(root->left, space+1);
    printTree(root->right, space+1);
}

vector<int> pre_order_tree(TreeNode *root)
{
    vector<int> res;
    stack<TreeNode*> q;
    if(!root) return res;
    while(root)
    {
        res.push_back(root->val);
        q.push(root);
        root = root->left;
        while(root)
        {
            res.push_back(root->val);
            root = root->left;
        }

        while(!q.empty())
        {
            root = q.top();
            q.pop();
            if(root->right)
            {
                root = root->right;
                break;
            }
        }
    }
    return res;
}

