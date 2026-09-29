# 03 — Linked List Syntax

> Definition never changes. Memorise this one struct.

## Node definition (template for SLL)

```cpp
struct ListNode
{
    int val;           // stores the node's value

    ListNode* next;    // stores address of the next node

    ListNode(int x)    // constructor, receives a value
        : val(x),      // initialize val with x
          next(nullptr) // initialize next as null
    {}
};

```

## Build list from vector (for local testing)

```cpp
ListNode* build(vector<int> &v){ ListNode dummy(0), *t=&dummy; // dummy head avoids edge case
  for(int x:v){ t->next=new ListNode(x); t=t->next; } return dummy.next; }
```

## Print list

```cpp
for(ListNode* p=head; p; p=p->next) cout<<p->val<<"->"; // walk till null
```

## Insert

```cpp
head = new ListNode(x); head->next = oldHead; // insert at head O(1)
ListNode* p=head; while(p->next) p=p->next; p->next=new ListNode(x); // insert at tail O(n)
```

## Reverse (most asked snippet)

```cpp
ListNode *prev=nullptr, *cur=head; // two pointers
while(cur){ auto nxt=cur->next; cur->next=prev; prev=cur; cur=nxt; } // flip link then advance
head=prev;
```

## Fast & slow (middle / cycle / kth-end)

```cpp
ListNode *slow=head,*fast=head; // fast moves 2x
while(fast && fast->next){ slow=slow->next; fast=fast->next->next; } // slow = middle at end
```

```cpp
// cycle detect: same loop, if slow==fast → cycle — Floyd's algo
// kth from end: move fast k steps first, then both together
```

## Doubly node (extra prev)

```cpp
struct DNode{ int val; DNode *next,*prev; DNode(int x):val(x),next(nullptr),prev(nullptr){} }; // same + prev link
```

---
## 5 Must-Do Problems (sufficient for this topic)

1. **Reverse Linked List (LC 206)** — Input: `1->2->3` → `3->2->1`. Why: THE pointer-flip snippet from this file. Memorise `nxt/prev/cur` order. Iterative + try recursive once.
2. **Middle of Linked List (LC 876)** — Input: `1->2->3->4->5` → `3`. Why: fast & slow template. Pattern: fast 2x, slow 1x. No length precompute needed.
3. **Linked List Cycle (LC 141)** — Input: `[3,2,0,-4], pos=1` → `true`. Why: same fast-slow, but `slow==fast` check. Teaches Floyd's intuition.
4. **Remove Nth Node From End (LC 19)** — Input: `1->2->3->4->5, n=2` → `1->2->3->5`. Why: gap technique — move fast n steps, then both. Uses dummy head + build/print helpers.
5. **Merge Two Sorted Lists (LC 21)** — Input: `[1,2,4],[1,3,4]` → `[1,1,2,3,4,4]`. Why: dummy + tail pointer pattern reused in merge-K-lists. Pattern: pick smaller head, advance.

