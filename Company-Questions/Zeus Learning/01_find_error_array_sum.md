// Q1 [EASY - 2 marks] Spot errors in pseudocode: array sum
// ROUND CONTEXT: Zeus pen-paper "identify errors in simple pseudocode".
//
// BUGGY PSEUDOCODE (as given on paper):
//   int arr[n]; int sum; int i;
//   for(i=0; i<=n; i++)      // ERROR 1
//       sum = sum + arr[i];  // ERROR 2 (sum garbage) + ERROR 1 (out of bounds)
//   print sum
//
// ERRORS TO WRITE ON PAPER:
//  1. `sum` not initialised -> garbage value. Fix: int sum = 0;
//  2. `i <= n` runs n+1 times -> accesses arr[n] (out of bounds). Fix: i < n
//  3. (minor) n must be read/defined before declaring array.
//
// FIXED C++ below + runnable demo.
#include <bits/stdc++.h>
using namespace std;

int arraySum(const vector<int>& a) {
    int sum = 0;                       // FIX: initialise
    for (size_t i = 0; i < a.size(); i++) // FIX: < not <=
        sum += a[i];
    return sum;
}

int main() {
    vector<int> arr = {5, 2, 8, 1, 9};
    cout << "Sum = " << arraySum(arr) << " (expected 25)\n";
    // Trace table for paper: i=0..4, sum=0->5->7->15->16->25
    return 0;
}
