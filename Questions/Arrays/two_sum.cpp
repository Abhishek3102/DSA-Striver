#include <bits/stdc++.h>
using namespace std;

int find_two_sum_no(int arr[], int n, int target)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] + arr[j] == target)
            {
                cout << arr[i] << " " << arr[j] << endl;
                cout << i << " " << j << endl;
            }
        }
    }
}

// better solution than brute force
string read(int n, vector<int> book, int target)
{
    // This has tc : O(N log N)
    map<int, int> mpp;
    for (int i = 0; i < n; i++)
    {
        int a = book[i];
        int more = target - a;
        if (mpp.find(more) != mpp.end())
        {
            return "YES"; // return (mpp[more], i) for index
        }
        mpp[a] = i;
    }
    return "NO";
}

// optimal approach without using map. this is just for type one(whether there are elements that sum up to target, not return index just confirms yes or no)
string read_optimal(int n, vector<int> book, int target)
{
    // using two pointer approach
    // tc : O(N) + O(N log N)
    int left = 0, right = 0;
    sort(book.begin(), book.end());
    while (left < right)
    {
        int sum = book[left] + book[right];
        if (sum == target)
        {
            return "YES";
        }
        else if (sum < target)
            left++;
        else
            right--;
    }
    return "NO";
}

int main()
{ /*
     int n;
     cin >> n;
     int arr[n];                 // sc : O(1)
     for (int i = 0; i < n; i++) // tc : O(N)
     {
         cin >> arr[i];
     }

     int target;
     cin >> target;

     cout << find_two_sum_no(arr, n, target) << endl;
     */

    // ---------- Static input ----------
    vector<int> static_books = {3, 1, 4, 6, 5};
    int static_target = 10;
    int static_n = static_books.size();
    cout << "Static Input Result: " << read(static_n, static_books, static_target) << endl;

    // // ---------- User input ----------
    // int n, target;
    // cout << "\nEnter number of elements: ";
    // cin >> n;

    // vector<int> user_books(n);
    // cout << "Enter the book values: ";
    // for (int i = 0; i < n; i++) {
    //     cin >> user_books[i];
    // }

    // cout << "Enter the target sum: ";
    // cin >> target;

    // string result = read(n, user_books, target);
    // cout << "User Input Result: " << result << endl;

    // return 0;
}