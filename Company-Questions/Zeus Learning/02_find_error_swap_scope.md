// Q2 [EASY - 2 marks] Spot errors: swap + scope + = vs ==
// BUGGY PSEUDOCODE (as given on paper):
//   void swap(int a, int b) { int t = a; a = b; b = t; }  // ERROR 1: pass by value
//   main: x=5, y=10; swap(x,y); print x y;               // prints 5 10, not swapped
//   if (x = y) print "equal";                            // ERROR 2: = is assignment, always true
//
// ERRORS TO WRITE ON PAPER:
//  1. swap takes copies -> originals unchanged. Fix: void swap(int &a, int &b)
//  2. `if (x = y)` assigns y to x, condition = value of x (non-zero = true).
//     Fix: `if (x == y)`.
//  3. Related trap: uninitialised variable / missing return type.
//
// FIXED C++ below + runnable demo.
#include <bits/stdc++.h>
using namespace std;

void mySwap(int &a, int &b) { // FIX: references
    int t = a; a = b; b = t;
}

int main() {
    int x = 5, y = 10;
    mySwap(x, y);
    cout << "After swap: x=" << x << " y=" << y << " (expected 10 5)\n";
    if (x == y) cout << "equal\n";       // FIX: == not =
    else cout << "not equal (correct)\n";
    return 0;
}
