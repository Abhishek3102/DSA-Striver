#include <bits/stdc++.h>
using namespace std;

// Linear search to check if a given element exists in the array
bool linearSearch(int arr[], int n, int x)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == x)
            return true;
    }
    return false;
}

/*
pair<int, vector<int>> find_lcs(int arr[], int n)
{
    int longest = 1;
    vector<int> longestSeq;  // This will store the longest subsequence

    for (int i = 0; i < n; i++)
    {
        int x = arr[i];
        int count = 1;
        vector<int> currentSeq = {x};  // This will store the current subsequence

        // Start looking for a consecutive subsequence
        while (linearSearch(arr, n, x + 1))
        {
            x = x + 1;
            count++;
            currentSeq.push_back(x);  // Add the next number to the subsequence
        }

        // If the current subsequence is longer, update the longest subsequence
        if (count > longest)
        {
            longest = count;
            longestSeq = currentSeq;
        }
    }

    return {longest, longestSeq};  // Return the length and the subsequence
}
*/

int find_lcs(int arr[], int n)
{
    int longest = 1;

    for (int i = 0; i < n; i++)
    {
        int x = arr[i];
        int count = 1;

        while (linearSearch(arr, n, x + 1))
        {
            x = x + 1;
            count++;
        }

        longest = max(longest, count);
    }

    return longest;
}

int find_lcs_better(vector<int> &nums)
{
    if (nums.size() == 0)
        return 0;
    sort(nums.begin(), nums.end());
    int n = nums.size();
    int lastSmaller = INT_MIN;
    int currentCount = 0;
    int longest = 1;
    for (int i = 0; i < n; i++)
    {
        if (nums[i] - 1 == lastSmaller)
        {
            currentCount += 1;
            lastSmaller = nums[i];
        }
        else if (lastSmaller != nums[i])
        {
            currentCount = 1;
            lastSmaller = nums[i];
        }
        longest = max(longest, currentCount);
    }
    return longest;
}

int find_lcs_optimal(vector<int> &a)
{
    int n = a.size();
    if (n == 0)
        return 0;
    int longest = 1;
    unordered_set<int> st;
    for (int i = 0; i < n; i++)
    {
        st.insert(a[i]);
    }

    for (auto it : st)
    {
        if (st.find(it - 1) == st.end())
        {
            int count = 1;
            int x = it;
            while (st.find(x + 1) != st.end())
            {
                x = x + 1;
                count += 1;
            }
            longest = max(longest, count);
        }
    }
    return longest;
}

int main()
{
    int arr[] = {1, 4, 3, 3, 2, 103, 100, 101, 101};
    int n = sizeof(arr) / sizeof(arr[0]);
    cout << "Length of Longest Consecutive Subsequence is: " << find_lcs(arr, n) << endl;
    return 0;

    // vector<int> nums = {100, 4, 200, 1, 3, 2};

    // Find and output the length of the longest consecutive subsequence
    // cout << "Length of Longest Consecutive Subsequence is: " << find_lcs_better(nums) << endl;

    // return 0;
}
