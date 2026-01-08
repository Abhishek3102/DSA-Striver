/*
  PREVIOUS SMALLER ELEMENT

  This code finds the previous smaller element for each element in an array.

  WHAT IT DOES:
  - For each element, find the first element to its left that is smaller than it
  - If no smaller element exists on the left, return -1
  - Uses stack-based approach for optimal O(n) solution
  - Includes both brute force O(n^2) and optimal O(n) approaches

  INPUT:
  - Array of integers
  - Example: [4, 5, 2, 10, 8]

  OUTPUT:
  - Array where each element is replaced by its previous smaller element
  - Example output: [-1, 4, -1, 2, 2]
  - 4 → -1 (no smaller on left), 5 → 4, 2 → -1, 10 → 2, 8 → 2
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> findPreviousSmallerElement(vector<int> arr)
{
    int n = arr.size();
    vector<int> nse(n, -1);
    for (int i = 0; i < n; i++)
    {
        for (int j = i - 1; j >= 0; j--)
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

// optimal approach
vector<int> findPSEOptimal(vector<int> arr)
{
    int n = arr.size();
    vector<int> nse(n, -1);
    stack<int> st;
    for (int i = 0; i < n; i++)
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
    std::vector<int> arr = {4, 5, 2, 10, 8};
    std::vector<int> result = findPSEOptimal(arr);

    std::cout << "Input Array: ";
    for (int x : arr)
        std::cout << x << " ";
    std::cout << "\nNSE to Left (Brute Force): ";
    for (int x : result)
        std::cout << x << " ";
    std::cout << "\n";

    return 0;
}