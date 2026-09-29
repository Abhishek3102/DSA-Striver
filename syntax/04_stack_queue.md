# 04 — Stack & Queue Syntax

## Stack (LIFO) — brackets, NGE, histogram
```cpp
stack<int> st; st.push(1); st.top(); st.pop(); st.empty(); // all O(1)
```
```cpp
// Next Greater Element template (monotonic decreasing stack)
vector<int> nge(n,-1); stack<int> s; // store indices
for(int i=0;i<n;i++){ while(!s.empty() && a[s.top()]<a[i]){ nge[s.top()]=a[i]; s.pop(); } s.push(i); } // pop smaller, current is their answer
// flip < to > for Next Smaller; loop from right for "to the right"
```

## Queue (FIFO) — BFS, level order
```cpp
queue<int> q; q.push(1); q.front(); q.pop(); q.empty(); // FIFO
```
```cpp
// Level-order template (size snapshot = one level)
while(!q.empty()){ int sz=q.size(); for(int i=0;i<sz;i++){ int u=q.front();q.pop(); /* process */ } } // outer=levels, inner=nodes of that level
```

## Deque — sliding window max, 0-1 BFS
```cpp
deque<int> d; d.push_back(1); d.push_front(2); d.pop_back(); d.pop_front(); // both ends O(1)
```
```cpp
// Sliding window max (k): keep decreasing deque of indices
for(int i=0;i<n;i++){ if(!d.empty()&&d.front()<=i-k) d.pop_front(); // drop out-of-window
  while(!d.empty()&&a[d.back()]<=a[i]) d.pop_back(); d.push_back(i); } // drop smaller
```

## Min-stack trick (getMin O(1))
```cpp
stack<long long> s, mn; // second stack tracks min so far
// push x: s.push(x); mn.push(min(x, mn.empty()?x:mn.top())); // carry min down
```

## Brackets check
```cpp
unordered_map<char,char> mp={{')','('},{']','['},{'}','{'}}; // closing→opening
// if opening push; if closing: check top==mp[ch] else invalid
```

---
## 5 Must-Do Problems (sufficient for this topic)

1. **Valid Parentheses (LC 20)** — Input: `"({[]})"` → `true`. Why: stack 101 — push opens, match closes via map. Do first.
2. **Next Greater Element I (LC 496)** — Input: `nums1=[4,1,2], nums2=[1,3,4,2]` → `[-1,3,-1]`. Why: monotonic stack template verbatim from this file. Then try LC 503 (circular — loop 2n).
3. **Largest Rectangle in Histogram (LC 84)** — Input: `[2,1,5,6,2,3]` → `10`. Why: Next-Smaller-Left + Right with stack. Hard but one solution unlocks Maximal Rectangle + Trapping Water.
4. **Sliding Window Maximum (LC 239)** — Input: `[1,3,-1,-3,5,3,6,7], k=3` → `[3,3,5,5,6,7]`. Why: deque template — drop out-of-window + drop smaller. Uses deque both-ends ops.
5. **Implement Queue using Stacks / Min Stack (LC 232, LC 155)** — Why pair: first teaches queue-via-2-stacks (FIFO from LIFO), second teaches aux-min-stack trick. Both are pure API problems — perfect for syntax fluency.

