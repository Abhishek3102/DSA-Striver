// Q4 [MEDIUM - related] Min depth, diameter, balanced check
// WHY: if Zeus asks "depth of tree", follow-ups are min-depth, diameter,
// and is-balanced. All three reuse the same height() helper - learn together.
#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left, *right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

int height(TreeNode *r) { return r ? 1 + max(height(r->left), height(r->right)) : 0; }

// Min depth: nodes from root to nearest LEAF (BFS is natural; recursion must
// NOT do 1+min when one child is missing - classic paper trap).
int minDepth(TreeNode *r)
{
    if (!r)
        return 0;
    if (!r->left)
        return 1 + minDepth(r->right); // since left child missing, so we go to right
    if (!r->right)
        return 1 + minDepth(r->left);                      // since right child missing, we go to left
    return 1 + min(minDepth(r->left), minDepth(r->right)); // when both left right exists, we calculate min of them using recursion
}

// Diameter (longest path in EDGES): post-order returns height, updates ans
int diameterOfBinaryTree(TreeNode *root)
{
    int ans = 0;
    function<int(TreeNode *)> dfs = [&](TreeNode *n) -> int
    {
        if (!n)
            return 0;
        int L = dfs(n->left), R = dfs(n->right);
        ans = max(ans, L + R);
        return 1 + max(L, R);
    };
    dfs(root);
    return ans;
}

// Balanced: |hL - hR| <= 1 everywhere; -1 sentinel = unbalanced
int checkBal(TreeNode *r)
{
    if (!r)
        return 0;
    int L = checkBal(r->left);
    if (L == -1)
        return -1;
    int R = checkBal(r->right);
    if (R == -1)
        return -1;
    if (abs(L - R) > 1)
        return -1;
    return 1 + max(L, R);
}
bool isBalanced(TreeNode *r) { return checkBal(r) != -1; }

int main()
{
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    cout << "height=" << height(root) << " (3)  minDepth=" << minDepth(root)
         << " (2 via 1->3)  diameter=" << diameterOfBinaryTree(root)
         << " (3 edges: 4-2-1-3)  balanced=" << (isBalanced(root) ? "yes" : "no") << " (yes)\n";
    // Skewed: 1->2->3 : height 3, minDepth 3, diameter 2, balanced no
    TreeNode *s = new TreeNode(1);
    s->right = new TreeNode(2);
    s->right->right = new TreeNode(3);
    cout << "skewed: height=" << height(s) << " minDepth=" << minDepth(s)
         << " diameter=" << diameterOfBinaryTree(s)
         << " balanced=" << (isBalanced(s) ? "yes" : "no") << "\n";
    return 0;
}
