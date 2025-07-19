#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> quadruplets(int n, vector<int> &num)
{
    set<vector<int>> st;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            for (int k = j + 1; k < n; k++)
            {
                for (int l = k + 1; l < n; l++)
                {
                    // here we are checking if the sum of num[i] + num[j] + num[k] + num[l] == 0
                    if (num[i] + num[j] + num[k] + num[l] == 0)
                    {
                        vector<int> temp = {num[i], num[j], num[k], num[l]};
                        sort(temp.begin(), temp.end());
                        st.insert(temp);
                    }
                }
            }
        }
    }
    vector<vector<int>> ans(st.begin(), st.end());
    return ans;
}

// better approach
// in last approach we are using 4 loops, we can reduce it to 3 loops
vector<vector<int>> fourSum(vector<int> &nums, int target)
{
    // total tc : O(N^3 * log(size of set)) and sc : 2 * O(no. of quadruplets) + O(N)
    int n = nums.size();
    set<vector<int>> st;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            set<long long> hashset;
            for (int k = j + 1; j < n; j++)
            {
                long long fourth = target - nums[i] - nums[j] - nums[k];
                // this is to check if fourth is present in hashset
                if (hashset.find(fourth) != hashset.end())
                {
                    vector<int> temp = {nums[i], nums[j], nums[k], (int)fourth};
                    sort(temp.begin(), temp.end());
                    st.insert(temp);
                }
                // nums[k] is inserted into hashset so that, in subsequent iterations, you can quickly check if the required fourth number
                // to complete the quadruplet has already been seen. This is a common technique for reducing nested loops using hashing
                hashset.insert(nums[k]);
            }
        }
    }
    vector<vector<int>> ans(st.begin(), st.end());
    return ans;
}

// optimal approachthis is similar to 3 sum problem
vector<vector<int>> fourSumOptimal(vector<int> &nums, int target)
{
    int n = nums.size();
    vector<vector<int>> ans;
    sort(nums.begin(), nums.end()); // sorting the array to use two pointers approach
    for (int i = 0; i < n; i++)
    {
        if (i > 0 && nums[i] == nums[i - 1])
            continue; // to avoid duplicates
        for (int j = i + 1; j < n; j++)
        {
            if (j != (i + 1) && nums[j] == nums[j - 1])
                continue; // to avoid duplicates
            int k = j + 1, l = n - 1;
            while (k < l)
            {
                long long sum = nums[i];
                // elements at indices j, k, and l are added to the sum in this way, so that integer overflow does not happen
                sum += nums[j];
                sum += nums[k];
                sum += nums[l];
                if (sum == target)
                {
                    vector<int> temp = {nums[i], nums[j], nums[k], nums[l]};
                    ans.push_back(temp);
                    k++;
                    l--;
                    // this is to skip duplicates in the current iteration
                    // to avoid duplicates
                    while (k < l && nums[k] == nums[k - 1])
                        k++;
                    while (k < l && nums[l] == nums[l + 1])
                        l--;
                    k++;
                    l--;
                }
                else if (sum < target)
                    k++;
                else
                    l--;
            }
        }
    }
    return ans;
}

int main()
{
    int n;
    cout << "Enter number of elements: ";
    cin >> n;
    /*
        Enter number of elements: 6
        Enter 6 integers: 1 0 -1 0 2 -2

        ans : Quadruplets with sum 0 are:
        -2 -1 1 2
        -2 0 0 2
        -1 0 0 1

    */

    vector<int> num(n);
    cout << "Enter " << n << " integers: ";
    for (int i = 0; i < n; ++i)
    {
        cin >> num[i];
    }

    vector<vector<int>> result = quadruplets(n, num);

    cout << "Quadruplets with sum 0 are:\n";
    for (const auto &quad : result)
    {
        for (int val : quad)
        {
            cout << val << " ";
        }
        cout << "\n";
    }

    return 0;
}
