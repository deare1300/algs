#include "maximum_depth_tree.h"
#include "treenode.h"
#include "header.h"
Maximum_Depth_Tree::Maximum_Depth_Tree()
{
    //ctor
}

Maximum_Depth_Tree::~Maximum_Depth_Tree()
{
    //dtor
}

int Maximum_Depth_Tree::maxDepth(TreeNode *root)
{
    //queue<vector<TreeNode *> > v;
    vector<TreeNode *> temp;
    int res = 0;
    if(!root) return 0;
    //v.push(vector<TreeNode *>(1, root));
    temp.push_back(root);
    while(temp.size() > 0)
    {
        vector<TreeNode *> front = temp;
        ++res;
        temp.clear();
        for(vector<TreeNode *>::iterator it = front.begin(); it != front.end(); ++it)
        {
            if((*it)->left)
                temp.push_back((*it)->left);
            if((*it)->right)
                temp.push_back((*it)->right);
        }
    }
    return res;
}

void test_max_depth()
{
    Maximum_Depth_Tree md;
}
