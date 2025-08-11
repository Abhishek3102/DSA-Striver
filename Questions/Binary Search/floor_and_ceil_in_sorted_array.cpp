// floor means largest no. in array which is <= x
// ceil means smallest no. in array which is >= x.

#include <bits/stdc++.h>
using namespace std;

int floor(vector<int> arr, int x)
{
    int n = arr.size();
    int answer = -1;
    int low = 0, high = n - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (arr[mid] <= mid)
        {
            answer = arr[mid];
            low = mid + 1;
        }
        else
            high = mid - 1;
    }
}

int main()
{
    return 0;
}