/*
  NEXT SMALLER ELEMENT

  This code finds the next smaller element for each element in an array.

  WHAT IT DOES:
  - For each element, find the first element to its right that is smaller than it
  - If no smaller element exists on the right, return -1
  - Uses stack-based approach for optimal O(n) solution
  - Includes both brute force O(n^2) and optimal O(n) approaches

  INPUT:
  - Array of integers
  - Example: [4, 5, 2, 10, 8]

  OUTPUT:
  - Array where each element is replaced by its next smaller element
  - Example output: [2, 2, -1, 8, -1]
  - 4 → 2, 5 → 2, 2 → -1 (no smaller on right), 10 → 8, 8 → -1
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> findNSEBrute(vector<int> arr)
{
    int n = arr.size();
    vector<int> nse(n, -1);

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[i])
            {
                nse[i] = arr[j];
                break;
            }
        }
    }
    return nse;
}

vector<int> findNSEOptimal(vector<int> arr)
{
    int n = arr.size();
    vector<int> nse(n, -1);
    stack<int> st;

    for (int i = n - 1; i >= 0; i--)
    {
        while (!st.empty() && st.top() >= arr[i])
        {
            st.pop();
        }

        nse[i] = st.empty() ? -1 : st.top();
        st.push(arr[i]);
    }
    return nse;
}

int main()
{
    vector<int> arr = {4, 5, 2, 10, 8};
    vector<int> nse_optimal = findNSEOptimal(arr);
    cout << "Optimal NSE: ";
    for (int i = 0; i < nse_optimal.size(); i++)
    {
        cout << nse_optimal[i] << " ";
    }
    cout << endl;

    return 0;
}