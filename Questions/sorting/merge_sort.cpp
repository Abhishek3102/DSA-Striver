#include <bits/stdc++.h>
using namespace std;

void merge(vector<int> &arr, int low, int mid, int high)
{
    vector<int> temp; // Temporary array to store merged result
    // Space Complexity: O(n), where n = high - low + 1

    // Left subarray -> [low....mid]
    // Right subarray -> [mid+1....high]

    int left = low;
    int right = mid + 1;

    // Merge the two sorted halves
    while (left <= mid && right <= high)
    {
        // Time Complexity (in total for the entire merge step across the array): O(n)
        if (arr[left] <= arr[right])
        {
            temp.push_back(arr[left]);
            left++;
        }
        else
        {
            temp.push_back(arr[right]);
            right++;
        }
    }

    // Copy any remaining elements from the left subarray
    while (left <= mid)
    {
        temp.push_back(arr[left]);
        left++;
        // Worst case: O(n) if all elements are in left subarray
    }

    // Copy any remaining elements from the right subarray
    while (right <= high)
    {
        temp.push_back(arr[right]);
        right++;
        // Worst case: O(n) if all elements are in right subarray
    }

    // Copy merged elements back into original array
    for (int i = low; i <= high; i++)
    {
        arr[i] = temp[i - low];
        // Time Complexity: O(n)
    }

    // Total Time Complexity of merge() = O(n), where n = high - low + 1
    // Total Space Complexity of merge() = O(n)
}

void mS(vector<int> &arr, int low, int high)
{
    // Base case: when only one element is left
    if (low == high)
        return;

    // Calculate the middle point
    int mid = (low + high) / 2;

    // Recursively sort the left half
    mS(arr, low, mid);

    // Recursively sort the right half
    mS(arr, mid + 1, high);

    // Merge the sorted halves
    merge(arr, low, mid, high);

    // Time Complexity per level: O(n) (from merge)
    // Number of levels (recursive depth): O(log n)
    // So, total Time Complexity: O(n log n)

    // Space Complexity: O(log n) due to recursive call stack (implicit)
    // Plus O(n) for temp arrays in each merge
    // So, overall space:
    // - Auxiliary/Recursive stack: O(log n)
    // - Temporary arrays: O(n) (not per call, total across all levels)
}

void mergeSort(vector<int> &arr, int n)
{
    mS(arr, 0, n - 1);
    // This function is just a wrapper, no additional complexity added
}

int main()
{
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> arr(n);

    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i]; // Read each element from user input
    }

    // Call mergeSort to sort the array
    mergeSort(arr, n);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " "; // Output each element followed by a space
    }
    cout << endl;

    return 0;
}
