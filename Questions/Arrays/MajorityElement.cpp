// given an array, find element that appears more than n/2 times
// for example, array has 9 elements, so we will be looking for element which appears more than 4 times

#include <bits/stdc++.h>
using namespace std;

// brute force
void find_majority_element(int arr[], int n)
{
    // tc : O(N^2) since for loop inside for loop and both running till n
    // int vis[n] = {0};
    for (int i = 0; i < n; i++)
    {
        int count = 0;
        for (int j = 0; j < n; j++)
        {
            if (arr[i] == arr[j])
                count++;
        }
        if (count > n / 2)
        {
            cout << "Majority Element is : " << arr[i] << endl;
            return;
        }
    }
    cout << "No majority element found." << endl;
}

int find_majority_element_better(vector<int> v)
{
    map<int, int> mpp;
    // Time Complexity: O(N log N) for inserting into the map + O(N) for iterating through the map
    // Overall time complexity: O(N log N)
    // O(N log N) + O(N) which simplifies to O(NlogN)

    for (int i = 0; i < v.size(); i++)
    {
        mpp[v[i]]++; // This increments the count of the element arr[i] in the map 'mpp'.
        // If arr[i] is not already present in the map, it is added with an initial count of 1.
    }

    for (auto it : mpp) // iterating through all values in map
    {
        if (it.second > (v.size() / 2)) // checking if count > n/2
        {
            return it.first; // it.first is the number and it.second is count for that number
        }
    }
    return -1;
}

int find_majority_element_optimal(vector<int> v)
{
    // tc : O(N) + O(N). the second O(N) will only happen if there's a chance of not having a majority element, else that step will nopt happen
    // sc : O(1)
    int count = 0;
    int element;
    for (int i = 0; i < v.size(); i++)
    {
        if (count == 0)
        {
            count = 1;
            element = v[i];
        }

        else if (v[i] == element)
        {
            count++;
        }

        else
        {
            count--;
        }
    }
    int count1 = 0;
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] == element)
            count1++;
    }

    if (count1 > (v.size() / 2))
    {
        return element;
    }
    return -1;
}

int main()
{
    /*
    int n;
    cin >> n;
    int arr[n];                 // sc : O(1)
    for (int i = 0; i < n; i++) // tc : O(N)
    {
        cin >> arr[i];
    }

    find_majority_element(arr, n);
    */

    vector<int> arr;
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    /*
    arr = {2, 2, 1, 2, 2, 3, 2};
    n = arr.size();
    */

    // User input
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        arr.push_back(x);
    }

    int majority = find_majority_element_optimal(arr);

    if (majority != -1)
        cout << "Majority element: " << majority << endl;
    else
        cout << "No majority element found." << endl;

    return 0;
}