/*
Here's your code with detailed explanatory comments.

```cpp
class Solution {
public:
    int myAtoi(string s) {

        // If the string is empty, there is nothing to convert.
        if(s.size() == 0) return 0;

        int i = 0;

        // --------------------------------------------------------
        // Step 1: Remove leading whitespaces.
        //
        // Example:
        // "     -42"
        //        ^
        //
        // Keep moving until a non-space character is found.
        // --------------------------------------------------------
        while(i < s.size() && s[i] == ' '){
            i++;
        }

        // Keep only the remaining useful part of the string.
        //
        // Example:
        // Original : "    -42"
        // After    : "-42"
        //
        s = s.substr(i);

        // By default assume the number is positive.
        int sign = +1;

        // 'ans' stores the number being formed digit by digit.
        //
        // Example:
        // "1234"
        //
        // ans progresses as
        // 1
        // 12
        // 123
        // 1234
        //
        long ans = 0;

        // Check whether the number is negative.
        if(s[0] == '-')
            sign = -1;

        int MAX = INT_MAX;
        int MIN = INT_MIN;

        // Skip '+' or '-' before reading digits.
        i = (s[0] == '+' || s[0] == '-') ? 1 : 0;

        while(i < s.size()){

            // Stop when a non-digit character is found.
            //
            // Example:
            // "123abc"
            //     ^
            //
            // Parsing stops here.
            if(!isdigit(s[i]))
                break;

            // Convert the current digit character into an integer
            // and append it to the previously formed number.
            //
            // Example:
            //
            // ans = 56
            // current character = '7'
            //
            // ans becomes
            //
            // 56 * 10 + 7 = 567
            //
            ans = ans * 10 + s[i] - '0';

            // Check overflow for negative numbers.
            if(sign == -1 && -ans < MIN)
                return MIN;

            // Check overflow for positive numbers.
            if(sign == 1 && ans > MAX)
                return MAX;

            i++;
        }

        // Apply the sign.
        return (int)(sign * ans);
    }
};
```

---

# 1. Why

```cpp
ans = ans * 10 + s[i] - '0';
```

This is probably the most common line in parsing problems.

Suppose the string is

```text
"527"
```

Initially

```text
ans = 0
```

Read first character

```text
'5'
```

`'5'` is **not** the integer 5.

It is a character whose ASCII value is

```text
'0' = 48
'1' = 49
'2' = 50
...
'5' = 53
...
'9' = 57
```

So

```cpp
'5' - '0'
```

means

```text
53 - 48 = 5
```

Hence

```cpp
digit = s[i] - '0';
```

converts a character digit into an integer digit.

---

## Example

Suppose

```text
ans = 52
```

Next character

```text
'7'
```

First convert

```cpp
'7' - '0'
```

↓

```text
55 - 48 = 7
```

Now

```cpp
ans = ans * 10 + 7;
```

↓

```text
52 * 10 = 520

520 + 7

= 527
```

---

# Why multiply by 10?

Think of decimal numbers.

Suppose

```text
52
```

Appending 7 gives

```text
527
```

Mathematically

```text
52 × 10 = 520

520 + 7 = 527
```

Similarly

```text
123

↓

123 × 10

↓

1230

↓

1234
```

---

# General formula

Whenever you are building a number digit by digit

```cpp
number = number * 10 + digit;
```

This is true in every programming language.

---

# Where is this used?

Almost everywhere.

### 1. atoi()

Exactly this question.

---

### 2. Parsing numbers from strings

```text
Input

"98765"
```

Convert to integer.

---

### 3. Very Large Integer problems

Example

```text
99999999999999999999999
```

You read one digit at a time.

---

### 4. Expression Evaluators

Example

```text
"25+36-18"
```

Need to build

```text
25

36

18
```

using

```cpp
num = num * 10 + digit;
```

---

### 5. DFS/BFS problems

Sometimes digits come separately.

Example

```text
Digits

1

2

3
```

Need

```text
123
```

---

### 6. Binary to Decimal

Instead of

```cpp
ans = ans * 10 + digit;
```

you write

```cpp
ans = ans * 2 + bit;
```

because binary is base 2.

---

### 7. Hexadecimal

```cpp
ans = ans * 16 + value;
```

---

## Rule

For any base

```text
number = number × base + current_digit
```

---

# Why subtract '0'?

Because characters and integers are different.

Suppose

```cpp
char ch = '8';
```

Printing

```cpp
cout << (int)ch;
```

gives

```text
56
```

Not

```text
8
```

Subtracting

```cpp
ch - '0'
```

makes

```text
56 - 48

=

8
```

---

# When should you use

```cpp
digit = ch - '0';
```

Whenever you know

```cpp
ch
```

contains a numeric character

like

```text
'0'

'1'

...

'9'
```

Never do

```cpp
'a' - '0'
```

because that isn't a valid digit.

Usually you first check

```cpp
isdigit(ch)
```

then

```cpp
digit = ch - '0';
```

---

# 2. What is substr()?

Syntax

```cpp
string.substr(start, length)
```

Returns a **new string**.

Original string remains unchanged.

---

## Example

```cpp
string s = "Programming";
```

```
012345678910
Programming
```

---

### Example 1

```cpp
s.substr(3)
```

returns

```text
gramming
```

Everything from index 3 onwards.

---

### Example 2

```cpp
s.substr(0,4)
```

returns

```text
Prog
```

---

### Example 3

```cpp
s.substr(4,3)
```

returns

```text
ram
```

---

# Why used here?

Suppose

```text
"      -42"
```

After counting spaces

```text
i = 6
```

Then

```cpp
s = s.substr(i);
```

becomes

```text
"-42"
```

Now your parsing starts from index 0, making the rest of the code simpler.

Without `substr`, you'd have to keep using the original index `i` throughout the function.

---

# General uses of substr()

## 1. Extract first n characters

```cpp
name.substr(0,5);
```

---

## 2. Remove first character

```cpp
s.substr(1);
```

Example

```text
Hello

↓

ello
```

---

## 3. Remove last character

```cpp
s.substr(0,s.size()-1);
```

Example

```text
Hello

↓

Hell
```

---

## 4. Get last k characters

```cpp
s.substr(s.size()-k);
```

Example

```text
Programming

↓

ming
```

---

## 5. Split strings

Example

```text
abc:def
```

Find

```cpp
int pos = s.find(':');
```

Then

```cpp
left = s.substr(0,pos);

right = s.substr(pos+1);
```

Result

```text
abc

def
```

---

## 6. Reverse engineering strings

Many string problems involve comparing parts of strings:

```cpp
if(s.substr(i,3) == "cat")
```

or

```cpp
if(s.substr(i,5) == "apple")
```

---

## 7. Palindrome problems

Extract part of a string:

```cpp
string part = s.substr(l,r-l+1);
```

Useful in problems like longest palindrome or partitioning.

---

## 8. Recursion / Backtracking

Remove one character:

```cpp
string next = s.substr(0,i) + s.substr(i+1);
```

Example

```text
abcd

remove c

↓

abd
```

This pattern appears in permutation and recursive string problems.

---

### Key Takeaways

* `ch - '0'` converts a digit character (`'7'`) to its integer value (`7`).
* `number = number * 10 + digit` is the standard way to build a decimal number one digit at a time.
* The same idea generalizes to any base: `number = number * base + digit`.
* `substr(start)` returns the string from `start` to the end; `substr(start, length)` returns a portion of the string.
* `substr()` is widely used for trimming prefixes, splitting strings, extracting tokens, checking prefixes/suffixes, recursion, and many string manipulation problems.

*/