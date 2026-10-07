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

class Solution
{
public:
    int diameter = 0;

    int height(TreeNode *root)
    {
        if (root == NULL)
            return 0;

        int lh = height(root->left);
        int rh = height(root->right);

        diameter = max(diameter, lh + rh);

        return 1 + max(lh, rh);
    }

    int diameterOfBinaryTree(TreeNode *root)
    {
        height(root);
        return diameter;
    }
};

/*

Key idea
At every node:

lh + rh

is the diameter passing through that node.

We calculate the height and simultaneously update the answer.

Important distinction:

height = number of nodes in longest downward path
diameter = number of edges in longest path between two nodes

That's why lh + rh gives the diameter.

*/