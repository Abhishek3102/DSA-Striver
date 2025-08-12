#include <bits/stdc++.h>
using namespace std;

int find_first_occurrence_using_plain_binary(vector<int> arr, int x)
{
    int n = arr.size();
    int low = 0, high = n - 1;
    int first = -1;
    while (low <= high)
    {
        int mid = (low + high) / 2;

        if (arr[mid] == x)
        {
            first = mid;
            high = mid - 1; // Look for earlier occurrences on the left side
        }

        else if (arr[mid] < x)
        {
            low = mid + 1; // Move to the right part
        }

        else
            high = mid - 1; // Move to the left part
    }
    return first;
}

int find_last_occurrence_using_plain_binary(vector<int> arr, int x)
{
    int n = arr.size();
    int low = 0, high = n - 1;
    int last = -1;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        if (arr[mid] == x)
        {
            last = mid;
            low = mid + 1; // Look for later occurrences on the right side
        }

        else if (arr[mid] < x)
        {
            low = mid + 1; // Move to the right part
        }

        else
            high = mid - 1; // Move to the left part
    }
    return last;
}

pair<int, int> firstAndLastPosition(vector<int> arr, int x)
{
    int first = find_first_occurrence_using_plain_binary(arr, x);
    if (first == -1)
        return {-1, -1}; // If element x is not found, return {-1, -1}
    int last = find_last_occurrence_using_plain_binary(arr, x);
    return {first, last};
}

int count(vector<int> arr, int x)
{

    /*

    Enter the size of the array: 9
    Enter the elements of the array (sorted in non-decreasing order): 3 6 8 8 8 11 12 14 19
    Enter the number to find occurrences of: 8
    First occurrence of 8 is at index: 2
    Last occurrence of 8 is at index: 4
    Total occurrences of 8: 3

    */

    int n = arr.size();
    pair<int, int> answer = firstAndLastPosition(arr, x);
    if (answer.first == -1)
        return 0;                            // If x is not found, return 0
    return answer.second - answer.first + 1; // Calculate the count of x by the difference of indices + 1
}

int main()
{
    int n, x;

    // Input the size of the array
    cout << "Enter the size of the array: ";
    cin >> n;

    // Input the elements of the array
    vector<int> arr(n);
    cout << "Enter the elements of the array (sorted in non-decreasing order): ";
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
    }

    // Input the number x whose occurrences need to be counted
    cout << "Enter the number to find occurrences of: ";
    cin >> x;

    // Find the first and last position of x
    pair<int, int> positions = firstAndLastPosition(arr, x);
    if (positions.first == -1)
    {
        cout << "Element " << x << " not found in the array." << endl;
    }
    else
    {
        cout << "First occurrence of " << x << " is at index: " << positions.first << endl;
        cout << "Last occurrence of " << x << " is at index: " << positions.second << endl;

        // Calculate and output the total count of x in the array
        int occurrence_count = count(arr, x);
        cout << "Total occurrences of " << x << ": " << occurrence_count << endl;
    }

    return 0;
}