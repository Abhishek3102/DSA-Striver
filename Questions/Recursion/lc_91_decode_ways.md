Yes — the question in the image is the **Decode Ways / Number of Ways to Decode a String** problem.

For example:

`"122016"`

Each digit can represent `1 -> A, 2 -> B, ..., 26 -> Z`.

We want the **number of possible decodings**.

The key idea is exactly like Striver's DP style:

At every position, we have two choices:

1. Take **one digit** if it is not `'0'`.
2. Take **two digits** if the number formed is between `10` and `26`.

Below are the **3 approaches**: brute-force recursion, memoization, and space optimization.

---

## 1. Brute Force / Recursion

```cpp
#include <bits/stdc++.h>
using namespace std;

// Recursive function
// index = number of characters already processed
//
// Example:
// s = "226"
// index = 2
// means we have processed "22"
// and now we are trying to process from position 2.
int f(int index, string &s)
{
    // Base case:
    // If we have processed the entire string,
    // we found one valid way of decoding it.
    //
    // Example:
    // "226" -> "2" "2" "6"
    // when index becomes 3, we return 1.
    if (index == s.length())
        return 1;

    // If the current character is '0',
    // it cannot be decoded by itself.
    //
    // There is no mapping:
    // 0 -> ?
    if (s[index] == '0')
        return 0;

    // --------------------------------------------------
    // OPTION 1: Take one digit
    // --------------------------------------------------
    //
    // Since s[index] is not '0',
    // it can be decoded as:
    //
    // '1' -> A
    // '2' -> B
    // ...
    // '9' -> I
    //
    // So we move to the next character.
    int oneDigit = f(index + 1, s);

    // --------------------------------------------------
    // OPTION 2: Take two digits
    // --------------------------------------------------
    //
    // We can take two digits only if:
    // 1. There are at least two characters remaining.
    // 2. The two-digit number is between 10 and 26.
    //
    // Examples:
    // 12 -> valid
    // 26 -> valid
    // 27 -> invalid
    // 05 -> invalid
    int twoDigit = 0;

    if (index + 1 < s.length())
    {
        int number = (s[index] - '0') * 10
                     + (s[index + 1] - '0');

        if (number >= 10 && number <= 26)
        {
            twoDigit = f(index + 2, s);
        }
    }

    // The total number of ways is:
    //
    // ways by taking one digit
    // +
    // ways by taking two digits
    return oneDigit + twoDigit;
}


// Main function
int numDecodings(string s)
{
    return f(0, s);
}


int main()
{
    string s;
    cin >> s;

    cout << numDecodings(s) << endl;

    return 0;
}
```

### Recursion idea

For `"226"`:

```text
                    "226"
                   /     \
                take 2   take 22
                  /         \
                "26"         "6"
               /   \           |
            take 2 take 26    take 6
              /       \         |
            "6"       ""        ""
              |         |         |
              1         1         1
```

So:

```text
"226"
    -> "2" "2" "6"
    -> "2" "26"
    -> "22" "6"

Answer = 3
```

### Complexity

There are overlapping recursive calls, so the worst-case time is approximately:

```text
Time:  O(2^N)
Space: O(N)       // recursion stack
```

---

# 2. Memoization

Now we notice that the same `index` is calculated multiple times.

For example, when decoding:

```text
"226"
```

the state for `"6"` can be reached through different paths.

So we store the answer for every `index` in a `dp` array.

This is the same pattern as your **Max Sum Not Adjacent** and **Frog Jump** code.

