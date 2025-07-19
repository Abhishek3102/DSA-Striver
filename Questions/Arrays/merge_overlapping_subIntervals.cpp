// in this problem, we are given a set of intervals and we need to merge all overlapping intervals
// for eg : (1,3) (2,6) (8,9) (9,11) (8,10) (2,4) (15,18) (16,17) will be merged to (1,6) (8,11) (15,18)

// brute force approach
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> mergeOverlappingIntervals(vector<vector<int>> &arr)
{
    int n = arr.size();
    sort(arr.begin(), arr.end()); // sort the intervals based on the starting point
    vector<vector<int>> ans;
    for (int i = 0; i < n; i++)
    {
        int start = arr[i][0];
        int end = arr[i][1];
        if (!ans.empty() && end <= ans.back()[1])
            continue; // if the current interval is completely inside the last interval in ans, skip it
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j][0] <= end)
            {
                end = max(end, arr[j][1]); // merge the intervals
            }
            else
            {
                break; // no more overlapping intervals
            }
        }
        ans.push_back({start, end}); // add the merged interval to ans
    }
    return ans;
}

// better approach
vector<vector<int>> mergeOverlappingIntervalsBetter(vector<vector<int>> &arr)
{
    int n = arr.size();
    sort(arr.begin(), arr.end()); // sort the intervals based on the starting point
    vector<vector<int>> ans;
    for (int i = 0; i < n; i++)
    {
        if (ans.empty() || arr[i][0] > ans.back()[1])
        {                          // if current interval does not overlap with the last interval in ans}
            ans.push_back(arr[i]); // add the current interval to ans
        }
        else
        {
            ans.back()[1] = max(ans.back()[1], arr[i][1]); // merge the current interval with the last interval in ans.
        }
    }
    return ans;
}