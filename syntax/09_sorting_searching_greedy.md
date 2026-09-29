# 09 — Sorting, Searching & Greedy Syntax

## Binary search templates (memorise both)
```cpp
// Exact search on sorted array
int lo=0, hi=n-1; while(lo<=hi){ int mid=lo+(hi-lo)/2; // overflow-safe mid
  if(a[mid]==x) break; else if(a[mid]<x) lo=mid+1; else hi=mid-1; }
```
```cpp
// Search answer space (min max / capacity problems): first true
int lo=1, hi=1e9, ans=hi; while(lo<=hi){ int mid=lo+(hi-lo)/2;
  if(can(mid)){ ans=mid; hi=mid-1; } else lo=mid+1; } // can()=feasibility check you write
```

## Sort + comparator for structs/pairs
```cpp
sort(v.begin(), v.end()); // numbers ascending
sort(v.begin(), v.end(), [](auto &a, auto &b){ if(a.first!=b.first) return a.first<b.first; return a.second>b.second; }); // multi-key: first asc, second desc
```

## Intervals (merge / insert) — sort by start first
```cpp
sort(v.begin(), v.end()); // pairs sort by first then second
vector<vector<int>> m; for(auto &in:v){ if(m.empty()||in[0]>m.back()[1]) m.push_back(in); // no overlap → new
  else m.back()[1]=max(m.back()[1],in[1]); } // overlap → extend end
```

## Greedy patterns
```cpp
sort(jobs.begin(), jobs.end(), [](auto &a, auto &b){ return a.profit>b.profit; }); // profit-first (job sequencing) — sort by what you want most
// Activity selection: sort by END time, pick if start >= lastEnd — earliest-finish wins
// Fractional knapsack: sort by value/weight ratio desc, take as much as fits
```

## Two sorted arrays merge (merge sort step)
```cpp
int i=0,j=0; while(i<n&&j<m){ if(a[i]<b[j]) c.push_back(a[i++]); else c.push_back(b[j++]); } // pick smaller head
while(i<n) c.push_back(a[i++]); while(j<m) c.push_back(b[j++]); // drain leftovers
```

---
## 5 Must-Do Problems (sufficient for this topic)

1. **Binary Search (LC 704)** — Input: `[-1,0,3,5,9,12], target=9` → `4`. Why: exact-search template with overflow-safe mid. Do once blind.
2. **Search in Rotated Sorted Array (LC 33)** — Input: `[4,5,6,7,0,1,2], target=0` → `4`. Why: which-half-is-sorted check. Teaches modifying the `if` inside same loop.
3. **Koko Eating Bananas / Search-Answer (LC 875)** — Input: `piles=[3,6,7,11], h=8` → `4`. Why: first-true `can(mid)` template. Same code solves Ship Capacity, Split Array.
4. **Merge Intervals + Insert Interval (LC 56, LC 57)** — Why pair: sort-by-start + extend; insert = same with one extra interval. Covers all interval syntax.
5. **Activity Selection / Job Sequencing + Fractional Knapsack (GFG)** — Why: the 3 greedy sorts — by end time, by profit, by ratio. Do all three in one sitting; greedy = knowing what to sort by.

