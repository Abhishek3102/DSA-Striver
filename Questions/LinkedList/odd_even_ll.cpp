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

Node *oddEvenList(Node *head)
{
    // edge cases : if no element or only 1 element
    if (head == NULL || head->next == NULL)
        return head;

    vector<int> arr;

    Node *temp = head;

    // store odd position nodes
    while (temp != NULL && temp->next != NULL)
    {
        arr.push_back(temp->data); // FIX: arr.add -> push_back
        temp = temp->next->next;
    }

    if (temp)
        arr.push_back(temp->data);

    // store even position nodes
    temp = head->next;
    while (temp != NULL && temp->next != NULL)
    {
        arr.push_back(temp->data);
        temp = temp->next->next;
    }

    if (temp)
        arr.push_back(temp->data);

    // rewrite linked list
    int i = 0;
    temp = head;
    while (temp != NULL)
    {
        temp->data = arr[i];
        i++;
        temp = temp->next;
    }

    return head;
}

// optimal approach
// Traverse odd and even positioned nodes simultaneously
// and rearrange links without using extra space
Node *oddEvenListOptimal(Node *head)
{
    if (head == NULL || head->next == NULL)
        return head;

    Node *odd = head;
    Node *even = head->next;
    Node *evenHead = even; // to connect later(memoize)

    while (even != NULL && even->next != NULL)
    {
        odd->next = odd->next->next;
        odd = odd->next;

        even->next = even->next->next;
        even = even->next;
    }

    odd->next = evenHead; // attach even list after odd list
    return head;
}