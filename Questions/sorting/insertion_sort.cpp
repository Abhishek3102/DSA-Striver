#include <bits/stdc++.h>
using namespace std;

void inser_sort(int arr[], int n)
{
    // best t.c. -> O(N) already sorted array
    // avg, worst t.c. -> O(N^2)
    for (int i = 0; i < n; i++)
    {
        int swaps = 0;
        int j = i;
        while (j > 0 && arr[j - 1] > arr[j])
        {
            int temp = arr[j - 1];
            arr[j - 1] = arr[j];
            arr[j] = temp;
            j--;
            swaps++;
        }
        cout << swaps << endl;
    }
}

int main()
{
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    inser_sort(arr, n);
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}

/*

Initial Array: 46 13 24 9 20 52
i = 0 (46)

    Already the first element → no swaps
    ✅ swaps = 0

i = 1 (13)

    Compare with 46 → swap → [13, 46, 24, 9, 20, 52]
    ✅ swaps = 1

i = 2 (24)

    Compare with 46 → swap

    Compare with 13 → no swap
    → [13, 24, 46, 9, 20, 52]
    ✅ swaps = 1

i = 3 (9)

    9 < 46 → swap

    9 < 24 → swap

    9 < 13 → swap
    → [9, 13, 24, 46, 20, 52]
    ✅ swaps = 3

i = 4 (20)

    20 < 46 → swap

    20 < 24 → swap

    20 > 13 → stop
    → [9, 13, 20, 24, 46, 52]
    ✅ swaps = 2

i = 5 (52)

    Already in correct position
    ✅ swaps = 0

Final Output:

0
1
1
3
2
0
9 13 20 24 46 52

*/