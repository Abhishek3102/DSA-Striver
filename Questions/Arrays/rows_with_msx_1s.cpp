#include <bits/stdc++.h>
using namespace std;

int find_lower_bound_binary(vector<int> arr, int x)
{
    // tc : O (log(n) base 2)
    int n = arr.size();
    int low = 0, high = n - 1;
    int answer = n;
    while (low <= high)
    {
        int mid = (low + high) / 2;

        // maybe an answer. agar iss se chhota nahi mila to ye answer hoga warna iss se chhota waala agar mila to wo answer hoga
        if (arr[mid] >= x)
        {
            answer = mid;

            // look for smaller index on left
            high = mid - 1;
        }
        else
            low = mid + 1; // look in right-side direction
    }
    // if no such answer found then return the size of array.
    // eg :
    // 6 - size of array
    // 15 - x
    // 2 3 7 6 14 12 - elements of array
    // 6 - returned size of array
    return answer;
}

int findMax1(vector<vector<int>> mat, int n, int m)
{
    // Initialize the maximum count of 1s found so far to 0
    int cnt_max = 0;
    // Initialize the index of the row with the most 1s to -1 (meaning not found yet)
    int index = -1;

    // Loop through each row of the matrix
    for (int i = 0; i < n; i++)
    {
        // Use binary search to find the index of the first occurrence of 1 in the current row.
        // Since the row is sorted, all 0s will be before the first 1
        int count_ones = m - find_lower_bound_binary(mat[i], 1);

        // If the current row has more 1s than any previous row
        if (count_ones > cnt_max)
        {
            // Update the maximum count
            cnt_max = count_ones;
            // Update the index of the row with the most 1s
            index = i;
        }
    }

    return index;
}

int main()
{
    vector<vector<int>> mat = {
        {0, 0, 1, 1},
        {0, 0, 0, 1},
        {0, 0, 0, 1}};

    int n = mat.size();
    int m = mat[0].size();

    int result = findMax1(mat, n, m);
    if (result != -1)
        cout << "Row with maximum number of 1s: " << result << endl;
    else
        cout << "No 1s found in the matrix." << endl;

    return 0;
}