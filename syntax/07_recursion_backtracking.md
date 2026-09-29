# 07 — Recursion & Backtracking Syntax

## Recursion template (every recursive fn is this)
```cpp
void f(int i){ if(i==n) return; /* base case stops */ f(i+1); /* shrink problem */ } // always: base → work → recurse
// recursion = fn calls itself with smaller input; stack remembers path back
```

## Take / not-take (subsets, knapsack, subsequence count)
```cpp
void f(int i, vector<int>&cur){ if(i==n){ ans.push_back(cur); return; } // reached end → one answer
  cur.push_back(a[i]); f(i+1,cur); cur.pop_back(); // TAKE a[i]
  f(i+1,cur); } // NOT-TAKE a[i]
```

## Permutations (swap-in-place, no extra set)
```cpp
void perm(int i){ if(i==n){ ans.push_back(a); return; }
  for(int j=i;j<n;j++){ swap(a[i],a[j]); perm(i+1); swap(a[i],a[j]); } } // swap → recurse → swap-back (backtrack)
```

## Backtracking guard (N-queens / sudoku / maze)
```cpp
for(auto opt:options){ if(!isValid(opt)) continue; // prune bad branch early
  place(opt); f(next); remove(opt); } // choose → explore → unchoose
```

## Input pattern for recursion problems
```cpp
int n; cin>>n; vector<int> a(n); for(int &x:a) cin>>x; // array first
sort(a.begin(), a.end()); // sort to handle duplicates: skip if a[i]==a[i-1] and not used
```

---
## 5 Must-Do Problems (sufficient for this topic)

1. **Subsets (LC 78)** — Input: `[1,2,3]` → `[[],[1],[1,2],...]`. Why: THE take/not-take template. Every subsequence problem is this + a condition.
2. **Subsets II (LC 90)** — Input: `[1,2,2]` → dedup. Why: same + `sort` + skip `a[i]==a[i-1]` on not-take branch. Teaches duplicate handling.
3. **Permutations (LC 46)** — Input: `[1,2,3]` → 6 perms. Why: swap-in-place template. No extra visited array needed.
4. **Combination Sum (LC 39)** — Input: `candidates=[2,3,6,7], target=7` → `[[2,2,3],[7]]`. Why: reuse same index on take (`f(i)` not `f(i+1)`). Teaches unlimited-use variation.
5. **N-Queens (LC 51)** — Input: `n=4` → 2 boards. Why: `isValid` prune + choose-explore-unchoose on 2D. If you can write this, backtracking is done. (Palindromic Partitioning LC 131 as bonus — same skeleton on strings.)

