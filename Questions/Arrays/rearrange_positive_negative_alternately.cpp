#include <bits/stdc++.h>
using namespace std;

// arrange negative and positive elements alternately
int rearrange_elements(int arr[], int n)
{
    int pos[n];
    int neg[n];
    int pos_count = 0, neg_count = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > 0)
        {
            pos[pos_count++] = arr[i];
        }
        else
        {
            neg[neg_count++] = arr[i];
        }
    }

    for (int i = 0; i < n / 2; i++)
    {
        arr[2 * i] = pos[i];
        arr[2 * i + 1] = neg[i];
    }
    // return arr[n];
}

// vector approach, his code
vector<int> rearrangeArray(vector<int> &nums)
{
    int n = nums.size();
    vector<int> ans(n, 0);
    int posIndex = 0, negIndex = 1;
    for (int i = 0; i < n; i++)
    {
        if (nums[i] < 0)
        {
            ans[negIndex] = nums[i];
            negIndex += 2;
        }
        else
        {
            ans[posIndex] = nums[i];
            posIndex += 2;
        }
    }
    return ans;
}

vector<int> rearrangeArrayPosNotEqualToNeg(vector<int> &a)
{
    vector<int> pos, neg;
    int n = a.size();
    for (int i = 0; i < n; i++)
    {
        if (a[i] > 0)
        {
            pos.push_back(a[i]);
        }
        else
        {
            neg.push_back(a[i]);
        }
    }

    if (pos.size() > neg.size())
    {
        for (int i = 0; i < neg.size(); i++)
        {
            a[2 * i] = pos[i];
            a[2 * i + 1] = neg[i];
        }
        int index = neg.size() * 2;
        for (int i = neg.size(); i < pos.size(); i++)
        {
            a[index] = pos[i];
            index++;
        }
    }

    else
    {
        for (int i = 0; i < pos.size(); i++)
        {
            a[2 * i] = pos[i];
            a[2 * i + 1] = neg[i];
        }
        int index = pos.size() * 2;
        for (int i = pos.size(); i < pos.size(); i++)
        {
            a[index] = neg[i];
            index++;
        }
    }
    return a;
}

int main()
{
    /*
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    if (rearrange_elements(arr, n) == 0)
    {
        // Output the rearranged array
        for (int i = 0; i < n; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    */

    // vector<int> nums = {1, 5, 3, -4, -9, -6};
    vector<int> a = {1, 5, 3, -4, -9, -6, 7, 2};

    // Dynamic input for array size and elements
    // int n;
    // cin >> n;

    // // Check if n is even
    // if (n % 2 != 0)
    // {
    //     cout << "Array size must be even!" << endl;
    //     return -1;
    // }

    // vector<int> nums(n);

    // // Input elements
    // for (int i = 0; i < n; i++)
    // {
    //     cin >> nums[i];
    // }

    // Get the rearranged array
    // vector<int> result = rearrangeArray(nums);
    vector<int> result = rearrangeArrayPosNotEqualToNeg(a);

    // Output the rearranged array
    for (int i = 0; i < a.size(); i++)
    {
        cout << result[i] << " ";
    }
    cout << endl;
    return 0;
}