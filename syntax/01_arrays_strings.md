# 01 — Arrays & Strings Syntax

> Copy the template, fill only TODO.

## Boilerplate (every file)

```cpp
#include <bits/stdc++.h>
using namespace std; // so you don't write std:: every time
int main(){ ios::sync_with_stdio(false); cin.tie(nullptr); // fast IO
  // TODO
}
```

## Declare + init

```cpp
int a[5] = {1,2,3,4,5}; // C-array, fixed size
vector<int> v = {1,2,3}; // dynamic array, use this 99% times
vector<int> v2(5, 0); // [0,0,0,0,0] — size 5 filled with 0
vector<vector<int>> mat(3, vector<int>(4, 0)); // 3x4 zero matrix
string s = "hello"; // string is vector<char> with helpers
```

## Take input (GFG style)

```cpp
int n; cin >> n; // size first
vector<int> v(n); for(int &x : v) cin >> x; // range-for with & modifies real element

Yes, this syntax is extremely common and widely used in both LeetCode and Codeforces (CF). It is considered standard modern C++ for competitive programming and technical interviews.
Here is how it applies to both platforms:
## 1. In Codeforces (CF)
In Codeforces, you are responsible for reading the input yourself from cin. This exact line is the go-to, idiomatic way to read an array of values in modern C++ (C++11 and newer).
A typical Codeforces problem setup look like this:

#include <iostream>#include <vector>using namespace std;
int main() {
    int t;
    cin >> t; // Read number of test cases
    while (t--) {
        int n;
        cin >> n; // Read size of array

        vector<int> v(n);
        for(int &x : v) cin >> x; // Fast and clean input

        // Your logic here...
    }
    return 0;
}

## 2. In LeetCode
In LeetCode, you rarely need to use cin >> x because LeetCode passes the input directly into your function as a pre-populated vector<int>.
However, you will still use the range-based loop with a reference (&) on LeetCode to modify the given vector in-place or to avoid copying large objects to save memory.
Example: Modifying a vector in-place on LeetCode

class Solution {public:
    void squareElements(vector<int>& nums) {
        // Use & to square the actual elements inside 'nums'
        for (int &x : nums) {
            x = x * x;
        }
    }
};

## Why Competitive Programmers Prefer It

* It is faster to type than for(int i=0; i<n; i++) cin >> v[i];.
* It eliminates bugs related to out-of-bounds indexing (like typing i <= n by mistake).
* It is cleaner to read and looks more professional.

Are you practicing for an upcoming contest on Codeforces, or are you preparing for interviews on LeetCode? I can give you a template for optimizing cin/cout speeds for CF.


```

```cpp
int r,c; cin>>r>>c; vector<vector<int>> a(r, vector<int>(c));
for(int i=0;i<r;i++) for(int j=0;j<c;j++) cin>>a[i][j]; // matrix input row-major
```

```cpp
string s; getline(cin, s); // full line with spaces (after cin, do cin.ignore() once)
```

## Print (for debugging)

```cpp
for(int x : v) cout << x << ' '; cout << '\n'; // print 1D
for(auto &row : mat){ for(int x:row) cout<<x<<' '; cout<<'\n'; } // print 2D
```

## Traversals you reuse everywhere

```cpp
for(int i=0;i<n;i++){ /* forward */ } // normal scan
for(int i=n-1;i>=0;--i){ /* backward */ } // right-to-left (DP, rain water)
for(int i=0,j=n-1;i<j;i++,j--){ swap(v[i],v[j]); } // two pointers inward
```

## Insert / erase (know cost)

```cpp
v.push_back(10); // O(1) add at end — most common
v.pop_back(); // O(1) remove end
v.insert(v.begin()+i, 99); // O(n) insert at i — avoid in loop
v.erase(v.begin()+i); // O(n) erase at i
```

## Sort + reverse + max/min

```cpp
sort(v.begin(), v.end()); // ascending O(n log n)
sort(v.begin(), v.end(), greater<int>()); // descending
reverse(v.begin(), v.end()); // in-place reverse
cout << *max_element(v.begin(), v.end()); // max value (needs <algorithm>)
cout << accumulate(v.begin(), v.end(), 0); // sum (needs <numeric>)
```

## Strings — only these 6

```cpp
s.size(); // length
s.substr(i, len); // slice from i of length len
s.find("abc"); // index or string::npos if absent
s += 'x'; // append char
stoi("123"); to_string(123); // str<->int
reverse(s.begin(), s.end()); // reverse string
```

## Matrix directions trick

```cpp
int dr[4]={-1,1,0,0}, dc[4]={0,0,-1,1}; // U D L R — reuse in BFS/DFS/flood fill
for(int k=0;k<4;k++){ int nr=r+dr[k], nc=c+dc[k]; } // neighbour cell
```

---
## 5 Must-Do Problems (sufficient for this topic)

1. **Two Sum (LC 1)** — Input: `nums=[2,7,11,15], target=9` → Output: `[0,1]`. Why: teaches `unordered_map` freq/complement + single pass. Pattern: store `target-x` as you scan. Uses: input loop + map from this file.
2. **Best Time to Buy & Sell Stock (LC 121)** — Input: `[7,1,5,3,6,4]` → `5`. Why: forward scan + `min so far`. Pattern: track `mn`, `ans=max(ans,p-mn)`. No sorting needed.
3. **Maximum Subarray / Kadane (LC 53)** — Input: `[-2,1,-3,4,-1,2,1,-5,4]` → `6`. Why: running sum reset logic. Pattern: `cur=max(x,cur+x)`. Uses: forward traversal.
4. **Rotate Array by K (LC 189)** — Input: `[1,2,3,4,5,6,7], k=3` → `[5,6,7,1,2,3,4]`. Why: `reverse()` 3-step trick. Pattern: reverse whole, reverse first k, reverse rest. Uses: `reverse`, `k%=n`.
5. **Spiral Matrix (LC 54)** — Input: 3x3 matrix → spiral order. Why: 4-boundary (`top,bottom,left,right`) matrix traversal. Pattern: shrink boundaries after each wall. Uses: matrix print + directions trick.
6. **String: Valid Anagram + Longest Substring Without Repeat (LC 242, LC 3)** — Why pair: first teaches freq count/sort on strings, second teaches sliding window on string. Do both — they cover 90% string syntax (`substr`, map, two pointers).

