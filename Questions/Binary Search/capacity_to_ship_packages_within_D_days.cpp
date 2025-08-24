// find least capacity to ship packages within D days
// whatever is the max weight on the ship, the minimum capacity of ship has to be that much and maximum capacity of ship in which all items can be loaded together in one go(one day) is sum of all weights of array.
// so capacity range of ship is (max weight of array, sum of all weights of array)
// so our ans will lie between it.

#include <bits/stdc++.h>
using namespace std;

int funcDaysReq(vector<int> &weight, int capacity)
{
    int n = weight.size();
    // Initialize the number of days, start with 1 (since at least 1 day is required)
    int days = 1, load = 0; // The current load of the ship for the current day

    // Loop through each package
    for (int i = 0; i < n; i++)
    {
        // Check if adding the current package exceeds the current capacity
        if (load + weight[i] > capacity)
        {
            // If it does, we need a new day to ship this package
            days++;           // Increment the number of days, i.e., start counting load for next day
            load = weight[i]; // Start a new day with the current package
        }
        else
        {
            // If it doesn't exceed the capacity, add the current package to the current day's load
            load += weight[i];
        }
    }
    return days;
}

int func(vector<int> &arr, int days)
{
    int n = arr.size();
    int maxi = *max_element(arr.begin(), arr.end()); // Maximum weight of a package

    // built in function for calculating sum of all elements of array, with 0 as the inital value like we do (int sum = 0 and then add values to it)
    int sum = accumulate(arr.begin(), arr.end(), 0); // Sum of all weights

    // Linear search between max weight and sum of weights
    for (int capacity = maxi; capacity <= sum; capacity++)
    {
        int daysReq = funcDaysReq(arr, capacity);

        if (daysReq <= days)
        {
            return capacity; // Found the minimum capacity that works within the required days
        }
    }

    return sum; // This is the maximum capacity required (if no smaller capacity is found)
}

int bsFindCapShip(vector<int> arr, int days)
{
    int n = arr.size();

    int maxi = *max_element(arr.begin(), arr.end());
    int sum = accumulate(arr.begin(), arr.end(), 0);
    int ans = -1;

    int low = maxi, high = sum;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        // The Line int noOfDays = funcDaysReq(arr, mid);
        // Here, mid represents the current capacity being tested during the binary search.
        // mid is not part of the funcDaysReq function itself. It’s the parameter passed from the binary search loop to funcDaysReq.
        // funcDaysReq is a function that takes arr: The list of package weights.
        // capacity (in this case, mid): The maximum weight that the ship can carry in a single day.
        int noOfDays = funcDaysReq(arr, mid);

        // If the number of days required is less than or equal to the allowed days, we can try smaller capacities.
        if (noOfDays <= days)
        {
            ans = mid;
            high = mid - 1; // We reduce the search range, aiming to find a smaller possible capacity.
        }
        else
        {
            low = mid + 1; // If more days are required than allowed, we need a larger capacity.
        }
    }
    return low;
    // return ans;
}

int main()
{
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int D = 5; // Number of days

    int minCapacity = bsFindCapShip(arr, D);
    cout << "Minimum capacity of the ship: " << minCapacity << endl;

    return 0;
}
