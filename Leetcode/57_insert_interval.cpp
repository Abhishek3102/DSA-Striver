// this problem is solved using the : Three-phase logic (line sweep idea)
/*
Example 1:

Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]
Example 2:

Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]
Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].

*/

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> insert(vector<vector<int>> &intervals, vector<int> &newInterval)
{
    vector<vector<int>> result;
    int i = 0;
    int n = intervals.size();

    // Step 1: Add all intervals before newInterval
    while (i < n && intervals[i][1] < newInterval[0])
    {
        result.push_back(intervals[i]);
        i++;
    }

    // Step 2: Merge overlapping intervals with newInterval
    while (i < n && intervals[i][0] <= newInterval[1])
    {
        newInterval[0] = min(newInterval[0], intervals[i][0]);
        newInterval[1] = max(newInterval[1], intervals[i][1]);
        i++;
    }
    result.push_back(newInterval);

    // Step 3: Add remaining intervals
    while (i < n)
    {
        result.push_back(intervals[i]);
        i++;
    }

    return result;
}
