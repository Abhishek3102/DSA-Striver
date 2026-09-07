/*
  LARGEST RECTANGLE IN HISTOGRAM

  This code finds the area of the largest rectangle that can be formed in a histogram.

  WHAT IT DOES:
  - Given heights of bars in a histogram, find the largest rectangular area
  - Uses stack to find next smaller element (NSE) and previous smaller element (PSE)
  - For each bar, calculates area with that bar as the shortest in the range
  - Maximum of all such areas is the answer

  INPUT:
  - Array of integers representing heights of histogram bars
  - Example: {2, 1, 5, 6, 2, 3} (heights of bars)

  OUTPUT:
  - Single integer representing the maximum rectangular area
  - Example output: 10 (rectangle of height 2 and width 5)
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> findPSEOptimal(vector<int> arr)
{
    int n = arr.size();
    vector<int> nse(n, -1);
    stack<int> st;
    for (int i = 0; i < n; i++)
    {
        while (!st.empty() && st.top() >= arr[i])
        {
            st.pop();
        }

        nse[i] = st.empty() ? -1 : st.top();
        st.push(arr[i]);
    }
    return nse;
}

vector<int> findNSEOptimal(vector<int> arr)
{
    int n = arr.size();
    vector<int> nse(n, -1);
    stack<int> st;

    for (int i = n - 1; i >= 0; i--)
    {
        while (!st.empty() && st.top() >= arr[i])
        {
            st.pop();
        }

        nse[i] = st.empty() ? -1 : st.top();
        st.push(arr[i]);
    }
    return nse;
}

// this is brute coz we use both pse and nse which increases time and space complexity
int findLargestRectAreaHisto(vector<int> arr)
{
    vector<int> nse = findNSEOptimal(arr);
    vector<int> pse = findPSEOptimal(arr);
    int n = arr.size();

    int maxi = 0;
    for (int i = 0; i < n; i++)
    {
        maxi = max(maxi, arr[i] * (nse[i] - pse[i] - 1));
    }
    return maxi;
}

// optimal for finding max area
int findMaxAreaHisto(vector<int> arr)
{
    int n = arr.size();
    stack<int> st;
    int maxArea = 0;
    for (int i = 0; i < n; i++)
    {
        while (!st.empty() && arr[st.top()] > arr[i])
        {
            int element = st.top();
            st.pop();
            int nse = i;
            int pse = st.empty() ? -1 : st.top();
            maxArea = max(arr[element] * (nse - pse - 1), maxArea);
        }
        st.push(i);
    }
    while (!st.empty())
    {
        int nse = n;
        int element = st.top();
        st.pop();

        int pse = st.empty() ? -1 : st.top();
        maxArea = max(maxArea, (nse - pse - 1) * arr[element]);
    }
    return maxArea;
}

int main()
{
    vector<int> arr = {3, 2, 10, 11, 5, 10, 6, 3};
    int maxArea = findMaxAreaHisto(arr);
    cout << "The maximum rectangular area is: " << maxArea << endl;
    return 0;
}

/*

Your **`findMaxAreaHisto()` (optimal solution)** is correct and runs in **O(n)** time with **O(n)** stack space.

However, your **PSE/NSE functions are incorrect**, so `findLargestRectAreaHisto()` will produce wrong answers.

### Problem 1: You're storing values instead of indices

In both functions, you're doing:

```cpp
st.push(arr[i]);
```

and

```cpp
nse[i] = st.empty() ? -1 : st.top();
```

Here `st.top()` is the **height**, not the **index**.

For the largest rectangle problem, you need the **index of the previous/next smaller element**, because the width is computed as

```cpp
width = nse[i] - pse[i] - 1;
```

That formula only works with indices.

---

## Correct Previous Smaller Element (PSE)
Index : 0  1  2  3  4  5
Value : 2  1  5  6  2  3

PSE   : -1 -1  1  2  1  4

```cpp
vector<int> findPSEOptimal(vector<int> &arr)
{
    int n = arr.size();
    vector<int> pse(n);
    stack<int> st;   // stores indices

    for (int i = 0; i < n; i++)
    {
        while (!st.empty() && arr[st.top()] >= arr[i])
            st.pop();

        pse[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }

    return pse;
}
```

---

## Correct Next Smaller Element (NSE)
Index : 0  1  2  3  4  5
Value : 2  1  5  6  2  3

NSE   : 1  6  4  4  6  6

```cpp
vector<int> findNSEOptimal(vector<int> &arr)
{
    int n = arr.size();
    vector<int> nse(n);
    stack<int> st;   // stores indices

    for (int i = n - 1; i >= 0; i--)
    {
        while (!st.empty() && arr[st.top()] >= arr[i])
            st.pop();

        nse[i] = st.empty() ? n : st.top();
        st.push(i);
    }

    return nse;
}
```

Notice two differences:

* Stack stores **indices** (`i`), not values.
* If there is no next smaller element, return **`n`**, not `-1`.

---

## Problem 2: Width calculation

Your code has

```cpp
arr[i] * (nse[i] - pse[i] - 1)
```

which is correct **only if**

* `pse[i]` is an index
* `nse[i]` is an index (or `n` when none exists)

Since your current functions return heights, the width becomes meaningless.

---

3. Largest Rectangle using PSE + NSE

Width is

width = nse[i] - pse[i] - 1;
i	Height	PSE	NSE	Width	Area
0	2	-1	1	1	2
1	1	-1	6	6	6
2	5	1	4	2	10
3	6	2	4	1	6
4	2	1	6	4	8
5	3	4	6	1	3

Maximum area:

10

## Problem 3: Comment

You wrote

```cpp
// this is brute coz we use both pse and nse
```

This isn't really brute force.

Complexities are:

* Finding PSE → **O(n)**
* Finding NSE → **O(n)**
* Computing areas → **O(n)**

Overall:

* **Time:** `O(n)`
* **Space:** `O(n)`

The one-stack method is also **O(n)** time and **O(n)** space, but it avoids creating two extra arrays, so it's more space-efficient in practice.

---

# Your optimal function

```cpp
int findMaxAreaHisto(vector<int> arr)
```

is correct.

The only small improvement I'd suggest is using `>=` instead of `>`:

```cpp
while (!st.empty() && arr[st.top()] >= arr[i])
```

instead of

```cpp
while (!st.empty() && arr[st.top()] > arr[i])
```

Using `>=` handles equal-height bars consistently and is the more common implementation. Your version with `>` still works for many inputs, but `>=` avoids subtle duplicate-height edge cases.

---

### Final verdict

* ✅ `findMaxAreaHisto()` — Correct (`O(n)`).
* ❌ `findPSEOptimal()` — Incorrect (stores values instead of indices).
* ❌ `findNSEOptimal()` — Incorrect (stores values instead of indices and should return `n` when no smaller element exists).
* ❌ `findLargestRectAreaHisto()` — Incorrect because it depends on the faulty PSE/NSE arrays. Once those are fixed, this function will also be correct.


*/