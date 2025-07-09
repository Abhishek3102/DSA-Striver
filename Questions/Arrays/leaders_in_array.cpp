#include <bits/stdc++.h>
using namespace std;

// leader means a number which is greater than all numbers on its right side in an array
list<int> find_leader(int arr[], int n)
{
    list<int> ans;
    for (int i = 0; i < n; i++)
    {
        bool leader = true;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] > arr[i])
            {
                leader = false;
                break;
            }
        }
        if (leader == true)
            ans.push_back(arr[i]);
    }
    return ans;
}

vector<int> find_leaders_optimal(vector<int> &a)
{
    // O(N)
    vector<int> ans;
    int maxi = INT_MIN;
    int n = a.size();

    // O(N)
    for (int i = n - 1; i >= 0; i--)
    {
        if (a[i] > maxi)
        {
            ans.push_back(a[i]);
        }

        // keeps track of right maximum
        maxi = max(maxi, a[i]);
    }

    // O(N log N)
    sort(ans.begin(), ans.end());
    return ans;
}

int main()
{
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    list<int> leaders = find_leader(arr, n);
    for (int leader : leaders)
    {
        cout << leader << " ";
    }
    cout << endl;

    return 0;
}