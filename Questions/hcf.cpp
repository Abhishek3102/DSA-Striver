#include <iostream>
#include <cmath>
#include <bits/stdc++.h>
using namespace std;

void get_hcf()
{
    int n1, n2, gcd = 1;
    cout << "Enter n1" << endl;
    cin >> n1;
    cout << "Enter n2" << endl;
    cin >> n2;

    // t.c. : O(min(n1,n2))
    for (int i = 1; i <= min(n1, n2); i++)
    {
        if (n1 % i == 0 && n2 % i == 0)
        {
            gcd = i;
            cout << gcd << endl; // this prints all common divisors
        }
    }
    cout << gcd << endl; // this gives the actual gcd/hcf.
}

// to reduce t.c. further, use euclidean algorithm which states that
// gcd(a,b) = gcd(a-b, b) where a > b
// but there can be catch in many case

// so use this maybe for better t.c.
// gcd(a,b) == gcd(a%b, b) where a > b go on doing this step, untill one of them becomes 0.
// when one number becomes 0, the other will be gcd

// So now, t.c. becomes O(logₓ(min(a,b))) where x = φ

int main()
{
    int t;
    cout << "Enter number of test cases : ";
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        // get_all_divisors();
        get_hcf();
    }
    return 0;
}