```cpp
#include <bits/stdc++.h>
using namespace std;


// Memoization function
//
// index = current position in the string
// dp[index] = number of ways to decode
//             the substring starting from index
int fMemoization(int index, string &s, vector<int> &dp)
{
    // --------------------------------------------------
    // BASE CASE
    // --------------------------------------------------
    //
    // If we have reached the end of the string,
    // we have successfully decoded the entire string.
    //
    // Therefore, this represents one valid way.
    if (index == s.length())
        return 1;


    // --------------------------------------------------
    // INVALID CASE
    // --------------------------------------------------
    //
    // '0' cannot be decoded by itself.
    //
    // There is no mapping:
    // 0 -> ?
    if (s[index] == '0')
        return 0;


    // --------------------------------------------------
    // CHECK IF ALREADY CALCULATED
    // --------------------------------------------------
    //
    // If dp[index] is not -1,
    // we have already calculated this state.
    //
    // So simply return the stored answer.
    if (dp[index] != -1)
        return dp[index];


    // --------------------------------------------------
    // OPTION 1: TAKE ONE DIGIT
    // --------------------------------------------------
    //
    // Since s[index] != '0',
    // we can decode this digit individually.
    //
    // Then move to index + 1.
    int oneDigit = fMemoization(index + 1, s, dp);


    // --------------------------------------------------
    // OPTION 2: TAKE TWO DIGITS
    // --------------------------------------------------
    //
    // Initially, assume taking two digits is impossible.
    int twoDigit = 0;

    // We need at least two characters.
    if (index + 1 < s.length())
    {
        // Convert two characters into an integer.
        //
        // Example:
        // s[index]     = '2'
        // s[index + 1] = '6'
        //
        // number = 26
        int number = (s[index] - '0') * 10
                     + (s[index + 1] - '0');


        // A valid two-digit encoding is from 10 to 26.
        if (number >= 10 && number <= 26)
        {
            // We consumed two characters,
            // so move to index + 2.
            twoDigit = fMemoization(index + 2, s, dp);
        }
    }


    // --------------------------------------------------
    // STORE THE ANSWER
    // --------------------------------------------------
    //
    // Total ways =
    //
    // ways by taking one digit
    // +
    // ways by taking two digits
    //
    // Store it so that we don't calculate
    // the same state again.
    return dp[index] = oneDigit + twoDigit;
}


// Main function for memoization
int numDecodingsMemo(string s)
{
    int n = s.length();

    // dp[i] stores the number of ways
    // to decode the string starting from index i.
    //
    // Initially -1 means:
    // "This state has not been calculated yet."
    vector<int> dp(n, -1);

    return fMemoization(0, s, dp);
}


int main()
{
    string s;
    cin >> s;

    cout << numDecodingsMemo(s) << endl;

    return 0;
}
```

### Why memoization works

Suppose:

```text
s = "1234"
```

The recursion may ask for the answer starting at:

```text
index = 2
```

multiple times.

Instead of calculating it repeatedly:

```cpp
if (dp[index] != -1)
    return dp[index];
```

we calculate it once and reuse it.

### Complexity

There are only `N` different states:

```text
index = 0
index = 1
index = 2
...
index = N
```

Each state does constant work.

Therefore:

```text
Time:  O(N)
Space: O(N) + O(N)
        dp array + recursion stack

      = O(N)
```

---

# 3. Space Optimization

Now we can convert the memoized solution into a bottom-up DP.

The important observation is:

```text
dp[index]
```

only depends on:

```text
dp[index + 1]
dp[index + 2]
```

So we don't actually need the entire `dp` array.

We only need the previous two values.

This is exactly the same idea as your:

```cpp
prev
prev2
curi
```

in **Frog Jump** and **Maximum Sum Not Adjacent**.

