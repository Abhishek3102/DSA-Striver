Here’s a list of commonly used functions and algorithms with `vector` in C++ (from the STL), each explained in about two lines:

---

### 🔢 **Element-wise Operations**

1. **`std::max_element(v.begin(), v.end())`**
   Returns an iterator to the maximum element in the vector.
   Dereference it with `*` to get the value.

2. **`std::min_element(v.begin(), v.end())`**
   Returns an iterator to the minimum element in the vector.
   Like `max_element`, use `*` to access the value.

3. **`std::accumulate(v.begin(), v.end(), 0)`** _(needs `<numeric>`)_
   Returns the sum of all elements in the vector starting from 0.
   You can change the third argument to any initial value.

4. **`std::count(v.begin(), v.end(), x)`**
   Counts how many times `x` appears in the vector.
   Useful for frequency checking of an element.

5. **`std::find(v.begin(), v.end(), x)`**
   Returns iterator to the first occurrence of `x`.
   If not found, returns `v.end()`.

6. **`std::binary_search(v.begin(), v.end(), x)`**
   Returns `true` if `x` is found in the **sorted** vector.
   Requires `<algorithm>` and prior sorting.

---

### 🔁 **Modifying and Rearranging**

7. **`std::sort(v.begin(), v.end())`**
   Sorts the vector in ascending order in-place.
   Use `greater<int>()` for descending order.

8. **`std::reverse(v.begin(), v.end())`**
   Reverses the vector in-place.
   After this, the first becomes last, and so on.

9. **`std::rotate(v.begin(), v.begin() + k, v.end())`**
   Rotates vector so that element at index `k` becomes first.
   Good for cyclic shifts.

10. **`std::unique(v.begin(), v.end())`**
    Removes consecutive duplicates; use with `sort` and then `erase`.
    Returns new end iterator, so use `v.erase(...)` to resize vector.

---

### 🎲 **Others**

11. **`std::next_permutation(v.begin(), v.end())`**
    Rearranges the vector to the next lexicographically greater permutation.
    Returns `false` if it was the last permutation.

12. **`std::lower_bound(v.begin(), v.end(), x)`**
    Returns iterator to the first element `>= x` in a sorted vector.
    Use `*` to get value or subtract `v.begin()` for index.

13. **`std::upper_bound(v.begin(), v.end(), x)`**
    Returns iterator to the first element `> x` in a sorted vector.
    Useful for finding range or count of a value.

14. **`std::equal(v1.begin(), v1.end(), v2.begin())`**
    Returns `true` if two vectors (or sequences) are equal element-wise.
    Make sure sizes are the same or handle carefully.

15. **`std::all_of(v.begin(), v.end(), pred)`**
    Returns `true` if all elements satisfy the predicate `pred`.
    Similarly: `any_of`, `none_of` for other checks.

---

Great! Here's a simple C++ example demonstrating most of these STL functions on a `vector<int>`:

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>   // for accumulate
using namespace std;

