#include <bits/stdc++.h>
using namespace std;

list<int> findAsteroidSolution(int arr[], int n)
{
    list<int> st;

    for (int i = 0; i < n; i++)
    {
        // If current asteroid is positive, just push it to the stack
        if (arr[i] > 0)
        {
            st.push_back(arr[i]);
        }
        else
        {
            // Handle collision with stack
            while (!st.empty() && st.back() > 0 && st.back() < abs(arr[i]))
            {
                // Pop the top of the stack if it is a smaller positive asteroid
                st.pop_back();
            }
            if (!st.empty() && st.back() == abs(arr[i]))
            {
                // If the current negative asteroid equals the positive asteroid, pop both
                st.pop_back();
            }
            else if (st.empty() || st.back() < 0)
            {
                // If stack is empty or the top is negative, push the negative asteroid
                st.push_back(arr[i]);
            }
        }
    }

    return st;
}

int main()
{
    int arr[] = {4, 7, 1, 1, 2, -3, -7, 17, 15, -18, -19};
    int n = sizeof(arr) / sizeof(arr[0]);

    list<int> result = findAsteroidSolution(arr, n);

    for (int asteroid : result)
    {
        cout << asteroid << " ";
    }

    return 0;
}
