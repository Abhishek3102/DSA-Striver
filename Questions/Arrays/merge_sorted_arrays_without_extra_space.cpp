#include <bits/stdc++.h>
using namespace std;

// brute force approach where tc : O(n+m)(for storing all elements in arr3) + O(n+m)(for merging the two arrays) = O(n+m)
// sc : O(n+m) for storing the merged elements in arr3
void merge(long long arr1[], long long arr2[], int n, int m)
{
    long long arr3[n + m];
    int left = 0;
    int right = 0;
    int index = 0;

    // merge the two sorted arrays into arr3
    while (left < n && right < m)
    {
        // compare the elements of both arrays and add the smaller one to arr3
        // increment the index of the array from which the element was taken
        if (arr1[left] <= arr2[right])
        {
            arr3[index] = arr1[left];
            left++, index++;
        }
        else
        {
            // if the element in arr2 is smaller, add it to arr3
            // increment the index of arr2
            arr3[index] = arr2[right];
            right++, index++;
        }
    }

    // if there are remaining elements in arr1, add them to arr3
    while (left < n)
    {
        arr3[index] = arr1[left++];
    }

    // if there are remaining elements in arr2, add them to arr3
    while (right < m)
    {
        arr3[index] = arr2[right++];
    }

    for (int i = 0; i < n + m; i++)
    {
        if (i < n)
            arr1[i] = arr3[i]; // this line is important as it fills the first array with the merged elements
        else
            arr2[i - n] = arr3[i]; // this line is important as it fills the second array with the remaining elements
    }
}

// optiml approach 1 where tc : O(min(n+m)) + O(n log n) + O(m log m) = O(nlogn + mlogm)
// sc : O(1) as we are not using any extra space
void mergeOptimal1(long long arr1[], long long arr2[], int n, int m)
{
    int left = n - 1; // last index of arr1
    int right = 0;    // first index of arr2

    // we will swap elements from arr1 and arr2 until we find the correct position for the elements in arr1
    // we will do this by comparing the last element of arr1 with the first element of arr2
    // if the last element of arr1 is greater than the first element of arr2,
    // we will swap them and move the pointers accordingly
    // we will continue this process until we reach the end of arr1 or the end of arr2
    // this way we will ensure that both arrays are sorted and we will not use any extra space
    // this is a two pointer approach
    while (left >= 0 && right < m)
    {
        if (arr1[left] > arr2[right])
        {
            swap(arr1[left], arr2[right]);
            left--, right++;
        }

        else
        {
            break; // if the current element in arr1 is less than or equal to the current element in arr2, we can stop as both arrays are sorted
        }
    }

    sort(arr1, arr1 + n); // sort arr1
    sort(arr2, arr2 + m); // sort arr2
}

void swapIfGreater(long long arr1[], long long arr2[], int index1, int index2)
{
    if (arr1[index1] > arr2[index2])
    {
        swap(arr1[index1], arr2[index2]);
    }
}

// optimal approach 2, using shell sort (gap method)
// where tc : O((n+m) * log2(n+m)) and sc : O(1) as we are not using any extra space
// this approach is based on the idea of shell sort, where we will compare elements at a certain gap and swap them if they are not in the correct order
// we will keep reducing the gap until it becomes 0, and at that point, both
// arrays will be sorted
// this is a two pointer approach
void mergeOptimal2(long long arr1[], long long arr2[], int n, int m)
{
    int length = n + m;                    // total length of both arrays
    int gap = (length / 2) + (length % 2); // calculate the gap, len /2 will give us the half of the length, and if the length is odd, we will add 1 to it. and so len % 2 will give us the extra element if the length is odd
    while (gap > 0)
    {
        int left = 0;           // pointer for arr1
        int right = left + gap; // pointer for arr2
        while (right < length)
        {
            // comparing elements of arr1 and arr2
            if (left < n && right >= n)
            {
                // here right - n is used to get the index of arr2
                // as right is the index of the merged array, we need to subtract n to get
                // the index of arr2
                // if left is in arr1 and right is in arr2
                // we will compare the elements of arr1 and arr2
                // if the element in arr1 is greater than the element in arr2, we will
                // swap them
                // this is done to ensure that both arrays are sorted
                swapIfGreater(arr1, arr2, left, right - n); // swap if the element in arr1 is greater than the element in arr2
            }

            // comparing elements of arr2 and arr2 (both  pointer are in arr2)
            else if (left >= n)
            {
                swapIfGreater(arr2, arr2, left - n, right - n); // here left - n and right - n are used to get the index of arr2
            }

            // comparing elements of arr1 and arr1 (both pointer are in arr1)
            else
            {
                swapIfGreater(arr1, arr2, left, right); // here right is the index of arr1, so we can directly use it
            }
            left++, right++; // increment both pointers to move to the next elements in the arrays
        }

        if (gap == 1)
            break;                   // if gap is 1, we can stop as we have already sorted the arrays
        gap = (gap / 2) + (gap % 2); // calculate the new gap, len /2 will give us the half of the length, and if the length is odd, we will add 1 to it. and so len % 2 will give us the extra element if the length is odd
    }
}