int main() {
    vector<int> v = {5, 3, 8, 3, 9, 1, 5};

    // Max and Min
    cout << "Max: " << *max_element(v.begin(), v.end()) << endl;
    cout << "Min: " << *min_element(v.begin(), v.end()) << endl;

    // Accumulate (Sum)
    cout << "Sum: " << accumulate(v.begin(), v.end(), 0) << endl;

    // Count
    cout << "Count of 3: " << count(v.begin(), v.end(), 3) << endl;

    // Find
    auto it = find(v.begin(), v.end(), 8);
    if (it != v.end()) cout << "Found 8 at index: " << (it - v.begin()) << endl;

    // Sort
    sort(v.begin(), v.end());
    cout << "Sorted: ";
    for (int x : v) cout << x << " ";
    cout << endl;

    // Binary Search
    cout << "Is 5 in vector? " << binary_search(v.begin(), v.end(), 5) << endl;

    // Lower and Upper Bound
    cout << "Lower bound of 5 at index: " << (lower_bound(v.begin(), v.end(), 5) - v.begin()) << endl;
    cout << "Upper bound of 5 at index: " << (upper_bound(v.begin(), v.end(), 5) - v.begin()) << endl;

    // Reverse
    reverse(v.begin(), v.end());
    cout << "Reversed: ";
    for (int x : v) cout << x << " ";
    cout << endl;

    // Rotate
    rotate(v.begin(), v.begin() + 2, v.end());
    cout << "Rotated (2 steps): ";
    for (int x : v) cout << x << " ";
    cout << endl;

    // Unique (remove duplicates)
    sort(v.begin(), v.end());              // First sort
    auto last = unique(v.begin(), v.end()); // Remove consecutive duplicates
    v.erase(last, v.end());                // Resize vector
    cout << "After unique: ";
    for (int x : v) cout << x << " ";
    cout << endl;

    // Next Permutation
    if (next_permutation(v.begin(), v.end())) {
        cout << "Next permutation: ";
        for (int x : v) cout << x << " ";
        cout << endl;
    } else {
        cout << "No next permutation." << endl;
    }

    // All_of
    bool allPositive = all_of(v.begin(), v.end(), [](int x){ return x > 0; });
    cout << "All elements positive? " << (allPositive ? "Yes" : "No") << endl;

    return 0;
}
```

### ✅ Output (will vary slightly depending on operations):

```
Max: 9
Min: 1
Sum: 34
Count of 3: 2
Found 8 at index: 2
Sorted: 1 3 3 5 5 8 9
Is 5 in vector? 1
Lower bound of 5 at index: 3
Upper bound of 5 at index: 5
Reversed: 9 8 5 5 3 3 1
Rotated (2 steps): 5 5 3 3 1 9 8
After unique: 1 3 5 8 9
Next permutation: 1 3 5 9 8
All elements positive? Yes
```

---

Perfect. Let's break this down into two parts:

---

## ✅ Part 1: STL Functions for `vector<string>` and `vector<vector<int>>`

Each with **2-line** explanations.

---

### 🔤 `vector<string>`

1. **`sort(v.begin(), v.end())`**
   Sorts strings in lexicographical (dictionary) order.
   Use `greater<string>()` for reverse alphabetical order.

2. **`max_element(v.begin(), v.end())`**
   Returns iterator to the lexicographically largest string.
   Use `*` to get the actual string.

3. **`min_element(v.begin(), v.end())`**
   Returns iterator to the smallest string.
   Works the same way as with integers.

4. **`count(v.begin(), v.end(), "hello")`**
   Counts how many times `"hello"` appears.
   Good for frequency checking.

5. **`find(v.begin(), v.end(), "target")`**
   Finds the string `"target"`; returns iterator to it or `v.end()`.
   Use `it - v.begin()` for the index.

6. **`reverse(v.begin(), v.end())`**
   Reverses the order of strings in the vector.
   Does not reverse individual characters.

---

### 🔢 `vector<vector<int>>` (2D vectors)

1. **Looping with `for (auto &row : grid)`**
   Standard way to iterate rows in 2D vector.
   Inner `for` loop accesses elements in each row.

2. **`sort(grid.begin(), grid.end())`**
   Sorts rows based on their first differing element (lexicographical).
   You can use custom comparator for more control.

3. **`accumulate(row.begin(), row.end(), 0)`**
   Use to compute sum of each row.
   Needs `<numeric>` header.

4. **Custom sort with lambda**
   You can sort rows by sum, size, max element, etc.
   Use `sort(grid.begin(), grid.end(), [&](...) { ... })`.

---

## ✅ Part 2: Code Example (`vector<string>` + `vector<vector<int>>`)

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;

int main() {
    // === vector<string> example ===
    vector<string> words = {"banana", "apple", "cherry", "banana", "date"};

    // Sort
    sort(words.begin(), words.end());
    cout << "Sorted words: ";
    for (auto& w : words) cout << w << " ";
    cout << endl;

    // Max and Min
    cout << "Max word: " << *max_element(words.begin(), words.end()) << endl;
    cout << "Min word: " << *min_element(words.begin(), words.end()) << endl;

    // Count
    cout << "Count of 'banana': " << count(words.begin(), words.end(), "banana") << endl;

    // Find
    auto it = find(words.begin(), words.end(), "cherry");
    if (it != words.end())
        cout << "'cherry' found at index: " << (it - words.begin()) << endl;

    // Reverse
    reverse(words.begin(), words.end());
    cout << "Reversed words: ";
    for (auto& w : words) cout << w << " ";
    cout << endl;

    // === vector<vector<int>> example ===
    vector<vector<int>> grid = {
        {3, 4, 5},
        {1, 2},
        {7, 8, 9},
        {2, 3, 4}
    };

    // Print grid
    cout << "\nOriginal grid:\n";
    for (auto& row : grid) {
        for (int x : row) cout << x << " ";
        cout << endl;
    }

    // Sort rows lexicographically
    sort(grid.begin(), grid.end());
    cout << "\nGrid after row-wise lexicographical sort:\n";
    for (auto& row : grid) {
        for (int x : row) cout << x << " ";
        cout << endl;
    }

    // Sort rows by sum
    sort(grid.begin(), grid.end(), [](vector<int>& a, vector<int>& b) {
        return accumulate(a.begin(), a.end(), 0) < accumulate(b.begin(), b.end(), 0);
    });
    cout << "\nGrid after sorting rows by sum:\n";
    for (auto& row : grid) {
        for (int x : row) cout << x << " ";
        cout << endl;
    }

    return 0;
}
```

---

### ✅ Sample Output:

```
Sorted words: apple banana banana cherry date
Max word: date
Min word: apple
Count of 'banana': 2
'cherry' found at index: 3
Reversed words: date cherry banana banana apple

Original grid:
3 4 5
1 2
7 8 9
2 3 4

Grid after row-wise lexicographical sort:
1 2
2 3 4
3 4 5
7 8 9

Grid after sorting rows by sum:
1 2
2 3 4
3 4 5
7 8 9
```

---

Let me know if you want these in a header-style cheat sheet or if you'd like to cover more advanced patterns like flattening, transposing, or searching in 2D grids.
