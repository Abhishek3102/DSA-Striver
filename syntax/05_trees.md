# 05 — Trees Syntax (visualise + build + traverse)

## How to visualise

```
      1
     / \
    2   3
   / \
  4   5
```

```cpp
// Same tree as level-order array: [1,2,3,4,5] (null = missing child)
// index i → left=2*i+1, right=2*i+2 — heap indexing, helps build from array
```

## Node definition (same everywhere)

```cpp
struct TreeNode{ int val; TreeNode *left,*right; TreeNode(int x):val(x),left(nullptr),right(nullptr){} }; // left/right start null
```

## Build from level-order array (for local testing like LeetCode)

```cpp
TreeNode* build(vector<int> &a){ // use -1 for null, e.g. {1,2,3,-1,5}
  if(a.empty()||a[0]==-1) return nullptr; TreeNode* root=new TreeNode(a[0]); queue<TreeNode*> q; q.push(root);
  for(size_t i=1;i<a.size();){ TreeNode* u=q.front();q.pop();
    if(i<a.size()&&a[i]!=-1){ u->left=new TreeNode(a[i]); q.push(u->left);} i++; // left child
    if(i<a.size()&&a[i]!=-1){ u->right=new TreeNode(a[i]); q.push(u->right);} i++; } return root; }
```

## Take tree input (GFG style: n then level array)

```cpp
int n; cin>>n; vector<int> v(n); for(int &x:v) cin>>x; // -1 or N = null
TreeNode* root = build(v); // reuse builder above
```

## 3 DFS traversals (only order of lines changes)

```cpp
void inorder(TreeNode* r){ if(!r) return; inorder(r->left); cout<<r->val; inorder(r->right); } // L-N-R = sorted for BST
void preorder(TreeNode* r){ if(!r) return; cout<<r->val; preorder(r->left); preorder(r->right); } // N-L-R = copy/serialise
void postorder(TreeNode* r){ if(!r) return; postorder(r->left); postorder(r->right); cout<<r->val; } // L-R-N = delete/height
```

## BFS / Level order (most used in interviews)

```cpp
queue<TreeNode*> q; q.push(root); // FIFO gives top-to-bottom, left-to-right
while(!q.empty()){ auto u=q.front();q.pop(); cout<<u->val;
  if(u->left) q.push(u->left); if(u->right) q.push(u->right); } // push children
```

## Height / size / search snippets

```cpp
int height(TreeNode* r){ return !r?0:1+max(height(r->left),height(r->right)); } // postorder pattern
bool searchBST(TreeNode* r,int x){ while(r){ if(x==r->val) return true; r = x<r->val?r->left:r->right; } return false; } // go left if smaller
TreeNode* insertBST(TreeNode* r,int x){ if(!r) return new TreeNode(x); // create leaf
  if(x<r->val) r->left=insertBST(r->left,x); else r->right=insertBST(r->right,x); return r; }
```

## Iterative inorder (no recursion, asked explicitly)

```cpp
stack<TreeNode*> s; auto cur=root; // go left fully, then pop, then right
while(cur||!s.empty()){ while(cur){ s.push(cur); cur=cur->left; } cur=s.top();s.pop(); cout<<cur->val; cur=cur->right; }
```

---

## 6 Must-Do Problems (sufficient for this topic)

1. **Binary Tree Inorder Traversal (LC 94)** — Do recursive + iterative (stack) versions. Why: locks the 3 DFS orders — only line order changes. Test with `build([1,2,3,4,5])`.
2. **Maximum Depth of Binary Tree (LC 104)** — Input: `[3,9,20,null,null,15,7]` → `3`. Why: postorder `1+max(L,R)` one-liner. Base for diameter/balanced.
3. **Diameter of Binary Tree (LC 543)** — Why: same height fn + global `ans=max(ans,L+R)`. Teaches returning height while updating answer — key tree DP idea.
4. **Level Order Traversal (LC 102)** — Why: BFS queue + level-size snapshot template. Output `vector<vector<int>>`. Base for Zigzag, Right View.
5. **Validate BST (LC 98)** — Input: `[2,1,3]` → `true`. Why: inorder = sorted OR min/max bounds recursion. Kills the "just check children" mistake.
6. **Lowest Common Ancestor of BST / Binary Tree (LC 235, LC 236)** — Why pair: BST version uses `searchBST` while-loop logic; BT version uses postorder return. Doing both separates BST vs BT thinking.

---

Yes — you’re thinking about it correctly. There are **two separate things** here:

