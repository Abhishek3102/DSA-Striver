# Syntax Cheatsheets — Read This First

> Goal: NOT full problems. Only **short copy-paste snippets** you see in 90% of DSA problems, with 1-2 line explanation. Read each file 4-5 times and you'll stop struggling with boilerplate.

## How to use
1. Picking a new problem? Open only that topic's file.
2. Copy the `Template` block at top of each file.
3. Fill only the `// TODO` part.

## Files
| File | When to open it |
|------|-----------------|
| `01_arrays_strings.md` | Any array / string / matrix problem, input-output, traversals |
| `02_stl_essentials.md` | `vector, map, set, sort, binary_search` — your daily driver |
| `03_linkedlist.md` | LinkedList definition, insert, reverse, fast-slow |
| `04_stack_queue.md` | Stack, Queue, Deque, Monotonic stack, BFS queue pattern |
| `05_trees.md` | **How trees are visualised, built from array, traversals** |
| `06_graphs.md` | Adj list build, BFS, DFS, topo, Dijkstra, DSU |
| `07_recursion_backtracking.md` | Recursion template, subsets, permutations, N-queens |
| `08_dp.md` | **How to write memo / tabulation / space-opt for any DP** |
| `09_sorting_searching_greedy.md` | Binary search templates, comparators, intervals, greedy |
| `10_heap_hashing_sliding.md` | Heap, hashing freq, two-pointer, sliding window, prefix sum |
| `11_input_output_debug.md` | Fast IO, LeetCode vs GFG input, printing vectors/trees |

## Tree visualisation in 10 seconds
```
      1
     / \
    2   3
   / \
  4   5
```
This is written as level-order array: `[1,2,3,4,5,null,null]` — `null` = missing child. See `05_trees.md` for how to build it in code.

## DP in 10 seconds
```cpp
// 1. Memo: f(i) = answer for prefix i, store in dp[i] = -1 initially
// 2. Tabulation: dp[0]=base; for i 1..n: dp[i] = transition
// 3. Space-opt: keep only prev, curr variables
```
See `08_dp.md` — same 3 shapes repeat for knapsack, LIS, grid, strings.
