#include <bits/stdc++.h>
using namespace std;

// balanced bt - for every node, height(left) - height(right) <= 1;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

bool checkBalancedBT(TreeNode *root)
{
    if (root == NULL)
    {
        return true;
    }

    int lh = findHleft(root->left);
    int rh = findHright(root->right);

    if (abs(rh - lh) > 1)
        return false;

    bool left = checkBalancedBT(root->left);
    bool right = checkBalancedBT(root->right);

    if (!left || !right)
        return false;
    return true;
}

int height(TreeNode *root)
{
    if (root == NULL)
        return 0;

    return 1 + max(height(root->left), height(root->right));
}

bool checkBalancedBT(TreeNode *root)
{
    if (root == NULL)
        return true;

    int lh = height(root->left);
    int rh = height(root->right);

    if (abs(lh - rh) > 1)
        return false;

    bool left = checkBalancedBT(root->left);
    bool right = checkBalancedBT(root->right);

    return left && right;
}
