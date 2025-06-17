#include <iostream>
#include <string>

using namespace std;

void print11(int n)
{
    /*
    Solution :
    5
1
01
101
0101
10101

    */
    int start = 1;
    for (int i = 0; i < n; i++)
    {
        if (i % 2 == 0)
            start = 1;
        else
            start = 0;
        for (int j = 0; j <= i; j++)
        {
            cout << start;
            start = 1 - start;
        }
        cout << endl;
    }
}

void print12(int n)
{
    /*
    Solution:

4
1      1
12    21
123  321
12344321

    */
    int space = 2 * (n - 1);
    for (int i = 1; i <= n; i++)
    {
        // numbers
        for (int j = 1; j <= i; j++)
        {
            cout << j;
        }

        // space
        for (int j = 1; j <= space; j++)
        {
            cout << " ";
        }

        // numbers
        for (int j = i; j >= 1; j--)
        {
            cout << j;
        }
        cout << endl;
        space -= 2;
    }
}

void print13(int n)
{
    /*
    solution :
    5

    1
    2 3
    4 5 6
    7 8 9 10
    11 12 13 14 15

    */
    int num = 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= i; j++)
        {
            cout << num << " ";
            num = num + 1;
        }
        cout << endl;
    }
}

void print14(int n)
{
    /*
    solution :
    7
    A
    A B
    A B C
    A B C D
    A B C D E
    A B C D E F
    A B C D E F G
    */
    for (int i = 0; i < n; i++)
    {
        for (char ch = 'A'; ch <= 'A' + i; ch++)
        {
            cout << ch << " ";
        }
        cout << endl;
    }
}

void print15(int n)
{
    /*
    Solution :
    7
    A B C D E F G
    A B C D E F
    A B C D E
    A B C D
    A B C
    A B
    A

    */

    // Commented out code is his. gives same result.

    for (int i = n; i >= 1; i--)
    // for(int i=0; i<n; i++)
    {
        for (char ch = 'A'; ch < 'A' + i; ch++)
        // for(char ch = 'A'; ch <= 'A'+(n-i-1); ch++)
        {
            cout << ch << " ";
        }
        cout << endl;
    }
}

void print16(int n)
{
    /*
    Solution :
    4
A
B B
C C C
D D D D
    */
    for (int i = 0; i < n; i++)
    {
        char ch = 'A' + i;
        for (int j = 0; j <= i; j++)
        {
            cout << ch << " ";
        }
        cout << endl;
    }
}

void try1(int n)
{
    for (int i = 0; i <= n; i++)
    {
        for (int j = 1; j <= 2 * i + 1; j++)
        {
            cout << j << " ";
        }
        cout << endl;
    }
}

void print17(int n)
{
    /*
    Question :

    5
    *
   ***
  *****
 *******
*********

    */
    for (int i = 0; i < n; i++)
    {
        /*
        Solution :
        4
   A
  ABA
 ABCBA
ABCDCBA
        */
        char ch = 'A';
        // Increment till breakpoint and decrement henceforth
        int breakpoint = (2 * i + 1) / 2;
        // space
        for (int j = 0; j < n - i - 1; j++)
        {
            cout << " ";
        }
        // star
        // Condition changed
        // for (int j = 0; j < 2 * i + 1; j++)
        for (int j = 1; j <= 2 * i + 1; j++)
        {
            cout << ch;
            if (j <= breakpoint)
                ch++;
            else
                ch--;
        }
        // space
        for (int j = 0; j < n - i - 1; j++)
        {
            cout << " ";
        }
        cout << endl;
    }
}

void print18(int n)
{

    for (int i = 0; i <= n; i++)
    {
        // char ch = 'E' - i;
        // for (int j = i; j >= i; j--)
        for (char ch = 'E' - i; ch <= 'E'; ch++)
        {
            cout << ch << " ";
            // ch--;
        }
        cout << endl;
    }
}

int main()
{
    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        int n;
        cin >> n;
        print18(n);
    }
}