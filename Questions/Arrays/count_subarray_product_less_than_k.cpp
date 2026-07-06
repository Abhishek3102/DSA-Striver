#include <bits/stdc++.h>
using namespace std;

int subarrayProductLessThanK(vector<int> &v, int k)
{
    int n = v.size();

    // Left and right pointers of the sliding window
    int left = 0, right = 0;

    // Stores the product of the current window
    int product = 1;

    // Final answer
    int total = 0;

    while (right < n)
    {
        // Include the current element in the window
        product *= v[right];

        // If the product becomes >= k,
        // shrink the window from the left
        while (left <= right && product >= k)
        {
            product /= v[left];
            left++;
        }

        /*
           At this point, the window [left...right]
           has product < k.

           Every subarray ending at 'right'
           and starting anywhere between left and right
           is also valid.

           Number of such subarrays:

               right - left + 1
        */

        total += (right - left + 1);

        // Expand the window
        right++;
    }

    return total;
}