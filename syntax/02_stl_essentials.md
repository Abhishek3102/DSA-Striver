# 02 — STL Essentials (vector/map/set/sort)

> If you know only this file, you can write 60% of solutions.

## Vector

```cpp
vector<int> v; v.push_back(5); v.back(); v.pop_back(); // stack-like end ops
v.size(); v.empty(); v.clear(); // size / check / wipe
v.front(); // first element
sort(v.begin(), v.end()); // sort in place
```

## Pair + tuple

```cpp
pair<int,int> p = {1,2}; cout<<p.first<<p.second; // two values together
tuple<int,int,int> t = {1,2,3}; auto [a,b,c]=t; // 3 values (C++17)
```

## Map (ordered, O(log n)) vs Unordered_map (hash, O(1))

```cpp
map<int,int> m; m[2]++; // ordered by key — use when need sorted keys
unordered_map<int,int> f; f[x]++; // freq count — most used
f.count(x); // 1 if exists else 0 — check before f[x]
for(auto &kv : f) cout<<kv.first<<kv.second; // iterate key-value
```

## Set (unique sorted) vs Unordered_set

```cpp
set<int> s; s.insert(5); s.erase(5); s.count(5); // unique + sorted, O(log n)
unordered_set<int> us; us.insert(5); // unique + fast, no order
multiset<int> ms; // allows duplicates + sorted (top-K, sliding median)
```

## Stack / Queue / Deque / Priority_queue (see file 04/10 for patterns)

```cpp
stack<int> st; st.push(1); st.top(); st.pop(); // LIFO
queue<int> q; q.push(1); q.front(); q.pop(); // FIFO (BFS)
deque<int> d; d.push_front(1); d.push_back(2); // both ends (sliding window max)
priority_queue<int> mx; // max-heap by default
priority_queue<int, vector<int>, greater<int>> mn; // min-heap — flip with greater
```

## Sort with custom rule

```cpp
sort(v.begin(), v.end(), [](auto &a, auto &b){ return a.second < b.second; }); // lambda comparator — sort pairs by second
sort(s.begin(), s.end()); // strings sort lexicographically
```

## Binary search on sorted vector

```cpp
binary_search(v.begin(), v.end(), x); // true/false if x exists
lower_bound(v.begin(), v.end(), x) - v.begin(); // first idx >= x
upper_bound(v.begin(), v.end(), x) - v.begin(); // first idx > x
```

```cpp
// count occurrences of x: upper - lower — O(log n)
auto r = equal_range(v.begin(), v.end(), x); // both bounds at once

`equal_range()` is used on a **sorted range** to find the range of elements equal to `x`.

 Your code:

```

auto r = equal_range(v.begin(), v.end(), x);

```

 basically gives you **two iterators**:

```

r.first → first position where x occurs
r.second → position just AFTER the last x

```

 So:

```

r.first = lower_bound(...)
r.second = upper_bound(...)

```

 ## Example

```

vector<int> v = {1, 2, 2, 2, 3, 4, 5};

auto r = equal_range(v.begin(), v.end(), 2);

```

 Visually:

```

index: 0 1 2 3 4 5 6
↓ ↓ ↓ ↓ ↓ ↓ ↓
v: 1 2 2 2 3 4 5
↑ ↑
first after
2 2

```

 So:

```

r.first

```

 points to the **first `2`**.

 And:

```

r.second

```

 points to the position **after the last `2`** (the `3`).

 Therefore:

```

r.second - r.first

```

 gives:

```

3

```

 because there are three `2`s.

---

 ## Why is it called `equal_range`?

 Because it finds the entire range of values **equal to `x`**:

```

1 [2 2 2] 3 4 5
↑ ↑
first after-last

```

 So this:

```

auto r = equal_range(v.begin(), v.end(), x);

```

 is essentially shorthand for:

```

auto lower = lower_bound(v.begin(), v.end(), x);
auto upper = upper_bound(v.begin(), v.end(), x);

```

 and then:

```

r.first == lower
r.second == upper

```

 ## When do you use it?

 Very commonly when you want to **count occurrences in a sorted vector**:

```

vector<int> v = {1, 2, 2, 2, 3, 4};

int x = 2;

auto r = equal_range(v.begin(), v.end(), x);

int count = r.second - r.first;

cout << count;

```

 Output:

```

3

```

 ### Complexity

 Since `v` is sorted:

```

equal_range → O(log n)

```

 So if you just need:

 > "How many times does `x` occur in this sorted array?"

 you can do:

```

auto r = equal_range(v.begin(), v.end(), x);
cout << r.second - r.first;

```

 **Mental shortcut:**

```

lower_bound → first x
upper_bound → after last x
equal_range → gives BOTH

```

```

## Must-know algorithms

```cpp
reverse(v.begin(), v.end()); // reverse

max({a,b,c}); min({a,b,c}); swap(a,b); // variadic max/min
The nested version:

max(a, max(b, max(c, d)));

uses essentially O(1) extra space.

But when youre doing:

max({a, b, c});

with just 3–5 values, this difference is irrelevant in practice.


accumulate(v.begin(), v.end(), 0LL); // sum (0LL for long long)
count(v.begin(), v.end(), x); // frequency of x
find(v.begin(), v.end(), x) != v.end(); // exists?
next_permutation(v.begin(), v.end()); // next lexicographic perm (loop for all)
iota(v.begin(), v.end(), 1); // fill 1,2,3...
fill(v.begin(), v.end(), -1); // fill same value (for dp init)
```

---
## 6 Must-Do Problems (sufficient for this topic)

1. **Contains Duplicate (LC 217)** — Input: `[1,2,3,1]` → `true`. Why: simplest `unordered_set` existence check. Pattern: insert + `count()`. 5 lines.
2. **Group Anagrams (LC 49)** — Input: `["eat","tea","tan","ate","nat","bat"]` → grouped. Why: `unordered_map<string,vector<string>>` with sorted key. Pattern: sort copy as key. Uses: map + sort.
3. **Top K Frequent Elements (LC 347)** — Input: `[1,1,1,2,2,3], k=2` → `[1,2]`. Why: freq map + min-heap of size K. Combines map + heap + comparator.
4. **Valid Parentheses (LC 20)** — Input: `"()[]{}"` → `true`. Why: `stack` + closing→opening map. Pattern: push opens, match on close. Uses: stack + `unordered_map`.
5. **Daily Temperatures (LC 739)** — Input: `[73,74,75,71,69,72,76,73]` → `[1,1,4,2,1,1,0,0]`. Why: monotonic stack storing indices. Uses: stack template + vector init.
6. **Merge Intervals (LC 56)** — Input: `[[1,3],[2,6],[8,10],[15,18]]` → `[[1,6],[8,10],[15,18]]`. Why: sort pairs + `max()` extend. Pattern: sort by start, merge overlap. Uses: custom lambda sort.

