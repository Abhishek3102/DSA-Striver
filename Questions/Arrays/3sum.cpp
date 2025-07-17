// here given an array we need to find all the triplets that sum to zero

#include <bits/stdc++.h>
using namespace std;

// brute force approach
vector<vector<int>> triplet(int n, vector<int> &num)
{
    // tc : O(N^3) + log(no. of unique triplets) and sc : 2 * O(no. of triplets)

    set<vector<int>> st;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            for (int k = j + 1; k < n; k++)
            {
                // here we are checking if the sum of num[i] + num[j] + num[k] == 0
                if (num[i] + num[j] + num[k] == 0)
                {
                    vector<int> temp = {num[i], num[j], num[k]};
                    sort(temp.begin(), temp.end());
                    st.insert(temp);
                }
            }
        }
    }
    vector<vector<int>> ans(st.begin(), st.end());
    return ans;
}

// better approach
// in last approach we are using 3 loops, we can reduce it to 2 loops
// there it was num[i] + num[j] + num[k] == 0, so here, num[k] = -(num[i] + num[j])
vector<vector<int>> triplet_2(int n, vector<int> &num)
{
    // tc : O(N^2) * log(size of set) and sc : 2 * O(no. of triplets) + O(N)
    set<vector<int>> st;
    for (int i = 0; i < n; i++)
    {
        set<int> hashset;
        for (int j = i + 1; j < n; j++)
        {
            int third = -(num[i] + num[j]);
            if (hashset.find(third) != hashset.end())
            {
                vector<int> temp = {num[i], num[j], third};
                sort(temp.begin(), temp.end());
                st.insert(temp);
            }
            hashset.insert(num[j]);
        }
    }
    vector<vector<int>> ans(st.begin(), st.end());
    return ans;
}

// optimal approach
// here we will sort the array and then use 2 pointers approach
vector<vector<int>> triplet(int n, vector<int> &num)
{
    vector<vector<int>> ans;
    sort(num.begin(), num.end());
    for (int i = 0; i < n; i++)
    {
        if (i > 0 && num[i] == num[i - 1])
            continue; // skip duplicates for the first element
        int j = i + 1, k = n - 1;
        while (j < k)
        {
            int sum = num[i] + num[j] + num[k];
            if (sum < 0)
            {
                j++;
            }
            else if (sum > 0)
            {
                k--;
            }
            else
            {
                vector<int> temp = {num[i], num[j], num[k]};
                ans.push_back(temp);
                j++;
                k--;
                while (j < k && num[j] == num[j - 1])
                    j++;
                while (j < k && num[k] == num[k + 1])
                    k--;
            }
        }
    }
    return ans;
}
