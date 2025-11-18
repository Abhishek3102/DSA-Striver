// same as first problem of nge where traverse all elements of array, here find nge by going ahead in array, if not found ahead
// then traverse in circular manner, that is go back and check if something is greater. if not found in circular manner too, then return -1.
// eg : [ 2, 10, 12, 1, 11] ans = [ 10, 12, -1, 11, 12]

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
