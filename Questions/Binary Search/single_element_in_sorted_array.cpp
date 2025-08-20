// here an element will have a single occurrence whereas others will have 2. array will always be sorted

#include <bits/stdc++.h>
using namespace std;

int findSingleElementBrute(vector<int> &arr)
{
    int n = arr.size();
    if (n == 1)
        return arr[0];

    for (int i = 0; i < n; i++)
    {
        if (i == 0) // if element is the first element
        {
            if (arr[i] != arr[i + 1]) // since, it is first element, we are checking if it is not equal to its next element
                return arr[0];
        }

        else if (i == n - 1) // if element is last element of array
        {
            if (arr[i] != arr[i - 1]) // since, it is last element, we are checking if it is not equal to its previous element
                return arr[i];
        }

        // if element is not first element or last element of array, then it will be somewhere in the middle.
        else
        {
            // in this case, check both left and right side and see if it is equal to any of them. if not, then that element is the single element
            if (arr[i] != arr[i + 1] && arr[i] != arr[i - 1])
                return arr[i];
        }
    }
    return -1;
}

// optimal approach using binary search
// here we are using binary search in a manipulative way, bcoz if it is used like normal, then a lot of conditions would have to be checked.
// like we will have to consider if it is first element or last element or last, then accordingly check only right and left sides, for suitable cases.
// (even, odd) -> this is index of element. if element is in right half, eliminate left half
// (odd, even) -> if element is on left half, eliminate right half.

int findSingleElementOptimal(vector<int> &arr)
{
    int n = arr.size();

    // check for edge cases separately, bcoz we are taking low from 1 and high from n-2

    // if array has only one element
    if (n == 1)
        return arr[0];

    // if first element
    if (arr[0] != arr[1])
        return arr[0];

    // if last element
    if (arr[n - 1] != arr[n - 2])
        return arr[n - 1];

    int low = 1, high = n - 2;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] != arr[mid + 1] && arr[mid] != arr[mid - 1])
            return arr[mid];

        // we are on left side
        // mid % 2 == 1 means we are odd index and left side element is equal whereas mid % 2 == 0 means we are at even index and right side element is equal, so we will eliminate left half
        if ((mid % 2 == 1 && arr[mid - 1] == arr[mid]) || (mid % 2 == 0 && arr[mid] == arr[mid + 1]))
        {
            low = mid + 1;
        }

        // we are standing on right half
        else
        {
            high = mid - 1; // eliminate right half
        }
    }
    return -1;
}

int main()
{
    int n;
    cout << "Enter the number of elements in the array: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the elements (sorted, with exactly one element occurring once):\n";
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }

    int result = findSingleElementOptimal(arr);
    cout << "The single element is: " << result << endl;

    return 0;
}