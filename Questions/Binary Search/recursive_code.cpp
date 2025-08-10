#include <bits/stdc++.h>
using namespace std;

int recursive_search_target(vector<int> arr, int low, int high, int target)
{
    if (low > high)
        return -1;

    int mid = (low + high) / 2;
    if (arr[mid] == target)
        return mid;
    else if (target > arr[mid])
        return recursive_search_target(arr, mid + 1, high, target); // searches on right side
    return recursive_search_target(arr, low, mid - 1, target);      // searches on left side
}

int main()
{
    /*
        output :
        6
        11
        5 9 7 15 11 14
        3
    */

    int n;
    cin >> n;
    vector<int> arr(n);
    int target;
    cin >> target;
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());
    cout << recursive_search_target(arr, 0, n - 1, target);
}

// overflow case where low and high are both INT_MAX so (low + high) / 2 = 2 * INT_MAX / 2 which can't be stored in int. so use long long or do
//  mid = low + ((high - low) / 2) coz this is same as (low + high) / 2