// a peak is a number which is greater than its previous and its next number. eg : 5 7 6, so 7 is peak here.
#include <bits/stdc++.h>
using namespace std;

// this returns only one peak
int findPeak(vector<int> arr)
{
    int n = arr.size();
    // these are edge cases, if only one element present or number is first number of array or last.
    if (n == 1)
        return 0;
    if (arr[0] > arr[1])
        return 0; // this is for first number, so no left side for this
    if (arr[n - 1] > arr[n - 2])
        return n - 1; // this is the last number so no right side for this

    int low = 1, high = n - 2;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] > arr[mid - 1] && arr[mid] > arr[mid + 1])
            return mid;

        else if (arr[mid] > arr[mid - 1])
            low = mid + 1;

        else if (arr[mid] > arr[mid + 1])
            high = mid - 1;

        // this line works when above lines fail.
        // eg : 1 5 1 2 1 -> here mid is not greater than left side nor right side but we still have a peak so we go towards either left or right side.
        else
            low = mid + 1;
        // or  high = mid - 1;
    }
    return -1;
}

int main()
{
    vector<int> arr = {1, 3, 7, 9, 4};
    cout << findPeak(arr);
    return 0;
}