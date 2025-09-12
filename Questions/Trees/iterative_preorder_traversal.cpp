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

vector<int> preOrderTraversal(TreeNode *root)
{
    vector<int> preorder; // To store the traversal result

    // If the tree is empty, return an empty vector
    if (root == NULL)
        return preorder;

    stack<TreeNode *> st; // Stack to simulate recursion
    st.push(root);        // Start with root node

    // Loop until stack is empty
    while (!st.empty())
    {
        root = st.top(); // Get the current node
        st.pop();        // Remove it from the stack

        preorder.push_back(root->val); // Visit the node (Preorder: Node -> Left -> Right)

        // Push right child first so that left is processed first (stack is LIFO)
        if (root->right != NULL)
        {
            st.push(root->right);
        }

        // Push left child
        if (root->left != NULL)
        {
            st.push(root->left);
        }
    }

    return preorder; // Return the final pre-order traversal list
}

int main()
{
    /*
        Building the following tree:

                1
              /   \
             2     7
            / \
           3   4
              / \
             5   6

        Expected Preorder: 1 2 3 4 5 6 7
    */

    // Leaf nodes
    TreeNode *node5 = new TreeNode(5);
    TreeNode *node6 = new TreeNode(6);
    TreeNode *node3 = new TreeNode(3);
    TreeNode *node7 = new TreeNode(7);

    // Subtree
    TreeNode *node4 = new TreeNode(4, node5, node6);
    TreeNode *node2 = new TreeNode(2, node3, node4);

    // Root node
    TreeNode *root = new TreeNode(1, node2, node7);

    // Preorder traversal
    vector<int> result = preOrderTraversal(root);

    // Print result
    cout << "Preorder Traversal: ";
    for (int val : result)
    {
        cout << val << " ";
    }
    cout << endl;

    // Cleanup: delete all allocated nodes to avoid memory leak
    delete node5;
    delete node6;
    delete node3;
    delete node4;
    delete node2;
    delete node7;
    delete root;

    return 0;
}

/*

🧠 Detailed Explanation (Line-by-line)
🔹 #include <bits/stdc++.h>

Includes all standard C++ libraries (like iostream, vector, stack, etc.).

Useful for competitive programming or fast prototyping, but avoid in production.

🔹 struct TreeNode
Defines the structure of a binary tree node.
Contains:
An int val to store the value.
Pointers left and right to the left and right child nodes respectively.

Three constructors:
Default (value 0, children null). With value only.
With value and specified children.

🔹 vector<int> preOrderTraversal(TreeNode *root)
Declares a function that returns a vector of integers representing the preorder traversal of a binary tree.
Parameter: Pointer to the root of the tree.

🔹 vector<int> preorder;
A vector to store the traversal result in preorder format:
Visit node.
Traverse left subtree.
Traverse right subtree.

🔹 if (root == NULL) return preorder;
Checks if the tree is empty (i.e., no nodes).
Returns an empty result if so.

🔹 stack<TreeNode*> st;
Creates a stack to simulate the function call stack of a recursive traversal.

🔹 st.push(root);
Pushes the root node onto the stack to start the traversal.

🔹 while (!st.empty())
Main loop that continues until the stack is empty (i.e., all nodes are visited).

🔹 root = st.top(); st.pop();
Retrieves the node from the top of the stack and removes it.
This is the current node to process.

🔹 preorder.push_back(root->val);
Processes the current node by adding its value to the result list.
This is what makes it a preorder traversal.

🔹 if (root->right != NULL) st.push(root->right);
Pushes the right child to the stack first.

This ensures the left child is processed first, since the stack is LIFO (Last In, First Out).

🔹 if (root->left != NULL) st.push(root->left);
Pushes the left child after the right one.
This preserves the correct preorder order: Node → Left → Right.

🔹 return preorder;
After the loop, returns the final traversal result.

🧾 Summary of Key Concepts
Concept	Explanation
Preorder Traversal	Visit root → left → right
Stack-based Traversal	Simulates recursion using a stack
Order of Push	Right child first → left child later, so left is processed before
Why Iterative?	Avoids recursion, useful for very deep trees (avoids stack overflow)

*/