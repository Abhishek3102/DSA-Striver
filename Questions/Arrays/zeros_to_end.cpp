#include <bits/stdc++.h>
using namespace std;

void zero_to_end(int arr[], int n)
{
    int temp[n];
    // int nonze = temp.size(); this will work for vectors not arrays
    int nonze = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] != 0)
        {
            temp[nonze] = arr[i];
            nonze++;
        }
    }

    for (int i = 0; i < nonze; i++)
    {
        arr[i] = temp[i];
    }

    for (int i = nonze; i < n; i++)
    {
        arr[i] = 0;
    }
}

vector<int> zero_end_vec(int n, vector<int> a)
{

    // step 1
    vector<int> temp;
    for (int i = 0; i < n; i++) // O(N)
    {
        if (a[i] != 0)
        {
            temp.push_back(a[i]);
        }
    }

    // step 2
    int nonZero = temp.size();
    for (int i = 0; i < nonZero; i++) // O(X) if X non-zero nos. are present
    {
        a[i] = temp[i];
    }

    // step 3
    for (int i = nonZero; i < n; i++) // O(N-X) // coz X non zero nos., so n-x zeros
    {
        a[i] = 0;
    }
    return a;

    // Total t.c. : O(N) + O(X) + O(N-X) = O(2N)
    // S.C. : O(N) for n sized array + O(X) for non zero numbers
    // worst case in s.c. : when all numbers in array is non zero, so total tc : O(N) + O(N) = O(2N)
}

void zero_to_end_optimal(int arr[], int n)
{
    // step 1
    int j = -1;
    for (int i = 0; i < n; i++) // O(x) for non zero nos
    {
        if (arr[i] == 0)
        {
            j = i;
            break;
        }
    }

    // if(j == -1) return arr; no non zero nos. present

    // step 2
    for (int i = j + 1; i < n; i++) // remaining array i.e. O(n-x)
    {
        if (arr[i] != 0)
        {
            swap(arr[i], arr[j]);
            j++;
        }
    }

    // Total tc : O(X) + O(N-X) = O(N)
    // s.c. : 0(1) just modifying the given array, nothing extra used
}

int main()
{
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    zero_to_end_optimal(arr, n);
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    return 0;
}