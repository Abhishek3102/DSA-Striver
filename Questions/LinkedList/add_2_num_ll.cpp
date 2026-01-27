#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    Node *next;

    Node(int x)
    {
        data = x;
        next = NULL;
    }
};

Node *add_2_num(Node *head1, Node *head2)
{
    Node *t1 = head1;
    Node *t2 = head2;

    // dummy node
    // here dummy node concept is used which makes the problem easy.
    // whenever we need to create a new list, then always use this concept of dummynode.
    Node *dummyNode = new Node(-1);
    Node *current = dummyNode;

    int carry = 0;

    while (t1 != NULL || t2 != NULL)
    {
        int sum = carry;

        if (t1)
            sum += t1->data;
        if (t2)
            sum += t2->data;

        carry = sum / 10;
        Node *newNode = new Node(sum % 10);
        current->next = newNode;
        current = current->next;

        if (t1)
            t1 = t1->next;
        if (t2)
            t2 = t2->next;
    }

    if (carry)
    {
        current->next = new Node(carry);
    }

    return dummyNode->next;
}
