#include <iostream>
#include <cmath>
#include <bits/stdc++.h>
using namespace std;

bool check_prime()
{
    int n;
    cin >> n;

    if (n <= 1)
        return false;

    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return false;
    }

    return true; // n is prime if no divisors were found
}

int main()
{
    int t;
    cout << "Enter number of test cases: ";
    cin >> t;

    for (int i = 0; i < t; i++)
    {
        if (check_prime())
            cout << "prime" << endl;
        else
            cout << "not prime" << endl;
    }

    return 0;
}