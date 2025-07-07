#include <bits/stdc++.h>
using namespace std;

void sort_arr_012(int arr[], int n)
{
    // int count0 = 0, count1 = 1, count2 = 2; striver
    int count0 = 0, count1 = 0, count2 = 0; // correct
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == 0)
            count0++;
        else if (arr[i] == 1)
            count1++;
        else
            count2++;
    }
    for (int i = 0; i < count0; i++)
        arr[i] = 0;
    for (int i = count0; i < count0 + count1; i++)
        arr[i] = 1;
    for (int i = count0 + count1; i < n; i++)
        arr[i] = 2;
}

// optimal approach using dutch flag(3 pointers)
void sortArray(vector<int> &arr, int n)
{
    int low = 0, mid = 0, high = n - 1;
    while (mid <= high)
    {
        if (arr[mid] == 0)
        {
            swap(arr[low], arr[mid]);
            low++;
            mid++;
        }
        else if (arr[mid] == 1)
        {
            mid++;
        }
        else
        {
            swap(arr[mid], arr[high]);
            high--;
        }
    }
}

int main()
{
    int n;
    cin >> n;
    // int arr[n];
    vector<int> arr(n);         // sc : O(1)
    for (int i = 0; i < n; i++) // tc : O(N)
    {
        cin >> arr[i];
    }

    sortArray(arr, n);
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}