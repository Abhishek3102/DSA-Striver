#include <bits/stdc++.h>
using namespace std;

void printSubsequence(int index, vector<int> &ds, vector<int> &arr, int n)
{
    if (index == n)
    {
        for (auto it : ds)
        {
            cout << it << " ";
        }
        cout << endl;
        return;
    }

    // include the element at index
    ds.push_back(arr[index]);
    printSubsequence(index + 1, ds, arr, n);

    // exclude the element at index
    ds.pop_back();
    printSubsequence(index + 1, ds, arr, n);
}

int main()
{
    vector<int> arr = {1, 2, 3};
    vector<int> ds;
    printSubsequence(0, ds, arr, arr.size());
    return 0;
}