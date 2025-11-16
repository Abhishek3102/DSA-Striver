// in this problem, traverse all elements of array and then return the element which is the next greater element for each of the element.
// if element has greater elements ahead in the array then return that, if not than return -1 for that element.

// eg : [ 6, 0, 8, 1, 3] ans = [ 8, 8, -1, 3, -1]

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
