#include <bits/stdc++.h>
using namespace std;

/* this is binary exponentiation
int func(int mid, int n)
{
    long long ans = 1;
    while(n > 0){
        if(n % 2 == 1){
            ans = ans * mid;
            n = n - 1;
        }

        else{
            mid = mid * mid;
            n = n / 2;
        }
    }
    // mid ^ n
    return ans;
}
*/

// using binary search
// return 1 if == target
// return 0 if < target
// return 2 > target
int func(int mid, int target, int n)
{
    long long ans = 1; // to prevent overflow when multiplying
    for (int i = 1; i <= n; i++)
    {
        ans = ans * mid;
        if (ans > target) // Early stopping: if ans already exceeds 'm', no point in continuing
            return 2;     // Return 2 to indicate mid^n > target
    }
    if (ans == target)
        return 1; // Return 1 if mid^n exactly equals m

    return 0; // Return 0 if mid^n < m
}

int NthRoot(int n, int target)
{
    int low = 1, high = target; // The possible values for the nth root lie between 1 and target
    while (low <= high)         // Binary search loop
    {
        int mid = low + (high - low) / 2;
        int midN = func(mid, target, n); // Evaluate mid^n compared to target

        if (midN == 1)
            return mid; // Found the exact nth root

        else if (midN == 0)
            low = mid + 1; // mid^n < target → try larger numbers

        else
            high = mid - 1; // mid^n > target → try smaller numbers
    }
    return -1; // No integer nth root found
}

int main()
{
    int n, target;
    cout << "Enter the root (n): ";
    cin >> n;
    cout << "Enter the number (target): ";
    cin >> target;

    int result = NthRoot(n, target);
    if (result == -1)
        cout << "No integer " << n << "-th root exists for " << target << endl;
    else
        cout << "The " << n << "-th root of " << target << " is: " << result << endl;

    return 0;
}
