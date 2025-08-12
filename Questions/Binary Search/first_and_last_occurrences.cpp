#include <bits/stdc++.h>
using namespace std;

// this was using linear search which gave tc : O(N)
vector<int> find_first_and_last_occurrence(vector<int> arr, int x)
{
    /*

    8 - size of array
    3 - x
    4 3 5 3 6 7 3 3 - elements of array
    0 3 - first and last occurrence in sorted array

    */
    int n = arr.size();
    int first = -1, last = -1;
    for (int i = 0; i < n; i++)
    {
        // if (arr[i] == x)
        // {
        //     first = i;
        //     last = i;
        // }
        // if (last == -1)
        // {
        //     last = i;
        // }

        if (arr[i] == x)
        {
            if (first == -1)
            {
                first = i; // First occurrence
            }
            last = i; // Last occurrence (updated every time)
        }
    }
    return {first, last};
}

int find_lower_bound_binary(vector<int> arr, int x)
{
    // tc : O (log(n) base 2)
    int n = arr.size();
    int low = 0, high = n - 1;
    int answer = n;
    while (low <= high)
    {
        int mid = (low + high) / 2;

        // maybe an answer. agar iss se chhota nahi mila to ye answer hoga warna iss se chhota waala agar mila to wo answer hoga
        if (arr[mid] >= x)
        {
            answer = mid;

            // look for smaller index on left
            high = mid - 1;
        }
        else
            low = mid + 1; // look in right-side direction
    }
    // if no such answer found then return the size of array.
    // eg :
    // 6 - size of array
    // 15 - x
    // 2 3 7 6 14 12 - elements of array
    // 6 - returned size of array
    return answer;
}

int find_upper_bound(vector<int> arr, int x)
{
    // tc : O (log(n) base 2)
    int n = arr.size();
    int low = 0, high = n - 1;
    int answer = n;
    while (low <= high)
    {
        int mid = (low + high) / 2;

        // maybe an answer. agar iss se chhota nahi mila to ye answer hoga warna iss se chhota waala agar mila to wo answer hoga
        if (arr[mid] > x) // this is the only change from lower bound. there it was = .
        {
            answer = mid;

            // look for smaller index on left
            high = mid - 1;
        }
        else
            low = mid + 1; // look in right-side direction
    }
    // if no such answer found then return the size of array.
    // eg :
    // 6 - size of array
    // 15 - x
    // 2 3 7 6 14 12 - elements of array
    // 6 - returned size of array
    return answer;
}

// using binary search
pair<int, int> find_first_and_last_occurrence_binary(vector<int> arr, int x)
{
    // tc : O(2 * log(n) base 2)
    int lb = find_lower_bound_binary(arr, x);
    if (lb == arr.size() || arr[lb] != x)
        return {-1, -1};
    return {lb, find_upper_bound(arr, x) - 1};
}

int find_first_occurrence_using_plain_binary(vector<int> arr, int x)
{
    int n = arr.size();
    int low = 0, high = n - 1;
    int first = -1;
    while (low <= high)
    {
        int mid = (low + high) / 2;

        if (arr[mid] == x)
        {
            first = mid;
            high = mid - 1;
        }

        else if (arr[mid] < x)
        {
            low = mid + 1;
        }

        else
            high = mid - 1;
    }
    return first;
}

int find_last_occurrence_using_plain_binary(vector<int> arr, int x)
{
    int n = arr.size();
    int low = 0, high = n - 1;
    int last = -1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (arr[mid] == x)
        {
            last = mid;
            low = mid + 1;
        }

        else if (arr[mid] < x)
        {
            low = mid + 1;
        }

        else
            high = mid - 1;
    }
    return last;
}

int main()
{
    int n;
    cin >> n;
    int x;
    cin >> x;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());
    // vector<int> results = find_first_and_last_occurrence(arr, x);
    pair<int, int> results = find_first_and_last_occurrence_binary(arr, x);
    // for (auto it : results)
    // {
    //     cout << it << " ";
    // }
    // cout << endl;

    if (results.first == -1)
    {
        cout << "Element " << x << " not found in the array." << endl;
    }
    else
    {
        cout << "First occurrence of " << x << " is at index: " << results.first << endl;
        cout << "Last occurrence of " << x << " is at index: " << results.second << endl;
    }

    // for plain binary search without using upper and lower bounds
    int first_occurrence = find_first_occurrence_using_plain_binary(arr, x);
    int last_occurrence = find_last_occurrence_using_plain_binary(arr, x);

    // Output the results
    if (first_occurrence == -1)
    {
        cout << "Element " << x << " not found in the array." << endl;
    }
    else
    {
        cout << "First occurrence of " << x << " is at index: " << first_occurrence << endl;
        cout << "Last occurrence of " << x << " is at index: " << last_occurrence << endl;
    }

    return 0;
}

