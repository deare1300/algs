#include "include/flatten.h"
#include "include/treenode.h"

Flatten::Flatten()
{
    //ctor
}

Flatten::~Flatten()
{
    //dtor
}

void Flatten::flatten(TreeNode *root) {
    if(root == NULL) return;
    right = root;
    TreeNode *p;
    while(right->right) {
        right = right->right;
    }
    p = root->right;
    while(p) {
        buildRight(p->left);
        p->left = NULL;
        p = p->right;
    }
    buildRight(root->left);
    root->left = NULL;
    cout<<"before"<<endl;
    printTree(root);
    sortTree(root);
}

void Flatten::buildRight(TreeNode *root) {
    if(root == NULL) return;
    buildRight(root->left);
    buildRight(root->right);
    right->right = root;
    right = root;
    root->left  = NULL;
    root->right = NULL;
}

void Flatten::sortTree(TreeNode *root) {

    while(true) {
        bool change = false;
        TreeNode *p = root;
        while(p) {
            if(p->right) {
                if(p->val > p->right->val) {
                    int temp = p->val;
                    p->val = p->right->val;
                    p->right->val = temp;
                    change = true;
                }
            }
            p = p->right;
        }
        if(change == false)
            break;
    }
}


void test_flatten()
{
    TreeNode *root = new TreeNode(1);
    TreeNode * left = root->left = new TreeNode(2);
    TreeNode * right = root->right = new TreeNode(4);
    left->right = new TreeNode(3);
    right->left = new TreeNode(5);
    printTree(root);
    Flatten fl;
    fl.flatten(root);
    printTree(root);
}
