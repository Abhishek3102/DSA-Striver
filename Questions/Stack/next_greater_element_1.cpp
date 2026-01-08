/*
  NEXT GREATER ELEMENT - I
  
  This code finds the next greater element for each element in an array.
  
  WHAT IT DOES:
  - For each element, find the first element to its right that is greater than it
  - If no greater element exists on the right, return -1
  - Uses stack-based approach for optimal O(n) solution
  - Includes both brute force O(n^2) and optimal O(n) approaches
  
  INPUT:
  - Array of integers
  - Example: [6, 0, 8, 1, 3]
  
  OUTPUT:
  - Array where each element is replaced by its next greater element
  - Example output: [8, 8, -1, 3, -1]
  - 6 → 8 (next greater to right), 0 → 8, 8 → -1 (no greater on right), 1 → 3, 3 → -1
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> findNextGreaterElement(vector<int> arr)
{
    int n = arr.size();
    vector<int> nge(n, -1); // Initialize nge vector with -1

    for (int i = 0; i < n - 1; i++)
    {
        // Fix the loop condition, use "j < n" to avoid infinite loop
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] > arr[i])
            {
                nge[i] = arr[j];
                break; // Exit inner loop once the next greater element is found
            }
        }
    }
    return nge;
}

// optimal way
list<int> findNGE(vector<int> arr)
{
    int n = arr.size();
    vector<int> nge(n);
    list<int> st;

    for (int i = n - 1; i >= 0; i--)
    {
        while (!st.empty() && st.back() <= arr[i])
        {
            st.pop_back();
        }

        if (st.empty())
            nge[i] = -1;
        else
            nge[i] = st.back();

        st.push_back(arr[i]);
    }

    return list<int>(nge.begin(), nge.end());
}

int main()
{
    vector<int> arr = {6, 0, 8, 1, 3};
    vector<int> result = findNextGreaterElement(arr); // Store the result

    for (int i = 0; i < result.size(); i++)
    {
        cout << result[i] << " "; // Print the result
    }
    cout << endl;
    return 0;
}
