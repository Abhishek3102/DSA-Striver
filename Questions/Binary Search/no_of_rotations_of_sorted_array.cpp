#include <bits/stdc++.h>
using namespace std;

int findKRotation(vector<int> &arr)
{
    int low = 0, high = arr.size() - 1;
    int answer = INT_MAX; // Initialize answer to maximum possible value
    int index = -1;       // This stores the index of the smallest element found. It is the number of rotations.

    while (low <= high)
    {
        int mid = low + (high - low) / 2; // Find the mid index to divide the array for binary search

        // ✅ Case 1: The current search space [low...high] is already sorted
        // In a sorted subarray, the smallest element is at index `low`
        if (arr[low] <= arr[high])
        {
            // If this subarray is sorted, the smallest element must be at `low`
            if (arr[low] < answer) // We compare with the smallest element we've seen so far
            {
                index = low;       // The index of the smallest element (answer) in this sorted subarray
                answer = arr[low]; // Update the minimum value found
            }
            break; // Since the subarray is sorted, no need to continue searching
        }

        // ✅ Case 2: Left half [low...mid] is sorted
        if (arr[low] <= arr[mid])
        {
            // Since left half is sorted, arr[low] is the minimum in this half
            if (arr[low] < answer) // If arr[low] is smaller than the smallest we've found
            {
                index = low;       // We update the index to `low` as it's the current smallest element
                answer = arr[low]; // Update the answer to the new smallest element
            }

            // Eliminate the left half and search in the right half
            low = mid + 1;
        }

        // ✅ Case 3: Right half [mid...high] is sorted
        else
        {
            // Since right half is sorted, arr[mid] is the minimum in this half
            if (arr[mid] < answer) // If arr[mid] is smaller than the smallest we've found
            {
                index = mid;       // Update index to `mid` as the new smallest element
                answer = arr[mid]; // Update the answer to the new smallest element
            }
            // Eliminate the right half and search in the left half
            high = mid - 1;
        }
    }

    return index;
}

int main()
{
    int n;
    cout << "Enter the number of elements in the rotated sorted array: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the elements:\n";
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }

    int k = findKRotation(arr);
    cout << "The array has been rotated " << k << " times.\n";

    return 0;
}