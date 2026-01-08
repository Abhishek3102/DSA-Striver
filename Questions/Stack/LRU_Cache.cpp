#include <bits/stdc++.h>
using namespace std;

/* Doubly linked list node */
struct Node
{
    int key, val;
    Node *next;
    Node *prev;

    Node(int k, int v)
    {
        key = k;
        val = v;
        next = prev = nullptr;
    }
};

/* Removes a node from the doubly linked list */
void deleteNode(Node *node)
{
    Node *prevNode = node->prev;
    Node *afterNode = node->next;

    prevNode->next = afterNode;
    afterNode->prev = prevNode;
}

/* Inserts node right after head (most recently used position) */
void insertAfterHead(Node *head, Node *node)
{
    Node *currentAfterHead = head->next;

    head->next = node;
    node->prev = head;

    node->next = currentAfterHead;
    currentAfterHead->prev = node;
}

class LRUCache
{
private:
    int capacity;
    unordered_map<int, Node *> mpp;
    Node *head;
    Node *tail;

public:
    LRUCache(int capacity_)
    {
        capacity = capacity_;

        /* Dummy head and tail simplify insert/delete operations */
        head = new Node(-1, -1);
        tail = new Node(-1, -1);

        head->next = tail;
        tail->prev = head;
    }

    int get(int key)
    {
        /* If key not found, return -1 */
        if (mpp.find(key) == mpp.end())
            return -1;

        Node *node = mpp[key];

        /* Move accessed node to front (MRU) */
        deleteNode(node);
        insertAfterHead(head, node);

        return node->val;
    }

    void put(int key, int value)
    {
        if (mpp.find(key) != mpp.end())
        {
            /* Update value and move node to front */
            Node *node = mpp[key];
            node->val = value;

            deleteNode(node);
            insertAfterHead(head, node);
        }
        else
        {
            if (mpp.size() == capacity)
            {
                /* Remove least recently used node (before tail) */
                Node *lru = tail->prev;
                mpp.erase(lru->key);
                deleteNode(lru);
                delete lru;
            }

            /* Insert new node as most recently used */
            Node *node = new Node(key, value);
            mpp[key] = node;
            insertAfterHead(head, node);
        }
    }
};

int main()
{
    LRUCache cache(2);

    cache.put(1, 10);
    cache.put(2, 20);

    cout << cache.get(1) << endl; // 10

    cache.put(3, 30); // evicts key 2

    cout << cache.get(2) << endl; // -1
    cout << cache.get(3) << endl; // 30

    cache.put(4, 40); // evicts key 1

    cout << cache.get(1) << endl; // -1
    cout << cache.get(3) << endl; // 30
    cout << cache.get(4) << endl; // 40

    return 0;
}
