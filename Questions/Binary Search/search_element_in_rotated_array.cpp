#include <bits/stdc++.h>
using namespace std;

int find_element(vector<int> arr, int target)
{
    int n = arr.size();
    int low = 0, high = n - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        // If target is found, return its index
        if (arr[mid] == target)
            return mid;

        // left sorted array
        if (arr[low] <= arr[mid])
        {

            // Target is in the left half
            if (arr[low] <= target && target <= arr[mid])
            {
                high = mid - 1; // trim the right half, i.e., eliminate right half
            }
            // Target is in the right half
            else
            {
                low = mid + 1; // trim the left half, i.e., eliminate left half
            }
        }
        // Right sorted part
        else
        {
            // Target is in the right half
            if (arr[mid] <= target && target <= arr[high])
            {
                low = mid + 1; // trim the left half, i.e., eliminate the left half
            }
            // Target is in the left half
            else
                high = mid - 1; // trim the right half, i.e., eliminate the right half
        }
    }
    return -1; // Return -1 if target is not found
}

int main()
{
    int n, target;

    cout << "Enter the size of the array: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the elements of the rotated sorted array: ";
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }

    cout << "Enter the target element to search for: ";
    cin >> target;

    int result = find_element(arr, target);

    if (result != -1)
    {
        cout << "Element " << target << " found at index: " << result << endl;
    }
    else
    {
        cout << "Element " << target << " not found in the array." << endl;
    }

    return 0;
}