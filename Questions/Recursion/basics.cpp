#include <iostream>
using namespace std;

void printFiveXName(int i, int n)
{
    // T.C. : O(n) and S.C. :  O(n)

    // i = 1;
    // cin >> n;
    if (i > n)
        return;
    cout << "name" << endl;
    printFiveXName(i + 1, n);
    return;
}

void print1toN(int i, int n)
{
    // int N;
    // cin >> N;
    if (i > n)
        return;
    cout << i << endl;
    print1toN(i + 1, n);
    return;
}

void printNto1(int n, int i)
{
    if (i > n)
        return;
    cout << n << endl;
    printNto1(n - 1, i);
    return;
}

void OnetoNusingBack(int i, int n)
{
    if (i < 1)
        return;
    OnetoNusingBack(i - 1, n);
    cout << i << endl;
}

void NtoOneusingBack(int i, int n)
{
    if (i < 1)
        return;
    NtoOneusingBack(i - 1, n);
    cout << i << endl;
}

void sumOfN(int i, int n, int &sum)
{

    if (i > n)
        return;
    sum += i;
    sumOfN(i + 1, n, sum);
}

// Parametrized way
void hisSumToN(int i, int sum)
{
    if (i < 1)
    {
        cout << sum << endl;
        return;
    }
    hisSumToN(i - 1, sum + i);
}

// functional way
int funcSum1toN(int n)
{
    if (n == 0)
    {
        return 0;
    }
    return n + funcSum1toN(n - 1);
}

int fibo(int n)
{
    if (n == 0)
    {
        return 0;
    }
    else if (n == 1)
    {
        return 1;
    }
    else
    {
        return fibo(n - 1) + fibo(n - 2);
    }
}

int factorialN(int n)
{
    if (n == 0 || n == 1)
    {
        return 1;
    }
    return n * factorialN(n - 1);
}

void print(int i, int n)
{
    // Relying on the function call stack to stop recursion
    try
    {
        print(i + 1, n);  // Go till i > n (no base case)
        cout << i << " "; // Print during backtracking
    }
    catch (...)
    {
        // Catch any exception (not mandatory here)
    }
}

int main()
{
    // sumOfN - commented part
    // int sum = 0;
    // sumOfN(1, 6, sum);
    // cout << "sum is : " << sum << endl;

    // hisSumToN(6, 0);

    cout << factorialN(5);
    return 0;
}

/* code that improved mistakes and logic where i was lacking

The issue with your code lies in how the variable `sum` is being handled within the recursive function.

### Problem Explanation:

1. **Local Scope of `sum`:**

   * The variable `sum` is declared inside the function `sumOfN`, which means it is a **local variable**. Each time the function is called (via recursion), a new instance of `sum` is created and initialized to `0`. Therefore, any updates to `sum` within a recursive call will not persist across different calls.
   * In other words, you're trying to accumulate the sum, but since the variable is local to each call, it resets every time you call `sumOfN(i + 1, n)`.

2. **Recursive Calls Don't Accumulate `sum`:**

   * You are not returning or passing `sum` to the next recursive call, so the value of `sum` is lost as each recursive call gets its own local copy.
   * You need to accumulate the sum across different recursive calls. This requires either:

     * Passing the `sum` variable along with each recursive call.
     * Returning `sum` from each recursive call and combining it with the value from the next call.

### How to Fix It:

You should modify the function to accumulate `sum` properly, either by passing it as a parameter or by using a return value. Here's a fixed version of the code where `sum` is passed as a parameter and accumulated:

### Solution 1: Pass `sum` as a parameter:

```cpp
#include <iostream>
using namespace std;

void sumOfN(int i, int n, int& sum)
{
    if (i > n)
        return;

    sum += i;  // Add i to sum

    sumOfN(i + 1, n, sum);  // Recursively call with the updated sum
}

int main()
{
    int sum = 0;
    sumOfN(1, 6, sum);  // Pass the initial sum (0) by reference
    cout << "Sum: " << sum << endl;  // Print the final sum
    return 0;
}
```

### Explanation:

* `sum` is now passed by reference (`int& sum`), so when it is updated inside `sumOfN`, the changes persist across recursive calls.
* The final sum is computed and printed in `main()` after the recursive calls finish.

### Output:

```
Sum: 21
```

### Solution 2: Return the sum (alternative approach):

Alternatively, you could return the sum from each recursive call and combine the results. Here's the code for that:

```cpp
#include <iostream>
using namespace std;

int sumOfN(int i, int n)
{
    if (i > n)
        return 0;  // Base case: return 0 when i > n

    return i + sumOfN(i + 1, n);  // Return the sum of i and the result of the next recursive call
}

int main()
{
    int sum = sumOfN(1, 6);  // Call the recursive function and store the result
    cout << "Sum: " << sum << endl;  // Print the final sum
    return 0;
}
```

### Explanation:

* Instead of using a reference to `sum`, we return the sum from each recursive call. Each recursive call computes its own sum and returns it.
* When `i > n`, we return `0` as the base case, and the recursion unwinds by adding `i` to the returned values.

### Output:

```
Sum: 21
```

### Conclusion:

The main issue was that the `sum` variable was not accumulating across recursive calls due to its local scope. To fix it, either pass `sum` by reference or return it from each call, ensuring the sum is correctly accumulated.

*/