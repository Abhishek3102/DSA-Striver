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

