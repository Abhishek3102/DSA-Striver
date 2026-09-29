// here we have to find max length of subarray where there are at most 2 types of numbers
// arr = [3 3 3 1 2 1 1 2 3 3 4], here the max length is 5 for subarray 1 2 1 1 2.

#include <bits/stdc++.h>
using namespace std;

int findMaxLength(vector<int> arr)
{
    int n = arr.size();
    int l = 0;
    int r = 0;
    int k = 2;
    int maxLength = 0;
    map<int, int> mpp;
    while (r < n)
    {
        mpp[arr[r]]++;

        if (mpp.size() > k)
        {
            while (mpp.size() > k)
            {
                mpp[arr[l]]--;

                if (mpp[arr[l]] == 0)
                    mpp.erase(arr[l]);
                l++;
            }
        }

        if (mpp.size() <= k)
        {
            maxLength = max(maxLength, r - l + 1);
        }
        r++;
    }
    return maxLength;
}

int main()
{
    int findMaxLength(vector<int> arr);
    vector<int> arr = {3, 3, 3, 1, 2, 1, 1, 2, 3, 3, 4};
    cout << findMaxLength(arr);
}

/*

int findMaxLength(vector<int> arr)
{
    int n = arr.size();

    // Left and right pointers of the sliding window
    int l = 0;
    int r = 0;

    // We are allowed to have at most 2 distinct numbers
    int k = 2;

    // Stores the maximum valid window length found so far
    int maxLength = 0;

    // map stores:
    // number -> frequency of that number inside
    // the current sliding window
    map<int, int> mpp;

    while (r < n)
    {
        // Add the current element to the window
        // and increase its frequency
        mpp[arr[r]]++;

        /*
            If the window contains more than 2 distinct numbers,
            it is no longer valid.

            Example:
                Window = {3, 1, 2}

            Distinct numbers = {3, 1, 2} = 3

            We need to shrink the window from the left
            until only 2 distinct numbers remain.
        */
/*if (mpp.size() > k)
{
    while (mpp.size() > k)
    {
        // Remove arr[l] from the current window
        mpp[arr[l]]--;

        // If its frequency becomes 0,
        // completely remove it from the map.
        //
        // This is important because map.size()
        // represents the number of DISTINCT numbers.
        if (mpp[arr[l]] == 0)
            mpp.erase(arr[l]);

        // Move left pointer forward
        l++;
    }
}

/*
    Now the window contains at most 2 distinct numbers.

    Current window:
            [l ........ r]

    Its length is:
            r - l + 1

    Update the maximum length.
*/
/*if (mpp.size() <= k)
{
    maxLength = max(maxLength, r - l + 1);
}

// Expand the window by moving right pointer
r++;
}

return maxLength;
}

*/