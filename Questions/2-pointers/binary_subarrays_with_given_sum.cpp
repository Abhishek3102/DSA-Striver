// this is similar to count subarray sum equals k which was an array question.
// there the optimal approach was using map, to check a target which pre-existed
// but here we get rid of map due to extra space and we use 2-pointer and sliding window

#include <bits/stdc++.h>
using namespace std;

/*
    This function returns the number of subarrays having SUM <= k.

    Why does sliding window work?
    -----------------------------
    Since this is a positive ARRAY (contains only positive integers),
    extending the window can only increase the sum or keep it the same.
    It can NEVER decrease the sum.

    This monotonic property allows us to use the sliding window.

    If the array contained negative numbers,
    sliding window would fail because removing/adding elements
    wouldn't have a predictable effect on the sum.
*/

int findSumwithKBetter(vector<int> &arr, int k) {}

int findBinarySubarrayWiSum(vector<int> &arr, int k)
{
    // No subarray can have sum <= negative value.
    if (k < 0)
        return 0;

    int n = arr.size();

    // Left and right pointers of the sliding window
    int l = 0, r = 0;

    // Current window sum
    int sum = 0;

    // Total number of valid subarrays
    int count = 0;

    while (r < n)
    {
        // Expand the window by including arr[r]
        sum += arr[r];

        /*
            If window sum exceeds k,
            keep shrinking the window from the left
            until it becomes valid again.
        */
        while (sum > k)
        {
            sum -= arr[l];
            l++;
        }

        /*
            At this point:
            window [l...r] has sum <= k.

            Even more importantly...

            Every subarray ending at r and starting anywhere
            between l and r is also valid.

            Valid subarrays are:

            [r]
            [r-1 ... r]
            [r-2 ... r]
            ...
            [l ... r]

            Number of such subarrays =
                    r - l + 1

            Example:

            l = 2, r = 5

            Valid ending at index 5:

            [5]
            [4,5]
            [3,4,5]
            [2,3,4,5]

            Total = 5 - 2 + 1 = 4
        */
        count += (r - l + 1);

        // Move right pointer forward
        r++;
    }

    return count;
}

int main()
{
    vector<int> arr = {1, 0, 0, 1, 1, 0};
    int k = 2;

    /*
        findBinarySubarrayWiSum(k)
            gives number of subarrays having sum <= k

        findBinarySubarrayWiSum(k-1)
            gives number of subarrays having sum <= k-1

        Therefore,

        (sum <= k)
        -
        (sum <= k-1)

        leaves only

        (sum == k)

        This is exactly the same trick used in many sliding
        window problems:
                EXACT = ATMOST(K) - ATMOST(K-1)
    */
    cout << findBinarySubarrayWiSum(arr, k) - findBinarySubarrayWiSum(arr, k - 1)
         << endl;

    // Number of subarrays with sum <= 2
    cout << findBinarySubarrayWiSum(arr, 2) << endl;

    // Number of subarrays with sum <= 1
    cout << findBinarySubarrayWiSum(arr, 1) << endl;

    return 0;
}