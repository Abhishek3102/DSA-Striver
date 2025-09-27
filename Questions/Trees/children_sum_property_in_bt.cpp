#include <bits/stdc++.h>
using namespace std;

struct BinaryTreeNode
{
    int data;
    BinaryTreeNode *left;
    BinaryTreeNode *right;

    // Constructors to initialize the nodes
    BinaryTreeNode() : data(0), left(nullptr), right(nullptr) {}
    BinaryTreeNode(int x) : data(x), left(nullptr), right(nullptr) {}
    BinaryTreeNode(int x, BinaryTreeNode *left, BinaryTreeNode *right) : data(x), left(left), right(right) {}
};

// Function to modify the tree according to the given problem
void changeTree(BinaryTreeNode *root)
{
    if (root == NULL)
        return;

    int childSum = 0;

    // Calculate sum of children's data
    if (root->left)
    {
        childSum += root->left->data;
    }

    if (root->right)
    {
        childSum += root->right->data;
    }

    // If the sum of children is greater than or equal to the current node, update the node's data
    if (childSum >= root->data)
        root->data = childSum;
    else
    {
        // Otherwise, set the left or right child's data to the current node's data
        if (root->left)
            root->left->data = root->data;
        else if (root->right)
            root->right->data = root->data;
    }

    // Recursively update left and right subtrees
    changeTree(root->left);
    changeTree(root->right);

    // Recalculate the total sum of the children's data
    int total = 0;
    if (root->left)
        total += root->left->data;
    if (root->right)
        total += root->right->data;

    // Update the current node's data with the total sum of its children's data
    if (root->left || root->right)
        root->data = total;
}

// Helper function to print the tree (pre-order traversal)
void printTree(BinaryTreeNode *root)
{
    if (root == NULL)
        return;
    cout << root->data << " ";
    printTree(root->left);
    printTree(root->right);
}

int main()
{
    // Creating a simple binary tree
    BinaryTreeNode *root = new BinaryTreeNode(10);
    root->left = new BinaryTreeNode(5);
    root->right = new BinaryTreeNode(15);
    root->left->left = new BinaryTreeNode(3);
    root->left->right = new BinaryTreeNode(7);
    root->right->left = new BinaryTreeNode(12);
    root->right->right = new BinaryTreeNode(20);

    cout << "Original Tree (pre-order): ";
    printTree(root);
    cout << endl;

    // Change the tree based on the logic
    changeTree(root);

    cout << "\nUpdated Tree (pre-order): ";
    printTree(root);
    cout << endl;

    return 0;
}

/*
output :
Original Tree (pre-order): 10 5 3 7 15 12 20

Updated Tree (pre-order): 42 10 3 7 32 12 20

*/