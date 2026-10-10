// Q3 [MEDIUM - 3/4 marks] Depth (height) of a binary tree
// ROUND CONTEXT: "Calculating the depth of a tree" - asked directly.
// Paper expects recursive logic + dry run. Two conventions:
//   depth by NODES: empty=0, single node=1  (LeetCode 104, use this)
//   depth by EDGES: empty=-1 or single node=0 (rare; mention it if asked)
//
// RECURRENCE (memorise):
//   depth(NULL) = 0
//   depth(node) = 1 + max(depth(left), depth(right))
//
// DRY RUN tree:      1
//                   / \
//                  2   3
//                 /
//                4
// depth = 3. Trace: depth(4)=1, depth(2)=2, depth(3)=1, depth(1)=1+max(2,1)=3
#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
    int val; TreeNode *left, *right;
    TreeNode(int v): val(v), left(nullptr), right(nullptr) {}
};

// Recursive O(n) time, O(h) stack
int maxDepth(TreeNode* root) {
    if (!root) return 0;
    return 1 + max(maxDepth(root->left), maxDepth(root->right));
}

// Iterative BFS version (handy if recursion banned on paper)
int maxDepthBFS(TreeNode* root) {
    if (!root) return 0;
    queue<TreeNode*> q; q.push(root);
    int depth = 0;
    while (!q.empty()) {
        int sz = q.size();
        while (sz--) {
            TreeNode* cur = q.front(); q.pop();
            if (cur->left) q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
        depth++;
    }
    return depth;
}

int main() {
    // Build: [1,2,3,4]
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    cout << "Max depth (rec) = " << maxDepth(root) << " (expected 3)\n";
    cout << "Max depth (BFS) = " << maxDepthBFS(root) << " (expected 3)\n";
    return 0;
}
