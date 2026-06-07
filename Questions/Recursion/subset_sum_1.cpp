// Given a list(Arr) of $N$ integers, print sums of all subsets in it. Output should be printed in increasing order of sums.
// Example 1:
// Input:
// N = 2
// text{Arr} = [2, 3]$
// Output:
// 0 2 3 5
// Explanation:
// When no elements is taken then $\text{Sum} = 0$.
// When only 2 is taken then $\text{Sum} = 2$.
// When only 3 is taken then $\text{Sum} = 3$.
// When element 2 and 3 are taken then
// {Sum} = 2+3 = 5.

#include <bits/stdc++.h>
using namespace std;

void findSubsetSum1(int index, int sum, vector<int> &arr, int N, vector<int> &sumSubset)
{
    if (index == N)
    {
        sumSubset.push_back(sum);
        return;
    }

    // pick the element
    findSubsetSum1(index + 1, sum + arr[index], arr, N, sumSubset);

    // don't pick the element
    findSubsetSum1(index + 1, sum, arr, N, sumSubset);
}

vector<int> subsetSum1(vector<int> arr, int N)
{
    vector<int> sumSubset;
    findSubsetSum1(0, 0, arr, N, sumSubset);
    sort(sumSubset.begin(), sumSubset.end());
    return sumSubset;
}

int main()
{
    int N = 2;
    vector<int> arr = {2, 3};

    vector<int> result = subsetSum1(arr, N);

    for (int sum : result)
    {
        cout << sum << " ";
    }
    cout << endl;

    return 0;
}