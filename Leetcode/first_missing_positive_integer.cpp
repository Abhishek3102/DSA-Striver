// needs to be corrected for some test cases

#include <bits/stdc++.h>
using namespace std;

int firstMissingPositive(vector<int> &nums)
{
    int n = nums.size();
    int sumN = 0;
    int sumNotN = 0;
    int maxi = 0;
    int out = 0;

    maxi = *max_element(nums.begin(), nums.end());
    // mini = *min_element(nums.begin(), nums.end());
    int mini = INT_MAX;
    for (int x : nums)
    {
        if (x > 0 && x < mini)
        {
            mini = x;
        }
    }
    if (mini == INT_MAX)
    {
        // No positive number found, handle accordingly
        mini = 1; // for example
    }

    for (int i = 0; i < n; i++)
    {

        if (nums[i] < 0)
            continue;
        sumNotN += nums[i];
        sumN = (maxi * (maxi + 1) / 2) - ((mini - 1) * mini / 2);
        out = sumN - sumNotN;
    }
    return out;
}

int main()
{
    vector<int> nums = {3, 4, -1, 1};
    cout << firstMissingPositive(nums) << "\n";
    return 0;
}
