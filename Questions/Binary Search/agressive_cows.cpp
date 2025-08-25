#include <bits/stdc++.h>
using namespace std;

bool canWePlace(vector<int> &stalls, int distance, int cows)
{
    int n = stalls.size();
    int cntCows = 1, last = stalls[0];

    for (int i = 1; i < n; i++)
    {
        if (stalls[i] - last >= distance)
        {
            cntCows++;
            last = stalls[i];
        }
        if (cntCows >= cows)
            return true;
    }
    return false;
}

int agressiveCows(vector<int> &stalls, int k)
{
    sort(stalls.begin(), stalls.end());
    int n = stalls.size();
    int low = 1, high = stalls[n - 1] - stalls[0];

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (canWePlace(stalls, mid, k) == true)
        {
            low = mid + 1;
        }

        else
        {
            high = mid - 1;
        }
    }

    return high;
}