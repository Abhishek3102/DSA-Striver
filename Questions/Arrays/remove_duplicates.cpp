#include <bits/stdc++.h>
using namespace std;

int remove_dup()
{

    /*

    Total Time Complexity:

    O(N) for input reading

    O(N * log N) for sorting the vector

    O(N * log N) for inserting elements into the set

    O(N) for copying the unique elements back into the vector and printing them

    O(1) for returning the size of the set

    So, the total time complexity is:

    O(N * log N) + O(N * log N) + O(N) = O(N * log N)

    */

    int n;
    cin >> n; // Input size of the array

    vector<int> a(n); // O(1) for creating an empty vector, O(N) for allocation of the vector
    for (int i = 0; i < n; i++)
    {
        cin >> a[i]; // O(N) for reading the input
    }

    sort(a.begin(), a.end()); // O(N * log N) for sorting the array

    set<int> st; // O(1) for creating an empty set

    for (int i = 0; i < n; i++)
    {
        st.insert(a[i]); // O(log N) for each insertion into the set, O(N * log N) for N insertions
    }

    int index = 0;
    for (auto it : st)
    {
        a[index] = it;     // O(1) for each assignment
        index++;           // O(1)
        cout << it << " "; // O(1) for each print operation
    }
    cout << endl; // O(1) for newline output

    return st.size(); // O(1) for returning the size of the set
}

// Pseudocode for optimal remove duplicates from array
/*
i = 0;
for(j = 1; j<n; j++){
    if(arr[j] != arr[i]){
    arr[i+1] = arr[j];
    i++;
}
}
return (i+1);
*/

int removeDuplicatesOptimal(vector<int> &arr, int n)
{
    int i = 0;
    for (int j = 1; j < n; j++)
    {
        if (arr[i] != arr[j])
        {
            arr[i + 1] = arr[j];
            i++;
        }
    }
    return i + 1;
}

int main()
{
    // cout << remove_dup() << endl; // O(N * log N)
    // return 0;                     // O(1)

    // hardcoded array
    // vector<int> arr = {1, 1, 2, 2, 3, 4, 5, 7};
    // int n = arr.size();
    // int newLength = removeDuplicatesOptimal(arr, n);
    // cout << newLength << endl;

    int n;
    cout << "Enter the number of elements in the array: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the elements of the sorted array (space separated): ";
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }

    // Call the removeDuplicates function
    int newLength = removeDuplicatesOptimal(arr, n);

    // Output the result
    cout << "The new length after removing duplicates is: " << newLength << endl;
    cout << "The modified array is: ";
    for (int i = 0; i < newLength; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}
