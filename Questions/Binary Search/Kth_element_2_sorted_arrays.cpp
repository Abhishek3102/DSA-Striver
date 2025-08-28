#include <bits/stdc++.h>
using namespace std;

// int kthElement(vector<int> &a, vector<int> &b, int n1, int n2, int k)
// {
//     if (n1 > n2)
//         return kthElement(b, a, n1, n1, k);
//     int low = 0, high = n1;
//     int left = k;
//     int n = n1 + n2;
//     while (low <= high)
//     {
//         int mid1 = (low + high) >> 1;
//         int mid2 = left - mid1;
//         int l1 = INT_MIN, l2 = INT_MIN;
//         int r1 = INT_MAX, r2 = INT_MAX;

//         if (mid1 < n1)
//             r1 = a[mid1];
//         if (mid2 < n2)
//             r2 = b[mid2];

//         if (mid1 - 1 >= 0)
//             l1 = a[mid1 - 1];
//         if (mid2 - 1 >= 0)
//             l2 = b[mid2 - 1];

//         if (l1 <= r2 && l2 <= r1)
//             return max(l1, l2);

//         else if (l1 > r2)
//             high = mid1 - 1;
//         else
//             low = mid1 + 1;
//     }
//     return 0;
// }

int kthElement(vector<int> &a, vector<int> &b, int n1, int n2, int k)
{
    // If the first array is larger than the second, swap them for better performance
    if (n1 > n2)
        return kthElement(b, a, n1, n1, k);

    // Set the initial search range for binary search on the smaller array `a`
    int low = max(k - n2, 0), high = min(k, n1);
    int left = k;
    int n = n1 + n2;
    while (low <= high)
    {
        int mid1 = (low + high) >> 1; // Midpoint in array `a`
        int mid2 = left - mid1;       // Complementary position in array `b`

        // Initialize left and right values for the partitions
        int l1 = INT_MIN, l2 = INT_MIN;
        int r1 = INT_MAX, r2 = INT_MAX;

        // Get the right element of each partition (if valid)
        if (mid1 < n1)
            r1 = a[mid1];
        if (mid2 < n2)
            r2 = b[mid2];

        // Get the left element of each partition (if valid)
        if (mid1 - 1 >= 0)
            l1 = a[mid1 - 1];
        if (mid2 - 1 >= 0)
            l2 = b[mid2 - 1];

        // If the partitions are valid (no inversion of order), return the kth element
        if (l1 <= r2 && l2 <= r1)
            return max(l1, l2);

        // If left element of `a` is too large, move the partition to the left
        else if (l1 > r2)
            high = mid1 - 1;

        // If left element of `b` is too large, move the partition to the right
        else
            low = mid1 + 1;
    }
    return 0;
}

int main()
{

    vector<int> a = {2, 5, 8, 10};
    vector<int> b = {1, 3, 4, 6};

    int n1 = a.size();
    int n2 = b.size();

    int k = 7;

    int result = kthElement(a, b, n1, n2, k);
    cout << "The " << k << "th smallest element is: " << result << endl;

    return 0;
}
