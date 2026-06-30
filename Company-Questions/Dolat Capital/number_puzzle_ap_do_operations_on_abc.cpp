/*
Question 2:

3 Number Puzzle (Arithmetic Progression)Problem Statement:You are given three numbers $A, B$, and $C$.
You are allowed to perform an operation where you multiply exactly one of the three numbers by a strictly positive integer $k$ ($k > 0$).
Your task is to determine whether it is possible to convert the sequence $A, B, C$ into an Arithmetic Progression (A.P.) using this operation.
An array of three numbers forms an A.P. if the common difference is the same, i.e., $B - A = C - B$ (which simplifies to $2B = A + C$).
Print "Yes" if it is possible, and "No" if it is not.
Input Format:The first line contains an integer $T$, the number of queries/test cases.
The next $T$ lines each contain three space-separated integers $A, B$, and $C$.
Examples:Input: 10 5 30Output: YesExplanation: Multiply 5 by 4 to get 20. The sequence becomes 10, 20, 30, which is an A.P.
Input: 30 5 10Output: YesExplanation: Multiply 5 by 4 to get 20. The sequence becomes 30, 20, 10, which is an A.P.
Input: 2 1 1Output: NoExplanation: There is no positive integer you can multiply one of the numbers by to form an A.P.

*/

#include <iostream>
using namespace std;

void solve()
{
    int A, B, C;
    cin >> A >> B >> C;

    // Case 1: We multiply B by some positive integer k
    if ((A + C) % (2 * B) == 0 && (A + C) / (2 * B) > 0)
    {
        cout << "Yes\n";
        return;
    }
    // Case 2: We multiply A by some positive integer k
    if ((2 * B - C) % A == 0 && (2 * B - C) / A > 0)
    {
        cout << "Yes\n";
        return;
    }
    // Case 3: We multiply C by some positive integer k
    if ((2 * B - A) % C == 0 && (2 * B - A) / C > 0)
    {
        cout << "Yes\n";
        return;
    }

    cout << "No\n";
}

int main()
{
    // Read number of test cases if required, else just call solve()
    int t;
    if (cin >> t)
    {
        while (t--)
            solve();
    }
    return 0;
}