```cpp
#include <bits/stdc++.h>
using namespace std;


// Space Optimized DP
int numDecodingsSO(string s)
{
    int n = s.length();

    // Empty string
    if (n == 0)
        return 0;


    // --------------------------------------------------
    // We are going to calculate:
    //
    // dp[i] = number of ways to decode
    //         first i characters
    //
    // Example:
    //
    // dp[0] = 1
    // dp[1] = ways to decode first 1 character
    // dp[2] = ways to decode first 2 characters
    // ...
    //
    // The recurrence is:
    //
    // dp[i] = dp[i - 1]       // take one digit
    //       + dp[i - 2]       // take two digits
    //
    // whenever the corresponding choice is valid.
    // --------------------------------------------------


    // dp[0] = 1
    //
    // There is exactly one way to decode an empty string:
    // choose nothing.
    int prev2 = 1;


    // dp[1]
    //
    // If the first character is not '0',
    // it can be decoded.
    //
    // Example:
    // "2" -> B
    //
    // Therefore dp[1] = 1.
    //
    // If it is '0', then:
    // dp[1] = 0
    int prev = (s[0] != '0') ? 1 : 0;


    // --------------------------------------------------
    // Start from the second character.
    // --------------------------------------------------
    //
    // i represents the number of characters
    // considered so far.
    //
    // Therefore the current character is:
    //
    // s[i - 1]
    //
    // because string indexing starts from 0.
    for (int i = 2; i <= n; i++)
    {
        // Initially there are no ways.
        int curi = 0;


        // --------------------------------------------------
        // OPTION 1: TAKE ONE DIGIT
        // --------------------------------------------------
        //
        // Current character:
        //
        // s[i - 1]
        //
        // It can be taken individually only if
        // it is not '0'.
        //
        // Example:
        // "1" -> A
        // "2" -> B
        // ...
        // "9" -> I
        if (s[i - 1] != '0')
        {
            curi += prev;
        }


        // --------------------------------------------------
        // OPTION 2: TAKE TWO DIGITS
        // --------------------------------------------------
        //
        // The two digits are:
        //
        // s[i - 2] and s[i - 1]
        //
        // Example:
        //
        // s = "226"
        // i = 3
        //
        // twoDigit = "26"
        //
        // It is valid if:
        //
        // 10 <= twoDigit <= 26
        int twoDigit = (s[i - 2] - '0') * 10
                       + (s[i - 1] - '0');


        if (twoDigit >= 10 && twoDigit <= 26)
        {
            curi += prev2;
        }


        // --------------------------------------------------
        // SHIFT THE VARIABLES
        // --------------------------------------------------
        //
        // Before moving forward:
        //
        // prev2 = dp[i - 2]
        // prev  = dp[i - 1]
        //
        // After calculating curi = dp[i]:
        //
        // prev2 becomes old prev
        // prev becomes curi
        prev2 = prev;
        prev = curi;
    }


    // prev now contains dp[n],
    // which is the answer for the entire string.
    return prev;
}


int main()
{
    string s;
    cin >> s;

    cout << numDecodingsSO(s) << endl;

    return 0;
}
```

---

# The Striver-style pattern

You can remember the entire problem using this recurrence:

```text
                     dp[i]
                    /     \
              one digit   two digits
                  |           |
               dp[i-1]     dp[i-2]
```

Therefore:

```cpp
dp[i] = dp[i - 1] + dp[i - 2]
```

**but only when the corresponding one/two-digit decoding is valid.**

For one digit:

```cpp
s[i - 1] != '0'
```

For two digits:

```cpp
10 <= twoDigit && twoDigit <= 26
```

---

## Complete version with all 3 approaches

This is probably the version I'd keep in your DSA notes, because it follows the same structure as your **Frog Jump → Recursion → Memoization → Space Optimization** code.

