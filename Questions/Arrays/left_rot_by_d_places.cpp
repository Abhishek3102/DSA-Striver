#include <bits/stdc++.h>
using namespace std;

void left_rot_by_d(int arr[], int n)
{
    // t.c. is O(N) coz for loop running till n-1, and s.c. is O(1) bcoz all operations are happening in given array only
    int temp = arr[0];
    for (int i = 0; i < n - 1; i++)
    {
        arr[i] = arr[i + 1];
    }
    arr[n - 1] = temp;
    // return arr[n];
}

void print_array(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
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
    left_rot_by_d(arr, n);
    print_array(arr, n);
    return 0;
}