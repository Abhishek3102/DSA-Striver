#include <bits/stdc++.h>
using namespace std;

// Define the structure of a binary tree node
struct TreeNode
{
    int val;                                             // Node value
    TreeNode *left, *right;                              // Pointers to left and right children
    TreeNode(int x) : val(x), left(NULL), right(NULL) {} // Constructor to initialize the node
};

// Function to get the inorder traversal of a binary tree without recursion
vector<int> getInorder(TreeNode *root)
{
    vector<int> inorder;   // This will store the inorder traversal result
    TreeNode *curr = root; // Start with the root node

    // Traverse the tree using the Morris Traversal method
    while (curr != NULL)
    {
        // If there is no left subtree
        if (curr->left == NULL)
        {
            inorder.push_back(curr->val); // Add the node's value to the result
            curr = curr->right;           // Move to the right subtree
        }
        else
        {
            // Find the rightmost node of the left subtree (predecessor)
            TreeNode *prev = curr->left;
            while (prev->right && prev->right != curr)
            {
                prev = prev->right;
            }

            // If the right pointer of the predecessor is null
            if (prev->right == NULL)
            {
                prev->right = curr; // Establish a temporary thread to the current node
                curr = curr->left;  // Move to the left subtree
            }
            else
            {
                // If the right pointer of the predecessor is already set to current node
                prev->right = NULL;           // Break the temporary thread
                inorder.push_back(curr->val); // Add the node's value to the result
                curr = curr->right;           // Move to the right subtree
            }
        }
    }

    return inorder;
}

vector<int> getPreorder(TreeNode *root)
{
    vector<int> preorder;  // This will store the inorder traversal result
    TreeNode *curr = root; // Start with the root node

    // Traverse the tree using the Morris Traversal method
    while (curr != NULL)
    {
        // If there is no left subtree
        if (curr->left == NULL)
        {
            preorder.push_back(curr->val); // Add the node's value to the result
            curr = curr->right;            // Move to the right subtree
        }
        else
        {
            // Find the rightmost node of the left subtree (predecessor)
            TreeNode *prev = curr->left;
            while (prev->right && prev->right != curr)
            {
                prev = prev->right;
            }

            // If the right pointer of the predecessor is null
            if (prev->right == NULL)
            {
                prev->right = curr;            // Establish a temporary thread to the current node
                preorder.push_back(curr->val); // Add the node's value to the result
                curr = curr->left;             // Move to the left subtree
            }
            else
            {
                // If the right pointer of the predecessor is already set to current node
                prev->right = NULL; // Break the temporary thread
                curr = curr->right; // Move to the right subtree
            }
        }
    }

    return preorder;
}

int main()
{

    TreeNode *root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    // Get the inorder traversal of the tree
    vector<int> inorder = getInorder(root);

    // Print the inorder traversal result
    for (int val : inorder)
    {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
