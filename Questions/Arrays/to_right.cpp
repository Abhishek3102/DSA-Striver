#include <bits/stdc++.h>
using namespace std;

void rot_right(int arr[], int n, int d)
{
    d = d % n;

    // Original array : [1, 6, 5, 9, 8, 4]

    reverse(arr, arr + n); // [4, 8, 9, 5, 6, 1]

    reverse(arr, arr + d); // [9, 8, 4, 5, 6, 1]

    reverse(arr + d, arr + n); // [9, 8, 4, 1, 6, 5]
}

int main()
{
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    int d;
    cin >> d;
    rot_right(arr, n, d);
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}