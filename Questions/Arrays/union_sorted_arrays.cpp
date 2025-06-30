#include <bits/stdc++.h>
using namespace std;

vector<int> find_union_sorted_arrays(int n1, int n2, vector<int> arr1, vector<int> arr2)
{
    set<int> st;

    // total t.c. for this for loop : O(N1 log n)
    for (int i = 0; i < n1; i++) // O(N1)
    {
        st.insert(arr1[i]); // log n, where n is size of set
    }

    // total t.c. for this for loop : O(N2 log n)
    for (int i = 0; i < n2; i++) // O(N2)
    {
        st.insert(arr2[i]); // log n, where n is size of set
    }

    // O(n1+n2)
    vector<int> union1;
    for (auto it : st)
    {
        union1.push_back(it);
    }
    return union1;
}

vector<int> sortedArray(vector<int> a, vector<int> b)
{
    // t.c : O(N1+N2)
    // S.C : O(N1+N2)

    int n1 = a.size();
    int n2 = b.size();
    int i = 0;
    int j = 0;
    vector<int> unionArr;
    while (i < n1 && j < n2)
    {
        if (a[i] <= b[j])
        {
            if (unionArr.size() == 0 || unionArr.back() != a[i])
            {
                unionArr.push_back(a[i]);
            }
            i++;
        }
        else
        {
            if (unionArr.size() == 0 || unionArr.back() != b[j])
            {
                unionArr.push_back(b[j]);
            }
            j++;
        }
    }

    while (j < n2)
    {
        if (unionArr.size() == 0 || unionArr.back() != b[j])
        {
            unionArr.push_back(b[j]);
        }
        j++;
    }

    while (i < n1)
    {
        if (unionArr.size() == 0 || unionArr.back() != a[i])
        {
            unionArr.push_back(a[i]);
        }
        i++;
    }

    return unionArr;
}

int main()
{
    int n1, n2;
    cin >> n1 >> n2; // Get sizes of both arrays
    vector<int> arr1(n1), arr2(n2);

    // Read the elements of the first array
    for (int i = 0; i < n1; i++)
    {
        cin >> arr1[i];
    }

    // Read the elements of the second array
    for (int i = 0; i < n2; i++)
    {
        cin >> arr2[i];
    }

    // Get the union of both arrays
    vector<int> union_result = sortedArray(arr1, arr2);

    for (int i : union_result)
    {
        cout << i << " ";
    }

    return 0;
}
