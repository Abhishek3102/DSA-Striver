/*
  NEXT GREATER ELEMENT - II (CIRCULAR ARRAY)
  
  This code finds the next greater element in a circular array.
  
  WHAT IT DOES:
  - Same as NGE-I but array is treated as circular (wraps around)
  - For each element, find first element greater than it in circular manner
  - First searches forward, then wraps around to beginning if not found
  - Uses stack-based approach with 2*n iterations for circular traversal
  
  INPUT:
  - Array of integers treated as circular
  - Example: [2, 10, 12, 1, 11]
  
  OUTPUT:
  - Array where each element is replaced by its next greater element (circular)
  - Example output: [10, 12, -1, 11, 12]
  - 2 → 10, 10 → 12, 12 → -1, 1 → 11, 11 → 12 (wraps around)
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> findNextGreaterElement(vector<int> arr)
{
    int n = arr.size();
    vector<int> nge(n, -1);

    for (int i = 0; i < n; i++)
    {
        bool found = false;

        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] > arr[i])
            {
                nge[i] = arr[j];
                found = true;
                break;
            }
        }

        if (!found)
        {
            for (int j = 0; j < i; j++)
            {
                if (arr[j] > arr[i])
                {
                    nge[i] = arr[j];
                    break;
                }
            }
        }
    }

    return nge;
}

vector<int> findNGE_Optimal(const vector<int> &arr)
{
    int n = arr.size();
    vector<int> nge(n, -1);
    stack<int> st;

    for (int i = 0; i < 2 * n; i++)
    {
        int currentIndex = i % n;
        while (!st.empty() && arr[st.top()] < arr[currentIndex])
        {
            nge[st.top()] = arr[currentIndex];
            st.pop();
        }
        if (i < n)
        {
            st.push(currentIndex);
        }
    }

    return nge;
}

int main()
{
    vector<int> arr = {2, 10, 12, 1, 11};
    vector<int> result = findNextGreaterElement(arr);

    for (int num : result)
    {
        cout << num << " ";
    }
    return 0;
}