/*

Answer explanation for finding first and last occurrences using binary search :
Certainly! The line of code:

```cpp
if (lb == arr.size() || arr[lb] != x)
    return {-1, -1};
```

is critical in determining whether the element `x` exists in the array and handling cases where it doesn't.

Let’s break it down step-by-step:

### 1. **Understanding `lb == arr.size()`**:

* `lb` is the **lower bound** index returned by the function `find_lower_bound_binary`.
* The purpose of the lower bound is to find the **first position** in the array where `x` could be inserted **while maintaining sorted order**.
* If `x` exists in the array, `lb` will be the index of the **first occurrence** of `x`.
* However, if `x` is **not present** in the array, `find_lower_bound_binary` will return an index equal to the **size of the array** (`arr.size()`).

#### Why is `lb == arr.size()` important?

* When `lb == arr.size()`, it means the function has reached an index **beyond the last element** of the array. This typically happens when `x` is greater than any element in the array (or if `x` does not exist at all).

For example, if you have an array:

```cpp
arr = {1, 2, 3, 5, 6}
```

and you’re looking for `x = 7`, the lower bound would return `5` (which is equal to the size of the array, i.e., `arr.size() == 5`), indicating that `x` is greater than all elements.

### 2. **Understanding `arr[lb] != x`**:

* The second part of the condition, `arr[lb] != x`, checks whether the element at the `lb` index **is not equal to `x`**.
* After the binary search in `find_lower_bound_binary`, if `x` **is present** in the array, `arr[lb]` should be equal to `x`.
* However, if `x` is **not found**, `arr[lb]` will be an element that is **greater than** `x` (in the case of `find_lower_bound`), or `lb` will be equal to `arr.size()`.

#### Why is `arr[lb] != x` important?

* This condition ensures that we’re checking whether the **first occurrence** of `x` is actually at index `lb`.
* If `arr[lb]` is not equal to `x`, it means `x` is not present at that position, or it is absent in the array altogether.

### 3. **Combining the two conditions**:

```cpp
if (lb == arr.size() || arr[lb] != x)
    return {-1, -1};
```

* This combined condition serves two purposes:

  1. **`lb == arr.size()`**: This checks whether the lower bound index points beyond the last element in the array. If `x` is greater than all elements or if `x` is missing, the function reaches the end of the array.
  2. **`arr[lb] != x`**: This checks whether the value at the lower bound index is actually the value `x`. If not, it means `x` is not present in the array.

### What happens when this condition is true?

* If either `lb == arr.size()` or `arr[lb] != x`, it means that `x` does **not exist** in the array.
* In that case, the function returns `{-1, -1}`, indicating that the element was not found in the array.

### Example Scenarios:

#### Scenario 1: Element **not found**

```cpp
arr = {1, 2, 4, 5, 6};
x = 3;
```

* `find_lower_bound_binary` will return `2` (position where `3` would be inserted).
* `arr[2]` is `4`, which is not equal to `3`, so `arr[lb] != x` is true.
* The condition `lb == arr.size()` is false (`lb = 2`), but `arr[lb] != x` is true. Therefore, the function returns `{-1, -1}`, indicating that `3` is not in the array.

#### Scenario 2: Element **found**

```cpp
arr = {1, 2, 3, 3, 3, 5, 6};
x = 3;
```

* `find_lower_bound_binary` will return `2` (index of the first occurrence of `3`).
* `arr[2]` is `3`, which is equal to `x`, so the second part of the condition `arr[lb] != x` is false.
* Therefore, the function does **not** return `{-1, -1}`, and it proceeds to find the **last occurrence** using the `find_upper_bound`.

### Summary of the condition:

* **`lb == arr.size()`**: Checks if `x` is not present in the array at all (either it's greater than all elements or absent).
* **`arr[lb] != x`**: Checks whether the element at `lb` is actually `x`. If not, it means `x` doesn't exist at that position.

When either of these conditions is true, the function correctly identifies that `x` is **not present** in the array and returns `{-1, -1}`. This handles edge cases such as `x` being larger than all elements or `x` being absent in the array.

This explanation should help you understand why the check is necessary and how it ensures the correct result.


*/