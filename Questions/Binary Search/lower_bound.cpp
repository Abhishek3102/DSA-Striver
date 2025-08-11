#include <bits/stdc++.h>
using namespace std;

// using linear search

/*

eg for no value found which is >= x

6
15
2 3 5 7 11 13
6

when value is found
6
15
11 17 8 9 22 13
4

*/
int find_lower_bound(vector<int> arr, int x)
{
    int n = arr.size();
    for (int i = 0; i < n; i++)
    {
        if (arr[i] >= x)
            return i;
    }
    return n;
}

// using binary search
int find_lower_bound_binary(vector<int> arr, int x)
{
    // tc : O (log(n) base 2)
    int n = arr.size();
    int low = 0, high = n - 1;
    int answer = n;
    while (low <= high)
    {
        int mid = (low + high) / 2;

        // maybe an answer. agar iss se chhota nahi mila to ye answer hoga warna iss se chhota waala agar mila to wo answer hoga
        if (arr[mid] >= x)
        {
            answer = mid;

            // look for smaller index on left
            high = mid - 1;
        }
        else
            low = mid + 1; // look in right-side direction
    }
    // if no such answer found then return the size of array.
    // eg :
    // 6 - size of array
    // 15 - x
    // 2 3 7 6 14 12 - elements of array
    // 6 - returned size of array
    return answer;
}

int find_upper_bound(vector<int> arr, int x)
{
    // tc : O (log(n) base 2)
    int n = arr.size();
    int low = 0, high = n - 1;
    int answer = n;
    while (low <= high)
    {
        int mid = (low + high) / 2;

        // maybe an answer. agar iss se chhota nahi mila to ye answer hoga warna iss se chhota waala agar mila to wo answer hoga
        if (arr[mid] > x) // this is the only change from lower bound. there it was = .
        {
            answer = mid;

            // look for smaller index on left
            high = mid - 1;
        }
        else
            low = mid + 1; // look in right-side direction
    }
    // if no such answer found then return the size of array.
    // eg :
    // 6 - size of array
    // 15 - x
    // 2 3 7 6 14 12 - elements of array
    // 6 - returned size of array
    return answer;
}

int main()
{
    int n;
    cin >> n;
    int x;
    cin >> x;
    vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    sort(arr.begin(), arr.end());
    // cout << find_lower_bound(arr, x);
    cout << find_lower_bound_binary(arr, x);
}