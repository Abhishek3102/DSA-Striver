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

vector<int> postOrderTraversal(TreeNode *root)
{
    vector<int> postorder; // To store the traversal result

    // If the tree is empty, return an empty vector
    if (root == NULL)
        return postorder;

    stack<TreeNode *> st1, st2; // Two stacks to simulate recursion
    st1.push(root);             // Start with root node

    // Loop until stack1 is empty
    while (!st1.empty())
    {
        root = st1.top(); // Get the current node
        st1.pop();        // Remove it from stack1

        // Push the node to the second stack
        st2.push(root);

        // Push left child first to process it later
        if (root->left != NULL)
        {
            st1.push(root->left);
        }

        // Push right child to process it later
        if (root->right != NULL)
        {
            st1.push(root->right);
        }
    }

    // Now transfer all elements from st2 to postorder
    while (!st2.empty())
    {
        postorder.push_back(st2.top()->val); // Visit the node (postorder: Left -> Right -> Node)
        st2.pop();
    }

    return postorder; // Return the final post-order traversal list
}
