#include <iostream>
#include <cmath>
#include <bits/stdc++.h>
using namespace std;

void get_all_divisors()
{
    // this has t.c. O(N)

    int num;
    int count = 0;
    cout << "Enter num :";
    cin >> num;

    if (num <= 0)
    {
        cout << "Please provide positive integer only" << endl;
        return;
    }

    cout << "The divisors of " << num << " are : " << endl;

    for (int i = 1; i <= num; i++)
    {

        if (num % i == 0)
        {
            cout << i << " ";
            count += 1;
            cout << endl;
        }
    }
    cout << "The number of divisors of " << num << " are : " << count << endl;
}

void get_div()
{
    // reducing the t.c.
    int n;
    cin >> n;
    vector<int> ls;

    // for (int i = 1; i <= sqrt(n); i++) here since sqrt itself is a function and every time it gets called it will take some time of its own too, to execute
    for (int i = 1; i * i <= n; i++) // another way for using sqrt
    {
        if (n % i == 0)
        {
            ls.push_back(i);
            if ((n / i) != i)
            {
                ls.push_back(n / i);
            }
        }
    }
    sort(ls.begin(), ls.end());
    for (auto it : ls)
        cout << it << " ";
}

int main()
{
    int t;
    cout << "Enter number of test cases : ";
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        // get_all_divisors();
        get_div();
    }
    return 0;
}