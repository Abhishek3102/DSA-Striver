Absolutely — let's go over how to use **built-in `lower_bound` and `upper_bound`** in C++ using the STL, with **two example cases**:

---

## ✅ STL Syntax

```cpp
#include <bits/stdc++.h>
using namespace std;

// lower_bound: first position where value >= x
// upper_bound: first position where value > x
```

---

## ✅ Example 1: Element from Start or End

### 🔹Input:

```cpp
arr = {5, 10, 15, 20, 25};
x = 5 (start)
x = 25 (end)
```

### 🔹Code:

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> arr = {5, 10, 15, 20, 25};

    int x1 = 5;  // from start
    int x2 = 25; // from end

    // lower_bound
    int lb1 = lower_bound(arr.begin(), arr.end(), x1) - arr.begin();
    int lb2 = lower_bound(arr.begin(), arr.end(), x2) - arr.begin();

    // upper_bound
    int ub1 = upper_bound(arr.begin(), arr.end(), x1) - arr.begin();
    int ub2 = upper_bound(arr.begin(), arr.end(), x2) - arr.begin();

    cout << "lower_bound of " << x1 << " is at index " << lb1 << endl;
    cout << "upper_bound of " << x1 << " is at index " << ub1 << endl;

    cout << "lower_bound of " << x2 << " is at index " << lb2 << endl;
    cout << "upper_bound of " << x2 << " is at index " << ub2 << endl;

    return 0;
}
```

### 🔹Output:

```
lower_bound of 5 is at index 0
upper_bound of 5 is at index 1
lower_bound of 25 is at index 4
upper_bound of 25 is at index 5
```

---

## ✅ Example 2: Element from the Middle

### 🔹Input:

```cpp
arr = {2, 4, 4, 4, 6, 8, 10};
x = 4
```

### 🔹Code:

```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> arr = {2, 4, 4, 4, 6, 8, 10};
    int x = 4;

    int lb = lower_bound(arr.begin(), arr.end(), x) - arr.begin();
    int ub = upper_bound(arr.begin(), arr.end(), x) - arr.begin();

    cout << "lower_bound of " << x << " is at index " << lb << endl;
    cout << "upper_bound of " << x << " is at index " << ub << endl;

    return 0;
}
```

### 🔹Output:

```
lower_bound of 4 is at index 1
upper_bound of 4 is at index 4
```

### 🔹Explanation:

- `lower_bound`: points to **first occurrence** of 4.
- `upper_bound`: points to the **first element greater than 4**, which is 6 (at index 4).

---

## ✅ Summary of STL Functions

| Function      | Description                     |
| ------------- | ------------------------------- |
| `lower_bound` | First index where `arr[i] >= x` |
| `upper_bound` | First index where `arr[i] > x`  |

Both functions **require sorted arrays**.

---

Let me know if you want an example where `x` is **not present at all** in the array.
