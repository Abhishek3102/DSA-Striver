/*
Given a string s which represents an expression, evaluate this expression and return its value.
The integer division should truncate toward zero.
You may assume that the given expression is always valid. All intermediate results will be in the range of [-231, 231 - 1].
Note: You are not allowed to use any built-in function which evaluates strings as mathematical expressions, such as eval().

Example 1:

Input: s = "3+2*2"
Output: 7
Example 2:

Input: s = " 3/2 "
Output: 1
Example 3:

Input: s = " 3+5 / 2 "
Output: 5


Constraints:

1 <= s.length <= 3 * 105
s consists of integers and operators ('+', '-', '*', '/') separated by some number of spaces.
s represents a valid expression.
All the integers in the expression are non-negative integers in the range [0, 231 - 1].
The answer is guaranteed to fit in a 32-bit integer.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int priority(char op)
    {
        if (op == '+' || op == '-')
            return 1;
        if (op == '*' || op == '/')
            return 2;
        return 0;
    }

    int applyOp(int a, int b, char op)
    {
        if (op == '+')
            return a + b;
        if (op == '-')
            return a - b;
        if (op == '*')
            return a * b;
        return a / b; // truncates toward zero
    }

    int calculate(string s)
    {
        stack<int> nums;
        stack<char> ops;
        int n = s.size();

        for (int i = 0; i < n; i++)
        {
            if (s[i] == ' ')
                continue;

            // parse number
            if (isdigit(s[i]))
            {
                long long num = 0;
                while (i < n && isdigit(s[i]))
                {
                    num = num * 10 + (s[i] - '0');
                    i++;
                }
                nums.push(num);
                i--; // step back
            }
            else
            {
                // operator
                while (!ops.empty() && priority(ops.top()) >= priority(s[i]))
                {
                    int b = nums.top();
                    nums.pop();
                    int a = nums.top();
                    nums.pop();
                    char op = ops.top();
                    ops.pop();
                    nums.push(applyOp(a, b, op));
                }
                ops.push(s[i]);
            }
        }

        // remaining operations
        while (!ops.empty())
        {
            int b = nums.top();
            nums.pop();
            int a = nums.top();
            nums.pop();
            char op = ops.top();
            ops.pop();
            nums.push(applyOp(a, b, op));
        }

        return nums.top();
    }
};

// optimal
class Solution
{
public:
    int calculate(string s)
    {
        stack<int> st;
        char prevOp = '+';
        int num = 0;

        for (int i = 0; i < s.size(); i++)
        {
            if (isdigit(s[i]))
            {
                num = num * 10 + (s[i] - '0');
            }

            if ((!isdigit(s[i]) && s[i] != ' ') || i == s.size() - 1)
            {
                if (prevOp == '+')
                    st.push(num);
                else if (prevOp == '-')
                    st.push(-num);
                else if (prevOp == '*')
                {
                    int x = st.top();
                    st.pop();
                    st.push(x * num);
                }
                else if (prevOp == '/')
                {
                    int x = st.top();
                    st.pop();
                    st.push(x / num);
                }

                prevOp = s[i];
                num = 0;
            }
        }

        int result = 0;
        while (!st.empty())
        {
            result += st.top();
            st.pop();
        }
        return result;
    }
};
