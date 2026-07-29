/*
If the array is **unsorted**, there are two possible interpretations.

## 1. Your approach (store all valid indices, then find the minimum)

```cpp
*/
#include <bits/stdc++.h>
using namespace std;

int findIndex(vector<int> &arr, int x)
{
    vector<int> ans;

    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] >= x)
            ans.push_back(i);
    }

    if (ans.empty())
        return arr.size();

    int mini = ans[0];
    for (int i = 1; i < ans.size(); i++)
    {
        mini = min(mini, ans[i]);
    }

    return mini;
}

int main()
{
    vector<int> arr = {8, 2, 6, 4, 7};
    int x = 5;

    cout << findIndex(arr, x);
}

/*
```

### Complexity

* Time: **O(n)**
* Space: **O(n)**

**Note:** Since indices are pushed in increasing order (`0, 2, 4...`), finding the minimum afterward is unnecessary. `ans[0]` is already the smallest index.

---

## 2. Better approach (no extra vector)

```cpp

*/
#include <bits/stdc++.h>
using namespace std;

int findIndex(vector<int> &arr, int x)
{
    for (int i = 0; i < arr.size(); i++)
    {
        if (arr[i] >= x)
            return i;
    }

    return arr.size();
}

int main()
{
    vector<int> arr = {8, 2, 6, 4, 7};
    int x = 5;

    cout << findIndex(arr, x);
}

/*
```

### Complexity

* Time: **O(n)**
* Space: **O(1)**

---

### If your goal is the smallest value ≥ `x` in an unsorted array

Sometimes people mean "find the minimum element that is at least `x`." In that case:

```cpp

*/

#include <bits/stdc++.h>
using namespace std;

int smallestGreaterEqual(vector<int> &arr, int x)
{
    int ans = INT_MAX;

    for (int num : arr)
    {
        if (num >= x)
            ans = min(ans, num);
    }

    if (ans == INT_MAX)
        return -1;

    return ans;
}

int main()
{
    vector<int> arr = {8, 2, 6, 4, 7};
    int x = 5;

    cout << smallestGreaterEqual(arr, x);
}
/*
```

For `arr = {8, 2, 6, 4, 7}` and `x = 5`, this returns **6**, because 6 is the smallest element that is greater than or equal to 5.

So for an **unsorted** array, be clear about whether you want:

* the **first index** satisfying `arr[i] >= x`,
* the **smallest index** satisfying `arr[i] >= x` (same as the first index during a left-to-right scan), or
* the **smallest value** satisfying `arr[i] >= x`. These are different problems.
*/