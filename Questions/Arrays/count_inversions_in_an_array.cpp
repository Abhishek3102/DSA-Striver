// in this sum, we have to find pairs in array such that the number on the left side of array is greater than number on the right.
// eg : vector<int> arr = {5, 3, 2, 4, 1}; the count of such pairs is 8. like (5,3) is a pair but (3,4) isn't coz 3 is less than 4. also (3,5) isn't bcoz left side number should be greater.

#include <bits/stdc++.h>
using namespace std;

// brute force approach, tc : O(N^2)
int find_pairs(vector<int> arr)
{
    int n = arr.size();
    int count_brute = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] > arr[j])
                count_brute++;
        }
    }
    return count_brute;
}

int merge(vector<int> &arr, int low, int mid, int high)
{
    int count = 0;
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
        if (arr[left] <= arr[right]) // left is smaller
        {
            temp.push_back(arr[left]);
            left++;
        }
        // right is smaller
        else
        {
            temp.push_back(arr[right]);
            count += (mid - left + 1);
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
    return count;
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

void mergeSort(vector<int> &arr, int low, int high)
{
    if (low >= high)
        return;
    int mid = (low + high) / 2;
    mergeSort(arr, low, mid);
    mergeSort(arr, mid + 1, high);
    merge(arr, low, mid, high);
}

int numberOfInversions(vector<int> &a, int n)
{
    mergeSort(a, 0, n - 1);
    // TO FIX : TODO
    // return count;
}

int main()
{
    vector<int> arr = {5, 3, 2, 4, 1};
    // int result = find_pairs_better(arr);
    // cout << result << endl;
}