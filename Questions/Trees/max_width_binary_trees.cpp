#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(0), left(left), right(right) {}
};

int widthBinaryTree(TreeNode *root)
{
    // If the tree is empty, return 0 width.
    if (!root)
        return 0;

    int ans = 0; // Variable to store the maximum width.

    // Queue to perform level-order traversal. Each element is a pair: node and its index.
    queue<pair<TreeNode *, int>> q;
    q.push({root, 0}); // Start with the root node at index 0.

    // Level-order traversal of the tree.
    while (!q.empty())
    {
        int size = q.size(); // Number of nodes at the current level.

        int mmin = q.front().second; // The index of the leftmost node at the current level.
        int first, last;             // To store the index of the first and last node at the current level.

        // Traverse all nodes at the current level.
        for (int i = 0; i < size; i++)
        {
            // Get the current node and its index, adjusting the index to start from zero.
            int cur_id = q.front().second - mmin;
            TreeNode *node = q.front().first;
            q.pop(); // Pop the front node from the queue.

            // Record the first and last node indices at the current level.
            if (i == 0)
                first = cur_id;
            if (i == size - 1)
                last = cur_id;

            // Push the left child to the queue with the new index.
            if (node->left)
                q.push({node->left, cur_id * 2 + 1});

            // Push the right child to the queue with the new index.
            if (node->right)
                q.push({node->right, cur_id * 2 + 2});
        }

        // Calculate the width at this level and update the maximum width.
        ans = max(ans, last - first + 1);
    }

    return ans;
}

int main()
{
    // simple binary tree:
    //           1
    //         /   \
    //        2     3
    //       / \   / \
    //      4   5 6   7

    TreeNode *root = new TreeNode(1);     // Root node with value 1.
    root->left = new TreeNode(2);         // Left child of root with value 2.
    root->right = new TreeNode(3);        // Right child of root with value 3.
    root->left->left = new TreeNode(4);   // Left child of node 2 with value 4.
    root->left->right = new TreeNode(5);  // Right child of node 2 with value 5.
    root->right->left = new TreeNode(6);  // Left child of node 3 with value 6.
    root->right->right = new TreeNode(7); // Right child of node 3 with value 7.

    cout << "Maximum width of the binary tree: " << widthBinaryTree(root) << endl;

    return 0;
}