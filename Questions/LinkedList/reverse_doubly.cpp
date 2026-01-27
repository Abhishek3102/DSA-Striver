#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    Node *next;
    Node *prev;
};

// brute force
void reverseDLL(Node *head)
{
    Node *temp = head;
    stack<int> st;

    while (temp != NULL)
    {
        st.push(temp->data);
        temp = temp->next;
    }

    temp = head;
    while (temp != NULL)
    {
        temp->data = st.top();
        st.pop();
        temp = temp->next;
    }
}

// optimal approach
Node *reverseDLLOpti(Node *head)
{
    if (head == NULL || head->next == NULL)
    {
        return head;
    }

    Node *prev = NULL;
    Node *current = head;

    while (current != NULL)
    {
        prev = current->prev;
        current->prev = current->next;
        current->next = prev;
        current = current->prev; // move forward
    }

    return prev->prev;
}
