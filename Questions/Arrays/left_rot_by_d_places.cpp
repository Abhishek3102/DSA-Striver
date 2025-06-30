#include <bits/stdc++.h>
using namespace std;

void left_rot_by_d(int arr[], int n, int d)
{
    d = d % n;
    int temp[d];

    // O(d)
    for (int i = 0; i < d; i++)
    {
        temp[i] = arr[i];
    }

    // O(n-d)
    for (int i = d; i < n; i++)
    {
        arr[i - d] = arr[i];
    }

    // O(d)
    for (int i = n - d; i < n; i++)
    {
        arr[i] = temp[i - (n - d)];
    }

    // Total t.c. is : O(d) + O(n-d) + O(d) = O(n+d)
    // extra space used is O(d) which is due to temp array
    // overall s.c is O(n) + O(d)
}

void left_rot_by_d_optimal(int arr[], int n, int d)
{
    // here we remove the extra space used due to temp array
    // we perform following reverses, to avoid making use of temp array

    // reverse (a, a+d)  |   O(d)
    // reverse(a+d, a+n) |   O(n-d)
    // reverse(a, a+n)   |   O(n)
    // so total t.c. here is : O(2n)
    // but extra space used is O(1) and overall s.c. is O(n) for n sized array

    /*
    Manual reverse function :
    void reverse(int arr[], int start, int end){
        while(start <= end){
            int temp = arr[start];
            arr[start] = arr[end];
            arr[end] = temp;
            start++;
            end--;
    }
    }
    */

    // Original array : [1, 8, 6, 3, 2, 5, 9]
    reverse(arr, arr + d);     // [6, 8, 1, 3, 2, 5, 9]
    reverse(arr + d, arr + n); // [6, 8, 1, 9, 5, 2, 3]
    reverse(arr, arr + n);     // [3, 2, 5, 9, 1, 8, 6]
    d = d % n;
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
    left_rot_by_d_optimal(arr, n, d);
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}