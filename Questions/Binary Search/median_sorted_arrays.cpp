// in this, we will be doing the brute and better approaches

#include <bits/stdc++.h>
using namespace std;

double median(vector<int> a, vector<int> b)
{
    vector<int> c;
    int n = a.size(), m = b.size();
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int j = 0;
    int i = 0;

    // Merge the two sorted arrays into one sorted array.
    while (i < n && j < m)
    {
        if (a[i] < b[j])
            c.push_back(a[i++]); // Add smaller element from a
        else
            c.push_back(b[j++]); // Add smaller element from b
    }

    // Append remaining elements of a (if any)
    while (i < n)
        c.push_back(a[i++]);

    // Append remaining elements of b (if any)
    while (j < m)
        c.push_back(b[j++]);

    int x = (n + m); // Total number of elements in merged array

    // If total elements are odd, return the middle element
    if (x % 2 == 1)
    {
        return c[x / 2];
    }

    // If even, return the average of the two middle elements
    return (double)((double)(c[x / 2]) + (double)(c[x / 2 - 1])) / 2.0;
}

// better approach without using extra space
// This function calculates the median without actually merging the arrays.
// It keeps track of the necessary median elements during the traversal.
double median(vector<int> a, vector<int> b)
{
    int n1 = a.size(), n2 = b.size();
    int i = 0, j = 0; // Pointers to traverse both arrays
    int n = (n1 + n2);

    int ind2 = n / 2;             // Index of the second median element (for even count)
    int ind1 = ind2 - 1;          // Index of the first median element (for even count)
    int cnt = 0;                  // To count number of merged elements processed
    int ind1el = -1, ind2el = -1; // To store median candidates

    // Traverse both arrays as in merge sort but only up to the median indices
    while (i < n1 && j < n2)
    {
        if (a[i] < b[j]) // If element in a[] is smaller than b[]
        {
            // If current element is at position 'ind1' in merged array, store it as 'ind1el'
            if (cnt == ind1)
                ind1el = a[i];

            // If current element is at position 'ind2' in merged array, store it as 'ind2el'
            if (cnt == ind2)
                ind1el = a[i];

            cnt++; // Increment counter after processing the element from array 'a'
            i++;   // Move pointer in array 'a'
        }

        // If element in b[] is smaller or equal to element in a[]
        else
        {
            // If current element is at position 'ind1' in merged array, store it as 'ind1el'
            if (cnt == ind1)
                ind1el = b[j];

            // If current element is at position 'ind2' in merged array, store it as 'ind2el'
            if (cnt == ind2)
                ind2el = b[j];

            cnt++; // Increment counter after processing the element from array 'b'
            j++;   // Move pointer in array 'b'
        }
    }

    // If elements remain in a[]
    while (i < n1)
    {
        // Check if this element is at position 'ind1' or 'ind2' in the merged array
        if (cnt == ind1)
            ind1el = a[i];
        if (cnt == ind2)
            ind2el = a[i];
        cnt++;
        i++;
    }

    // If elements remain in b[]
    while (j < n2)
    {
        // Check if this element is at position 'ind1' or 'ind2' in the merged array
        if (cnt == ind1)
            ind1el = b[j];
        if (cnt == ind2)
            ind2el = b[j];
        cnt++;
        j++;
    }

    // If total number of elements is odd, the second median (ind2el) is the only middle element
    if (n % 2 == 1)
    {
        return ind2el;
    }

    return (double)((double)(ind1el + ind2el)) / 2.0;
}

int main()
{
    vector<int> a = {1, 6, 7, 5, 11};
    vector<int> b = {4, 2, 9};
    // sort(a.begin(), a.end());
    // sort(b.begin(), b.end());

    cout << median(a, b);
    return 0;
}