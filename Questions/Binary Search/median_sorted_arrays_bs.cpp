#include <bits/stdc++.h>
using namespace std;

double median_binary_search(vector<int> a, vector<int> b)
{
    int n1 = a.size();
    int n2 = b.size();

    // Always apply binary search on the smaller array
    // This ensures logarithmic complexity is minimized (log(min(n1, n2))).
    if (n1 > n2)
        return median_binary_search(b, a);

    int low = 0, high = n1;

    // Total number of elements across both arrays
    int n = n1 + n2;

    // Number of elements we want on the "left partition"
    // Formula works for both odd & even:
    // If total is even, left = n/2
    // If total is odd, left = (n+1)/2 (ensures left side has 1 extra element)
    int left = (n1 + n2 + 1) / 2;

    while (low <= high)
    {
        // Partition size taken from array a
        int mid1 = (low + high) >> 1;

        // Remaining elements for left partition will come from array b
        int mid2 = left - mid1;

        // l1 = last element on left side of array a
        // r1 = first element on right side of array a
        // l2 = last element on left side of array b
        // r2 = first element on right side of array b
        // Use INT_MIN / INT_MAX when partition touches the boundaries
        int l1 = INT_MIN, l2 = INT_MIN;
        int r1 = INT_MAX, r2 = INT_MAX;

        if (mid1 < n1)
            r1 = a[mid1]; // Rightmost element of left partition in a
        if (mid2 < n2)
            r2 = b[mid2]; // Rightmost element of left partition in b

        if (mid1 - 1 >= 0)
            l1 = a[mid1 - 1]; // Leftmost element of right partition in a
        if (mid2 - 1 >= 0)
            l2 = b[mid2 - 1]; // Leftmost element of right partition in b

        // Check if we found the correct "symmetry":
        // Valid partition condition = all left elements ≤ all right elements
        if (l1 <= r2 && l2 <= r1)
        {
            // If total elements are odd → median is max of left side
            if (n % 2 == 1)
                return max(l1, l2);

            // If even → median is average of max(left) and min(right)
            return (double)(max(l1, l2) + min(r1, r2)) / 2.0;
        }

        // If l1 > r2 → we have taken too many elements from a
        // So, move "high" leftward (reduce partition from a)
        else if (l1 > r2)
            high = mid1 - 1;

        // If l2 > r1 → we have taken too few elements from a
        // So, move "low" rightward (take more from a)
        else
            low = mid1 + 1;
    }

    // Control should never reach here for valid input
    return 0;
}
