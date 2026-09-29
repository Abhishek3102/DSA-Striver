# 10 — Heap, Hashing, Two-Pointer, Sliding Window, Prefix

## Heap (top-K, Kth largest, merge K sorted)
```cpp
priority_queue<int> mx; // max-heap: top() = largest
priority_queue<int,vector<int>,greater<int>> mn; // min-heap: top() = smallest — use for K largest
```
```cpp
// K largest: push all, keep size K in min-heap
for(int x:a){ mn.push(x); if(mn.size()>K) mn.pop(); } // smallest of K at top, pop it → keeps K biggest
```
```cpp
// Custom heap of pairs: smallest distance first
priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> pq; pq.push({dist,node});
```

## Hashing freq (counting in O(n))
```cpp
unordered_map<int,int> f; for(int x:a) f[x]++; // freq map — 1 line solves many problems
f.count(x); // existence check
// top-K frequent: push {freq,val} into min-heap of size K (see heap above)
// group anagrams: key = sorted string → map<string,vector<string>>
```

## Two pointers (sorted array / linked list)
```cpp
int l=0,r=n-1; while(l<r){ int s=a[l]+a[r]; // pair-sum on sorted array
  if(s==target) break; else if(s<target) l++; else r--; } // need bigger → left++, smaller → right--
```

## Sliding window (fixed K then variable)
```cpp
// Fixed K: sum/max of every window
int sum=0; for(int i=0;i<n;i++){ sum+=a[i]; if(i>=K) sum-=a[i-K]; /* window=[i-K+1..i] */ }
```
```cpp
// Variable: longest subarray with condition (e.g. sum<=S, at most K distinct)
int l=0; for(int r=0;r<n;r++){ /* expand with a[r] */;
  while(invalid(l,r)){ /* shrink from l */ l++; } ans=max(ans,r-l+1); } // expand→shrink→record
```

## Prefix sum / diff (range queries O(1))
```cpp
vector<int> pre(n+1,0); for(int i=0;i<n;i++) pre[i+1]=pre[i]+a[i]; // pre[i]=sum of first i
int rangeSum = pre[r+1]-pre[l]; // sum[l..r] — no loop needed
```
```cpp
// Difference array: many range adds, one final rebuild
vector<int> d(n+1,0); d[l]+=v; d[r+1]-=v; // O(1) per update
// after all updates: for i 1..n-1 d[i]+=d[i-1]; → final array
```

## Bit tricks used often
```cpp
(x & 1); // odd check
x & -x; // lowest set bit (Fenwick core)
__builtin_popcount(x); // count 1-bits
1<<k; // 2^k — k-th bit mask
```

---
## 6 Must-Do Problems (sufficient for this topic)

1. **Kth Largest Element (LC 215)** — Input: `[3,2,1,5,6,4], k=2` → `5`. Why: min-heap size-K snippet. Also try quickselect once.
2. **Top K Frequent Elements (LC 347)** — Why: freq map + heap combo. Links hashing file to heap file.
3. **Two Sum II + 3Sum (LC 167, LC 15)** — Input: sorted `[2,7,11,15], target=9` → `[1,2]`; `[-1,0,1,2,-1,-4]` → triplets. Why: two-pointer inward + outer loop + dedup skip. Covers pair and triplet.
4. **Longest Substring Without Repeating Characters (LC 3)** — Input: `"abcabcbb"` → `3`. Why: variable window + last-index map. Template for all "longest with K" problems.
5. **Subarray Sum Equals K (LC 560)** — Input: `[1,1,1], k=2` → `2`. Why: prefix sum + `freq[sum-k]` map. O(n), no window (negatives allowed — window fails here).
6. **Sliding Window Maximum (LC 239)** — Input: `[1,3,-1,-3,5,3,6,7], k=3` → `[3,3,5,5,6,7]`. Why: deque decreasing-indices template. Hardest window — after this, all windows feel easy.

