#include <bits/stdc++.h>
using namespace std;

class st
{
    stack<pair<int, int>> s;

public:
    void push(int val)
    {
        // store (value, current minimum)
        if (s.empty())
            s.push({val, val});
        else
            s.push({val, min(val, s.top().second)});
    }

    void pop()
    {
        if (!s.empty())
            s.pop();
    }

    int top()
    {
        if (!s.empty())
            return s.top().first;
        throw runtime_error("Stack is empty");
    }

    int getMin()
    {
        if (!s.empty())
            return s.top().second;
        throw runtime_error("Stack is empty");
    }
};

class minStack
{
    stack<int> sta;
    int mini;

public:
    void push(int val)
    {
        if (sta.empty())
        {
            mini = val;
            sta.push(val);
        }
        else
        {
            if (val > mini)
                sta.push(val);
            else
            {
                sta.push(2 * val - mini); // encoded new minimum
                mini = val;
            }
        }
    }

    void pop()
    {
        if (sta.empty())
            return;

        int x = sta.top();
        sta.pop();

        if (x < mini)
            mini = 2 * mini - x; // decode previous minimum
    }

    int top()
    {
        if (sta.empty())
            throw runtime_error("Stack empty");

        int x = sta.top();
        if (x >= mini)
            return x; // real value
        return mini;  // encoded minimum
    }

    int getMini()
    {
        return mini;
    }
};

int main()
{

    cout << "Testing class st (pair-based min stack):\n";

    st ms1; // using pair approach
    ms1.push(5);
    ms1.push(3);
    ms1.push(7);
    ms1.push(2);

    // shows current minimum
    cout << "Min: " << ms1.getMin() << "\n";

    ms1.pop(); // popping 2
    cout << "Min after pop: " << ms1.getMin() << "\n";

    cout << "Top element: " << ms1.top() << "\n\n";

    cout << "Testing class minStack (encoded technique):\n";

    minStack ms2;
    ms2.push(5);
    ms2.push(3);
    ms2.push(7);
    ms2.push(2);

    cout << "Min: " << ms2.getMini() << "\n";

    ms2.pop();
    cout << "Min after pop: " << ms2.getMini() << "\n";

    cout << "Top element: " << ms2.top() << "\n";

    return 0;
}
