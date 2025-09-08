#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node *left;
    Node *right;

    Node(int val)
    {
        data = val;
        left = right = nullptr;
    }
};

// In-order traversal (Left, Root, Right)
void inorder(Node *root)
{
    if (root == nullptr)
        return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// Post-order traversal (Left, Right, Root)
void postorder(Node *root)
{
    if (root == nullptr)
        return;

    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

// Post-order traversal (Root, Left, Right)
void preorder(Node *root)
{
    if (root == NULL)
        return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

int main()
{
    /*
    Constructing the binary tree:
               1
              / \
             2   3
              \
               5

    */

    Node *root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->right = new Node(5);

    cout << "Inorder Traversal: ";
    inorder(root);
    cout << endl;

    cout << "Preorder Traversal: ";
    preorder(root);
    cout << endl;

    cout << "Postorder Traversal: ";
    postorder(root);
    cout << endl;

    return 0;
}
