#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int val;         // Value of the node
    TreeNode *left;  // Pointer to the left child
    TreeNode *right; // Pointer to the right child

    // Default constructor
    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    // Constructor that initializes with a value
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    // Constructor that initializes with a value and left, right children
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// Function to perform level order traversal on a binary tree
vector<vector<int>> levelOrder(TreeNode *root)
{
    vector<vector<int>> ans; // Vector to store the result of level order traversal

    if (root == NULL)
        return ans; // If the tree is empty, return an empty result

    queue<TreeNode *> q; // Queue to help in level-wise traversal
    q.push(root);        // Push the root node to the queue

    while (!q.empty())
    {
        int size = q.size(); // Get the number of nodes at the current level
        vector<int> level;   // Vector to store values of nodes at the current level

        // Process each node at the current level
        for (int i = 0; i < size; i++)
        {
            TreeNode *node = q.front(); // Get the front node of the queue
            q.pop();                    // Remove the node from the queue

            // If the left child exists, push it to the queue
            if (node->left != NULL)
            {
                q.push(node->left);
            }

            // If the right child exists, push it to the queue
            if (node->right != NULL)
            {
                q.push(node->right);
            }

            level.push_back(node->val); // Add the current node's value to the level
        }
        ans.push_back(level); // Add the current level to the result
    }

    return ans; // Return the result after processing all levels
}

int main()
{
    // Create nodes
    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(7);

    // Get the level order traversal
    vector<vector<int>> result = levelOrder(root);

    // Print the level order traversal
    for (const auto &level : result)
    {
        for (int val : level)
        {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}
