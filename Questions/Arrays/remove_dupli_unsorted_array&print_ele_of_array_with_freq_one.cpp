#include <bits/stdc++.h>
using namespace std;

vector<int> returnUnique(vector<int> &arr)
{
    unordered_map<int, int> mpp;

    // Count frequency of every element
    for (int i = 0; i < arr.size(); i++)
    {
        mpp[arr[i]]++;
    }

    vector<int> uniArr;

    // Add only elements whose frequency is 1
    for (int i = 0; i < arr.size(); i++)
    {
        if (mpp[arr[i]] == 1)
            uniArr.push_back(arr[i]);
    }

    return uniArr;
}

int main()
{
    vector<int> arr = {1, 2, 2, 3, 4, 4, 5};

    vector<int> ans = returnUnique(arr);

    for (int x : ans)
        cout << x << " ";
}

vector<int> removeDuplicates(vector<int> &arr)
{
    unordered_set<int> seen;
    vector<int> ans;

    for (int x : arr)
    {
        if (seen.insert(x).second)
        {
            ans.push_back(x);
        }
    }

    return ans;
}