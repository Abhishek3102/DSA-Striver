#include <iostream>
using namespace std;

int findNumOfOccurr(int number, int arr[], int n)
{
    // here for finding count for every number, N steps is performed so t.c. is O(N)
    // when number of numbers becomes very large, for eg, Q, then t.c. would be O(Q * N)

    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == number)
            count += 1;
    }
    return count;
}

int main()
{
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    cout << findNumOfOccurr(4, arr, n);
}