#include <iostream>
using namespace std;

int main()
{
    int n;
    // enter num of elements to be included in array
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        // enter value of elements of array
        cin >> arr[i];
    }

    // precompute
    int hash[13] = {0};
    for (int i = 0; i < n; i++)
    {
        hash[arr[i]] += 1;
    }

    int q;
    // enter the amount of number for which query needs to be done
    cin >> q;
    while (q--)
    {
        int number;
        // enter value of numbers for querying
        cin >> number;
        cout << hash[number] << endl;
    }
    return 0;
}