1. The `TreeNode` structure — usually provided/reused across many binary-tree problems.
2. Helper functions like `findHleft()` / `findHright()` — these are **problem-specific**, and you can often replace them with a standard `height()` / `maxDepth()` function.

### 1\. Is `TreeNode` always the same?

For **binary tree** problems, a structure like this is very common:

```
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right)
        : val(x), left(left), right(right) {}
};
```

You generally **don't write a different structure for every tree problem**.

On platforms like LeetCode, the `TreeNode` structure is often already given to you. You mainly write the function they ask for.

For example:

```
bool isBalanced(TreeNode* root)
```

or

```
int maxDepth(TreeNode* root)
```

or

```
vector<int> inorderTraversal(TreeNode* root)
```

The same `TreeNode` can be used for all of these.

There are exceptions, though. A problem might use:

- `TreeNode` → binary tree
- `Node` with multiple children → N-ary tree
- `ListNode` → linked list
- a special node containing `next`, `parent`, etc. → specialized tree problem

So **the node structure depends on the type of data structure**, not usually on each individual problem.

---

## 2\. What are `findHleft()` and `findHright()`?

In your code:

```
int lh = findHleft(root->left);
int rh = findHright(root->right);
```

These are **your own helper functions**. C++ doesn't have built-in functions called `findHleft()` or `findHright()`.

And conceptually, you don't really need two different functions.

You can have one standard function:

```
int height(TreeNode* root)
{
    if (root == NULL)
        return 0;

    return 1 + max(height(root->left), height(root->right));
}
```

Then:

```
int lh = height(root->left);
int rh = height(root->right);
```

That's much cleaner.

---

## 3\. Is `height()` the same as `maxDepth()`?

**Yes, essentially.**

For a binary tree, the following are usually describing the same concept:

- `height(root)`
- `maxDepth(root)`
- maximum depth of the tree

For example:

```
        1
       / \
      2   3
     /
    4
```

The height/max depth is 3 if you're counting **nodes**:

```
1 → 2 → 4
```

So:

```
int height(TreeNode* root)
{
    if (root == NULL)
        return 0;

    return 1 + max(height(root->left),
                   height(root->right));
}
```

gives `3`.

---

## 4\. Your balanced-tree code

Your approach is logically correct, assuming `findHleft/right` calculate the heights correctly.

You could write it as:

```
int height(TreeNode* root)
{
    if (root == NULL)
        return 0;

    return 1 + max(height(root->left), height(root->right));
}

bool checkBalancedBT(TreeNode *root)
{
    if (root == NULL)
        return true;

    int lh = height(root->left);
    int rh = height(root->right);

    if (abs(lh - rh) > 1)
        return false;

    bool left = checkBalancedBT(root->left);
    bool right = checkBalancedBT(root->right);

    return left && right;
}
```

This is a good **first implementation** to understand the concept.

---

## 5\. But there's an important optimization

The above solution repeatedly calculates heights.

For example, when you do:

```
checkBalancedBT(root)
```

you calculate:

```
height(left)
height(right)
```

Then when you recursively check the left subtree, you calculate its heights **again**.

So the same nodes can be visited many times.

The standard optimized solution combines:

> **"Calculate height" + "Check whether balanced"**

into one function.

```
int checkHeight(TreeNode* root)
{
    if (root == NULL)
        return 0;

    int lh = checkHeight(root->left);

    if (lh == -1)
        return -1;

    int rh = checkHeight(root->right);

    if (rh == -1)
        return -1;

    if (abs(lh - rh) > 1)
        return -1;

    return 1 + max(lh, rh);
}

bool checkBalancedBT(TreeNode* root)
{
    return checkHeight(root) != -1;
}
```

Here `-1` means:

> "This subtree is not balanced."

Otherwise, the function returns its height.

This makes the solution **O(n)** instead of potentially **O(n²)**.

---

### The important pattern to remember

When learning tree problems, don't memorize every complete solution. Instead, recognize these common building blocks:

```
TreeNode
   ↓
root
   ↓
base case: root == NULL
   ↓
recursive calls:
    root->left
    root->right
   ↓
combine left + right results
```

And common helper concepts are:

```
height(root)
maxDepth(root)
countNodes(root)
search(root, value)
inorder(root)
preorder(root)
postorder(root)
```

So **yes, `maxDepth()` can absolutely be your `height()` helper**. The name doesn't matter; what matters is what the function returns.

One small correction to your comment too:

```
// balanced bt - for every node, height(left) - height(right) <= 1;
```

should technically be:

```
// For every node, abs(height(left) - height(right)) <= 1
```

because the difference can be `-1` as well as `+1`.
