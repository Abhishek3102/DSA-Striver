// Q9 [EASY/MEDIUM] Bubble-sort + binary-search error spotting
// Pen-paper favourites: "find bug in sorting/searching pseudocode".
// BUGGY BUBBLE (paper): for(i=0;i<n;i++) for(j=0;j<n-i;j++) if(a[j]>a[j+1]) swap
//   ERROR: inner j<n-i accesses a[n-i] out of range on last iter. Fix: j < n-i-1
// BUGGY BINARY SEARCH (paper): mid=(low+high)/2; while(low<high){...}
//   ERRORS: (a) needs SORTED array, (b) loop must be low<=high (misses last
//   element otherwise), (c) overflow-safe mid = low+(high-low)/2.
#include <bits/stdc++.h>
using namespace std;

void bubbleSort(vector<int>& a) {
    int n = a.size();
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++) // FIX: -1
            if (a[j] > a[j + 1]) swap(a[j], a[j + 1]);
}
int binarySearch(const vector<int>& a, int target) {
    int low = 0, high = (int)a.size() - 1;
    while (low <= high) { // FIX: <= not <
        int mid = low + (high - low) / 2; // FIX: overflow-safe
        if (a[mid] == target) return mid;
        else if (a[mid] < target) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}
int main() {
    vector<int> a = {5, 1, 4, 2, 8};
    bubbleSort(a);
    cout << "Sorted: "; for (int x : a) cout << x << ' ';
    cout << "(expected 1 2 4 5 8)\n";
    cout << "idx(4)=" << binarySearch(a, 4) << " (2)  idx(7)=" << binarySearch(a, 7) << " (-1)\n";
    return 0;
}
