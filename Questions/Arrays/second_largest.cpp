#include <bits/stdc++.h>
#include <climits>
using namespace std;

int sec_large_brute()
{
    // t.c. here is O(N log N + N) bcoz N log N for sorting and +N for traversing the whole array for finding sec_largest_element

    int n;
    cin >> n;
    int arr[n];

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    // O(N log N): Sorting the array in ascending order
    sort(arr, arr + n);

    // O(1): Accessing the largest element (last element after sorting)
    int largest = arr[n - 1];
    // O(1): Initializing second largest to an invalid value
    int sec_largest = -1;

    // O(N): Traversing the array from the second last element to find the second largest distinct element
    for (int i = n - 2; i >= 0; i--)
    {
        if (arr[i] != largest)
        {
            sec_largest = arr[i];
            break;
        }
    }
    // O(1): Printing the largest element
    cout << largest << endl;
    // O(1): Returning the second largest element
    return sec_largest;
}

int sec_lar_better()
{
    // here t.c is O(N + N) = O(2N) because:
    // - For finding largest, it is O(N)
    // - For finding sec_largest, it is O(N)
    // So the overall time complexity is O(N)
    int n;
    cin >> n;
    int arr[n];
    // O(N): Reading the array input
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    // O(N): Finding the largest element by traversing the array once
    int largest = arr[0];
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > largest)
            largest = arr[i];
    }
    int sec_largest = -1;
    // O(N): Traversing the array again to find the second largest element
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > sec_largest && arr[i] != largest)
        {
            sec_largest = arr[i];
        }
    }
    cout << "Largest value is: " << largest << endl;
    return sec_largest;
}

int secondLargest(vector<int> &arr, int n)
{
    // Time complexity: O(N), as we loop through the array once to find the second largest element.
    int largest = arr[0]; // O(1) initialization of largest value.
    int slargest = -1;    // O(1) initialization of second largest value.

    // Time complexity: O(N) for the loop, as it checks each element once.
    for (int i = 1; i < n; i++) // O(N) loop
    {
        if (arr[i] > largest) // O(1) comparison
        {
            slargest = largest; // O(1) assignment
            largest = arr[i];   // O(1) assignment
        }
        else if (arr[i] < largest && arr[i] > slargest) // O(1) comparison
        {
            slargest = arr[i]; // O(1) assignment
        }
    }
    return slargest; // O(1) return
}

int secondSmallest(vector<int> &arr, int n)
{
    // Time complexity: O(N), as we loop through the array once to find the second smallest element.
    int smallest = arr[0];   // O(1) initialization of smallest value.
    int ssmallest = INT_MAX; // O(1) initialization of second smallest value.

    // Time complexity: O(N) for the loop, as it checks each element once.
    for (int i = 1; i < n; i++) // O(N) loop
    {
        if (arr[i] < smallest) // O(1) comparison
        {
            ssmallest = smallest; // O(1) assignment
            smallest = arr[i];    // O(1) assignment
        }
        else if (arr[i] != smallest && arr[i] < ssmallest) // O(1) comparison
        {
            ssmallest = arr[i]; // O(1) assignment
        }
    }
    return ssmallest; // O(1) return
}

vector<int> optimalSecLarSecSmall(int n, vector<int> arr)
{
    // Time complexity: O(N) for finding second largest element.
    int slargest = secondLargest(arr, n); // O(N)

    // Time complexity: O(N) for finding second smallest element.
    int ssmallest = secondSmallest(arr, n); // O(N)

    // Space complexity: O(1) for creating a result vector and returning it.
    return {slargest, ssmallest}; // O(1) return
}

int main()
{
    int n;    // O(1) initialization of the variable n.
    cin >> n; // O(1) input for the size of the array.

    // Space complexity: O(N) for storing the array of size n.
    vector<int> arr(n); // O(N) space allocation for the vector.

    // Time complexity: O(N) for reading the array elements.
    for (int i = 0; i < n; i++) // O(N) loop
    {
        cin >> arr[i]; // O(1) input for each element.
    }

    // Time complexity: O(N) for calling optimalSecLarSecSmall, which internally calls two O(N) functions.
    vector<int> result = optimalSecLarSecSmall(n, arr); // O(N) due to secondLargest and secondSmallest.

    // Time complexity: O(1) for printing the second largest and second smallest elements.
    cout << "Second Largest: " << result[0] << endl;  // O(1)
    cout << "Second Smallest: " << result[1] << endl; // O(1)

    return 0; // O(1) return statement.
}