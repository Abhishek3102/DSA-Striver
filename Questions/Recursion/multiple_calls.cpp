#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int f(int n)
{
    /* here for every step 2 recursion calls were made, so this is almost 2 to the power n.

    Why Time Complexity is Almost O(2n)O(2n):

    Exponential Growth of Recursive Calls:
    For each call, we make two additional recursive calls: one for f(n-1) and another for f(n-2). This creates a binary recursion tree.
    The number of calls grows exponentially as the input n increases. For instance, if n = 5, the number of calls increases further.

    2. **Why Almost \( O(2^n) \) and Not Exactly \( O(2^n) \)**:
 - **Exact Exponential Growth**: If each level of recursion were to always produce two new calls, the recursion tree would have \( 2^n \) nodes (i.e., each level would have twice as many nodes as the previous one).
 - However, because of overlapping subproblems (e.g., `f(2)` is called multiple times), the actual number of calls will be less than \( 2^n \). So while the growth is exponential, it's **not strictly \( 2^n \)** but rather **"almost" \( 2^n \)**, because the recursive calls reuse previous results.

 - In fact, without memoization or dynamic programming, you’ll end up recalculating values multiple times. For example, `f(2)` is called both from `f(3)` and `f(4)`, but both would independently calculate `f(2)` again.

 so this is an example of exponential time complexity
    */

    if (n <= 1)
        return n;
    int last, slast;
    last = f(n - 1);
    slast = f(n - 2);
    return last + slast;
}

int main()
{
    cout << f(0) << " " << f(1) << " " << f(2) << " " << f(3) << " " << f(4);
}