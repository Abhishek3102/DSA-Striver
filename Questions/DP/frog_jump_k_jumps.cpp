#include <bits/stdc++.h>
using namespace std;

int f(int index, vector<int> &heights, int k)
{
    if (index == 0)
        return 0;

    int minSteps = INT_MAX;

    for (int j = 1; j <= k; j++)
    {
        if (index - j >= 0)
        {
            int jump = f(index - j) + abs(heights[index] - heights[index - j]);
            minSteps = min(minSteps, jump);
        }
    }
    return minSteps;
}

// memoization
