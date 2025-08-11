// same code as lower bound. here we just have to insert the given element where lower bound index is found.

#include <bits/stdc++.h>
using namespace std;

int find_search_position(vector<int> arr, int x)
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
    return answer;
}