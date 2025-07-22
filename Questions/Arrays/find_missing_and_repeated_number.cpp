// in this problem, given an array of integers from 1 to n, find missing and repeated numbers in array

#include <bits/stdc++.h>
using namespace std;

// brute force approach
vector<int> find_missing_and_repeated(vector<int> &arr)
{
    int n = arr.size();
    int repeated = -1, missing = -1;
    for (int i = 1; i <= n; i++)
    {
        int count = 0;
        for (int j = 0; j < n; j++)
        {
            if (arr[j] == i)
                count++;
        }
        if (count == 2)
            repeated = i;
        else if (count == 0)
            missing = i;
        if (repeated != -1 && missing != -1)
        {
            break;
        }
    }
    return {repeated, missing};
}

// better approach using hash array, here tc : O(n) + O(n) = O(2n) and sc : O(n) for storing elements in hash array
vector<int> find_missing_and_repeated_better(vector<int> arr)
{
    int n = arr.size();
    int hash[n + 1] = {0}; // created a hash array of size n+1(where n is size of given array) and initialized all values of array to zero.
    for (int i = 0; i < n; i++)
    {
        hash[arr[i]]++; // increasing the count of numbers in array (eg : if 7 is found twice in array, then count starts from zero and incremented till 2)
    }

    int repeating = -1, missing = -1;
    // TODO : why above condition till n-1 and here n
    for (int i = 1; i <= n; i++)
    {
        if (hash[i] == 2)
            repeating = i;
        else if (hash[i] == 0)
            missing = i;

        if (repeating != -1 && missing != -1)
        {
            break;
        }
    }
    return {repeating, missing};
}

// optimal solution includes 2 approaches, one using basic maths and other using XOR(which is termed as hard here)
// in maths approach, we will create two equations. first by adding all the numbers of given array and subtracting it with sum of n numbers.
// here we will consider x and y, x is the repeated number and y is the missing one. so first eqn is created.
// then for second eqn., we all add squares of all numbers of given array and subtract it with squares of numbers till n. this will give us second eqn.
// solving both, will give value of x and y which is what we want.

vector<int> find_missing_and_repeated_optimal_maths(vector<int> arr)
{
    // here tc : O(n) and sc : O(1)
    long long n = arr.size();
    // S - Sn = x - y
    // S2 - S2n = x^2 - y^2 = (x+y)(x-y)

    long long Sn = (n * (n + 1)) / 2;
    long long S2n = (n * (n + 1) * (2 * n + 1)) / 6;
    long long S = 0, S2 = 0;

    for (int i = 0; i < n; i++)
    {
        S += arr[i];                                 // sum of all elements of given array
        S2 += (long long)arr[i] * (long long)arr[i]; // sum of squares of all numbers given in array
    }

    long long val1 = S - Sn; // x - y
    long long val2 = S2 - S2n;
    val2 = val2 / val1; // x + y
    long long x = (val1 + val2) / 2;
    long long y = x - val1;
    return {(int)x, (int)y};
}

vector<int> find_missing_and_repeated_optimal_xor(vector<int> arr)
{
    long long n = arr.size();
    int xr = 0;
    for (int i = 0; i < n; i++)
    {
        xr = xr ^ arr[i];
        xr = xr ^ (i + 1);
    }

    int bitNo = 0;
    while (1)
    {
        if ((xr & (1 << bitNo)) != 0)
        {
            break;
        }
        bitNo++;
    }

    // int number = xr & ~(xr - 1); this is an alternative for above while loop
    int zero = 0;
    int one = 0;
    for (int i = 0; i < n; i++)
    {
        // part of 1 club, i.e., number ka sabse pehla digit 1 hai in terms of bits. eg : 4 is written as 1 0 0
        if ((arr[i] & (1 << bitNo)) != 0)
        {
            one = one ^ arr[i];
        }

        // part of 0 club, i.e., number ka sabse pehla digit 0 hai in terms of bits. eg : 3 is written as 0 1 1
        else
        {
            zero = zero ^ arr[i];
        }
    }

    for (int i = 1; i <= n; i++)
    {
        // part of 1 club
        if ((i & (1 << bitNo)) != 0)
        {
            one = one ^ i;
        }

        // part of zero club
        else
        {
            zero = zero ^ i;
        }
    }

    int count = 0;
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == zero)
            count++;
    }

    if (count == 2)
        return {zero, one};
    return {one, zero};
}

int main()
{
    vector<int> arr = {1, 2, 2, 4, 5};
    vector<int> result = find_missing_and_repeated(arr);
    cout << "Repeated: " << result[0] << ", Missing: " << result[1] << endl;
    return 0;
}
