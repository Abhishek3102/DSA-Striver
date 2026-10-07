#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// Because this is a BST, we can use the ordering property:

// left < root < right

class Solution
{
public:
    TreeNode *lowestCommonAncestor(TreeNode *root,
                                   TreeNode *p,
                                   TreeNode *q)
    {

        if (p->val < root->val && q->val < root->val)
        {
            return lowestCommonAncestor(root->left, p, q);
        }

        if (p->val > root->val && q->val > root->val)
        {
            return lowestCommonAncestor(root->right, p, q);
        }

        return root;
    }
};

/*

The important observation
If both p and q are smaller:

p->val < root->val && q->val < root->val

go left.

If both are bigger:

p->val > root->val && q->val > root->val

go right.

Otherwise, we've found the split point:

return root;

For example:

        6
       / \
      2   8
     / \
    0   4
       / \
      3   5

For p = 2, q = 8:

6

is the LCA because they're on different sides of 6.

*/