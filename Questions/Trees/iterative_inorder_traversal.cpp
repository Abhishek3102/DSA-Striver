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

vector<int> inorderTraversal(TreeNode *root)
{
    stack<TreeNode *> st;  // Stack to simulate recursion
    TreeNode *node = root; // Pointer to traverse the tree
    vector<int> inorder;   // Vector to store the inorder traversal result

    // Loop until all nodes are processed
    while (true)
    {
        // Traverse to the leftmost node
        if (node != NULL)
        {
            st.push(node);     // Push the current node onto the stack
            node = node->left; // Move to the left child
        }
        else
        {
            // If the stack is empty, we have processed all nodes
            if (st.empty())
                break;

            // Pop the top node from the stack and process it
            node = st.top();
            st.pop();

            inorder.push_back(node->val); // Visit the node (add value to result)

            // Now, move to the right child
            node = node->right;
        }
    }

    return inorder; // Return the inorder traversal result
}

int main()
{
    /*
        Construct the following binary tree:

                1
              /   \
             2     3
            / \
           4   5
              / \
             6   7

        Inorder traversal: 4 2 6 5 7 1 3
    */

    // Creating leaf nodes
    TreeNode *node6 = new TreeNode(6);
    TreeNode *node7 = new TreeNode(7);
    TreeNode *node4 = new TreeNode(4);
    TreeNode *node3 = new TreeNode(3);

    // Creating internal nodes
    TreeNode *node5 = new TreeNode(5, node6, node7);
    TreeNode *node2 = new TreeNode(2, node4, node5);

    // Root node
    TreeNode *root = new TreeNode(1, node2, node3);

    // Calling inorder traversal function
    vector<int> result = inorderTraversal(root);

    // Printing the result of inorder traversal
    cout << "Inorder Traversal: ";
    for (int val : result)
    {
        cout << val << " ";
    }
    cout << endl;

    // Cleanup: delete dynamically allocated nodes to prevent memory leaks
    delete node6;
    delete node7;
    delete node4;
    delete node3;
    delete node5;
    delete node2;
    delete root;

    return 0;
}