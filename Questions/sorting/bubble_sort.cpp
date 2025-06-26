#include <bits/stdc++.h>
using namespace std;

void bubb_sort(int arr[], int n)
{
    for (int i = n - 1; i >= 1; i--)
    {
        int didSwap = 0;
        for (int j = 0; j <= i - 1; j++) // here j is going till i-1 bcoz if we went till i instead of i-1
        // then last element would have no next element to compare itself with
        // and it would have given a runtime error bcoz we are trying to access an index which is not present
        {
            if (arr[j] > arr[j + 1])
            {
                int temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
                didSwap = 1;
            }
        }

        // here didSwap variable is introduced to stop the loop if no swaps happened in the previous case.
        // This reduces the original time complexity from O(N^2) to O(N) which is the best t.c. for bubble sort
        cout << didSwap << endl;
        if (didSwap == 0)
        {
            break;
        }
    }
}

int main()
{
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    bubb_sort(arr, n);
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}