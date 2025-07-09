#include <bits/stdc++.h>
using namespace std;

// dictionary wise arrangement
vector<int> nextGreaterPermutation(vector<int> &a)
{
    int index = -1;
    // if(index == -1) reverse(A);
    int n = a.size();
    for (int i = n - 2; i >= 0; i--)
    {
        if (a[i] < a[i + 1])
        {
            index = i;
            break;
        }
    }

    if (index == -1)
    {
        reverse(a.begin(), a.end());
        return a;
    }

    for (int i = n - 1; i >= index; i--)
    {
        if (a[i] > a[index])
        {
            swap(a[i], a[index]);
            break;
        }
    }

    reverse(a.begin() + index + 1, a.end());
    return a;
}

int main()
{
    vector<int> a = {1, 5, 3, 4, 9, 6, 7, 2};
    vector<int> result = nextGreaterPermutation(a);

    cout << "Next greater permutation: ";
    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i] << " ";
    }
    cout << endl;
    return 0;
}

/*

### Input Vector:

`a = {1, 5, 3, 4, 9, 6, 7, 2}`

### Step-by-Step Process:

#### **Step 1: Find the rightmost pair where `a[i] < a[i+1]`.**

Start from the second-to-last element (`a[n-2]`) and look for the first position `i` where `a[i] < a[i + 1]`. This identifies the point where the sequence can be increased to generate the next permutation.

* Compare `a[6] (7)` and `a[7] (2)`: Since `7 > 2`, continue.
* Compare `a[5] (6)` and `a[6] (7)`: Since `6 < 7`, this is the **first pair** where `a[i] < a[i + 1]`. We have found `i = 5`. This means that the position `5` (value `6`) can be increased to generate the next permutation.

#### **Step 2: Find the largest element `a[j]` such that `a[j] > a[i]` and `j > i`.**

Now that we've found `i = 5` where `a[i] < a[i + 1]`, we need to find the largest element that is greater than `a[i]` (i.e., `a[5] = 6`) from the right end of the array. This element will swap with `a[i]` to create the next permutation.

* Start from the end of the array and look for a number greater than `a[5] (6)`.
* Compare `a[7] (2)` with `a[5] (6)`: Since `2 < 6`, continue.
* Compare `a[6] (7)` with `a[5] (6)`: Since `7 > 6`, we choose `j = 6` (value `7`).

#### **Step 3: Swap `a[i]` and `a[j]`.**

Now that we have found `i = 5` and `j = 6`, we swap `a[5]` with `a[6]`.

Before the swap:

* `a = {1, 5, 3, 4, 9, 6, 7, 2}`

After the swap:

* `a = {1, 5, 3, 4, 9, 7, 6, 2}`

#### **Step 4: Reverse the subarray from `i+1` to the end.**

Finally, to ensure that the next permutation is the smallest lexicographically larger permutation, we reverse the portion of the array starting from `i + 1` to the end of the array.

* The subarray starting from `i + 1 = 6` is `{6, 2}`.
* Reverse the subarray `{6, 2}` to get `{2, 6}`.

After reversing:

* `a = {1, 5, 3, 4, 9, 7, 2, 6}`

### Final Result:

The next greater permutation is:
`{1, 5, 3, 4, 9, 7, 2, 6}`

### Summary of the Steps:

1. **Find the first pair `a[i] < a[i+1]`**: We found `i = 5`.
2. **Find the largest `a[j] > a[i]` for `j > i`**: We found `j = 6`.
3. **Swap `a[i]` and `a[j]`**: The array becomes `{1, 5, 3, 4, 9, 7, 6, 2}`.
4. **Reverse the subarray from `i + 1` to the end**: The array becomes `{1, 5, 3, 4, 9, 7, 2, 6}`.

This gives us the next lexicographically greater permutation.


*/