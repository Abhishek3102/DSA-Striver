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