#include <bits/stdc++.h>
using namespace std;

// brute force approach, tc : O(N^2)
int count_reverse_pairs(vector<int> arr)
{
    int n = arr.size();
    int count_brute = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] > 2 * arr[j])
                count_brute++;
        }
    }
    return count_brute;
}

// better approach (similar to count pairs(count inversion in array), using merge sort)

int main()
{
    vector<int> arr = {40, 25, 19, 9, 6, 2};
    int result = count_reverse_pairs(arr);
    cout << result << endl;
}