```cpp
#include <bits/stdc++.h>
using namespace std;


// ============================================================
// 1. BRUTE FORCE / RECURSION
// ============================================================

// index = current position in the string
//
// We are trying to decode:
//
// s[index ... n-1]
//
// At every index we have two possibilities:
//
// 1. Take one digit
// 2. Take two digits
int f(int index, string &s)
{
    // If we reached the end,
    // one valid decoding has been completed.
    if (index == s.length())
        return 1;


    // '0' cannot be decoded individually.
    if (s[index] == '0')
        return 0;


    // --------------------------------------------------------
    // Take one digit
    // --------------------------------------------------------
    //
    // Since s[index] is not zero,
    // we can decode it individually.
    int oneDigit = f(index + 1, s);


    // --------------------------------------------------------
    // Take two digits
    // --------------------------------------------------------
    int twoDigit = 0;

    if (index + 1 < s.length())
    {
        int number = (s[index] - '0') * 10
                     + (s[index + 1] - '0');

        // Only 10 to 26 are valid two-digit mappings.
        if (number >= 10 && number <= 26)
        {
            twoDigit = f(index + 2, s);
        }
    }


    // Total number of ways.
    return oneDigit + twoDigit;
}


// Function to start recursion
int numDecodings(string s)
{
    return f(0, s);
}


// ============================================================
// 2. MEMOIZATION
// ============================================================

int fDP(int index, string &s, vector<int> &dp)
{
    // Reached the end:
    // one valid way has been found.
    if (index == s.length())
        return 1;


    // Cannot decode zero individually.
    if (s[index] == '0')
        return 0;


    // Already calculated?
    if (dp[index] != -1)
        return dp[index];


    // --------------------------------------------------------
    // Take one digit
    // --------------------------------------------------------
    int oneDigit = fDP(index + 1, s, dp);


    // --------------------------------------------------------
    // Take two digits
    // --------------------------------------------------------
    int twoDigit = 0;

    if (index + 1 < s.length())
    {
        int number = (s[index] - '0') * 10
                     + (s[index + 1] - '0');

        if (number >= 10 && number <= 26)
        {
            twoDigit = fDP(index + 2, s, dp);
        }
    }


    // Store and return answer.
    return dp[index] = oneDigit + twoDigit;
}


// Function to start memoization
int numDecodingsDP(string s)
{
    int n = s.length();

    vector<int> dp(n, -1);

    return fDP(0, s, dp);
}


// ============================================================
// 3. SPACE OPTIMIZATION
// ============================================================

int numDecodingsSO(string s)
{
    int n = s.length();

    if (n == 0)
        return 0;


    // --------------------------------------------------------
    // dp[0]
    // --------------------------------------------------------
    //
    // Empty string has exactly one way.
    int prev2 = 1;


    // --------------------------------------------------------
    // dp[1]
    // --------------------------------------------------------
    //
    // First character can be decoded only if it is not zero.
    int prev = (s[0] != '0') ? 1 : 0;


    // Calculate dp[2] ... dp[n]
    for (int i = 2; i <= n; i++)
    {
        int curi = 0;


        // ----------------------------------------------------
        // TAKE ONE DIGIT
        // ----------------------------------------------------
        //
        // Current digit is s[i - 1].
        //
        // If it is not zero, we can decode it individually.
        if (s[i - 1] != '0')
        {
            curi += prev;
        }


        // ----------------------------------------------------
        // TAKE TWO DIGITS
        // ----------------------------------------------------
        //
        // Take:
        //
        // s[i - 2] s[i - 1]
        //
        // and check whether the resulting number
        // lies between 10 and 26.
        int twoDigit = (s[i - 2] - '0') * 10
                       + (s[i - 1] - '0');


        if (twoDigit >= 10 && twoDigit <= 26)
        {
            curi += prev2;
        }


        // ----------------------------------------------------
        // SHIFT
        // ----------------------------------------------------
        //
        // dp[i - 2] -> prev2
        // dp[i - 1] -> prev
        // dp[i]     -> curi
        //
        // For the next iteration:
        //
        // prev2 = old prev
        // prev  = current answer
        prev2 = prev;
        prev = curi;
    }


    // dp[n]
    return prev;
}


// ============================================================
// MAIN
// ============================================================

int main()
{
    string s;
    cin >> s;


    cout << "Brute Force: "
         << numDecodings(s) << endl;


    cout << "Memoization: "
         << numDecodingsDP(s) << endl;


    cout << "Space Optimization: "
         << numDecodingsSO(s) << endl;


    return 0;
}
```

### Complexity summary

| Approach                |     Time |                  Space |
| ----------------------- | -------: | ---------------------: |
| Brute Force / Recursion | `O(2^N)` | `O(N)` recursion stack |
| Memoization             |   `O(N)` |                 `O(N)` |
| Space Optimization      |   `O(N)` |                 `O(1)` |

**One important correction compared with the code in your image:** for a string like `"06"`, you must **not** allow `"06"` as a two-digit number. The `10 <= twoDigit <= 26` check automatically handles that.
